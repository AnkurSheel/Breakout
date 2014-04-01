// *****************************************************************************
//  BaseBrick   version:  1.0   Ankur Sheel  date: 2013/05/14
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "BaseBrick.h"
#include "Ball.h"
#include "EventManager.hxx"
#include "BrickDestroyedEventData.h"

using namespace Base;
using namespace GameBase;

const Base::cHashedString	cBaseBrick::m_Name = cHashedString("basebrick");

// *****************************************************************************
cBaseBrick::cBaseBrick()
{
}

// *****************************************************************************
cBaseBrick::~cBaseBrick()
{
	VCleanup();
}

// *****************************************************************************
void cBaseBrick::VInitialize()
{
	cBaseEntity::VInitialize();
}

// *****************************************************************************
void cBaseBrick::VCleanup()
{
	cBaseEntity::VCleanup();
}

// *****************************************************************************
cBaseBrick * cBaseBrick::CastToBaseBrick()
{
	return this;
}

// *****************************************************************************
void cBaseBrick::VOnUpdate(const float deltaTime)
{
}

// *****************************************************************************
void cBaseBrick::VOnCollided(IBaseEntity * const pEntityCollider)
{
	if(pEntityCollider->VGetType() == cBall::m_Name)
	{
		shared_ptr<cBrickDestroyedEventData> pEvent(DEBUG_NEW cBrickDestroyedEventData());
		pEvent->m_pDestroyedEntity = this;
		IEventManager::Instance()->VTriggerEvent(pEvent);
	}
}
