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
#include "Graphics\ModelAnimator.h"

#include "Materials/DiffuseMaterial.h"
#include "EnemyCollision.h"
#include "EnemyCollisionPlayer.h"
#include "Fireball.h"
#include "Platformer.h"
#include "Level.h"
#include "MainCharacter.h"


Enemy::Enemy(XMFLOAT3 midPoint, float width, float height) :
	m_IsAlive(true),
	m_Speed(0.25f),
	m_GoalX(0.0f),
	m_GoalZ(0.0f),
	m_Goal(0.0f, 0.0f, 0.0f),
	m_IsFollowing(false),
	m_GoalSet(false),
	m_TotalFollowTime(2.0f),
	m_CurrFollowTime(0.0f),
	m_Midpoint(midPoint),
	m_Width(width),
	m_Height(height),
	m_Velocity(0.0f, 0.0f, 0.0f),
	m_Lives(3),
	m_LastState(EnemyState::WALKING),
	m_CurrState(EnemyState::WALKING),
	m_HurtTimer(1.0f),
	m_CurrHurtTimer(0.0f),
	m_DyingTimer(2.5f),
	m_CurrDyingTimer(0.0f)
{
}


Enemy::~Enemy()
{
}

void Enemy::Initialize(const GameContext & gameContext)
{
	
	//TO DO CHANGE 4 POINTS INIT TO
	//1 POINT AND WIDTH + DEPTH

	auto physX = PhysxManager::GetInstance()->GetPhysics();
	auto bouncyMaterial = physX->createMaterial(0.5, 0.5, 1.0f);

	//MODEL//
	m_pEnemyModel = new GameObject();

	m_pModel = new ModelComponent(L"Resources/Meshes/packed_toad.ovm");

	m_pEnemyModel->AddComponent(m_pModel);

	AddChild(m_pEnemyModel);

	m_pModel->GetTransform()->Scale(0.2f, 0.2f, 0.2f);


	m_pModel->SetMaterial(1);

	//FIREBALL COLLISION//
	auto enemyCollision = new EnemyCollision();
	enemyCollision->SetOnTriggerCallBack(FireballTrigger);
	AddChild(enemyCollision);

	//CONTROLLER//
	m_pController = new ControllerComponent(bouncyMaterial);
	AddComponent(m_pController);

	//WALKABLE AREA//
	GetMinMax();

	GetTransform()->Translate(m_Midpoint.x, m_Midpoint.y + 20.0f, m_Midpoint.z);

	
}

void Enemy::Update(const GameContext & gameContext)
{
	m_LastState = m_CurrState;

	if (m_IsAlive)
	{
		m_pEnemyModel->GetComponent<ModelComponent>()->GetAnimator()->Play();

		if (m_CurrState == EnemyState::WALKING)EnemyMovement(gameContext.pGameTime->GetElapsed());
		if(m_CurrState == EnemyState::FOLLOWING)FollowPlayerMovement(gameContext.pGameTime->GetElapsed());
		if (m_CurrState == EnemyState::DYING)
		{
			m_CurrDyingTimer += gameContext.pGameTime->GetElapsed();
			if (m_CurrDyingTimer >= m_DyingTimer)
			{
				m_CurrDyingTimer = 0.0f;
				m_IsAlive = false;
			}
		}
		if (m_CurrState == EnemyState::HURT)
		{
			m_CurrHurtTimer += gameContext.pGameTime->GetElapsed();
			if (m_CurrHurtTimer >= m_HurtTimer)
			{
				m_CurrHurtTimer = 0.0f;
				m_CurrState = EnemyState::WALKING;
			}
		}

		if (m_CurrState != m_LastState)
		{
			switch (m_CurrState)
			{	
			case 0:
				m_pEnemyModel->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(0);
				break;

			case 1:
				m_pEnemyModel->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(1);
				break;

			case 2:
				m_pEnemyModel->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(2);
				break;

			case 3:
				m_pEnemyModel->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(3);
				break;
			}
		}
		//Rotate with velocity
		float angle = (atan2(m_Velocity.x, m_Velocity.z) * 180 / XM_PI) + 180.f;
		GetTransform()->Rotate(0.0f, angle, 0.0f);

		//Rotate and translate child
		m_pEnemyModel->GetTransform()->Translate(GetParent()->GetTransform()->GetPosition().x, GetParent()->GetTransform()->GetPosition().y - 5.0f, GetParent()->GetTransform()->GetPosition().z);
		m_pEnemyModel->GetTransform()->Rotate(GetParent()->GetTransform()->GetRotation().x, GetParent()->GetTransform()->GetRotation().y, GetParent()->GetTransform()->GetRotation().z);


	}
	else
	{
		GetTransform()->Translate(0.0f, -100.0f, 0.0f);
	}
}

void Enemy::PostInit()
{
	//level
	auto scene = dynamic_cast<Platformer*>(GetScene());
	auto level = dynamic_cast<Level*>(scene->GetLevel());

	//CHARACTER COLLISION//
	auto enemyCollision = new EnemyCollisionPlayer();
	enemyCollision->SetOnTriggerCallBack(level->EnemyTrigger);
	AddChild(enemyCollision);

	m_pEnemyModel->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(0);
}

void Enemy::SetIsFollowing(bool isFollowing)
{
	
	m_IsFollowing = isFollowing;

	if (isFollowing)
	{
		m_CurrState = EnemyState::FOLLOWING;
		m_pEnemyModel->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(1);
	}
	else
	{
		m_CurrState = EnemyState::WALKING;
		m_pEnemyModel->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(0);
	}
}

void Enemy::ResetEnemy()
{
	m_CurrState = EnemyState::WALKING;
	m_LastState = EnemyState::WALKING;
	m_pEnemyModel->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(0);
	m_IsAlive = true;
	m_Lives = 3;
	m_Speed = 0.5f;
	GetTransform()->Translate(0.0f, 0.0f, 0.0f);
}

bool Enemy::SetIsHit()
{
	auto scene = dynamic_cast<Platformer*>(GetScene());
	

	if (scene)
	{
		auto level = dynamic_cast<Level*>(scene->GetLevel());

		level->AddPoints();
	}

	--m_Lives;

	m_CurrState = EnemyState::HURT;
	m_pEnemyModel->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(2);
	if (m_Lives <= 0)
	{
		m_pEnemyModel->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(3);
		m_CurrState = EnemyState::DYING;
		return true;
	}
	else return false;
}

void Enemy::EnemyMovement(float elapsedSec)
{
	if (!m_GoalSet)
	{
		m_GoalX = rand() % (int)(m_MaxX + ( -1.0f * m_MinX)) + (m_MinX);
		m_GoalZ = rand() % (int)(m_MaxZ + (-1.0f * m_MinZ)) + (m_MinZ);
		m_Goal = XMFLOAT3(m_GoalX, GetTransform()->GetPosition().y, m_GoalZ);
		m_GoalSet = true;
	}
	if (GetDistance(m_pController->GetTransform()->GetPosition(), m_Goal) <= 20.0f)
	{
		m_GoalSet = false;
	}
	else Move(elapsedSec);

}

void Enemy::FollowPlayerMovement(float elapsedSec)
{
	m_Speed = 0.5f;

	if (m_pCharacter != nullptr)
	{
		m_Goal = m_pCharacter->GetTransform()->GetPosition();
	}

	//Enemy will follow player for a certain amount of time or until he catches the player
	m_CurrFollowTime += elapsedSec;

	if (m_CurrFollowTime >= m_TotalFollowTime)
	{
		SetIsFollowing(false);
		m_CurrFollowTime = 0.0f;
		m_Speed = 0.1f;
	}
	if (GetDistance(m_pController->GetTransform()->GetPosition(), m_Goal) <= 5.0f)
	{
		//Attack I guess
		SetIsFollowing(false);
		m_CurrFollowTime = 0.0f;
		m_Speed = 0.1f;
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

	m_Goal.y = -10.0f;

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

	m_pController->Move(vec);
	m_Velocity = vec;
}

void Enemy::GetMinMax()
{
	float widthDiv2 = m_Width / 2.0f; //x
	float heightDiv2 = m_Height / 2.0f; //z

	m_MaxX = m_Midpoint.x + widthDiv2;
	m_MinX = m_Midpoint.x - widthDiv2;

	m_MaxZ = m_Midpoint.z + heightDiv2;
	m_MinZ = m_Midpoint.z - heightDiv2;

}

void Enemy::FireballTrigger(GameObject * triggerobject, GameObject * otherobject, TriggerAction action)
{
	auto fireball = dynamic_cast<Fireball*>(otherobject);
	auto enemy = dynamic_cast<EnemyCollision*>(triggerobject);

	if (enemy && fireball != nullptr)
	{
		enemy->Kill();
		fireball->SetIsAlive(false);
		return;
	}


}
