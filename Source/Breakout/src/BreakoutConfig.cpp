//  *******************************************************************************************************************
//  BreakoutConfig   version:  1.0   Ankur Sheel  date: 2014/03/27
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "BreakoutConfig.h"
#include "XmlNode.hxx"

using namespace Utilities;
using namespace GameBase;
using namespace Base;

//  *******************************************************************************************************************
cBreakoutConfig::cBreakoutConfig()
	: m_Lives(1)
{
}

//  *******************************************************************************************************************
cBreakoutConfig::~cBreakoutConfig()
{
}

//  *******************************************************************************************************************
void cBreakoutConfig::VInitialize(const Base::cString & FileName)
{
	cConfig::VInitialize(FileName);

	if(m_pRoot != NULL)
	{
		m_Lives = m_pRoot->VGetChildValueAsInt("Lives", 1);
	}
}