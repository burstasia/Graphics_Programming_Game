#include "stdafx.h"
#include "Pickup.h"

#include "Components/Components.h"
#include "Physx/PhysxManager.h"
#include "Scenegraph/GameObject.h"
#include "Physx\PhysxProxy.h"

#include "../OverlordProject/Materials/ColorMaterial.h"
#include "Content/ContentManager.h"
#include "../Week2/Character.h"

#include "Scenegraph/GameScene.h"


Pickup::Pickup(XMFLOAT3 pos):
	m_Pos(pos),
	m_AddForce(false),
	m_State(State::floating),
	m_CurrFlyingTime(0.0f),
	m_TotalFlyingTime(2.0f),
	m_HasBeenTriggered(false),
	m_Speed(5.0f)
{
}


Pickup::~Pickup()
{
}

void Pickup::Initialize(const GameContext & gameContext)
{

	auto physX = PhysxManager::GetInstance()->GetPhysics();
	auto bouncyMaterial = physX->createMaterial(0.5, 0.5, 1.0f);

	auto diamondModel = new ModelComponent(L"Resources/Meshes/diamond.ovm");

	AddComponent(diamondModel);

	auto rigidBody = new RigidBodyComponent();

	AddComponent(rigidBody);

	diamondModel->SetMaterial(0);

	std::shared_ptr<PxGeometry> geometry(new PxBoxGeometry(5.0f, 1.0f, 5.0f));

	ColliderComponent *collider = new ColliderComponent(geometry, *bouncyMaterial);

	collider->EnableTrigger(true);

	AddComponent(collider);

	GetTransform()->Translate(20.0f, 5.0f, 0.0f);

}

void Pickup::Update(const GameContext & gameContext)
{
	if(m_State == State::floating) GetTransform()->Translate(m_Pos);

	else if (m_State == State::flyingTowardsPlayer)
	{
		
		m_CurrFlyingTime += gameContext.pGameTime->GetElapsed();
		
		if (m_CurrFlyingTime < m_TotalFlyingTime)
		{
			AddForce(gameContext.pGameTime->GetElapsed());
		}
		else
		{
			SetIsActive(false);
			m_CurrFlyingTime = 0.0f;
		}
	}
}

void Pickup::SetState(State state)
{
	if (!m_HasBeenTriggered)
	{
		m_State = state;
		m_HasBeenTriggered = true;
	}
}

void Pickup::SetGoal(float x, float z)
{
	m_GoalX = (x - GetTransform()->GetPosition().x) * 2.0f;
	m_GoalZ = (z - GetTransform()->GetPosition().z) * 2.0f;
}

void Pickup::SetCharacterRef(Character * character)
{
	m_pCharacter = character;
}


void Pickup::AddForce(float elapsedSec)
{
	//goal - pos
	//clamp
	//max - min / max
	//* speed
	//elapsedSec

	//add world offset

	auto goal = m_pCharacter->GetTransform()->GetPosition();
	auto currPos = GetTransform()->GetPosition();

	XMVECTOR tempGoal = XMLoadFloat3(&goal);
	XMVECTOR tempCurrPos = XMLoadFloat3(&currPos);

	auto tempVec = XMVectorSubtract(tempGoal, tempCurrPos);

	XMFLOAT3 vec{};

	XMStoreFloat3(&vec, tempVec);

	vec.x *= m_Speed;
	vec.y *= m_Speed;
	vec.z *= m_Speed;

	vec.x *= elapsedSec;
	vec.y *= elapsedSec;
	vec.z *= elapsedSec;

	XMFLOAT3 pos = GetTransform()->GetPosition();

	GetTransform()->Translate(pos.x + vec.x, pos.y + vec.y , pos.z + vec.z);

	//GetComponent<RigidBodyComponent>()->AddForce(PxVec3(m_GoalX, 40.5f, m_GoalZ), PxForceMode::eVELOCITY_CHANGE, true);
}
