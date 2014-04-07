//  *******************************************************************************************************************
//  HelpScreen   version:  1.0   Ankur Sheel  date: 2014/04/07
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef StateHelpScreen_h__
#define StateHelpScreen_h__

#include "GameFlowStates.h"

namespace Graphics
{
	class IBaseControl;
	struct stUIEventCallbackParam;
}

class cGame;

class cStateHelpScreen 
	: public cGameFlowStates
{
public:
	virtual ~cStateHelpScreen();
	static cStateHelpScreen *Instance();
	virtual void VOnEnter(cGame *pGame);
	virtual void VOnUpdate(const TICK currentTick, const float deltaTime);
	virtual void VOnExit();

private:
	cStateHelpScreen();
	void EscapePressedListener(GameBase::IEventDataPtr pEventData);
	void BackButtonPressed(const Graphics::stUIEventCallbackParam& params);

private:
	shared_ptr<Graphics::IBaseControl>	m_pHelpScreen;
};

#endif // StateHelpScreen_h__