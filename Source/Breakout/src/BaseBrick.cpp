// *****************************************************************************
//  BaseBrick   version:  1.0   Ankur Sheel  date: 2013/05/14
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "BaseBrick.h"
#include "Ball.h"
#include "EntityManager.hxx"

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
		cBall * const pBall = dynamic_cast<cBall *>(pEntityCollider);
		IEntityManager::GetInstance()->VDeleteEntity(this);
	}
}
