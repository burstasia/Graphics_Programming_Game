#include "stdafx.h"
#include "Fireball.h"

#include "Components/Components.h"
#include "Physx/PhysxManager.h"
#include "Level.h"

Fireball::Fireball(XMFLOAT3 startPos, XMFLOAT3 forwardVec, Level* pLevel):
	m_StartPos(startPos),
	m_ForwardVec(forwardVec),
	m_Speed(10.0f),
	m_TimeAlive(0.0f),
	m_TotalTimeAlive(2.0f),
	m_IsAlive(true),
	m_pLevel(pLevel)
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


	std::shared_ptr<PxGeometry> geometry(new PxBoxGeometry(1.0f, 1.0f, 1.0f));

	ColliderComponent *collider = new ColliderComponent(geometry, *bouncyMaterial);

	collider->EnableTrigger(true);

	AddComponent(collider);

	GetTransform()->Translate(m_StartPos.x, m_StartPos.y + 5.0f, m_StartPos.z);
}

void Fireball::Update(const GameContext & gameContext)
{
	if (m_IsAlive)
	{
		XMFLOAT3 pos{};
		pos.x = (m_ForwardVec.x + GetTransform()->GetPosition().x);// *gameContext.pGameTime->GetElapsed() * m_Speed;
		pos.y = (m_ForwardVec.y + GetTransform()->GetPosition().y);// *gameContext.pGameTime->GetElapsed()* m_Speed;
		pos.z = (m_ForwardVec.z + GetTransform()->GetPosition().z);// *gameContext.pGameTime->GetElapsed()* m_Speed;

		m_TimeAlive += gameContext.pGameTime->GetElapsed();

		if (m_TimeAlive >= m_TotalTimeAlive) m_pLevel->RemoveChildRuntime(this);
		else GetTransform()->Translate(pos);
	}
	else m_pLevel->RemoveChildRuntime(this);
}
