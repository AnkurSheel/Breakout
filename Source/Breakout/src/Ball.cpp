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
#include "RandomGenerator.hxx"

using namespace Base;
using namespace GameBase;
using namespace Utilities;

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
	m_pRandomGenerator = IRandomGenerator::CreateRandomGenerator();
	if (m_pRandomGenerator)
	{
		Log_Write(ILogger::LT_DEBUG, 1, cString(100, "Random Generator created for Ball with seed %u", m_pRandomGenerator->GetRandomSeed()));
	}

	if(m_pTransFormComponent != NULL)
	{
		m_pTransFormComponent->SetPosition(cVector3(cGameOptions::GameOptions().iWidth/2.0f, cGameOptions::GameOptions().iHeight/2.0f, 0.0f));
	}
	if(m_pPhysicsComponent != NULL)
	{
		cVector3 direction;
		direction.x = m_pRandomGenerator->Random();
		direction.y = m_pRandomGenerator->Random();
		m_pPhysicsComponent->ApplyForce(direction);
	}
	VOnInitialized();
}

// *****************************************************************************
void cBall::VCleanup()
{
	cBaseEntity::VCleanup();
	SafeDelete(&m_pRandomGenerator);
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
