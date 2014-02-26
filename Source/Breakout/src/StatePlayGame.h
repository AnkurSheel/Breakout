//  *******************************************************************************************************************
//  StatePlayGame   version:  1.0   Ankur Sheel  date: 2013/04/04
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef StatePlayGame_h__
#define StatePlayGame_h__

#include "GameFlowStates.h"

namespace GameBase
{
	class IEventData;
	typedef shared_ptr<IEventData> IEventDataPtr;
}

class cStatePlayGame 
	: public cGameFlowStates
{
public:
	virtual ~cStatePlayGame();
	static cStatePlayGame *Instance();
	virtual void VOnEnter(cGame *pGame);
	virtual void VOnUpdate(const TICK currentTick, const float deltaTime);
	virtual void VOnExit();

private:
	cStatePlayGame();
};
#endif // StatePlayGame_h__