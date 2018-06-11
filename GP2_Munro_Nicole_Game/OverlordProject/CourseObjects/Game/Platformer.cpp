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

#include "../../Materials/DiffuseMaterial.h"

#include "MainCharacter.h"
#include "PauseScreen.h"
#include "MainMenu.h"
#include "GameOverScreen.h"
#include "Score.h"
#include "../../Materials/SkinnedDiffuseMaterial.h"
#include "Prefabs\Prefabs.h"

Platformer::Platformer():
	GameScene(L"SpyroScene"),
	m_MainGameState(MainGameState::MAIN_MENU)
{
}


Platformer::~Platformer()
{
}


void Platformer::RemoveLifePlayer()
{
	m_pMainCharacter->RemoveLife();
}

void Platformer::SetDead()
{
	m_MainGameState = MainGameState::GAME_OVER;
	m_pGameOverScreen->SetVisible(true);
}

void Platformer::Initialize(const GameContext & gameContext)
{
	//GetPhysxProxy()->EnablePhysxDebugRendering(true);

	//MAIN MATERIAL
	auto pDiffuseMaterial = new DiffuseMaterial();
	pDiffuseMaterial->SetDiffuseTexture(L"Resources/Textures/master.png");
	gameContext.pMaterialManager->AddMaterial(pDiffuseMaterial, UINT(10));

	//MATERIAL//
	auto pDiffuseMaterialEnemy = new SkinnedDiffuseMaterial();
	pDiffuseMaterialEnemy->SetDiffuseTexture(L"Resources/Textures/toadder_uv_tex.png");
	gameContext.pMaterialManager->AddMaterial(pDiffuseMaterialEnemy, UINT(1));

	//GROUND
	m_Level = new Level();
	AddChild(m_Level);
	
	m_Level->PostInit();

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

	//game over
	m_pGameOverScreen = new GameOverScreen();
	AddChild(m_pGameOverScreen);

	//controls
	auto controlGameObject = new GameObject();
	m_pControls = new SpriteComponent(L"./Resources/Textures/Controls.png");
	controlGameObject->AddComponent(m_pControls);
	m_pControls->SetVisible(false);
	m_pControls->SetPosition({ 0.0f, 0.0f });
	AddChild(controlGameObject);

	
	//HUD
	/*m_pScore = new Score();
	AddChild(m_pScore);*/


	//skybox
	auto skybox = new SkyBoxPrefab();
	AddChild(skybox);

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
				ResetLevel(gameContext);
				break;

			case 2:
				//exit
				m_MainGameState = MainGameState::MAIN_MENU;
				m_pMainMenu->SetVisible(true);
				m_PauseScreen->SetVisible(false);
				gameContext.pGameTime->Stop();
				
				break;

			case 3:
				PostQuitMessage(1);
				break;
			}
		}

		break;

	case Platformer::GAME_OVER:
		gameContext.pGameTime->Stop();
		if (gameContext.pInput->IsActionTriggered(32))
		{
			switch (m_pGameOverScreen->GetState())
			{
			case 0:
				//restart
				ResetLevel(gameContext);
				break;

			case 1:
				//main menu
				m_MainGameState = MainGameState::MAIN_MENU;
				m_pMainMenu->SetVisible(true);
				m_pGameOverScreen->SetVisible(false);
				gameContext.pGameTime->Stop();
				break;

			case 2:
				//exit
				PostQuitMessage(1);
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
				m_pMainMenu->SetVisible(false);
				m_pControls->SetVisible(true);
				m_MainGameState = MainGameState::CONTROLS;
				break;

			case 1:
				//exit
				PostQuitMessage(1);
				break;
			}
		}
		break;
	case Platformer::CONTROLS:

		gameContext.pGameTime->Stop();
		
		if (gameContext.pInput->IsActionTriggered(32))
		{
			m_MainGameState = MainGameState::PLAYING;
			m_pControls->SetVisible(false);
			gameContext.pGameTime->Start();
		}

		break;
	}
	
}

void Platformer::Draw(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void Platformer::ResetLevel(const GameContext& gameContext)
{
	m_Level->ResetLevel();

	m_Character->GetTransform()->Translate(-6.0f,5.0f,-50.0f);
	m_pMainCharacter->GetTransform()->Translate(-6.0f, 5.0f, -50.0f);
	m_pMainCharacter->SetLife(10);

	m_MainGameState = MainGameState::PLAYING;

	m_PauseScreen->SetVisible(false);
	m_pGameOverScreen->SetVisible(false);

	gameContext.pGameTime->Start();
}
