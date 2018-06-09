#include "stdafx.h"

#include "Platformer.h"
#include "Components/Components.h"
#include "Physx/PhysxManager.h"
#include "../OverlordEngine/Scenegraph/GameObject.h"
#include "Physx\PhysxProxy.h"

#include "../OverlordProject/Materials/ColorMaterial.h"
#include "Content/ContentManager.h"

#include "Level.h"

#include "../Week2/Character.h"

#include "Materials/DiffuseMaterial.h"

#include "MainCharacter.h"
#include "PauseScreen.h"
#include "MainMenu.h"

Platformer::Platformer():
	GameScene(L"SpyroScene"),
	m_MainGameState(MainGameState::MAIN_MENU)
{
}


Platformer::~Platformer()
{
}


void Platformer::Initialize(const GameContext & gameContext)
{
	GetPhysxProxy()->EnablePhysxDebugRendering(true);

	//MAIN MATERIAL
	auto pDiffuseMaterial = new DiffuseMaterial();
	pDiffuseMaterial->SetDiffuseTexture(L"Resources/Textures/master.png");
	gameContext.pMaterialManager->AddMaterial(pDiffuseMaterial, UINT(10));


	//GROUND
	m_Level = new Level();
	AddChild(m_Level);
	
	//CHARACTER
	m_Character = new Character();
	AddChild(m_Character);

	m_pMainCharacter = new MainCharacter(m_Character);

	AddChild(m_pMainCharacter);

	m_pMainCharacter->PostInit();

	//pause
	m_PauseScreen = new PauseScreen();
	AddChild(m_PauseScreen);

	//main menu
	m_pMainMenu = new MainMenu();
	AddChild(m_pMainMenu);
	m_pMainMenu->SetVisible(true);
	gameContext.pGameTime->Stop();

	gameContext.pInput->AddInputAction(InputAction(11, Released, VK_TAB));
	gameContext.pInput->AddInputAction(InputAction(32, Released, VK_RETURN));
}

void Platformer::Update(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	switch (m_MainGameState)
	{
	case Platformer::PLAYING:
		m_pMainMenu->SetVisible(false);
		m_PauseScreen->SetVisible(false);

		if (gameContext.pInput->IsActionTriggered(11))
		{
			//pause everything
			gameContext.pGameTime->Stop();
			m_PauseScreen->SetVisible(true);
			m_MainGameState = MainGameState::PAUSED;
		}
		break;
	case Platformer::PAUSED:
		if (gameContext.pInput->IsActionTriggered(32))
		{
			switch (m_PauseScreen->GetState())
			{
			case 0:
				m_MainGameState = MainGameState::PLAYING;
				m_PauseScreen->SetVisible(false);
				gameContext.pGameTime->Start();
				break;

			case 1:
				//reset level
				break;

			case 2:
				//exit
				break;

			case 3:
				m_MainGameState = MainGameState::MAIN_MENU;
				m_pMainMenu->SetVisible(true);
				m_PauseScreen->SetVisible(false);
				gameContext.pGameTime->Stop();
				break;
			}
		}

		break;
	case Platformer::MAIN_MENU:
		gameContext.pGameTime->Stop();
		if (gameContext.pInput->IsActionTriggered(32))
		{
			switch (m_pMainMenu->GetState())
			{
			case 0:
				//play
				m_MainGameState = MainGameState::PLAYING;
				m_pMainMenu->SetVisible(false);
				gameContext.pGameTime->Start();
				break;

			case 1:
				//exit
				break;
			}
		}
	}
}

void Platformer::Draw(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
