#pragma once
#include "Scenegraph/GameObject.h"

class Enemy final: public GameObject
{
public:
	Enemy();
	~Enemy();

	void Initialize(const GameContext & gameContext);
	void Update(const GameContext & gameContext);

	const bool GetIsFollowing() const { return m_IsFollowing; }
	void SetIsFollowing(bool isFollowing) { m_IsFollowing = isFollowing; }


private:
	float m_Speed;
	bool m_IsFollowing;

	void EnemyMovement(float elapsedSec);
	void FollowPlayerMovement(float elapsedSec);
};

