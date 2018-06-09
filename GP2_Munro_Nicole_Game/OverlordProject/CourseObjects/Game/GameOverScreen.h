#pragma once
#include "Scenegraph/GameObject.h"
#include "Components/Components.h"

class GameOverScreen final : public GameObject
{
public:

	enum PauseState
	{
		RESTART,
		MAIN_MENU,
		EXIT
	};

	GameOverScreen();
	~GameOverScreen();

	virtual void Initialize(const GameContext& gameContext);
	virtual void Update(const GameContext& gameContext);
	PauseState GetState()
	{ 
		switch (m_Pos)
		{
		case 5:
			m_MenuState = PauseState::RESTART;
			break;

		case 6:
			m_MenuState = PauseState::MAIN_MENU;
			break;

		case 7:
			m_MenuState = PauseState::EXIT;
			break;
		}
		return m_MenuState;
	
	}

	void SetVisible(bool isVisiable)
	{
		m_IsActive = isVisiable;
		m_pIndicator->SetVisible(isVisiable);
		m_pGameOver->SetVisible(isVisiable);
	}

private:
	SpriteComponent * m_pGameOver;
	SpriteComponent * m_pIndicator;

	PauseState m_MenuState;

	bool m_IsActive;

	float m_MoveDistance;
	float m_MaxHeight;
	float m_MinHeight;
	float m_CurrPos;
	int m_Pos;

	void MoveIndicatorUp();
	void MoveIndicatorDown();

};

