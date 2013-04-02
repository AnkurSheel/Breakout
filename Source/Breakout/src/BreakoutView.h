// *****************************************************************************
//  BreakoutView   version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef BreakoutView_h__
#define BreakoutView_h__

#include "HumanView.h"

class cGame;

namespace GameBase
{
	class IBaseApp;
}

class cBreakoutView 
	: public GameBase::cHumanView
{
public:
	cBreakoutView();
	~cBreakoutView();
	void VOnCreateDevice(GameBase::IBaseApp * pGame,
		const HINSTANCE & hInst, const HWND & hWnd);
	void VOnUpdate(const TICK tickCurrent, const float fElapsedTime);
	void VRenderPrivate();
	bool VOnMsgProc(const Base::AppMsg & msg );	

private:
	cGame	*					m_pGame;
};
#endif // BreakoutView_h__