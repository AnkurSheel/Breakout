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
#include "ComponentFactory.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

// *****************************************************************************
cBreakOutEntityFactory::cBreakOutEntityFactory()
{
}

// *****************************************************************************
cBreakOutEntityFactory::~cBreakOutEntityFactory()
{
}

// *****************************************************************************
void cBreakOutEntityFactory::VRegisterEntities()
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
				IBaseComponent * pComponent = cComponentFactory::Instance()->GetDuplicateComponent(Iter->second);
				if(pComponent != NULL)
				{
					pEntity->AddComponent(pComponent);
				}
			}
		}
	}
	else
	{
		Log_Write(ILogger::LT_ERROR, 1, "Entity not Registered: " + Type.GetString());
	}

	return pEntity;
}