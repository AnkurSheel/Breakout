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
#include "StatePlayGame.h"
#include "BreakoutEntityFactory.h"
#include "Config.h"
#include "ComponentFactory.h"
#include "EntityManager.hxx"
#include "EventManager.hxx"
#include "EventFactory.h"

using namespace Graphics;
using namespace Base;
using namespace GameBase;
using namespace Utilities;

// *****************************************************************************
cGame::cGame(const Base::cString & Name) 
	: cBaseApp(Name)
	, m_pStateMachine(NULL)
	, m_pConfig(NULL)
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

	if(m_Quitting)
	{
		return;
	}

	m_iDisplayHeight = static_cast<int>(m_pHumanView->m_pAppWindowControl->VGetHeight());
	m_iDisplayWidth = static_cast<int>(m_pHumanView->m_pAppWindowControl->VGetWidth());

	m_pStateMachine = DEBUG_NEW cGameFlowStateMachine(this);
	
	IEntityManager::GetInstance()->VInitializeEntityFactory(shared_ptr<cEntityFactory>(DEBUG_NEW cBreakOutEntityFactory()));
	IEntityManager::GetInstance()->VInitializeComponentFactory(shared_ptr<cComponentFactory>(DEBUG_NEW cComponentFactory()));
	IEventManager::Instance()->VInitializeEventFactory(shared_ptr<cEventFactory>(DEBUG_NEW cEventFactory()));

	m_pStateMachine->SetCurrentState(cStatePlayGame::Instance());
}

void cGame::VCreateHumanView()
{
	m_pHumanView = DEBUG_NEW cBreakoutView();
}

// *****************************************************************************
void cGame::VOnUpdate()
{
	if(m_Quitting)
	{
		return;
	}
	cBaseApp::VOnUpdate();
	m_pStateMachine->Update();
}

// *****************************************************************************
void cGame::VCleanup()
{
	cBaseApp::VCleanup();
	SafeDelete(&m_pConfig);
	SafeDelete(&m_pStateMachine);
}

// *****************************************************************************
bool cGame::VOnHandleMessage(const AI::Telegram & telegram)
{
	return m_pStateMachine->HandleMessage(telegram);
}

// *****************************************************************************
IBaseApp * IGame::CreateGame(const cString strName)
{
	return DEBUG_NEW cGame(strName);
}

