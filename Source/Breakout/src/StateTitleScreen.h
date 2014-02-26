//  *******************************************************************************************************************
//  StateTitleScreen   version:  1.0   Ankur Sheel  date: 2013/03/20
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef StateTitleScreen_h__
#define StateTitleScreen_h__

#include "GameFlowStates.h"

#include "vector2.h"

namespace Graphics
{
	class IBaseControl;
}

class cGame;

class cStateTitleScreen 
	: public cGameFlowStates
{
public:
	~cStateTitleScreen();
	static cStateTitleScreen *Instance();
	void VOnEnter(cGame *pGame);
	void VOnUpdate(const TICK currentTick, const float deltaTime);
	void VOnExit();

private:
	cStateTitleScreen();

private:
	float	m_DelayTime;
	Base::cVector2	m_Position;
	shared_ptr<Graphics::IBaseControl>	m_pTitleScreen;
};
#endif // StateTitleScreen_h__