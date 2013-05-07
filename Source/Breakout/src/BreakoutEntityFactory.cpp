// *****************************************************************************
//  BreakOutEntityFactory   version:  1.0   Ankur Sheel  date: 2013/05/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "StdAfx.h"
#include "BreakOutEntityFactory.h"
#include "Paddle.h"

using namespace GameBase;
using namespace Base;

// *****************************************************************************
cBreakOutEntityFactory::cBreakOutEntityFactory()
{
	if(m_pInstance == NULL)
		m_pInstance = this;
}

// *****************************************************************************
cBreakOutEntityFactory::~cBreakOutEntityFactory()
{
}

// *****************************************************************************
void cBreakOutEntityFactory::RegisterEntities()
{
	m_EntityFactory.Register<cPaddle>(cPaddle::m_Name.GetHash());
}

// *****************************************************************************
IBaseEntity * cBreakOutEntityFactory::VCreateEntity(const cHashedString & Type)
{
	IBaseEntity * pEntity = m_EntityFactory.Create(Type.GetHash());
	pEntity->VInitialize();
	return pEntity;
}