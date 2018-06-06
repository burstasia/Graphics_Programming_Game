#include "stdafx.h"
#include "Fireball.h"

#include "Components/Components.h"
#include "Physx/PhysxManager.h"

Fireball::Fireball(XMFLOAT3 startPos, XMFLOAT3 forwardVec):
	m_StartPos(startPos),
	m_ForwardVec(forwardVec),
	m_Speed(10.0f),
	m_TimeAlive(0.0f),
	m_TotalTimeAlive(2.0f),
	m_IsAlive(true)
{
}


Fireball::~Fireball()
{
}

void Fireball::Initialize(const GameContext & gameContext)
{
	auto physX = PhysxManager::GetInstance()->GetPhysics();
	auto bouncyMaterial = physX->createMaterial(0.5, 0.5, 1.0f);

	auto rigidBody = new RigidBodyComponent();

	AddComponent(rigidBody);


	std::shared_ptr<PxGeometry> geometry(new PxBoxGeometry(5.0f, 1.0f, 5.0f));

	ColliderComponent *collider = new ColliderComponent(geometry, *bouncyMaterial);

	collider->EnableTrigger(true);

	AddComponent(collider);

	GetTransform()->Translate(m_StartPos);
}

void Fireball::Update(const GameContext & gameContext)
{
	GetTransform()->Translate(m_ForwardVec.x + GetTransform()->GetPosition().x, m_ForwardVec.y + GetTransform()->GetPosition().y, m_ForwardVec.z + GetTransform()->GetPosition().z);
}
