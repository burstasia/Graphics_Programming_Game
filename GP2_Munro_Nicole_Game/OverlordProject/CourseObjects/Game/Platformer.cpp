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

	//PHYSX
	//auto physX = PhysxManager::GetInstance()->GetPhysics();
	//auto bouncyMaterial = physX->createMaterial(0.5, 0.5, 1.0f);

	GetPhysxProxy()->EnablePhysxDebugRendering(true);

	auto pColorMaterial = new ColorMaterial();
	pColorMaterial->SetColor(XMFLOAT4(0.0f, 0.5f, 0.5f, 1.0f));

	gameContext.pMaterialManager->AddMaterial(pColorMaterial, UINT(0));

	//GROUND
	auto pGround = new Level();

	pGround->Initialize(gameContext);

	AddChild(pGround);
	
	//CHARACTER
	auto chara = new Character();
	AddChild(chara);


}

void Platformer::Update(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void Platformer::Draw(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
