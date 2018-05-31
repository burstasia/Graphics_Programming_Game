//Precompiled Header [ALWAYS ON TOP IN CPP]
#include "stdafx.h"

#include "ParticleEmitterComponent.h"
#include "../Helpers/EffectHelper.h"
#include "../Content/ContentManager.h"
#include "../Content/TextureDataLoader.h"
#include "../Graphics/Particle.h"
#include "../Components/TransformComponent.h"
#include "../Diagnostics/Logger.h"


ParticleEmitterComponent::ParticleEmitterComponent(const wstring& assetFile, int particleCount) :
	m_ParticleCount(particleCount),
	m_AssetFile(assetFile)
{
	//See Lab10_2

}


ParticleEmitterComponent::~ParticleEmitterComponent(void)
{
	//See Lab10_2
}

void ParticleEmitterComponent::Initialize(const GameContext& gameContext)
{
	//See Lab10_2
}

void ParticleEmitterComponent::LoadEffect(const GameContext& gameContext)
{
	//See Lab10_2
}

void ParticleEmitterComponent::CreateVertexBuffer(const GameContext& gameContext)
{
	//See Lab10_2
}

void ParticleEmitterComponent::Update(const GameContext& gameContext)
{
	//See Lab10_2

	//BUFFER MAPPING CODE [PARTIAL :)]
	//D3D11_MAPPED_SUBRESOURCE mappedResource;
	//gameContext.pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	//ParticleVertex* pBuffer = (ParticleVertex*) mappedResource.pData;
}

void ParticleEmitterComponent::Draw(const GameContext& gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void ParticleEmitterComponent::PostDraw(const GameContext& gameContext)
{
	//See Lab10_2
}
