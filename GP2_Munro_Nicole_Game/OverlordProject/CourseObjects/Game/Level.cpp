#include "stdafx.h"
#include "Level.h"

#include "Components/Components.h"
#include "Physx/PhysxManager.h"
#include "../OverlordEngine/Scenegraph/GameObject.h"
#include "Physx\PhysxProxy.h"

#include "../OverlordProject/Materials/ColorMaterial.h"
#include "Content/ContentManager.h"

#include "../Week2/Character.h"
#include "Pickup.h"

Level::Level()
{
}

Level::~Level()
{
	GameObject::~GameObject();
}

void Level::Initialize(const GameContext & gameContext)
{
	auto pColorMaterial = new ColorMaterial();
	pColorMaterial->SetColor(XMFLOAT4(0.0f, 0.5f, 0.5f, 1.0f));

	gameContext.pMaterialManager->AddMaterial(pColorMaterial, UINT(0));
	UNREFERENCED_PARAMETER(gameContext);

	InitLevel(gameContext);
	InitItems(gameContext);
}

void Level::Update(const GameContext & gameContext)
{

}

void Level::InitLevel(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	auto physX = PhysxManager::GetInstance()->GetPhysics();
	auto bouncyMaterial = physX->createMaterial(0.5, 0.5, 1.0f);

	AddComponent(new RigidBodyComponent(true));

	auto geom(ContentManager::Load<PxTriangleMesh>(L"Resources/Meshes/floor.ovpt"));

	std::shared_ptr<PxGeometry> geometry(new PxTriangleMeshGeometry(geom));

	AddComponent(new ColliderComponent(geometry, *bouncyMaterial));


	auto pGroundModel = new ModelComponent(L"Resources/Meshes/floor.ovm");

	AddComponent(pGroundModel);

	pGroundModel->SetMaterial(0);
}

void Level::InitItems(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	for (size_t i = 0; i < 10; i++)
	{
		float randX = rand() % 100 + (-50);
		float randY = rand() % 5 + 2;
		float randZ = rand() % 100 + (-50);

		auto pickUp = new Pickup(XMFLOAT3(randX, randY, randZ));

		m_VectorPickups.push_back(pickUp);
		m_VectorPickups.at(i)->SetOnTriggerCallBack(test);
		AddChild(m_VectorPickups.at(i));
	}
}

void Level::test(GameObject * triggerobject, GameObject * otherobject, TriggerAction action)
{
	UNREFERENCED_PARAMETER(triggerobject);
	UNREFERENCED_PARAMETER(otherobject);
	UNREFERENCED_PARAMETER(action);

	auto chara = dynamic_cast<Character*>(otherobject);
	
	auto trigger = static_cast<Pickup*>(triggerobject);

	if (chara && trigger)
	{
		trigger->SetState(State::flyingTowardsPlayer);
		trigger->SetCharacterRef(chara);
	}
	
}
