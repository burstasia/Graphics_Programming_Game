#include "stdafx.h"
#include "MainCharacter.h"
#include "Components/Components.h"
#include "Materials/DiffuseMaterial.h"
#include "../Week2/Character.h"

MainCharacter::MainCharacter(Character * chara):
	m_pCharacter(chara)
{
}


MainCharacter::~MainCharacter()
{
}

void MainCharacter::Initialize(const GameContext & gameContext)
{
	auto model = new ModelComponent(L"Resources/Meshes/Dragon.ovm");

	auto pDiffuseMaterial = new DiffuseMaterial();
	pDiffuseMaterial->SetDiffuseTexture(L"Resources/Textures/Dragon.png");
	gameContext.pMaterialManager->AddMaterial(pDiffuseMaterial, UINT(3));

	model->SetMaterial(3);

	AddComponent(model);

	GetTransform()->Scale(0.1f, 0.1f, 0.1f);
	GetTransform()->Rotate(90.0f, -180.0f, 0.0f);
}

void MainCharacter::Update(const GameContext & gameContext)
{
	//Get rotations of character
	//Get positions of character
	//Update self with these

	if (m_pCharacter->GetState() == Character::State::flying)
	{
		auto velocity = m_pCharacter->GetVelocity();

		GetTransform()->Translate(m_pCharacter->GetTransform()->GetPosition().x, m_pCharacter->GetTransform()->GetPosition().y - 5.0f, m_pCharacter->GetTransform()->GetPosition().z);


		XMVECTOR tempVel = XMLoadFloat3(&velocity);

		XMVector3Normalize(tempVel);

		XMStoreFloat3(&velocity, tempVel);

		float angle = (atan2(velocity.x, velocity.z) * 180 / XM_PI) + 180.f;

		GetTransform()->Rotate(90.0f, angle, 0.0f);
	}
	

}
