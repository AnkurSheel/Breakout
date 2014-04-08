//  *******************************************************************************************************************
//  HighScoreScreen   version:  1.0   Ankur Sheel  date: 2013/03/20
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef StateHighScoreScreen_h__
#define StateHighScoreScreen_h__

#include "GameFlowStates.h"

namespace Graphics
{
	class IBaseControl;
	struct stUIEventCallbackParam;
}

class cGame;

class cStateHighScoreScreen 
	: public cGameFlowStates
{
public:
	virtual ~cStateHighScoreScreen();
	static cStateHighScoreScreen *Instance();
	virtual void VOnEnter(cGame *pGame);
	virtual void VOnUpdate(const TICK currentTick, const float deltaTime);
	virtual void VOnExit();

private:
	cStateHighScoreScreen();
	void BackButtonPressed(const Graphics::stUIEventCallbackParam& params);
	void EscapePressedListener(GameBase::IEventDataPtr pEventData);

private:
	shared_ptr<Graphics::IBaseControl>	m_pHighScoreScreen;
};

#endif // StateHighScoreScreen_h__