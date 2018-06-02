#include "stdafx.h"
#include "Level.h"

#include "Components/Components.h"
#include "Physx/PhysxManager.h"
#include "../OverlordEngine/Scenegraph/GameObject.h"
#include "Physx\PhysxProxy.h"

#include "../OverlordProject/Materials/ColorMaterial.h"
#include "Content/ContentManager.h"

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

	//InitLevel(gameContext);
	InitItems(gameContext);
}

void Level::InitLevel(const GameContext & gameContext)
{
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
	auto physX = PhysxManager::GetInstance()->GetPhysics();
	auto bouncyMaterial = physX->createMaterial(0.5, 0.5, 1.0f);

	GameObject *diamond = new GameObject();

	auto diamondModel = new ModelComponent(L"Resources/Meshes/diamond.ovm");

	diamond->AddComponent(diamondModel);

	diamond->AddComponent(new RigidBodyComponent(true));

	diamondModel->SetMaterial(0);

	diamond->SetOnTriggerCallBack(test);

	std::shared_ptr<PxGeometry> geometry(new PxBoxGeometry(1.0f, 1.0f, 1.0f));

	ColliderComponent *collider = new ColliderComponent(geometry, *bouncyMaterial);

	collider->EnableTrigger(true);

	diamond->AddComponent(collider);

	AddChild(diamond);
}

void Level::test(GameObject * triggerobject, GameObject * otherobject, TriggerAction action)
{

	Logger::LogInfo(L"EYO YOU HIT A DIAMOND NEATO WOW");

}
