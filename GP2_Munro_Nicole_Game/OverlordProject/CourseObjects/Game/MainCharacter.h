#pragma once
#include "Scenegraph/GameObject.h"

class Character;
class ModelComponent;

class MainCharacter final : public GameObject
{
public:

	enum State
	{
		idle,
		flying,
		stunned,
		fireball
	};

	MainCharacter(Character * chara);
	~MainCharacter();

	void Initialize(const GameContext & gameContext);
	void Update(const GameContext & gameContext);

	void PostInit();
private:

	Character * m_pCharacter;
	
	State m_State;
	State m_StateLastFrame;

	bool m_CanShootFireball;
	float m_CooldownTotal;
	float m_CooldownCurr;

	GameObject * m_pModelObject;
};

