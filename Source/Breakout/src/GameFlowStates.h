// *****************************************************************************
//  GameFlowStates   version:  1.0   Ankur Sheel  date: 2013/04/04
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef GameFlowStates_h__
#define GameFlowStates_h__

#include "fsm/State.h"

class cGame;

class IGameFlowStates
	: public AI::cState<cGame>
{
};

#endif // GameFlowStates_h__