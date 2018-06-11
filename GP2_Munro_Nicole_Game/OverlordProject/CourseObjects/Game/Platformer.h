#pragma once
#include "Scenegraph/GameScene.h"

class Character;
class Level;
class MainCharacter;
class PauseScreen;
class MainMenu;
class GameOverScreen;
class Score;
class SpriteComponent;


class Platformer : public GameScene
{
public:
	Platformer(void);
	virtual ~Platformer(void);

	Level* GetLevel() { return m_Level; }

	void RemoveLifePlayer();

	MainCharacter* GetMainCharacter() { return m_pMainCharacter; }

	void SetDead();

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
	GameOverScreen * m_pGameOverScreen;
	SpriteComponent * m_pControls;

	//Score * m_pScore;

	bool m_IsPaused;

	enum MainGameState
	{
		PLAYING,
		PAUSED,
		GAME_OVER,
		MAIN_MENU,
		CONTROLS
	};

	MainGameState m_MainGameState;

	void ResetLevel(const GameContext& gameContext);

	float m_TotalControlTime = 0.5f;
	float m_CurrControlTime = 0.0f;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Platformer(const Platformer &obj);
	Platformer& operator=(const Platformer& obj);
};

