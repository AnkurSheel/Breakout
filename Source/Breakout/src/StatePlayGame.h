//  *******************************************************************************************************************
//  StatePlayGame   version:  1.0   Ankur Sheel  date: 2013/04/04
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef StatePlayGame_h__
#define StatePlayGame_h__

#include "GameFlowStates.h"

namespace Graphics
{
	class IBaseControl;
}

namespace Utilities
{
	class ITimer;
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
	void DisplayTimerOnHUD();
	void EscapePressedListener(GameBase::IEventDataPtr pEventData);
	void OnLifeLost(GameBase::IEventDataPtr pEventData);
	void VOnPause();
	void VOnResume();

private:
	shared_ptr<Graphics::IBaseControl>	m_pHUDScreen;
	shared_ptr<Graphics::IBaseControl>	m_pTimerLabel;
	Utilities::ITimer *	m_pGameTimer;
};
#endif // StatePlayGame_h__