#pragma once
#include "Scenegraph/GameObject.h"
#include "Pickup.h"

class Character;
class Fireball;

class Level final : public GameObject
{
public:
	Level(void);
	virtual ~Level(void);

	void Initialize(const GameContext & gameContext);
	void Update(const GameContext & gameContext);

	void SpawnFireball(XMFLOAT3 startPos, XMFLOAT3 forwardVec);
	void DeletePickup(Pickup* pickupToDelete);

private:
	friend class Enemy;

	void InitLevel(const GameContext & gameContext);
	void InitItems(const GameContext & gameContext);

	static void ItemTrigger(GameObject* triggerobject, GameObject* otherobject, TriggerAction action);
	static void EnemyTrigger(GameObject* triggerobject, GameObject* otherobject, TriggerAction action);
	static void FireballTrigger(GameObject* triggerobject, GameObject* otherobject, TriggerAction action);

	//GameObject *m_Diamond;
	Enemy* m_pEnemy;
};

