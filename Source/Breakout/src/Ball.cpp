// *****************************************************************************
//  Ball   version:  1.0   Ankur Sheel  date: 2013/05/13
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "Ball.h"
#include "vector3.h"
#include "gameoptions.h"
#include "transformcomponent.h"
#include "physicscomponent.h"

using namespace Base;
using namespace GameBase;

const Base::cHashedString	cBall::m_Name = cHashedString("ball");

// *****************************************************************************
cBall::cBall()
	: m_pPhysicsComponent(NULL)
{
}

// *****************************************************************************
cBall::~cBall()
{
	VCleanup();
}

// *****************************************************************************
void cBall::VInitialize()
{
	cBaseEntity::VInitialize();
	m_pPhysicsComponent = dynamic_cast<cPhysicsComponent *>(GetComponent(cPhysicsComponent::GetName()));
	if(m_pTransFormComponent != NULL)
	{
		m_pTransFormComponent->SetPosition(cVector3(cGameOptions::GameOptions().iWidth/2.0f, cGameOptions::GameOptions().iHeight/2.0f, 0.0f));
	}
	if(m_pPhysicsComponent != NULL)
	{
		m_pPhysicsComponent->ApplyForce(cVector3(0,1,0));
	}
	VOnInitialized();
}

// *****************************************************************************
void cBall::VCleanup()
{
	cBaseEntity::VCleanup();
}

// *****************************************************************************
cBall * cBall::CastToBall()
{
	return this;
}

// *****************************************************************************
void cBall::VOnUpdate(const float deltaTime)
{
}
