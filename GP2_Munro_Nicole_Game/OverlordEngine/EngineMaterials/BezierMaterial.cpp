#include "stdafx.h"


#include "BezierMaterial.h"
#include "../Content/ContentManager.h"
#include "../Graphics/TextureData.h"





BezierMaterial::BezierMaterial(float radius, int numCircleSides, int segmentCount, bool isLeft, bool isRight, bool isCrossBeams, bool leftSupport, bool rightSupport) :
	Material(L"./Resources/Effects/Bezier.fx"),
	m_Radius(radius),
	m_CircleSides(numCircleSides),
	m_Segments(segmentCount),
	m_IsLeft(isLeft),
	m_IsRight(isRight),
	m_IsCrossBeams(isCrossBeams),
	m_IsLeftSupport(leftSupport),
	m_IsRightSupport(rightSupport)
{
}


BezierMaterial::~BezierMaterial()
{
}

int BezierMaterial::GetNumSegments()
{
	return m_Segments;
}

void BezierMaterial::SetNumSegments(int segments)
{
	m_Segments = segments;
}

int BezierMaterial::GetCircleSides()
{
	return m_CircleSides;
}

void BezierMaterial::SetCircleSides(int circleSides)
{
	m_CircleSides = circleSides;
}

float BezierMaterial::GetRadius()
{
	return m_Radius;
}

void BezierMaterial::SetRadius(float radius)
{
	m_Radius = radius;
}

bool BezierMaterial::GetLeft()
{
	return m_IsLeft;
}

void BezierMaterial::SetLeft(bool isLeft)
{
	m_IsLeft = isLeft;
}

bool BezierMaterial::GetRight()
{
	return m_IsRight;
}

void BezierMaterial::SetRight(bool isRight)
{
	m_IsRight = isRight;
}

bool BezierMaterial::GetCrossBeams()
{
	return m_IsCrossBeams;
}

void BezierMaterial::SetCrossBeams(bool isCrossBeams)
{
	m_IsCrossBeams = isCrossBeams;
}

void BezierMaterial::LoadEffectVariables()
{
	m_pRadius = m_pEffect->GetVariableByName("gRadius")->AsScalar();
	m_pSegments = m_pEffect->GetVariableByName("gNumSegments")->AsScalar();
	m_pCircleSides = m_pEffect->GetVariableByName("gNumCircleSides")->AsScalar();
	m_pIsRight = m_pEffect->GetVariableByName("gIsRight")->AsScalar();
	m_pIsLeft = m_pEffect->GetVariableByName("gIsLeft")->AsScalar();
	m_pIsCrossBeams = m_pEffect->GetVariableByName("gCrossBeam")->AsScalar();
	m_pIsLeftSupport = m_pEffect->GetVariableByName("gSupportLeft")->AsScalar();
	m_pIsRightSupport = m_pEffect->GetVariableByName("gSupportRight")->AsScalar();

}

void BezierMaterial::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
	//MODEL COMPONENT IS NO GO NO GOGOOGOOO DON'T USE STOP NO NICOLE
	m_pRadius->SetFloat(m_Radius);
	m_pSegments->SetInt(m_Segments);
	m_pCircleSides->SetInt(m_CircleSides);
	m_pIsRight->SetBool(m_IsRight);
	m_pIsLeft->SetBool(m_IsLeft);
	m_pIsCrossBeams->SetBool(m_IsCrossBeams);
	m_pIsLeftSupport->SetBool(m_IsLeftSupport);
	m_pIsRightSupport->SetBool(m_IsRightSupport);
}