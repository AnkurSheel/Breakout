//  *******************************************************************************************************************
//  Game   version:  1.0   Ankur Sheel  date: 2013/04/02
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef Game_h__
#define Game_h__

#include "Game.hxx"
#include "BaseApp.h"

namespace GameBase
{
	class cHumanView;
	class cGameElementDef;
	class cConfig;
	class cComponentFactory;
}

namespace AI
{
	struct Telegram;
}

class cGameFlowStateMachine;
class cBreakOutEntityFactory;


class cGame 
	: public IGame
	, public GameBase::cBaseApp
{
public:
	cGame(const Base::cString & Name);

private:
	~cGame();
	void VOnInitialization(const HINSTANCE & hInstance, const int CmdShow, const Base::cString & OptionsFile);
	void VOnUpdate();
	void VCleanup();
	bool VOnHandleMessage(const AI::Telegram & telegram);
	void VCreateHumanView();

private:
	int	m_DisplayHeight;	/// the display height of the window
	int	m_DisplayWidth;	/// the display width of the window
	cGameFlowStateMachine *	m_pStateMachine;	/// Pointer to the state machine
	GameBase::cConfig *	m_pConfig;

private:
	friend class cBreakoutView;
	friend class cStateTitleScreen;
	friend class cStateMenuScreen;
	friend class cStatePlayGame;
	friend class cStateOptionsScreen;
	friend class cStatePauseScreen;
};
#endif // Game_h__