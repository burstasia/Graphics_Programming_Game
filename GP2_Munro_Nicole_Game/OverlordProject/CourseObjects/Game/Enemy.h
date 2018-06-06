#pragma once
#include "Scenegraph/GameObject.h"

class Character;

class Enemy final: public GameObject
{
public:
	Enemy(XMFLOAT3 p1, XMFLOAT3 p2, XMFLOAT3 p3, XMFLOAT3 p4);
	~Enemy();

	void Initialize(const GameContext & gameContext);
	void Update(const GameContext & gameContext);

	const bool GetIsFollowing() const { return m_IsFollowing; }
	void SetIsFollowing(bool isFollowing) { m_IsFollowing = isFollowing; }

	void SetCharacterReference(Character* character) { m_pCharacter = character; }

private:
	float m_Speed;
	float m_GoalX;
	float m_GoalZ;
	XMFLOAT3 m_Goal;
	bool m_IsFollowing;
	bool m_GoalSet;

	float m_TotalFollowTime;
	float m_CurrFollowTime;

	XMFLOAT3 m_P1;
	XMFLOAT3 m_P2;
	XMFLOAT3 m_P3;
	XMFLOAT3 m_P4;

	float m_MaxX;
	float m_MinX;
	float m_MaxZ;
	float m_MinZ;


	Character* m_pCharacter;
	void EnemyMovement(float elapsedSec);
	void FollowPlayerMovement(float elapsedSec);
	float GetDistance(const XMFLOAT3& v1, const XMFLOAT3& v2);
	void Move(float elapsedSec);

	static void FireballTrigger(GameObject* triggerobject, GameObject* otherobject, TriggerAction action);
};

