#pragma once
#include "../OverlordEngine/Scenegraph/GameObject.h"

class Character;

class Level final : public GameObject
{
public:
	Level(void);
	virtual ~Level(void);

	void Initialize(const GameContext & gameContext);
	void Update(const GameContext & gameContext);


private:

	void InitLevel(const GameContext & gameContext);
	void InitItems(const GameContext & gameContext);

	static void test(GameObject* triggerobject, GameObject* otherobject, TriggerAction action);

	//GameObject *m_Diamond;

	bool m_AddForce = false;
};

