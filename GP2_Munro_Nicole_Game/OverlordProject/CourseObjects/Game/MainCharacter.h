#pragma once
#include "Scenegraph/GameObject.h"

class Character;

class MainCharacter final : public GameObject
{
public:
	MainCharacter(Character * chara);
	~MainCharacter();

	void Initialize(const GameContext & gameContext);
	void Update(const GameContext & gameContext);

private:

	Character * m_pCharacter;
};

