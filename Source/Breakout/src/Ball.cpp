//  *******************************************************************************************************************
//  Ball   version:  1.0   Ankur Sheel  date: 2013/05/13
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "Ball.h"
#include "vector3.h"
#include "gameoptions.h"
#include "transformcomponent.h"
#include "physicscomponent.h"
#include "RandomGenerator.hxx"
#include "BaseBrick.h"
#include "entitymanager.hxx"
#include "Wall.h"
#include "LifeLostEventData.h"
#include "EventManager.hxx"

using namespace Base;
using namespace GameBase;
using namespace Utilities;

const Base::cHashedString	cBall::m_Name = cHashedString("ball");

//  *******************************************************************************************************************
cBall::cBall()
	: m_pPhysicsComponent(NULL)
{
}

//  *******************************************************************************************************************
cBall::~cBall()
{
	VCleanup();
}

//  *******************************************************************************************************************
void cBall::VInitialize()
{
	cBaseEntity::VInitialize();
	m_pPhysicsComponent = dynamic_cast<cPhysicsComponent *>(GetComponent(cPhysicsComponent::GetName()));
	m_pRandomGenerator = IRandomGenerator::CreateRandomGenerator();
	if (m_pRandomGenerator)
	{
		Log_Write(ILogger::LT_DEBUG, 1, cStringUtilities::MakeFormatted("Random Generator created for Ball with seed %u", m_pRandomGenerator->GetRandomSeed()));
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
		Clamp<float>(direction.y, 0.5f, 1.0f);
		m_pPhysicsComponent->ApplyForce(direction);
	}

	VOnInitialized();
}

//  *******************************************************************************************************************
void cBall::VCleanup()
{
	cBaseEntity::VCleanup();
	SafeDelete(&m_pRandomGenerator);
}

//  *******************************************************************************************************************
cBall * cBall::CastToBall()
{
	return this;
}

//  *******************************************************************************************************************
void cBall::VOnUpdate(const float deltaTime)
{

}

//  *******************************************************************************************************************
void cBall::ApplyForce(const cVector3 & direction)
{
	if(m_pPhysicsComponent != NULL)
	{
		m_pPhysicsComponent->ApplyForce(direction);
	}
}

//  *******************************************************************************************************************
void cBall::VOnCollided(IBaseEntity * const pEntityCollider)
{
	if(pEntityCollider->VGetType() == cBaseBrick::m_Name)
	{
		ApplyForce(cVector3(0, 0.25f, 0.0f));
	}
}

//  *******************************************************************************************************************
void cBall::VOnEnteredTrigger(IBaseEntity * const pTrigger)
{
	if(pTrigger->VGetType() == cWall::m_Name)
	{
		shared_ptr<cLifeLostEventData> pEvent(DEBUG_NEW cLifeLostEventData());
		IEventManager::Instance()->VTriggerEvent(pEvent);
	}
}

//  *******************************************************************************************************************
void cBall::VOnRestart()
{
	if(m_pTransFormComponent != NULL)
	{
		m_pTransFormComponent->SetPosition(cVector3(cGameOptions::GameOptions().iWidth/2.0f, cGameOptions::GameOptions().iHeight/2.0f, 0.0f));
	}

	if(m_pPhysicsComponent != NULL)
	{
		cVector3 direction;
		direction.x = m_pRandomGenerator->Random();
		direction.y = m_pRandomGenerator->Random();
		Clamp<float>(direction.y, 0.5f, 1.0f);
		m_pPhysicsComponent->ApplyForce(direction);
	}

	cBaseEntity::VOnRestart();

}