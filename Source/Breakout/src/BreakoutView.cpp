// *****************************************************************************
//  BreakoutView   version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "BreakoutView.h"
#include "Camera.hxx"
#include "MessageDispatchManager.hxx"
#include "Game.h"
#include "Vector3.h"
#include "Messages.h"
#include "EntityManager.hxx"
#include "ProcessManager.hxx"
#include "RenderSystem.h"
#include "KeyboardController.hxx"

using namespace Utilities;
using namespace Graphics;
using namespace GameBase;
using namespace Base;

// *****************************************************************************
cBreakoutView::cBreakoutView()
: m_pGame(NULL)
{
}

// *****************************************************************************
cBreakoutView::~cBreakoutView()
{
}

void cBreakoutView::VOnCreateDevice(IBaseApp * pGame,
								 const HINSTANCE & hInst,
								 const HWND & hWnd)
{
	cHumanView::VOnCreateDevice(pGame, hInst, hWnd);
	m_pGame = dynamic_cast<cGame *>(pGame);
	if (m_pCamera)
	{
		m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -20.0f));
		m_pCamera->VUpdate();
	}
}

// *****************************************************************************
void cBreakoutView::VOnUpdate(const TICK tickCurrent, const float fElapsedTime)
{
	cHumanView::VOnUpdate(tickCurrent, fElapsedTime);
}

// *****************************************************************************
bool cBreakoutView::VOnMsgProc( const Base::AppMsg & msg )
{
	if(!cHumanView::VOnMsgProc(msg))
	{
		if(msg.m_uMsg == WM_KEYDOWN)
		{
			if(!IKeyboardController::Instance()->VIsKeyLocked(msg.m_wParam))
			{
				IKeyboardController::Instance()->VOnKeyDown(msg.m_wParam);
				
				if (msg.m_wParam == VK_ESCAPE)
				{
					// lock the ESC key
					IKeyboardController::Instance()->VLockKey(VK_ESCAPE);
					IMessageDispatchManager::GetInstance()->VDispatchMessage(0.0f,
						IEntityManager::GetInstance()->VGetEntityID(m_pGame), 
						IEntityManager::GetInstance()->VGetEntityID(m_pGame),
						MSG_ESCAPE_PRESSED, NULL);
				}
			}
			
		}
		else if (msg.m_uMsg == WM_KEYUP)
		{
			IKeyboardController::Instance()->VUnlockKey(msg.m_wParam);
			IKeyboardController::Instance()->VOnKeyUp(msg.m_wParam);
		}
	}
	return true;
}

// *******************************************************************************************
void cBreakoutView::VRenderPrivate()
{
	ProcessList pProcessList;
	ProcessList::iterator curProcess;

	m_pGame->VGetProcessManager()->VGetProcesses("RenderSystem", pProcessList);
	for (curProcess = pProcessList.begin(); curProcess != pProcessList.end(); curProcess++)
	{
		shared_ptr<cRenderSystem> p = dynamic_pointer_cast<cRenderSystem>(*curProcess);
		p->Render(m_pCamera);
	}
}
