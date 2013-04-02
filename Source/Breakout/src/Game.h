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

namespace Utilities
{
	class IRandomGenerator;
}

namespace MySound
{
	class ISound;
}

namespace Graphics
{
	class IBaseControl;
}

class cAsteroidGameElement;
class cGameFlowStateMachine;

class cGame 
	: public IGame
	, public GameBase::cBaseApp
{
public:
	cGame(const Base::cString strName);

private:
	~cGame();
	void VOnInitialization(const HINSTANCE & hInstance, const int nCmdShow,
		const Base::cString & strOptionsFile);
	Base::cString VGetGameTitle() const;
	void VOnUpdate();
	void VCleanup();
	bool VOnHandleMessage(const AI::Telegram & telegram);
	void VCreateHumanView();

private:
	int										m_iDisplayHeight ;		// the display height of the window
	int										m_iDisplayWidth ;		// the display width of the window

private:
	friend class cBreakoutView;
};
#endif // Game_h__