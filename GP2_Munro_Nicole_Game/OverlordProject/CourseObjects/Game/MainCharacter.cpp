#include "stdafx.h"
#include "MainCharacter.h"
#include "Components/Components.h"
#include "Materials/SkinnedDiffuseMaterial.h"
#include "Graphics\ModelAnimator.h"
#include "../Week2/Character.h"
#include "Level.h"
#include "Platformer.h"

MainCharacter::MainCharacter(Character * chara):
	m_pCharacter(chara),
	m_State(State::idle),
	m_StateLastFrame(State::idle),
	m_CanShootFireball(true),
	m_CooldownCurr(0.0f),
	m_CooldownTotal(1.0f)
{
}


MainCharacter::~MainCharacter()
{
}

void MainCharacter::Initialize(const GameContext & gameContext)
{

	m_pModelObject = new GameObject();


	auto model = new ModelComponent(L"Resources/Meshes/Dragon.ovm");

	auto pDiffuseMaterial = new SkinnedDiffuseMaterial();
	pDiffuseMaterial->SetDiffuseTexture(L"Resources/Textures/Dragon.png");
	gameContext.pMaterialManager->AddMaterial(pDiffuseMaterial, UINT(3));

	model->SetMaterial(3);

	m_pModelObject->AddComponent(model);

	GetTransform()->Scale(0.05f, 0.05f, 0.05f);

	m_pModelObject->GetTransform()->Rotate(0.0f, 180.0f, 0.0f);

	AddChild(m_pModelObject);

	//INPUT
	gameContext.pInput->AddInputAction(InputAction(50, Down, 'E'));

	GetTransform()->Translate(-6.0f, 5.0f, -50.0f);

	//DUST PARTICLE
	m_pParticleEmitter = new ParticleEmitterComponent(L"./Resources/Textures/dust_cloud.png", 20);
	m_pParticleEmitter->SetVelocity(XMFLOAT3(0, 0.3f, 0));
	m_pParticleEmitter->SetMinSize(1.0f);
	m_pParticleEmitter->SetMaxSize(3.0f);
	m_pParticleEmitter->SetMinEnergy(1.0f);
	m_pParticleEmitter->SetMaxEnergy(2.0f);
	m_pParticleEmitter->SetMinSizeGrow(3.5f);
	m_pParticleEmitter->SetMaxSizeGrow(6.5f);
	m_pParticleEmitter->SetMinEmitterRange(0.2f);
	m_pParticleEmitter->SetMaxEmitterRange(0.5f);
	m_pParticleEmitter->SetColor(XMFLOAT4(229.0f/255.0f, 184.0f/255.0f, 136.f/255.0f, 0.6f));
	AddComponent(m_pParticleEmitter);
}

void MainCharacter::Update(const GameContext & gameContext)
{
	m_StateLastFrame = m_State;
	//Get rotations of character
	//Get positions of character
	//Update self with these
	m_pModelObject->GetComponent<ModelComponent>()->GetAnimator()->Play();

	if (m_pCharacter->GetState() == Character::State::flying)
	{
		if (m_State != State::fireball)m_State = State::flying;

		auto velocity = m_pCharacter->GetVelocity();

		GetTransform()->Translate(m_pCharacter->GetTransform()->GetPosition().x, m_pCharacter->GetTransform()->GetPosition().y - 5.0f, m_pCharacter->GetTransform()->GetPosition().z);


		XMVECTOR tempVel = XMLoadFloat3(&velocity);

		tempVel = XMVector3Normalize(tempVel);

		XMStoreFloat3(&velocity, tempVel);

		float angle = (atan2(velocity.x, velocity.z) * 180 / XM_PI) + 180.f;

		GetTransform()->Rotate(0.0f, angle - 180, 0.0f);

		//m_pParticleEmitter->GetTransform()->Translate(GetTransform()->GetWorldPosition());
	}
	else
	{
		if(m_State != State::fireball)m_State = State::idle;
		
	}

	if (gameContext.pInput->IsActionTriggered(50))
	{
		//spawn fireball

		auto scene = static_cast<Platformer*>(GetScene());

		if (scene)
		{
			auto level = static_cast<Level*>(scene->GetLevel());

			if (level)
			{
				if (m_CanShootFireball)
				{
					level->SpawnFireball(GetTransform()->GetPosition(), GetTransform()->GetForward());
					m_CanShootFireball = false;
					m_State = State::fireball;
				}
			}
		}
	}

	if (!m_CanShootFireball)
	{
		m_State = State::fireball;

		m_CooldownCurr += gameContext.pGameTime->GetElapsed();

		if (m_CooldownCurr >= m_CooldownTotal)
		{
			m_CooldownCurr = 0.0f;
			m_CanShootFireball = true;
			m_State = State::idle;
		}
	}

	if (m_State != m_StateLastFrame)
	{
		switch (m_State)
		{
		case MainCharacter::idle:
			m_pModelObject->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(0);
			break;
		case MainCharacter::flying:
			m_pModelObject->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(1);
			break;
		case MainCharacter::stunned:
			m_pModelObject->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(4);
			break;
		case MainCharacter::fireball:
			m_pModelObject->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(2);
			break;
		default:
			break;
		}
	}
	
}

void MainCharacter::PostInit()
{
	m_pModelObject->GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(1);
}
