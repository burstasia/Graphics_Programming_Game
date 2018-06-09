#include "stdafx.h"
#include "MainMenu.h"


MainMenu::MainMenu():
	m_IsActive(false),
	m_MoveDistance(10.0f),
	m_MaxHeight(10.0f),
	m_MinHeight(0.0f),
	m_CurrPos(0.0f),
	m_MainMenuState(MainMenuState::PLAY)
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::Initialize(const GameContext & gameContext)
{
	m_pIndicator = new SpriteComponent(L"./Resources/Textures/indicator.png");
	AddComponent(m_pIndicator);

	m_pMainMenu = new SpriteComponent(L"./Resources/Textures/Knight.jpg");
	AddComponent(m_pMainMenu);

	//INPUT FOR MENU
	gameContext.pInput->AddInputAction(InputAction(40, Released, VK_DOWN));
	gameContext.pInput->AddInputAction(InputAction(41, Released, VK_UP));

}

void MainMenu::Update(const GameContext & gameContext)
{
	if (m_IsActive)
	{
		if (gameContext.pInput->IsActionTriggered(40)) MoveIndicatorDown();
		if (gameContext.pInput->IsActionTriggered(41)) MoveIndicatorUp();

		m_pIndicator->SetPosition({ 0.0f, m_CurrPos });
		m_pMainMenu->SetPosition({ 0.0f, 0.0f });
		//check position
		//update state
		//check if enter is hit
		//update scene on what to do

		m_Pos = (int)m_CurrPos / m_MoveDistance;

		switch (m_Pos)
		{
		case 0:
			m_MainMenuState = MainMenuState::PLAY;
			break;

		case 1:
			m_MainMenuState = MainMenuState::EXIT;
			break;
		}
	}
}

void MainMenu::MoveIndicatorUp()
{
	if (m_pIndicator->GetPos().y > m_MinHeight)
	{
		m_CurrPos -= m_MoveDistance;
	}
	else
	{
		m_CurrPos = m_MaxHeight;
	}
}

void MainMenu::MoveIndicatorDown()
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
