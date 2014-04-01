#include "stdafx.h"
#include "BrickDestroyedEventData.h"

using namespace Base;

cHashedString	cBrickDestroyedEventData::m_Name = cHashedString("eventbrickdestroyed");

// *****************************************************************************
cBrickDestroyedEventData::cBrickDestroyedEventData()
	: m_pDestroyedEntity(NULL)
{
}

// *****************************************************************************
cBrickDestroyedEventData::~cBrickDestroyedEventData()
{
}