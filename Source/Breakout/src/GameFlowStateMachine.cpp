// *****************************************************************************
//  GameFlowStateMachine   version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "GameFlowStateMachine.h"

cGameFlowStateMachine::cGameFlowStateMachine(cGame *pGame)
: cStateMachine<cGame>(pGame)
{
}
// ***************************************************************

cGameFlowStateMachine::~cGameFlowStateMachine(void)
{
}
// ***************************************************************