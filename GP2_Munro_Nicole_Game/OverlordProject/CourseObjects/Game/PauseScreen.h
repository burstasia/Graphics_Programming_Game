#pragma once
#include "Scenegraph/GameObject.h"
#include "Components/Components.h"


class PauseScreen final: public GameObject
{
public:

	enum MenuState
	{
		RESUME,
		RESTART,
		EXIT,
		MAIN_MENU

	};

	PauseScreen();
	~PauseScreen();

	virtual void Initialize(const GameContext& gameContext);
	virtual void Update(const GameContext& gameContext);
	MenuState GetState() { return m_MenuState; }

	void SetVisible(bool isVisiable) 
	{ 
		m_IsActive = isVisiable;
		m_pIndicator->SetVisible(isVisiable);
		m_pPause->SetVisible(isVisiable);
		
	}

private:
	SpriteComponent * m_pPause;
	SpriteComponent * m_pIndicator;

	MenuState m_MenuState;

	bool m_IsActive;

	float m_MoveDistance;
	float m_MaxHeight;
	float m_MinHeight;
	float m_CurrPos;
	int m_Pos;

	void MoveIndicatorUp();
	void MoveIndicatorDown();
};

