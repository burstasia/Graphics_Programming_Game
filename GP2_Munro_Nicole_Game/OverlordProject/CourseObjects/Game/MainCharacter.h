#pragma once
#include "Scenegraph/GameObject.h"

class Character;
class ModelComponent;
class ParticleEmitterComponent;

class MainCharacter final : public GameObject
{
public:

	enum MainCharacterState
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

	void RemoveLife();
	void SetLife(int life);

	void SetStunned();
	bool GetStunned();


private:

	Character * m_pCharacter;
	
	MainCharacterState m_State;
	MainCharacterState m_StateLastFrame;

	bool m_CanShootFireball;
	float m_CooldownTotal;
	float m_CooldownCurr;

	GameObject * m_pModelObject;

	ParticleEmitterComponent* m_pParticleEmitter = nullptr;

	int m_Lives = 10;

	float m_StunnedTimer;
	float m_CurrStunnedTime;
};

