// *****************************************************************************
//  BreakOutEntityFactory   version:  1.0   Ankur Sheel  date: 2013/05/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "StdAfx.h"
#include "BreakOutEntityFactory.h"
#include "Paddle.h"
#include "XMLNode.hxx"
#include "EntityManager.hxx"
#include "BaseComponent.hxx"
#include "Config.h"
#include "Ball.h"
#include "BaseBrick.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

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
	m_RegisteredEntities.Register<cPaddle>(cPaddle::m_Name.GetHash());
	m_RegisteredEntities.Register<cBall>(cBall::m_Name.GetHash());
	m_RegisteredEntities.Register<cBaseBrick>(cBaseBrick::m_Name.GetHash());
}

// *****************************************************************************
IBaseEntity * cBreakOutEntityFactory::VCreateEntity(const cHashedString & Type)
{
	cBaseEntity * pEntity = dynamic_cast<cBaseEntity *>(m_RegisteredEntities.Create(Type.GetHash()));
	if(pEntity != NULL)
	{
		const cEntityDef * const pEntityDef = cConfig::GetEntityDef(Type);
		if(pEntityDef != NULL)
		{
			ComponentMap::const_iterator Iter;
			for (Iter = pEntityDef->m_Components.begin(); Iter != pEntityDef->m_Components.end(); Iter++)
			{
				IBaseComponent * pComponent = Iter->second;
				if(pComponent != NULL)
				{
					pEntity->AddComponent(pComponent);
				}
		}

		}
		pEntity->VInitialize();
	}
	return pEntity;
}