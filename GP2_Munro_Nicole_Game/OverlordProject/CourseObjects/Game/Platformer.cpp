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

Platformer::Platformer():
	GameScene(L"SpyroScene")
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

	gameContext.pInput->AddInputAction(InputAction(11, Released, VK_TAB));
	gameContext.pInput->AddInputAction(InputAction(32, Released, VK_RETURN));
}

void Platformer::Update(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	if (gameContext.pInput->IsActionTriggered(11))
	{
		//pause everything
		gameContext.pGameTime->Stop();
		m_PauseScreen->SetVisible(true);
		m_IsPaused = true;
	}
	if (gameContext.pInput->IsActionTriggered(32) && m_IsPaused)
	{
		switch (m_PauseScreen->GetState())
		{
		case 0:
			m_IsPaused = false;
			m_PauseScreen->SetVisible(false);
			gameContext.pGameTime->Start();
			break;

		case 1:
			break;

		case 2:
			break;

		case 3:
			break;
		}
	}
}

void Platformer::Draw(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
