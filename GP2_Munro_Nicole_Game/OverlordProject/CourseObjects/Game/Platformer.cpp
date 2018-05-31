#include "stdafx.h"

#include "Platformer.h"
#include "Components/Components.h"
#include "Physx/PhysxManager.h"
#include "../OverlordEngine/Scenegraph/GameObject.h"
#include "Physx\PhysxProxy.h"

#include "../OverlordProject/Materials/ColorMaterial.h"
#include "Content/ContentManager.h"

#include "Level.h"


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

	//GROUND
	auto pGround = new Level();

	pGround->Initialize(gameContext);

	AddChild(pGround);
	/*pGround->AddComponent(new RigidBodyComponent(true));

	auto geom(ContentManager::Load<PxTriangleMesh>(L"Resources/Meshes/floor.ovpt"));
  
	std::shared_ptr<PxGeometry> geometry(new PxTriangleMeshGeometry(geom));

	pGround->AddComponent(new ColliderComponent(geometry, *bouncyMaterial));


	auto pGroundModel = new ModelComponent(L"Resources/Meshes/floor.ovm");

	pGround->AddComponent(pGroundModel);

	auto pColorMaterial = new ColorMaterial();
	pColorMaterial->SetColor(XMFLOAT4(0.0f, 0.5f, 0.5f, 1.0f));

	gameContext.pMaterialManager->AddMaterial(pColorMaterial, UINT(0));

	pGroundModel->SetMaterial(UINT(0));*/

	
	
}

void Platformer::Update(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void Platformer::Draw(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
