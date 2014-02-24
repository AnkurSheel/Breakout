//  *******************************************************************************************************************
//  TitleScreen   version:  1.0   Ankur Sheel  date: 2013/03/20
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef TitleScreen_h__
#define TitleScreen_h__

#include "GameFlowStates.h"

#include "vector2.h"

namespace GameBase
{
	class IEventData;
	typedef shared_ptr<IEventData> IEventDataPtr;
}

namespace Graphics
{
	class IBaseControl;
}

class cGame;

class cStateTitleScreen 
	: public IGameFlowStates
{
public:
	~cStateTitleScreen();
	static cStateTitleScreen *Instance();
	void VOnEnter(cGame *pGame);
	void VOnUpdate(const TICK currentTick, const float deltaTime);
	void VOnExit();
	bool VOnMessage(const AI::Telegram &msg);
	void EscapePressedListener(GameBase::IEventDataPtr pEventData);

private:
	cStateTitleScreen();

private:
	float	m_DelayTime;
	Base::cVector2	m_Position;
	shared_ptr<Graphics::IBaseControl>	m_pTitleScreen;
};
#endif // TitleScreen_h__