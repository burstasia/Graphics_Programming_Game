#include "stdafx.h"

#include "BezierScene.h"
#include "./Prefabs/BezierPrefab.h"
#include "./Components/TerrainComponent.h"
#include "./Prefabs/SkyBoxPrefab.h"

BezierScene::BezierScene():
	GameScene(L"BezierScene")
{
}


BezierScene::~BezierScene()
{
}

void BezierScene::Initialize(const GameContext & gameContext)
{
	//CONTROLS//
	Logger::LogInfo(L"Press keypad right to switch between beziers");
	Logger::LogInfo(L"Press keypad left to switch between bezier points");
	Logger::LogInfo(L"Press t to move the point in the positive x and g in negative x");
	Logger::LogInfo(L"Press y to move the point in the positive y and h in negative y");
	Logger::LogInfo(L"Press u to move the point in the positive z and j in negative z");
	Logger::LogInfo(L"Press arrow key up in increase the number of segments and arrow key down to decrease them");

	UNREFERENCED_PARAMETER(gameContext);

	//works best when z and x is mirrored for the connecting beziers
	m_pBezier_01 = new BezierPrefab({ 0,9.0f,0 }, { 2.5f,7,2.5f }, { 5,5,5 }, { 7.5,4,9 }, 0.2f, 5, 4);
	m_pBezier_02 = new BezierPrefab({ -7.5,10,-11 }, { -5,12,-5 }, { -2.5f,10.5,-2.5 }, { 0,9,0 }, 0.2f, 5, 4);
	//m_pBezier_03 = new BezierPrefab({ 15,9,0 }, { 17.5,11,0 }, { 20,12,0 }, { 22.5,10,0 }, 0.2f, 10, 4);
	AddChild(m_pBezier_01);
	AddChild(m_pBezier_02);
	//AddChild(m_pBezier_03);

	//terrain
	auto terrainGameObject = new GameObject();
	terrainGameObject->AddComponent(new TerrainComponent(L"./Resources/Terrain/Hawai_HeightMap_64x64x16.raw", L"./Resources/Terrain/Hawai_TexMap.dds", 64, 64, 64.0f, 64.0f, 10.0f));

	AddChild(terrainGameObject);

	//skyBox
	auto skybox = new SkyBoxPrefab();
	AddChild(skybox);

	//register input actions
	gameContext.pInput->AddInputAction(InputAction(InputActions::DECREASE_SEGS, Pressed,VK_DOWN));
	gameContext.pInput->AddInputAction(InputAction(InputActions::INCREASE_SEGS, Pressed,VK_UP));
	gameContext.pInput->AddInputAction(InputAction(InputActions::SWITCH_BEZIERS, Pressed, VK_RIGHT));
	gameContext.pInput->AddInputAction(InputAction(InputActions::SWITCH_ACTIVE_POINT, Pressed, VK_LEFT));
	gameContext.pInput->AddInputAction(InputAction(InputActions::MOVE_X_POS, Pressed, 'T'));
	gameContext.pInput->AddInputAction(InputAction(InputActions::MOVE_X_NEG, Pressed, 'G'));
	gameContext.pInput->AddInputAction(InputAction(InputActions::MOVE_Y_POS, Pressed, 'Y'));
	gameContext.pInput->AddInputAction(InputAction(InputActions::MOVE_Y_NEG, Pressed, 'H'));
	gameContext.pInput->AddInputAction(InputAction(InputActions::MOVE_Z_POS, Pressed, 'U'));
	gameContext.pInput->AddInputAction(InputAction(InputActions::MOVE_Z_NEG, Pressed, 'J'));
}

void BezierScene::Update(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	if (gameContext.pInput->IsActionTriggered(InputActions::INCREASE_SEGS))
	{
		m_pBezier_01->IncreaseSegments(gameContext);
		m_pBezier_02->IncreaseSegments(gameContext);
	}
	if (gameContext.pInput->IsActionTriggered(InputActions::DECREASE_SEGS))
	{
		m_pBezier_01->DecreaseSegments(gameContext);
		m_pBezier_02->DecreaseSegments(gameContext);
	}
	if (gameContext.pInput->IsActionTriggered(InputActions::SWITCH_BEZIERS))
	{
		bool active = m_pBezier_01->GetIsActive();
		m_pBezier_01->SetActive(!active);

		m_pBezier_02->SetActive(active);

	}
	if (gameContext.pInput->IsActionTriggered(InputActions::SWITCH_ACTIVE_POINT))
	{
		if (m_pBezier_01->GetIsActive()) m_pBezier_01->SwitchActivePoint();
		else m_pBezier_02->SwitchActivePoint();
	}
	if (gameContext.pInput->IsActionTriggered(InputActions::MOVE_X_POS))
	{
		if (m_pBezier_01->GetIsActive()) m_pBezier_01->MoveX(1.0f);
		else m_pBezier_02->MoveX(1.0f);
	}
	if (gameContext.pInput->IsActionTriggered(InputActions::MOVE_X_NEG))
	{
		if (m_pBezier_01->GetIsActive()) m_pBezier_01->MoveX(-1.0f);
		else m_pBezier_02->MoveX(-1.0f);
	}
	if (gameContext.pInput->IsActionTriggered(InputActions::MOVE_Y_POS))
	{
		if (m_pBezier_01->GetIsActive()) m_pBezier_01->MoveY(1.0f);
		else m_pBezier_02->MoveY(1.0f);
	}
	if (gameContext.pInput->IsActionTriggered(InputActions::MOVE_Y_NEG))
	{
		if (m_pBezier_01->GetIsActive()) m_pBezier_01->MoveY(-1.0f);
		else m_pBezier_02->MoveY(-1.0f);
	}
	if (gameContext.pInput->IsActionTriggered(InputActions::MOVE_Z_POS))
	{
		if (m_pBezier_01->GetIsActive()) m_pBezier_01->MoveZ(1.0f);
		else m_pBezier_02->MoveZ(1.0f);
	}
	if (gameContext.pInput->IsActionTriggered(InputActions::MOVE_Z_NEG))
	{
		if (m_pBezier_01->GetIsActive()) m_pBezier_01->MoveZ(-1.0f);
		else m_pBezier_02->MoveZ(-1.0f);
	}
}

void BezierScene::Draw(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
