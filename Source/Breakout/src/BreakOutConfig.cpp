// *****************************************************************************
//  BreakOutConfig   version:  1.0   Ankur Sheel  date: 2013/05/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "StdAfx.h"
#include "BreakOutConfig.h"
#include "Transform2DComponent.h"
#include "SpriteComponent.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

// *****************************************************************************
cBreakOutConfig::cBreakOutConfig()
{
	if(m_pInstance == NULL)
		m_pInstance = this;
}

// *****************************************************************************
cBreakOutConfig::~cBreakOutConfig()
{
}

// *****************************************************************************
void cBreakOutConfig::VInitialize(const cString & FileName)
{
	m_RegisteredComponents.Register<cTransform2DComponent>(cTransform2DComponent::GetName().GetHash());
	m_RegisteredComponents.Register<cSpriteComponent>(cSpriteComponent::GetName().GetHash());
	InitPrivate(FileName);
}