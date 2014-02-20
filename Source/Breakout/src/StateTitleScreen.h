//  *******************************************************************************************************************
//  TitleScreen   version:  1.0   Ankur Sheel  date: 2013/03/20
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef TitleScreen_h__
#define TitleScreen_h__

#include "GameFlowStates.h"

namespace GameBase
{
	class IEventData;
	typedef shared_ptr<IEventData> IEventDataPtr;
}

class cGame;

class cStateTitleScreen 
	: public IGameFlowStates
{
public:
	~cStateTitleScreen();
	static cStateTitleScreen *Instance();
	void VOnEnter(cGame *pGame);
	void VOnUpdate();
	void VOnExit();
	bool VOnMessage(const AI::Telegram &msg);
	void EscapePressedListener(GameBase::IEventDataPtr pEventData);

private:
	cStateTitleScreen();

};
#endif // TitleScreen_h__