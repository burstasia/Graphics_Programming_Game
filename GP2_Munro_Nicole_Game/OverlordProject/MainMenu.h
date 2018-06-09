#pragma once
#include "Scenegraph/GameObject.h"
#include "Components/Components.h"

class MainMenu final : public GameObject
{
public:

	enum MainMenuState
	{
		PLAY,
		EXIT
	};

	MainMenu();
	~MainMenu();

	virtual void Initialize(const GameContext& gameContext);
	virtual void Update(const GameContext& gameContext);
	MainMenuState GetState() { return m_MainMenuState; }

	void SetVisible(bool isVisible) 
	{
		m_pMainMenu->SetVisible(isVisible);
		m_pIndicator->SetVisible(isVisible);
		m_IsActive = isVisible;
	};

private:
	SpriteComponent * m_pMainMenu;
	SpriteComponent * m_pIndicator;

	MainMenuState m_MainMenuState;

	bool m_IsActive;

	float m_MoveDistance;
	float m_MaxHeight;
	float m_MinHeight;
	float m_CurrPos;
	int m_Pos;

	void MoveIndicatorUp();
	void MoveIndicatorDown();

};

