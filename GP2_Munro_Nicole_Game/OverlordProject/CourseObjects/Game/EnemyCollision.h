#pragma once
#include "Scenegraph/GameObject.h"

class Enemy;

//This class is here for the soul purpose of
//having collision with the players fireball
//this is ridiculous

class EnemyCollision final : public GameObject
{
public:
	EnemyCollision();
	~EnemyCollision();

	void Initialize(const GameContext & gameContext);
	void Update(const GameContext & gameContext);

	void Kill();
private:


};

