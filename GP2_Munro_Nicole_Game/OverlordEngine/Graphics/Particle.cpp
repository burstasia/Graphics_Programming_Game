//Precompiled Header [ALWAYS ON TOP IN CPP]
#include "stdafx.h"

#include "Particle.h"
#include "../Components/TransformComponent.h"
#include "../Helpers/MathHelper.h"


Particle::Particle(const ParticleEmitterSettings& emitterSettings) :
	m_EmitterSettings(emitterSettings)
{
}


Particle::~Particle(void)
{
}

void Particle::Update(const GameContext& gameContext)
{
	//See Lab10_2
	if (!m_IsActive) return;

	m_CurrentEnergy -= gameContext.pGameTime->GetElapsed();

	if (m_CurrentEnergy < 0.0f) m_IsActive = false; return;

	//XMFLOAT3 seconds{ gameContext.pGameTime->GetElapsed(), gameContext.pGameTime->GetElapsed(),gameContext.pGameTime->GetElapsed() };
	m_VertexInfo.Position.x +=  m_EmitterSettings.Velocity.x * gameContext.pGameTime->GetElapsed();
	m_VertexInfo.Position.y += m_EmitterSettings.Velocity.y * gameContext.pGameTime->GetElapsed();
	m_VertexInfo.Position.z += m_EmitterSettings.Velocity.z * gameContext.pGameTime->GetElapsed();

	m_VertexInfo.Color = m_EmitterSettings.Color;

	float particleLifePercent = m_CurrentEnergy / m_TotalEnergy;

	m_VertexInfo.Color.w = particleLifePercent * 2.0f;

	if (m_SizeGrow < 1.0f) m_VertexInfo.Size = m_InitSize + (m_SizeGrow * particleLifePercent);

	if (m_SizeGrow > 1.0f) m_VertexInfo.Size = m_InitSize + (m_SizeGrow * particleLifePercent); //might not work

}

void Particle::Init(XMFLOAT3 initPosition)
{

	//See Lab10_2
	m_IsActive = true;

	m_TotalEnergy = randF(m_EmitterSettings.MinEnergy, m_EmitterSettings.MaxEnergy);

	m_CurrentEnergy = randF(m_EmitterSettings.MinEnergy, m_EmitterSettings.MaxEnergy);

	XMVECTOR randomDirection{ 1, 0, 0 };

	XMMATRIX randomRotationMatrix  = XMMatrixRotationRollPitchYaw(randF(-XM_PI, XM_PI), randF(-XM_PI, XM_PI), randF(-XM_PI, XM_PI));

	randomDirection = XMVector3TransformNormal(randomDirection, randomRotationMatrix);

	float randomDistance = randF(m_EmitterSettings.MinEmitterRange, m_EmitterSettings.MaxEmitterRange);
	
	XMStoreFloat3(&m_VertexInfo.Position, randomDirection * randomDistance);

}
