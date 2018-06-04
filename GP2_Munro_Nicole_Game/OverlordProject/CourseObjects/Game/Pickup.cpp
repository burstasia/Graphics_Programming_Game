#include "stdafx.h"
#include "Pickup.h"

#include "Components/Components.h"
#include "Physx/PhysxManager.h"
#include "../OverlordEngine/Scenegraph/GameObject.h"
#include "Physx\PhysxProxy.h"

#include "../OverlordProject/Materials/ColorMaterial.h"
#include "Content/ContentManager.h"



Pickup::Pickup():
	m_AddForce(false)
{
}


Pickup::~Pickup()
{
}

void Pickup::Initialize(const GameContext & gameContext)
{

	auto physX = PhysxManager::GetInstance()->GetPhysics();
	auto bouncyMaterial = physX->createMaterial(0.5, 0.5, 1.0f);

	auto diamondModel = new ModelComponent(L"Resources/Meshes/diamond.ovm");

	AddComponent(diamondModel);

	auto rigidBody = new RigidBodyComponent();

	AddComponent(rigidBody);

	diamondModel->SetMaterial(0);

	std::shared_ptr<PxGeometry> geometry(new PxBoxGeometry(1.0f, 1.0f, 1.0f));

	ColliderComponent *collider = new ColliderComponent(geometry, *bouncyMaterial);

	collider->EnableTrigger(true);

	AddComponent(collider);

	GetTransform()->Translate(20.0f, 5.0f, 0.0f);

}

void Pickup::Update(const GameContext & gameContext)
{
	if(!m_AddForce) GetTransform()->Translate(10.0f, 5.0f, 0.0f);

	if (m_AddForce)
	{
		GetComponent<RigidBodyComponent>()->AddForce(PxVec3(1000.0f, 0.0f, 0.0f), PxForceMode::eIMPULSE, true);
	}
}

void Pickup::SetAddForce(bool addForce)
{
	m_AddForce = addForce;
}

void Pickup::ColliderCallback(GameObject * triggerobject, GameObject * otherobject, TriggerAction action)
{
	UNREFERENCED_PARAMETER(triggerobject);
	UNREFERENCED_PARAMETER(otherobject);
	UNREFERENCED_PARAMETER(action);

	/*auto trigger = static_cast<Pickup*>(triggerobject);

	trigger->m_AddForce = true;*/
}
