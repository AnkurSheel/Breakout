//  *******************************************************************************************************************
//  GameFlowStates   version:  1.0   Ankur Sheel  date: 2013/04/04
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef GameFlowStates_h__
#define GameFlowStates_h__

#include "State.h"

namespace GameBase
{
	class IEventData;
	typedef shared_ptr<IEventData> IEventDataPtr;
}

class cGame;

class cGameFlowStates
	: public AI::cState<cGame>
{
protected:
	bool VOnMessage(const AI::Telegram &msg) { return false; }
	void EscapePressedListener(GameBase::IEventDataPtr pEventData);
};

#endif // GameFlowStates_h__