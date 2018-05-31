#pragma once
#include "../OverlordEngine/Scenegraph/GameObject.h"
class Level final : public GameObject
{
public:
	Level(void);
	virtual ~Level(void);

	void Initialize(const GameContext & gameContext);

};

