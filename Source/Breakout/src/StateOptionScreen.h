//  *******************************************************************************************************************
//  StateOptionScreen   version:  1.0   Ankur Sheel  date: 2014/02/26
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef StateOptionScreen_h__
#define StateOptionScreen_h__

#include "GameFlowStates.h"

namespace Graphics
{
	class IBaseControl;
	struct stUIEventCallbackParam;
}

class cGame;

class cStateOptionsScreen 
	: public cGameFlowStates
{
public:
	virtual ~cStateOptionsScreen();
	static cStateOptionsScreen *Instance();
	virtual void VOnEnter(cGame *pGame);
	virtual void VOnUpdate(const TICK currentTick, const float deltaTime);
	virtual void VOnExit();

private:
	cStateOptionsScreen();
	void BackButtonPressed(const Graphics::stUIEventCallbackParam& params);
	void MusicScrollbarChanged(const Graphics::stUIEventCallbackParam& params);
	void SFXScrollbarChanged(const Graphics::stUIEventCallbackParam& params);
	void MusicCheckBoxPressed(const Graphics::stUIEventCallbackParam & params);

private:
	shared_ptr<Graphics::IBaseControl> m_pOptionsScreen;
};

#endif // StateOptionScreen_h__