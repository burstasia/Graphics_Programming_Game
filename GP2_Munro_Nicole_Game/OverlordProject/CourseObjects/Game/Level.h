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
	void DeleteFireball(Fireball* fireball);
	void DeletePickup(Pickup* pickupToDelete);
	void SpawnPickup(XMFLOAT3 pos);

	void ResetLevel();

	void PostInit();

private:
	friend class Enemy;

	void InitLevel(const GameContext & gameContext);
	void InitItems(const GameContext & gameContext);

	static void ItemTrigger(GameObject* triggerobject, GameObject* otherobject, TriggerAction action);
	static void EnemyTrigger(GameObject* triggerobject, GameObject* otherobject, TriggerAction action);
	static void FireballTrigger(GameObject* triggerobject, GameObject* otherobject, TriggerAction action);

	std::vector<Enemy*> m_pEnemyVec;
	std::vector<Pickup*> m_pPickupVec;
};

