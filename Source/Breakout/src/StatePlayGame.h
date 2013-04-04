// *****************************************************************************
//  StatePlayGame   version:  1.0   Ankur Sheel  date: 2013/04/04
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef StatePlayGame_h__
#define StatePlayGame_h__

#include "GameFlowStates.h"

class cStatePlayGame 
	: public IGameFlowStates
{
public:
	virtual ~cStatePlayGame();
	static cStatePlayGame *Instance();
	virtual void VOnEnter(cGame *pGame);
	virtual void VOnUpdate();
	virtual void VOnExit();
	virtual bool VOnMessage(const AI::Telegram &msg);
private:
	cStatePlayGame();
};


#endif // StatePlayGame_h__