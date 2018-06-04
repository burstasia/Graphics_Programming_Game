#pragma once
#include "../OverlordEngine/Scenegraph/GameObject.h"

class Pickup final : public GameObject
{
public:
	Pickup(void);
	virtual ~Pickup(void);

	void Initialize(const GameContext & gameContext);
	void Update(const GameContext & gameContext);

	void SetAddForce(bool addForce);

private:
	
	bool m_AddForce;

	static void ColliderCallback(GameObject* triggerobject, GameObject* otherobject, TriggerAction action);
};

