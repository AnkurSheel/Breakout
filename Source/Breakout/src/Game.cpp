// *****************************************************************************
//  Game   version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "Game.h"
#include "GameFlowStateMachine.h"
#include "BreakoutView.h"
#include "BaseControl.hxx"
#include "EntityManager.hxx"
#include "MessageDispatchManager.hxx"

using namespace MySound;
using namespace Graphics;
using namespace Base;
using namespace GameBase;
using namespace Utilities;

// *****************************************************************************
cGame::cGame(const cString strName)
: cBaseApp(strName)
{
}

// *****************************************************************************
cGame::~cGame()
{
	VCleanup();
}

// *****************************************************************************
void cGame::VOnInitialization(const HINSTANCE & hInstance, const int nCmdShow,
							  const cString & strOptionsFile)
{
	cBaseApp::VOnInitialization(hInstance, nCmdShow, strOptionsFile);

	m_iDisplayHeight = static_cast<int>(m_pHumanView->m_pAppWindowControl->VGetHeight());
	m_iDisplayWidth = static_cast<int>(m_pHumanView->m_pAppWindowControl->VGetWidth());


	IEntityManager::GetInstance()->VRegisterEntity(this);
}

void cGame::VCreateHumanView()
{
	m_pHumanView = DEBUG_NEW cBreakoutView();
}

// *****************************************************************************
void cGame::VOnUpdate()
{
	cBaseApp::VOnUpdate();
}

// *****************************************************************************
void cGame::VCleanup()
{
	cBaseApp::VCleanup();
}

// *****************************************************************************
bool cGame::VOnHandleMessage(const AI::Telegram & telegram)
{
	return false;
}

// *****************************************************************************
IBaseApp * IGame::CreateGame(const cString strName)
{
	return DEBUG_NEW cGame(strName);
}

