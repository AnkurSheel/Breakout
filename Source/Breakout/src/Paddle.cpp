//  *******************************************************************************************************************
//  Paddle   version:  1.0   Ankur Sheel  date: 2013/04/04
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "Paddle.h"
#include "TransformComponent.h"
#include "Level.h"
#include "physicscomponent.h"
#include "Ball.h"
#include "BreakoutControls.h"
#include "BaseApp.hxx"
#include "KeyboardController.hxx"

using namespace Base;
using namespace GameBase;
using namespace Utilities;

const Base::cHashedString cPaddle::m_Name = cHashedString("paddle");

//  *******************************************************************************************************************
cPaddle::cPaddle()
	: m_pPhysicsComponent(NULL)
{
}

//  *******************************************************************************************************************
cPaddle::~cPaddle()
{
	VCleanup();
}

//  *******************************************************************************************************************
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

//  *******************************************************************************************************************
void cPaddle::VCleanup()
{
	cBaseEntity::VCleanup();
}

//  *******************************************************************************************************************
cPaddle * cPaddle::CastToPaddle()
{
	return this;
}

//  *******************************************************************************************************************
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

//  *******************************************************************************************************************
void cPaddle::VHandleInput(const float inDeltaTime)
{
	if(m_pTransFormComponent != NULL)
	{
		if(IKeyboardController::Instance()->VIsKeyPressed(IBaseApp::GetInstance()->VGetGameControls()->GetKeyCode(BreakoutControls::MOVE_LEFT)))
		{
			m_ForceDirection = m_pTransFormComponent->GetLookAt().GetReverse();
		}
		if(IKeyboardController::Instance()->VIsKeyPressed(IBaseApp::GetInstance()->VGetGameControls()->GetKeyCode(BreakoutControls::MOVE_RIGHT)))
		{
			m_ForceDirection = m_pTransFormComponent->GetLookAt();
		}
	}
}

//  *******************************************************************************************************************
void cPaddle::VOnCollided(IBaseEntity * const pEntityCollider)
{
	if(pEntityCollider->VGetType() == cBall::m_Name)
	{
		cBall * const pBall = dynamic_cast<cBall *>(pEntityCollider);
		pBall->ApplyForce(cVector3(0, -10.0f, 0.0f));

		if(!m_ForceDirection.IsZero())
		{
			pBall->ApplyForce(m_ForceDirection * 5.f);
		}
	}
}

//  *******************************************************************************************************************
void cPaddle::VOnRestart()
{
	if(m_pTransFormComponent != NULL)
	{
		m_pTransFormComponent->SetPosition(cLevel::Level.GetPaddleSpawnPoint());
	}

	cBaseEntity::VOnRestart();
}
