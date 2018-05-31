#include "stdafx.h"
#include "ShadowMapRenderer.h"


ShadowMapRenderer::ShadowMapRenderer():
	m_IsInitialized(false),
	m_LightDirection(),
	m_LightPosition(),
	m_LightVP(),
	m_pShadowMat(),
	m_pShadowRT(),
	m_Size(100.0f)
{
}


ShadowMapRenderer::~ShadowMapRenderer()
{
}

void ShadowMapRenderer::Begin(const GameContext & gameContext)
{
}

void ShadowMapRenderer::Draw(const GameContext & gameContext, MeshFilter * pMeshFilter, XMFLOAT4X4 world)
{
}

void ShadowMapRenderer::End(const GameContext & gameContext)
{
}

XMFLOAT3 ShadowMapRenderer::GetLightDirection()
{
	return m_LightDirection;
}

XMFLOAT4X4 ShadowMapRenderer::GetLightVP()
{
	return m_LightVP;
}

ShadowMapMaterial * ShadowMapRenderer::GetMaterial()
{
	return m_pShadowMat;
}

ID3D11ShaderResourceView * ShadowMapRenderer::GetShadowMap()
{
	return nullptr;
}

void ShadowMapRenderer::Init(const GameContext & gameContext)
{
}

void ShadowMapRenderer::SetLight(XMFLOAT3 position, XMFLOAT3 direction)
{
}
