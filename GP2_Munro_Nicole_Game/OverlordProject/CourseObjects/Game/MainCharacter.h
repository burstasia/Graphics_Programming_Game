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
		stunned
	};

	MainCharacter(Character * chara);
	~MainCharacter();

	void Initialize(const GameContext & gameContext);
	void Update(const GameContext & gameContext);

	void PostInit();
private:

	Character * m_pCharacter;
	
	State m_State;
};

