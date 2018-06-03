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


}

void Platformer::Update(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	m_Level->Update(gameContext.pGameTime->GetElapsed(), m_Character);
}

void Platformer::Draw(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
