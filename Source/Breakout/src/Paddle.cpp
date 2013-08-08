// *****************************************************************************
//  Paddle   version:  1.0   Ankur Sheel  date: 2013/04/04
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "Paddle.h"
#include "TransformComponent.h"
#include "Level.h"
#include "physicscomponent.h"

using namespace Base;
using namespace GameBase;
using namespace Utilities;

const Base::cHashedString	cPaddle::m_Name = cHashedString("paddle");

// *****************************************************************************
cPaddle::cPaddle()
	: m_pPhysicsComponent(NULL)
{
}

// *****************************************************************************
cPaddle::~cPaddle()
{
	VCleanup();
}

// *****************************************************************************
void cPaddle::VInitialize()
{
	cBaseEntity::VInitialize();
	m_pPhysicsComponent = dynamic_cast<cPhysicsComponent *>(GetComponent(cPhysicsComponent::GetName()));

	if(m_pTransFormComponent != NULL)
	{
		m_pTransFormComponent->SetPosition(cLevel::Level.GetPaddleSpawnPoint());
	}
	VOnInitialized();
}

// *****************************************************************************
void cPaddle::VCleanup()
{
	cBaseEntity::VCleanup();
}

// *****************************************************************************
cPaddle * cPaddle::CastToPaddle()
{
	return this;
}

// *****************************************************************************
void cPaddle::VOnUpdate(const float deltaTime)
{
	if(!m_ForceDirection.IsZero())
	{
		if(m_pPhysicsComponent != NULL)
		{
			m_pPhysicsComponent->ApplyForce(m_ForceDirection);
		}
		m_ForceDirection = cVector3::Zero();
	}
}

// *****************************************************************************
void cPaddle::VHandleInput(const unsigned int CharID, const float deltaTime)
{
	if(m_pTransFormComponent != NULL)
	{
		if(CharID == VK_LEFT)
		{
			m_ForceDirection = m_pTransFormComponent->m_LookAt.GetReverse();
		}
		else if(CharID == VK_RIGHT)
		{
			m_ForceDirection = m_pTransFormComponent->m_LookAt;
		}
	}
}