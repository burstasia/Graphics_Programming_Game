#include "stdafx.h"
#include "PauseScreen.h"
#include "Components/Components.h"


PauseScreen::PauseScreen():
	m_IsActive(false),
	m_MoveDistance(10.0f),
	m_MaxHeight(50.0f),
	m_MinHeight(0.0f),
	m_CurrPos(0.0f),
	m_MenuState(MenuState::MAIN_MENU)
{
}


PauseScreen::~PauseScreen()
{
}

void PauseScreen::Initialize(const GameContext & gameContext)
{
	m_pIndicator = new SpriteComponent(L"./Resources/Textures/indicator.png");
	AddComponent(m_pIndicator);

	m_pPause = new SpriteComponent(L"./Resources/Textures/Chair_Dark.dds");
	AddComponent(m_pPause);

	

	//INPUT FOR PAUSE
	gameContext.pInput->AddInputAction(InputAction(30, Released, VK_DOWN));
	gameContext.pInput->AddInputAction(InputAction(31, Released, VK_UP));
	
}

void PauseScreen::Update(const GameContext & gameContext)
{
	if (m_IsActive)
	{

		if (gameContext.pInput->IsActionTriggered(30)) MoveIndicatorDown();
		if (gameContext.pInput->IsActionTriggered(31)) MoveIndicatorUp();

		m_pIndicator->SetPosition({ 0.0f, m_CurrPos });
		m_pPause->SetPosition({ 0.0f, 0.0f });
		//check position
		//update state
		//check if enter is hit
		//update scene on what to do

		m_Pos = (int)m_CurrPos / m_MoveDistance;

		switch (m_Pos)
		{
		case 0:
			m_MenuState = MenuState::RESUME;
			break;

		case 1:
			m_MenuState = MenuState::RESTART;
			break;

		case 2:
			m_MenuState = MenuState::EXIT;
			break;

		case 3:
			m_MenuState = MenuState::MAIN_MENU;
			break;
		}

		
	}
}

void PauseScreen::MoveIndicatorUp()
{
	//confusing as fuck because moving up means making the y pos smaller
	if (m_pIndicator->GetPos().y > m_MinHeight)
	{
		m_CurrPos -= m_MoveDistance;
	}
	else
	{
		m_CurrPos = m_MaxHeight;
	}
}

void PauseScreen::MoveIndicatorDown()
{
	if (m_pIndicator->GetPos().y < m_MaxHeight)
	{
		m_CurrPos += m_MoveDistance;
	}
	else
	{
		m_CurrPos = m_MinHeight;
	}
}


