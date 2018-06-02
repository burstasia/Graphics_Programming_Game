#pragma once
#include "../OverlordEngine/Scenegraph/GameObject.h"
class Level final : public GameObject
{
public:
	Level(void);
	virtual ~Level(void);

	void Initialize(const GameContext & gameContext);


private:

	void InitLevel(const GameContext & gameContext);
	void InitItems(const GameContext & gameContext);

	static void test(GameObject* triggerobject, GameObject* otherobject, TriggerAction action);

};

