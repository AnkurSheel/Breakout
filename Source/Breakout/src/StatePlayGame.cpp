//  *******************************************************************************************************************
//  StatePlayGame   version:  1.0   Ankur Sheel  date: 2013/03/20
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "StatePlayGame.h"
#include "EntityManager.hxx"
#include "Game.h"
#include "ProcessManager.hxx"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"
#include "Config.h"
#include "Level.h"
#include "HumanView.h"
#include "Timer.hxx"
#include "EventManager.hxx"
#include "EscapePressedEventData.h"
#include "UiManager.hxx"
#include "BaseControl.hxx"
#include "Timer.hxx"
#include "StatePauseScreen.h"
#include "GameFlowStateMachine.h"

using namespace Base;
using namespace GameBase;
using namespace AI;
using namespace Graphics;
using namespace Utilities;

//  *******************************************************************************************************************
cStatePlayGame::cStatePlayGame()
	: m_pGameTimer(NULL)
{
}

//  *******************************************************************************************************************
cStatePlayGame::~cStatePlayGame()
{
}

//  *******************************************************************************************************************
cStatePlayGame* cStatePlayGame::Instance()
{
	static cStatePlayGame instance;
	return &instance;
}

//  *******************************************************************************************************************
void cStatePlayGame::VOnEnter(cGame *pGame)
{
	cGameFlowStates::VOnEnter(pGame);
	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cRenderSystem()));
	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cInputSystem()));
	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cPhysicsSystem()));

	pGame->m_pConfig = DEBUG_NEW cConfig();
	pGame->m_pConfig->Initialize("Entities");
	cLevel::Level.Initialize("level1");

	IEntityManager::GetInstance()->VAddEntity("paddle");
	IEntityManager::GetInstance()->VAddEntity("ball");

	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pHUDScreen = IUiManager::GetInstance()->VCreateUI("HUD");
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(m_pHUDScreen);
		m_pTimerLabel = m_pHUDScreen->VFindChildControl("TimerLabel");
	}

	m_pGameTimer = ITimer::CreateTimer();
	m_pGameTimer->VStartTimer();

	EventListenerCallBackFn listener = bind(&cStatePlayGame::EscapePressedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEscapePressedEventData::m_Name);
}

//  *******************************************************************************************************************
void cStatePlayGame::VOnUpdate(const TICK currentTick, const float deltaTime)
{
	if(m_pOwner != NULL)
	{
		IEntityManager::GetInstance()->VUpdate(deltaTime);
		m_pOwner->m_pHumanView->VOnUpdate(currentTick, deltaTime);
	}

	if(m_pGameTimer != NULL)
	{
		m_pGameTimer->VOnUpdate();
		DisplayTimerOnHUD();
	}
}

//  *******************************************************************************************************************
void cStatePlayGame::VOnExit()
{
	m_pHUDScreen.reset();
	m_pTimerLabel.reset();
	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("HUD");
	}

	SafeDelete(&m_pGameTimer);

	EventListenerCallBackFn listener = bind(&cStatePlayGame::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);
}

//  *******************************************************************************************************************
void cStatePlayGame::VOnPause()
{
	cGameFlowStates::VOnPause();
	if(m_pGameTimer != NULL)
	{
		m_pGameTimer->VStopTimer();
	}
}

//  *******************************************************************************************************************
void cStatePlayGame::VOnResume()
{
	cGameFlowStates::VOnResume();
	if(m_pGameTimer != NULL)
	{
		m_pGameTimer->VStartTimer();
	}
}

//  *******************************************************************************************************************
void cStatePlayGame::EscapePressedListener(IEventDataPtr pEventData)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->m_pStateMachine->RequestPushState(cStatePauseScreen::Instance());
	}
}

//  *******************************************************************************************************************
void cStatePlayGame::DisplayTimerOnHUD()
{
	if(m_pTimerLabel != NULL)
	{
		int time = static_cast<int>(m_pGameTimer->VGetRunningTime());
		int hour = time / 3600;
		time = time % 3600;
		int min = time / 60;
		int sec = time % 60;
		m_pTimerLabel->VSetText(cString(30, "%02d:%02d:%02d", hour, min, sec));
	}
}