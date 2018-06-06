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

#include "Materials/DiffuseMaterial.h"
#include "EnemyCollision.h"
#include "Fireball.h"

Enemy::Enemy(XMFLOAT3 p1, XMFLOAT3 p2, XMFLOAT3 p3, XMFLOAT3 p4):
	m_Speed(0.5f),
	m_GoalX(0.0f),
	m_GoalZ(0.0f),
	m_Goal(0.0f,0.0f,0.0f),
	m_IsFollowing(false),
	m_GoalSet(false),
	m_TotalFollowTime(2.0f),
	m_CurrFollowTime(0.0f),
	m_P1(p1),
	m_P2(p2),
	m_P3(p3),
	m_P4(p4)
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

	std::shared_ptr<PxGeometry> geometry(new PxBoxGeometry(6.0f,4.0f,6.0f));

	ColliderComponent *collider = new ColliderComponent(geometry, *bouncyMaterial, PxTransform(PxVec3(0.0f,5.0f,-4.0f)));

	collider->EnableTrigger(true);

	AddComponent(collider);


	auto enemyModel = new ModelComponent(L"Resources/Meshes/Knight.ovm");

	AddComponent(enemyModel);

	auto pDiffuseMaterial = new DiffuseMaterial();
	pDiffuseMaterial->SetDiffuseTexture(L"Resources/Textures/Knight.jpg");
	gameContext.pMaterialManager->AddMaterial(pDiffuseMaterial, UINT(1));
	
	enemyModel->SetMaterial(1);

	enemyModel->GetTransform()->Scale(0.03f, 0.03f, 0.03f);

	//getting max and min values
	std::vector<XMFLOAT3> tempVec{};
	tempVec.push_back(m_P1);
	tempVec.push_back(m_P2);
	tempVec.push_back(m_P3);
	tempVec.push_back(m_P4);

	m_MaxX = 0;
	m_MinX = tempVec.at(0).x;
	m_MaxZ = 0;
	m_MinZ = tempVec.at(0).z;

	for (size_t i = 0; i < tempVec.size(); i++)
	{
		//min and max x
		if (tempVec.at(i).x < m_MinX) m_MinX = tempVec.at(i).x;
		else if(tempVec.at(i).x > m_MaxX) m_MaxX = tempVec.at(i).x;

		//min and max z
		if (tempVec.at(i).z < m_MinZ) m_MinZ = tempVec.at(i).z;
		else if(tempVec.at(i).z > m_MaxZ) m_MaxZ = tempVec.at(i).z;
	}

	auto enemyCollision = new EnemyCollision();
	enemyCollision->SetOnTriggerCallBack(FireballTrigger);
	AddChild(enemyCollision);
}

void Enemy::Update(const GameContext & gameContext)
{
	if(!m_IsFollowing)EnemyMovement(gameContext.pGameTime->GetElapsed());
	else FollowPlayerMovement(gameContext.pGameTime->GetElapsed());

	

	//float angle = (atan2(velocity.x, velocity.z) * 180 / XM_PI) + 180.f;
}

void Enemy::EnemyMovement(float elapsedSec)
{
	if (!m_GoalSet)
	{
		m_GoalX = rand() % (int)(m_MaxX + ( -1.0f * m_MinX)) + (m_MinX);
		m_GoalZ = rand() % (int)(m_MaxZ + (-1.0f * m_MinZ)) + (m_MinZ);
		m_Goal = XMFLOAT3(m_GoalX, GetTransform()->GetPosition().y, m_GoalZ);
		m_GoalSet = true;

		//set angle
		XMFLOAT2 forward{ GetTransform()->GetForward().x, GetTransform()->GetForward().z };
		XMFLOAT2 goal{ m_Goal.x, m_Goal.z };

		XMVECTOR forwardVec = XMLoadFloat2(&forward);
		forwardVec = XMVector3Normalize(forwardVec);

		XMVECTOR goalVec = XMLoadFloat2(&goal);
		goalVec = XMVector3Normalize(goalVec);

		XMVECTOR angleVec = XMVector2Dot(forwardVec, goalVec);

		float angle{};

		XMStoreFloat(&angle, angleVec);

		angle = XMConvertToDegrees(angle);

		GetTransform()->Rotate(0.0f, 90.0f + angle, 0.0f);

	}
	if (GetDistance(GetTransform()->GetPosition(), m_Goal) <= 5.0f)
	{
		m_GoalSet = false;
	}
	else Move(elapsedSec);

}

void Enemy::FollowPlayerMovement(float elapsedSec)
{
	m_Speed = 1.0f;

	if (m_pCharacter)
	{
		m_Goal = m_pCharacter->GetTransform()->GetPosition();
	}

	//Enemy will follow player for a certain amount of time or until he catches the player
	m_CurrFollowTime += elapsedSec;

	if (m_CurrFollowTime >= m_TotalFollowTime)
	{
		m_IsFollowing = false;
		m_CurrFollowTime = 0.0f;
		m_Speed = 0.5f;
	}
	if (GetDistance(GetTransform()->GetPosition(), m_Goal) <= 5.0f)
	{
		//Attack I guess
		m_IsFollowing = false;
		m_CurrFollowTime = 0.0f;
		m_Speed = 0.5f;
	}
	else Move(elapsedSec);

}

float Enemy::GetDistance(const XMFLOAT3& v1, const XMFLOAT3& v2)
{
	XMVECTOR vector1 = XMLoadFloat3(&v1);
	XMVECTOR vector2 = XMLoadFloat3(&v2);
	XMVECTOR vectorSub = XMVectorSubtract(vector1, vector2);
	XMVECTOR length = XMVector3Length(vectorSub);

	float distance = 0.0f;
	XMStoreFloat(&distance, length);
	return distance;
}

void Enemy::Move(float elapsedSec)
{
	auto currPos = GetTransform()->GetPosition();

	XMVECTOR tempGoal = XMLoadFloat3(&m_Goal);
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

	GetTransform()->Translate(pos.x + vec.x, pos.y + vec.y, pos.z + vec.z);
}

void Enemy::FireballTrigger(GameObject * triggerobject, GameObject * otherobject, TriggerAction action)
{
	auto fireball = static_cast<Fireball*>(otherobject);
	auto enemy = dynamic_cast<EnemyCollision*>(triggerobject);

	if (enemy && fireball)
	{
		fireball->SetIsAlive(false);
	}
}
