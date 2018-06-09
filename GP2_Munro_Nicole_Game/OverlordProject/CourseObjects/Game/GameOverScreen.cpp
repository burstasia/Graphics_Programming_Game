#include "stdafx.h"
#include "GameOverScreen.h"


GameOverScreen::GameOverScreen():
	m_IsActive(false),
	m_MoveDistance(86.0f),
	m_MaxHeight(609.0f),
	m_MinHeight(437.0f),
	m_CurrPos(437.0f),
	m_MenuState(PauseState::RESTART)
{
}


GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::Initialize(const GameContext & gameContext)
{
	m_pIndicator = new SpriteComponent(L"./Resources/Textures/indicator.png");
	AddComponent(m_pIndicator);

	m_pGameOver = new SpriteComponent(L"./Resources/Textures/PauseScreen.png");
	AddComponent(m_pGameOver);

	//INPUT FOR PAUSE
	gameContext.pInput->AddInputAction(InputAction(30, Released, VK_DOWN));
	gameContext.pInput->AddInputAction(InputAction(31, Released, VK_UP));
}

void GameOverScreen::Update(const GameContext & gameContext)
{
	if (m_IsActive)
	{

		if (gameContext.pInput->IsActionTriggered(30)) MoveIndicatorDown();
		if (gameContext.pInput->IsActionTriggered(31)) MoveIndicatorUp();

		m_pIndicator->SetPosition({ 423.0f, m_CurrPos });
		m_pGameOver->SetPosition({ 0.0f, 0.0f });


		m_Pos = (int)m_CurrPos / m_MoveDistance;

	}

}

void GameOverScreen::MoveIndicatorUp()
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

void GameOverScreen::MoveIndicatorDown()
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
