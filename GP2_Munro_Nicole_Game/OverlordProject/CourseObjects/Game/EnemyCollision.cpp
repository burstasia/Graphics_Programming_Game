#include "stdafx.h"
#include "EnemyCollision.h"

#include "Components/Components.h"
#include "Physx/PhysxManager.h"
#include "Scenegraph/GameObject.h"


EnemyCollision::EnemyCollision()
{
}


EnemyCollision::~EnemyCollision()
{
}

void EnemyCollision::Initialize(const GameContext & gameContext)
{
	auto physX = PhysxManager::GetInstance()->GetPhysics();
	auto bouncyMaterial = physX->createMaterial(0.5, 0.5, 1.0f);

	auto rigidBody = new RigidBodyComponent();

	AddComponent(rigidBody);

	rigidBody->SetKinematic(true);

	std::shared_ptr<PxGeometry> geometry(new PxBoxGeometry(6.0f, 4.0f, 2.0f));

	ColliderComponent *collider = new ColliderComponent(geometry, *bouncyMaterial);

	collider->EnableTrigger(true);

	AddComponent(collider);
}

void EnemyCollision::Update(const GameContext & gameContext)
{
	GetTransform()->Translate(GetParent()->GetTransform()->GetPosition());
}
