#pragma once
#include "Scenegraph/GameScene.h"

class Character;
class Level;
class MainCharacter;
class PauseScreen;
class MainMenu;

class Platformer : public GameScene
{
public:
	Platformer(void);
	virtual ~Platformer(void);

	Level* GetLevel() { return m_Level; }

protected:
	virtual void Initialize(const GameContext& gameContext);
	virtual void Update(const GameContext& gameContext);
	virtual void Draw(const GameContext& gameContext);

	
private:
	Level * m_Level;
	Character * m_Character;
	MainCharacter * m_pMainCharacter;
	PauseScreen * m_PauseScreen;
	MainMenu * m_pMainMenu;

	bool m_IsPaused;

	enum MainGameState
	{
		PLAYING,
		PAUSED,
		MAIN_MENU
	};

	MainGameState m_MainGameState;

	void ResetLevel(const GameContext& gameContext);

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Platformer(const Platformer &obj);
	Platformer& operator=(const Platformer& obj);
};

