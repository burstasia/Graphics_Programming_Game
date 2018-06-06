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
	m_State(State::idle)
{
}


MainCharacter::~MainCharacter()
{
}

void MainCharacter::Initialize(const GameContext & gameContext)
{
	auto model = new ModelComponent(L"Resources/Meshes/idle.ovm");

	auto pDiffuseMaterial = new SkinnedDiffuseMaterial();
	pDiffuseMaterial->SetDiffuseTexture(L"Resources/Textures/Dragon.png");
	gameContext.pMaterialManager->AddMaterial(pDiffuseMaterial, UINT(3));

	model->SetMaterial(3);

	AddComponent(model);

	//model->GetAnimator()->SetAnimation(0);

	GetTransform()->Scale(0.05f, 0.05f, 0.05f);
	//GetTransform()->Rotate(0.0f, 180.0f, 0.0f);

	//INPUT
	gameContext.pInput->AddInputAction(InputAction(50, Down, 'E'));
}

void MainCharacter::Update(const GameContext & gameContext)
{
	//Get rotations of character
	//Get positions of character
	//Update self with these
	GetComponent<ModelComponent>()->GetAnimator()->Play();

	if (m_pCharacter->GetState() == Character::State::flying)
	{
		m_State = State::flying;

		auto velocity = m_pCharacter->GetVelocity();

		GetTransform()->Translate(m_pCharacter->GetTransform()->GetPosition().x, m_pCharacter->GetTransform()->GetPosition().y - 5.0f, m_pCharacter->GetTransform()->GetPosition().z);


		XMVECTOR tempVel = XMLoadFloat3(&velocity);

		tempVel = XMVector3Normalize(tempVel);

		XMStoreFloat3(&velocity, tempVel);

		float angle = (atan2(velocity.x, velocity.z) * 180 / XM_PI) + 180.f;

		GetTransform()->Rotate(0.0f, angle - 180, 0.0f);
	}
	else m_State = State::idle;

	if (gameContext.pInput->IsActionTriggered(50))
	{
		//spawn fireball

		auto scene = static_cast<Platformer*>(GetScene());

		if (scene)
		{
			auto level = static_cast<Level*>(scene->GetLevel());

			if (level)
			{
				level->SpawnFireball(GetTransform()->GetPosition(), GetTransform()->GetForward());
			}
		}
	}
}

void MainCharacter::PostInit()
{
	GetComponent<ModelComponent>()->GetAnimator()->SetAnimation(0);
}
