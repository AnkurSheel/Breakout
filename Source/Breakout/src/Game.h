// *****************************************************************************
//  Game   version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Game_h__
#define Game_h__

#include "Game.hxx"
#include "BaseApp.h"

namespace GameBase
{
	class cHumanView;
	class cGameElementDef;
}

namespace AI
{
	struct Telegram;
}

class cGameFlowStateMachine;

class cGame 
	: public IGame
	, public GameBase::cBaseApp
{
public:
	cGame(const Base::cString & Name);

private:
	~cGame();
	virtual void VInitialize();

	void VOnInitialization(const HINSTANCE & hInstance, const int nCmdShow,
		const Base::cString & strOptionsFile);
	void VOnUpdate();
	void VCleanup();
	bool VOnHandleMessage(const AI::Telegram & telegram);
	void VCreateHumanView();

private:
	int						m_iDisplayHeight;	/// the display height of the window
	int						m_iDisplayWidth;	/// the display width of the window
	cGameFlowStateMachine *	m_pStateMachine;	/// Pointer to the state machine

private:
	friend class cBreakoutView;
	friend class cStatePlayGame;
};
#endif // Game_h__