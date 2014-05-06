//  *******************************************************************************************************************
//  Game   version:  1.0   Ankur Sheel  date: 2013/04/02
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "Game.h"
#include "GameFlowStateMachine.h"
#include "BreakoutView.h"
#include "BaseControl.hxx"
#include "StateTitleScreen.h"
#include "BreakoutEntityFactory.h"
#include "BreakOutConfig.h"
#include "ComponentFactory.h"
#include "EntityManager.hxx"
#include "EventManager.hxx"
#include "EventFactory.h"
#include "Timer.hxx"
#include "HighScoreTable.hxx"

using namespace Graphics;
using namespace Base;
using namespace GameBase;
using namespace Utilities;

//  *******************************************************************************************************************
cGame::cGame(const Base::cString & Name) 
	: cBaseApp(Name)
	, m_pStateMachine(NULL)
	, m_pConfig(NULL)
	, m_CurrentLives(1)
	, m_GameOver(false)
	, m_pHighScoreTable(NULL)
{
}

//  *******************************************************************************************************************
cGame::~cGame()
{
	VCleanup();
}

//  *******************************************************************************************************************
void cGame::VOnInitialization(const HINSTANCE & hInstance, const int CmdShow, const cString & OptionsFile)
{
	cBaseApp::VOnInitialization(hInstance, CmdShow, OptionsFile);

	if(m_Quitting)
	{
		return;
	}

	m_DisplayHeight = static_cast<int>(m_pHumanView->m_pAppWindowControl->VGetHeight());
	m_DisplayWidth = static_cast<int>(m_pHumanView->m_pAppWindowControl->VGetWidth());

	m_pStateMachine = DEBUG_NEW cGameFlowStateMachine(this);
	
	IEntityManager::GetInstance()->VInitializeEntityFactory(shared_ptr<cEntityFactory>(DEBUG_NEW cBreakOutEntityFactory()));
	IEntityManager::GetInstance()->VInitializeComponentFactory(shared_ptr<cComponentFactory>(DEBUG_NEW cComponentFactory()));
	IEventManager::Instance()->VInitializeEventFactory(shared_ptr<cEventFactory>(DEBUG_NEW cEventFactory()));

	m_pConfig = DEBUG_NEW cBreakoutConfig();
	m_pConfig->VInitialize("GameConfig");
	
	stHighScoreTableDef def;
	def.m_FileName = "scr";
	def.m_NumberOfRecords = 10;
	def.m_StoreInAscendingOrder = true;
	def.m_DefaultScore = 20000;
	def.m_StepMultiplier = 4;
	def.m_DefaultPlayerName = "Speedrun";
	m_pHighScoreTable = IHighScoreTable::CreateHighScoreTable(def);

	m_CurrentLives = m_pConfig->GetLives();

	m_pStateMachine->SetCurrentState(cStateTitleScreen::Instance());
}

//  *******************************************************************************************************************
void cGame::VCreateHumanView()
{
	m_pHumanView = DEBUG_NEW cBreakoutView();
}

//  *******************************************************************************************************************
void cGame::VOnUpdate()
{
	if(m_Quitting)
	{
		return;
	}
	cBaseApp::VOnUpdate();
	if(m_pGameTimer != NULL && m_pStateMachine != NULL)
	{
		m_pStateMachine->Update(m_pGameTimer->VGetRunningTicks(), m_pGameTimer->VGetDeltaTime());
	}
}

//  *******************************************************************************************************************
void cGame::VCleanup()
{
	SafeDelete(&m_pConfig);
	SafeDelete(&m_pHighScoreTable);
	SafeDelete(&m_pStateMachine);
	cBaseApp::VCleanup();
}

//  *******************************************************************************************************************
bool cGame::VOnHandleMessage(const AI::Telegram & telegram)
{
	return m_pStateMachine->HandleMessage(telegram);
}

//  *******************************************************************************************************************
void cGame::OnGameOver()
{
	m_GameOver = true;
	m_CurrentLives = m_pConfig->GetLives();
}

//  *******************************************************************************************************************
IBaseApp * IGame::CreateGame(const cString Name)
{
	return DEBUG_NEW cGame(Name);
}


