//  *******************************************************************************************************************
//  StateMenuScreen   version:  1.0   Ankur Sheel  date: 2014/02/24
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef MenuScreen_h__
#define MenuScreen_h__

#include "GameFlowStates.h"

namespace Graphics
{
	class IBaseControl;
	struct stUIEventCallbackParam;
}

class cGame;

class cStateMenuScreen 
	: public cGameFlowStates
{
public:
	~cStateMenuScreen();
	static cStateMenuScreen *Instance();
	void VOnEnter(cGame *pGame);
	void VOnUpdate(const TICK currentTick, const float deltaTime);
	void VOnExit();
	void VOnPause();
	void VOnResume();

private:
	cStateMenuScreen();
	void PlayButtonPressed(const Graphics::stUIEventCallbackParam& params);
	void ControlsButtonPressed(const Graphics::stUIEventCallbackParam& params);
	void OptionsButtonPressed(const Graphics::stUIEventCallbackParam& params);
	void HighScoreButtonPressed(const Graphics::stUIEventCallbackParam& params);
	void QuitButtonPressed(const Graphics::stUIEventCallbackParam& params);

private:
	Graphics::IBaseControl * m_pMenuScreen;
};

#endif // MenuScreen_h__