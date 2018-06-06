#include "stdafx.h"
#include "Level.h"

#include "Components/Components.h"
#include "Physx/PhysxManager.h"
#include "Scenegraph/GameObject.h"
#include "Physx\PhysxProxy.h"

#include "Materials/ColorMaterial.h"
#include "Content/ContentManager.h"

#include "../Week2/Character.h"
#include "Pickup.h"
#include "Enemy.h"
#include "Fireball.h"

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

void Level::SpawnFireball(XMFLOAT3 startPos, XMFLOAT3 forwardVec)
{
	auto fireball = new Fireball(startPos, forwardVec, this);
	AddChildRuntime(fireball);
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

	//Cylinder
	geom = (ContentManager::Load<PxTriangleMesh>(L"Resources/Meshes/cylinder.ovpt"));

	geometry = std::make_shared<PxTriangleMeshGeometry>(geom);

	AddComponent(new ColliderComponent(geometry, *bouncyMaterial));

	auto pCylinderModel = new ModelComponent(L"Resources/Meshes/cylinder.ovm");

	AddComponent(pCylinderModel);
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
		m_VectorPickups.at(i)->SetOnTriggerCallBack(ItemTrigger);
		AddChild(m_VectorPickups.at(i));
	}

	m_pEnemy = new Enemy({50.0f, 0.0f, 50.0f}, {-50.0f,0.0f,50.0f}, {-50.0f,0.0f,-50.0f}, { 50.0f,0.0f,-50.0f });
	m_pEnemy->SetOnTriggerCallBack(EnemyTrigger);
	AddChild(m_pEnemy);


}

void Level::ItemTrigger(GameObject * triggerobject, GameObject * otherobject, TriggerAction action)
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

void Level::EnemyTrigger(GameObject * triggerobject, GameObject * otherobject, TriggerAction action)
{
	auto chara = dynamic_cast<Character*>(otherobject);

	auto enemy = static_cast<Enemy*>(triggerobject);

	if (chara && enemy)
	{
		enemy->SetIsFollowing(true);
		enemy->SetCharacterReference(chara);
	}

}

void Level::FireballTrigger(GameObject * triggerobject, GameObject * otherobject, TriggerAction action)
{
	auto fireball = static_cast<Fireball*>(otherobject);
	auto enemy = dynamic_cast<Enemy*>(triggerobject);

	if (enemy && fireball)
	{
		fireball->SetIsAlive(false);
	}

}

