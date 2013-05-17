// *****************************************************************************
//  Paddle   version:  1.0   Ankur Sheel  date: 2013/04/04
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "Paddle.h"
#include "transform2dComponent.h"
#include "Level.h"

using namespace Base;
using namespace GameBase;
using namespace Utilities;

const Base::cHashedString	cPaddle::m_Name = cHashedString("paddle");

// *****************************************************************************
cPaddle::cPaddle()
{
}

// *****************************************************************************
cPaddle::~cPaddle()
{
	VCleanup();
}

// *****************************************************************************
void cPaddle::VInitialize()
{
	cBaseEntity::VInitialize();
	cTransform2DComponent * pTransFormComponent = dynamic_cast<cTransform2DComponent *>(GetComponent(cTransform2DComponent::GetName().GetHash()));
	if(pTransFormComponent != NULL)
	{
		pTransFormComponent->m_vPosition = cLevel::Level.GetPaddleSpawnPoint();
	}
	
}

// *****************************************************************************
void cPaddle::VCleanup()
{
	cBaseEntity::VCleanup();
}

// *****************************************************************************
cPaddle * cPaddle::CastToPaddle()
{
	return this;
}

// *****************************************************************************
void cPaddle::VOnUpdate()
{
}

// *****************************************************************************
void cPaddle::VHandleInput(const unsigned int CharID)
{
	if(CharID == VK_LEFT)
	{
		Log_Write(ILogger::LT_COMMENT, 1, "Left Pressed " + VGetName());
	}
	else if(CharID == VK_RIGHT)
	{
		Log_Write(ILogger::LT_COMMENT, 1, "Right Pressed " + VGetName());
	}

}
