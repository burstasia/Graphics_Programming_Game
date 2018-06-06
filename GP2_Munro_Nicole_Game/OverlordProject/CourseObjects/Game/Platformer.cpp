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


	//GROUND
	//auto pGround = new Level();
	m_Level = new Level();
	AddChild(m_Level);
	
	//CHARACTER
	//auto chara = new Character();
	m_Character = new Character();
	AddChild(m_Character);

	m_pMainCharacter = new MainCharacter(m_Character);

	AddChild(m_pMainCharacter);

	m_pMainCharacter->PostInit();

	//m_Character->GetTransform()->Translate(-50.0f, 50.0f, -50.0f);

}

void Platformer::Update(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void Platformer::Draw(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
