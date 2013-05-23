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
		m_pTransFormComponent->m_Position = cLevel::Level.GetPaddleSpawnPoint();
	}
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
void cPaddle::VOnUpdate()
{
}

// *****************************************************************************
void cPaddle::VHandleInput(const unsigned int CharID)
{
	if(CharID == VK_LEFT)
	{
		if(m_pPhysicsComponent != NULL && m_pTransFormComponent != NULL)
		{
			m_pPhysicsComponent->ApplyForce(m_pTransFormComponent->m_LookAt.GetReverse());
		}
	}
	else if(CharID == VK_RIGHT)
	{
		if(m_pPhysicsComponent != NULL && m_pTransFormComponent != NULL)
		{
			m_pPhysicsComponent->ApplyForce(m_pTransFormComponent->m_LookAt);
		}
	}
}
