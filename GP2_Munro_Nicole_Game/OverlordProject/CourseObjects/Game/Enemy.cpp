#include "stdafx.h"
#include "Enemy.h"

#include "Components/Components.h"
#include "Physx/PhysxManager.h"
#include "Scenegraph/GameObject.h"
#include "Physx\PhysxProxy.h"

#include "../OverlordProject/Materials/ColorMaterial.h"
#include "Content/ContentManager.h"
#include "../Week2/Character.h"

#include "Scenegraph/GameScene.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Initialize(const GameContext & gameContext)
{
	auto physX = PhysxManager::GetInstance()->GetPhysics();
	auto bouncyMaterial = physX->createMaterial(0.5, 0.5, 1.0f);

	auto rigidBody = new RigidBodyComponent();

	AddComponent(rigidBody);

	rigidBody->SetKinematic(true);

	std::shared_ptr<PxGeometry> geometry(new PxBoxGeometry(5.0f, 1.0f, 5.0f));

	ColliderComponent *collider = new ColliderComponent(geometry, *bouncyMaterial);

	collider->EnableTrigger(true);

	AddComponent(collider);
}

void Enemy::Update(const GameContext & gameContext)
{
	EnemyMovement(gameContext.pGameTime->GetElapsed());

}

void Enemy::EnemyMovement(float elapsedSec)
{

}

void Enemy::FollowPlayerMovement(float elapsedSec)
{
}
