#pragma once
#include "Scenegraph/GameScene.h"

class Character;
class Level;

class Platformer : public GameScene
{
public:
	Platformer(void);
	virtual ~Platformer(void);

protected:
	virtual void Initialize(const GameContext& gameContext);
	virtual void Update(const GameContext& gameContext);
	virtual void Draw(const GameContext& gameContext);

private:
	Level * m_Level;
	Character * m_Character;
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Platformer(const Platformer &obj);
	Platformer& operator=(const Platformer& obj);
};

