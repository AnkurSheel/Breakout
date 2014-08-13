// *****************************************************************************
//  GameFlowStateMachine   version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef GameFlowStateMachine_h__
#define GameFlowStateMachine_h__

#include "statemachine.h"
#include "Game.h"

class cGameFlowStateMachine :
	public AI::cStateMachine<cGame>
{
public:
	cGameFlowStateMachine(cGame *pGame);
	~cGameFlowStateMachine(void);
};
#endif // GameFlowStateMachine_h__
