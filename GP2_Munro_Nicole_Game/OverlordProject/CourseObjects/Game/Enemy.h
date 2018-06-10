#pragma once
#include "Scenegraph/GameObject.h"

class Character;
class ControllerComponent;
class ModelComponent;

class Enemy final: public GameObject
{
public:

	enum EnemyState
	{
		WALKING,
		FOLLOWING,
		HURT,
		DYING
	};
	Enemy(XMFLOAT3 midPoint, float width, float height);
	~Enemy();

	virtual void Initialize(const GameContext & gameContext);
	virtual void Update(const GameContext & gameContext);
	void PostInit();

	const bool GetIsFollowing() const { return m_IsFollowing; }
	void SetIsFollowing(bool isFollowing);

	void SetState(EnemyState newState) 
	{ 
		m_CurrState = newState; 
	}

	void SetCharacterReference(Character* character) { m_pCharacter = character; }

	void SetIsAlive(bool alive) { m_IsAlive = alive; }
	void ResetEnemy();

	bool SetIsHit();

private:
	bool m_IsAlive;

	float m_Speed;
	float m_GoalX;
	float m_GoalZ;
	XMFLOAT3 m_Goal;
	bool m_IsFollowing;
	bool m_GoalSet;

	float m_TotalFollowTime;
	float m_CurrFollowTime;

	XMFLOAT3 m_Midpoint;
	float m_Width;
	float m_Height;

	float m_MaxX;
	float m_MinX;
	float m_MaxZ;
	float m_MinZ;

	int m_Lives;

	ControllerComponent* m_pController;

	Character* m_pCharacter = nullptr;

	XMFLOAT3 m_Velocity;

	GameObject* m_pEnemyModel;

	ModelComponent * m_pModel;

	EnemyState m_LastState;
	EnemyState m_CurrState;

	float m_HurtTimer;
	float m_CurrHurtTimer;

	float m_DyingTimer;
	float m_CurrDyingTimer;

	void EnemyMovement(float elapsedSec);
	void FollowPlayerMovement(float elapsedSec);
	float GetDistance(const XMFLOAT3& v1, const XMFLOAT3& v2);
	void Move(float elapsedSec);
	void GetMinMax();

	static void FireballTrigger(GameObject* triggerobject, GameObject* otherobject, TriggerAction action);
};

