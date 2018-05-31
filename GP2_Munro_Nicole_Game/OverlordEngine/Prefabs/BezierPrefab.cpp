#include "stdafx.h"
#include "BezierPrefab.h"
#include "../Content/ContentManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/CameraComponent.h"
#include "../Base/GeneralStructs.h"
#include "../Scenegraph/GameObject.h"
#include "../Scenegraph/GameScene.h"
#include "../Helpers/EffectHelper.h"
#include "../EngineMaterials/BezierMaterial.h"
#include "../Components/MaterialComponentBezier.h"
#include "../Prefabs/Prefabs.h"

BezierPrefab::BezierPrefab(XMFLOAT3 P0, XMFLOAT3 P1, XMFLOAT3 P2, XMFLOAT3 P3, 
	float radius, int segs, int circleSides):
	m_Radius(radius),
	m_CircleSides(circleSides),
	m_SegmentCount(segs),
	m_P0(P0),
	m_P1(P1),
	m_P2(P2),
	m_P3(P3),
	m_IsActiveBezier(false),
	m_pP0_Sphere(new SpherePrefab()),
	m_pP1_Sphere(new SpherePrefab()),
	m_pP2_Sphere(new SpherePrefab()),
	m_pP3_Sphere(new SpherePrefab()),
	m_ActivePoint(0)
{
	m_pBezierMatComponentLeftTrack = new MaterialComponentBezier(P0, P1, P2, P3, radius, segs, circleSides, true, false, false, false, false);
	m_pBezierMatComponentRightTrack = new MaterialComponentBezier(P0, P1, P2, P3, radius, segs, circleSides, false, true, false, false, false);
	m_pBezierMatComponentBeams = new MaterialComponentBezier(P0, P1, P2, P3, radius, segs, circleSides, false, false, true, false, false);
	m_pBezierMatComponentSupportsLeft = new MaterialComponentBezier(P0, P1, P2, P3, radius, segs, circleSides, false, false, false, true, false);
	m_pBezierMatComponentSupportsRight = new MaterialComponentBezier(P0, P1, P2, P3, radius, segs, circleSides, false, false, false, false,true);
}


BezierPrefab::~BezierPrefab()
{
}

void BezierPrefab::IncreaseSegments(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	int segs = m_pBezierMatComponentLeftTrack->m_pBezierMaterialLeft->GetNumSegments();
	m_pBezierMatComponentLeftTrack->m_pBezierMaterialLeft->SetNumSegments(++segs);

	segs = m_pBezierMatComponentRightTrack->m_pBezierMaterialLeft->GetNumSegments();
	m_pBezierMatComponentRightTrack->m_pBezierMaterialLeft->SetNumSegments(++segs);

	segs = m_pBezierMatComponentBeams->m_pBezierMaterialLeft->GetNumSegments();
	m_pBezierMatComponentBeams->m_pBezierMaterialLeft->SetNumSegments(++segs);

	segs = m_pBezierMatComponentSupportsLeft->m_pBezierMaterialLeft->GetNumSegments();
	m_pBezierMatComponentSupportsLeft->m_pBezierMaterialLeft->SetNumSegments(++segs);

	segs = m_pBezierMatComponentSupportsRight->m_pBezierMaterialLeft->GetNumSegments();
	m_pBezierMatComponentSupportsRight->m_pBezierMaterialLeft->SetNumSegments(++segs);

}

void BezierPrefab::DecreaseSegments(const GameContext & gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	int segs = m_pBezierMatComponentLeftTrack->m_pBezierMaterialLeft->GetNumSegments();
	m_pBezierMatComponentLeftTrack->m_pBezierMaterialLeft->SetNumSegments(--segs);

	segs = m_pBezierMatComponentRightTrack->m_pBezierMaterialLeft->GetNumSegments();
	m_pBezierMatComponentRightTrack->m_pBezierMaterialLeft->SetNumSegments(--segs);

	segs = m_pBezierMatComponentBeams->m_pBezierMaterialLeft->GetNumSegments();
	m_pBezierMatComponentBeams->m_pBezierMaterialLeft->SetNumSegments(--segs);

	segs = m_pBezierMatComponentSupportsLeft->m_pBezierMaterialLeft->GetNumSegments();
	m_pBezierMatComponentSupportsLeft->m_pBezierMaterialLeft->SetNumSegments(--segs);

	segs = m_pBezierMatComponentSupportsRight->m_pBezierMaterialLeft->GetNumSegments();
	m_pBezierMatComponentSupportsRight->m_pBezierMaterialLeft->SetNumSegments(--segs);
}

void BezierPrefab::SetActive(bool isActive)
{
	m_IsActiveBezier = isActive;
}

bool BezierPrefab::GetIsActive()
{
	return m_IsActiveBezier;
}

void BezierPrefab::SwitchActivePoint()
{
	if (m_ActivePoint < 3) ++m_ActivePoint;
	else if (m_ActivePoint == 3) m_ActivePoint = 0;
}

void BezierPrefab::MoveX(float value)
{
	//TODO use switch case
	if (m_ActivePoint == 0) m_P0.x += value;
	else if (m_ActivePoint == 1) m_P1.x += value;
	else if (m_ActivePoint == 2) m_P2.x += value;
	else if (m_ActivePoint == 3) m_P3.x += value;
}

void BezierPrefab::MoveY(float value)
{
	if (m_ActivePoint == 0) m_P0.y += value;
	else if (m_ActivePoint == 1) m_P1.y += value;
	else if (m_ActivePoint == 2) m_P2.y += value;
	else if (m_ActivePoint == 3) m_P3.y += value;
}

void BezierPrefab::MoveZ(float value)
{
	if (m_ActivePoint == 0) m_P0.z += value;
	else if (m_ActivePoint == 1) m_P1.z += value;
	else if (m_ActivePoint == 2) m_P2.z += value;
	else if (m_ActivePoint == 3) m_P3.z += value;
}


void BezierPrefab::Initialize(const GameContext& gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	AddComponent(m_pBezierMatComponentLeftTrack);
	AddComponent(m_pBezierMatComponentRightTrack);
	AddComponent(m_pBezierMatComponentBeams);
	AddComponent(m_pBezierMatComponentSupportsLeft);
	AddComponent(m_pBezierMatComponentSupportsRight);

	m_pP0_Sphere->GetTransform()->Translate(m_P0);
	m_pP0_Sphere->GetTransform()->Scale(m_ScaleBalls);
	AddChild(m_pP0_Sphere);

	m_pP1_Sphere->GetTransform()->Translate(m_P1);
	m_pP1_Sphere->GetTransform()->Scale(m_ScaleBalls);
	AddChild(m_pP1_Sphere);

	m_pP2_Sphere->GetTransform()->Translate(m_P2);
	m_pP2_Sphere->GetTransform()->Scale(m_ScaleBalls);
	AddChild(m_pP2_Sphere);

	m_pP3_Sphere->GetTransform()->Translate(m_P3);
	m_pP3_Sphere->GetTransform()->Scale(m_ScaleBalls);
	AddChild(m_pP3_Sphere);
	
}


void BezierPrefab::Update(const GameContext& gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	m_pP0_Sphere->GetTransform()->Translate(m_P0);
	m_pP1_Sphere->GetTransform()->Translate(m_P1);
	m_pP2_Sphere->GetTransform()->Translate(m_P2);
	m_pP3_Sphere->GetTransform()->Translate(m_P3);

	if (m_IsActiveBezier)
	{
		if (m_ActivePoint == 0)
		{
			m_pP0_Sphere->UpdateColour(m_ActivePointColour);
			m_pP1_Sphere->UpdateColour(m_InactivePointColour);
			m_pP2_Sphere->UpdateColour(m_InactivePointColour);
			m_pP3_Sphere->UpdateColour(m_InactivePointColour);
		}
		else if (m_ActivePoint == 1)
		{
			m_pP1_Sphere->UpdateColour(m_ActivePointColour);
			m_pP0_Sphere->UpdateColour(m_InactivePointColour);
			m_pP2_Sphere->UpdateColour(m_InactivePointColour);
			m_pP3_Sphere->UpdateColour(m_InactivePointColour);
		}
		else if (m_ActivePoint == 2)
		{
			m_pP0_Sphere->UpdateColour(m_InactivePointColour);
			m_pP1_Sphere->UpdateColour(m_InactivePointColour);
			m_pP2_Sphere->UpdateColour(m_ActivePointColour);
			m_pP3_Sphere->UpdateColour(m_InactivePointColour);
		}
		else if (m_ActivePoint == 3)
		{
			m_pP0_Sphere->UpdateColour(m_InactivePointColour);
			m_pP1_Sphere->UpdateColour(m_InactivePointColour);
			m_pP2_Sphere->UpdateColour(m_InactivePointColour);
			m_pP3_Sphere->UpdateColour(m_ActivePointColour);
		}
	}
	
	else
	{
		m_pP0_Sphere->UpdateColour(m_InactiveBezierColour);
		m_pP1_Sphere->UpdateColour(m_InactiveBezierColour);
		m_pP2_Sphere->UpdateColour(m_InactiveBezierColour);
		m_pP3_Sphere->UpdateColour(m_InactiveBezierColour);
	}
	m_pBezierMatComponentLeftTrack->UpdateBezierPoints(m_P0, m_P1, m_P2, m_P3);
	m_pBezierMatComponentRightTrack->UpdateBezierPoints(m_P0, m_P1, m_P2, m_P3);
	m_pBezierMatComponentBeams->UpdateBezierPoints(m_P0, m_P1, m_P2, m_P3);
	m_pBezierMatComponentSupportsLeft->UpdateBezierPoints(m_P0, m_P1, m_P2, m_P3);
	m_pBezierMatComponentSupportsRight->UpdateBezierPoints(m_P0, m_P1, m_P2, m_P3);

}

void BezierPrefab::Draw(const GameContext& gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}


