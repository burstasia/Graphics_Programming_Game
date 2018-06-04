#pragma once
#include "../OverlordEngine/Scenegraph/GameObject.h"

class Character;

enum State
{
	floating = 0,
	flyingTowardsPlayer = 1,
	falling = 2
};

class Pickup final : public GameObject
{
public:
	Pickup(XMFLOAT3 pos);
	virtual ~Pickup(void);

	void Initialize(const GameContext & gameContext);
	void Update(const GameContext & gameContext);

	void SetState(State state);
	void SetGoal(float x, float z);
	void SetCharacterRef(Character* character);

private:
	XMFLOAT3 m_Pos;

	bool m_AddForce;
	State m_State;
	float m_CurrFlyingTime;
	float m_TotalFlyingTime;
	bool m_HasBeenTriggered;

	float m_GoalX;
	float m_GoalZ;

	float m_Speed;

	Character *m_pCharacter;

	void AddForce(float elapsedSec);

};

