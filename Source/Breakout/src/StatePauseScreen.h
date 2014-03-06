//  *******************************************************************************************************************
//  StatePauseScreen   version:  1.0   Ankur Sheel  date: 2013/03/20
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef StatePauseScreen_h__
#define StatePauseScreen_h__

#include "GameFlowStates.h"

namespace Graphics
{
	class IBaseControl;
	struct stUIEventCallbackParam;
}

class cGame;

class cStatePauseScreen 
	: public cGameFlowStates
{
public:
	virtual ~cStatePauseScreen();
	static cStatePauseScreen *Instance();
	virtual void VOnEnter(cGame *pGame);
	virtual void VOnUpdate(const TICK currentTick, const float deltaTime);
	virtual void VOnExit();
	void VOnPause();
	void VOnResume();

private:
	cStatePauseScreen();
	void OptionsButtonPressed(const Graphics::stUIEventCallbackParam& params);
	void HelpButtonPressed(const Graphics::stUIEventCallbackParam& params);
	void QuitButtonPressed(const Graphics::stUIEventCallbackParam& params);
	void BackButtonPressed(const Graphics::stUIEventCallbackParam& params);
	void EscapePressedListener(GameBase::IEventDataPtr pEventData);

private:
	shared_ptr<Graphics::IBaseControl>	m_pPauseScreen;
};

#endif // StatePauseScreen_h__