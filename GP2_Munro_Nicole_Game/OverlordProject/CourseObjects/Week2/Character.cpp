//Precompiled Header [ALWAYS ON TOP IN CPP]
#include "stdafx.h"

#include "Character.h"
#include "Components\Components.h"
#include "Prefabs\Prefabs.h"
#include "Physx/PhysxManager.h"

Character::Character(float radius, float height, float moveSpeed) :
	m_Radius(radius),
	m_Height(height),
	m_MoveSpeed(moveSpeed),
	m_pCamera(nullptr),
	m_pController(nullptr),
	m_TotalPitch(0),
	m_TotalYaw(0),
	m_RotationSpeed(90.f),
	//Running
	m_MaxRunVelocity(50.0f),
	m_TerminalVelocity(20),
	m_Gravity(9.81f),
	m_RunAccelerationTime(0.3f),
	m_JumpAccelerationTime(0.8f),
	m_RunAcceleration(m_MaxRunVelocity / m_RunAccelerationTime),
	m_JumpAcceleration(m_Gravity / m_JumpAccelerationTime),
	m_RunVelocity(0),
	m_JumpVelocity(0),
	m_Velocity(0, 0, 0)
{
}


Character::~Character(void)
{
}

void Character::Initialize(const GameContext& gameContext)
{
	//UNREFERENCED_PARAMETER(gameContext);
	// Create controller
	auto physX = PhysxManager::GetInstance()->GetPhysics();

	auto bouncyMaterial = physX->createMaterial(0, 0, 1);

	m_pController = new ControllerComponent(bouncyMaterial);
	AddComponent(m_pController);
	// Add a fixed camera as child
	auto pFixedCamera = new FixedCamera();
	AddChild(pFixedCamera);
	m_pCamera = pFixedCamera->GetComponent<CameraComponent>();

	// Register all Input Actions
	gameContext.pInput->AddInputAction(InputAction(CharacterMovement::FORWARD, Down, 'W'));
	gameContext.pInput->AddInputAction(InputAction(CharacterMovement::BACKWARD, Down, 'S'));
	gameContext.pInput->AddInputAction(InputAction(CharacterMovement::RIGHT, Down, 'D'));
	gameContext.pInput->AddInputAction(InputAction(CharacterMovement::LEFT, Down, 'A'));
	gameContext.pInput->AddInputAction(InputAction(CharacterMovement::JUMP, Down, VK_SPACE));
}

void Character::PostInitialize(const GameContext& gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	// Set the camera as active
	m_pCamera = GetChild<FixedCamera>()->GetComponent<CameraComponent>();
	m_pCamera->SetActive();

	// We need to do this in the PostInitialize because child game objects only get initialized 
	//after the Initialize of the current object finishes

}


void Character::Update(const GameContext& gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	//Update the character (Camera rotation, Character Movement, Character Gravity)
	if (m_pCamera->IsActive())
	{
		XMFLOAT3 move = XMFLOAT3(0, 0, 0);
		move.z = gameContext.pInput->IsActionTriggered(FORWARD) ? 1.0f : 0.0f;
		if (move.z == 0) move.z = gameContext.pInput->IsActionTriggered(BACKWARD) ? -1.0f : 0.0f;

		move.x = gameContext.pInput->IsActionTriggered(RIGHT) ? 1.0f : 0.0f;
		if (move.x == 0) move.x = gameContext.pInput->IsActionTriggered(LEFT) ? -1.0f : 0.0f;

		move.y = gameContext.pInput->IsActionTriggered(JUMP) ? 1.0f : 0.0f;


		XMFLOAT2 look = XMFLOAT2(0, 0);
		auto mouseMove = gameContext.pInput->GetMouseMovement();
		look.x = static_cast<float>(mouseMove.x);
		look.y = static_cast<float>(mouseMove.y);

		//Calculate Transforms
		XMVECTOR currPos = XMLoadFloat3(&GetTransform()->GetPosition());

		XMFLOAT3 forward = GetTransform()->GetForward();
		XMFLOAT3 right = GetTransform()->GetRight();
		auto elapsed = gameContext.pGameTime->GetElapsed();

		if (move.x != 0 || move.z != 0)
		{
			m_RunVelocity += m_RunAcceleration * elapsed;
			if (m_RunVelocity >= m_MaxRunVelocity)
			{
				m_RunVelocity = m_MaxRunVelocity;
			}

			m_Velocity.x = ((forward.x * move.z) + (right.x * move.x)) * m_RunVelocity;
			m_Velocity.z = ((forward.z * move.z) + (right.z * move.x)) * m_RunVelocity;
		}
		else
		{
			m_Velocity.x = 0.0f;
			m_Velocity.z = 0.0f;
		}

		XMFLOAT3 currPosFloat3;
		XMStoreFloat3(&currPosFloat3, currPos);
		if (currPosFloat3.y >= 5)
		{
			m_JumpVelocity += m_JumpAcceleration * elapsed;
			if (m_JumpVelocity >= m_TerminalVelocity)
			{
				m_JumpVelocity = m_TerminalVelocity;
			}
			m_Velocity.y -= m_JumpVelocity;
		}
		else if (move.y != 0)
		{
			m_JumpVelocity = 0;
			m_Velocity.y = 200;
		}
		else
		{
			m_Velocity.y = 0;
		}

		auto tempVel = XMFLOAT3(m_Velocity.x * elapsed, m_Velocity.y * elapsed, m_Velocity.z * elapsed);
		m_pController->Move(tempVel);

		m_TotalYaw += look.x * m_RotationSpeed * elapsed;
		m_TotalPitch += look.y * m_RotationSpeed * elapsed;
		if (m_TotalPitch > 75.0f) m_TotalPitch = 75.0f;
		if (m_TotalPitch < 15.0f) m_TotalPitch = 15.0f;
		GetTransform()->Rotate(m_TotalPitch, m_TotalYaw, 0);
	}

}