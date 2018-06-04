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
	m_TotalFlyingTime(0.5f),
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


}

void Pickup::Update(const GameContext & gameContext)
{
	
	if(m_State == State::floating) GetTransform()->Translate(m_Pos);

	//pickup flies towards you for a certain amount of time then after that time it
	//disappears
	else if (m_State == State::flyingTowardsPlayer)
	{
		
		m_CurrFlyingTime += gameContext.pGameTime->GetElapsed();
		AddForce(gameContext.pGameTime->GetElapsed());

		if (m_CurrFlyingTime > m_TotalFlyingTime)
		{
			if (AddForce(gameContext.pGameTime->GetElapsed()))
			{
				SetIsActive(false);
				m_CurrFlyingTime = 0.0f;
			}
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


bool Pickup::AddForce(float elapsedSec)
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

	if (GetDistance(vec, pos) <= 30.0f)
	{
		return true;
	}
	else return false;
	//GetComponent<RigidBodyComponent>()->AddForce(PxVec3(m_GoalX, 40.5f, m_GoalZ), PxForceMode::eVELOCITY_CHANGE, true);
}

float Pickup::GetDistance(const XMFLOAT3& v1, const XMFLOAT3& v2)
{
	XMVECTOR vector1 = XMLoadFloat3(&v1);
	XMVECTOR vector2 = XMLoadFloat3(&v2);
	XMVECTOR vectorSub = XMVectorSubtract(vector1, vector2);
	XMVECTOR length = XMVector3Length(vectorSub);

	float distance = 0.0f;
	XMStoreFloat(&distance, length);
	return distance;
}
