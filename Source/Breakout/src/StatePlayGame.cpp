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
#include "LifeLostEventData.h"
#include "KeyboardController.hxx"
#include "BaseEntity.hxx"
#include "StateTitleScreen.h"
#include "BrickDestroyedEventData.h"

using namespace Base;
using namespace GameBase;
using namespace AI;
using namespace Graphics;
using namespace Utilities;

//  *******************************************************************************************************************
cStatePlayGame::cStatePlayGame()
	: m_pGameTimer(NULL)
	, m_WaitingToStart(false)
	, m_pPaddle(NULL)
	, m_pBall(NULL)
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
void cStatePlayGame::VOnEnter(cGame * pGame)
{
	cGameFlowStates::VOnEnter(pGame);
	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cRenderSystem()));
	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cInputSystem()));
	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cPhysicsSystem()));

	cLevel::Level.Initialize("level1");

	m_RemainingBricks = cLevel::Level.GetTotalNoOfBricks();

	m_pPaddle = IEntityManager::GetInstance()->VAddEntity("paddle");
	m_pBall = IEntityManager::GetInstance()->VAddEntity("ball");

	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pHUDScreen = IUiManager::GetInstance()->VCreateUI("HUD");
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(m_pHUDScreen);
		m_pTimerLabel = m_pHUDScreen->VFindChildControl("TimerLabel");
		m_pLivesLabel = m_pHUDScreen->VFindChildControl("LivesLabel");
		m_pBeginLabel = m_pHUDScreen->VFindChildControl("StartGame");
		m_pGameOverLabel = m_pHUDScreen->VFindChildControl("GameOver");

		if(m_pLivesLabel != NULL)
		{
			m_pLivesLabel->VSetText(cString(20, "%01d", m_pOwner->m_CurrentLives));
		}
	}

	m_pGameTimer = ITimer::CreateTimer();
	m_pGameTimer->VStartTimer();

	EventListenerCallBackFn listener = bind(&cStatePlayGame::EscapePressedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEscapePressedEventData::m_Name);

	EventListenerCallBackFn onLifeLostlistener = bind(&cStatePlayGame::OnLifeLost, this, _1);
	IEventManager::Instance()->VAddListener(onLifeLostlistener, cLifeLostEventData::m_Name);

	EventListenerCallBackFn onBrickDestroyedlistener = bind(&cStatePlayGame::OnBrickDestroyed, this, _1);
	IEventManager::Instance()->VAddListener(onBrickDestroyedlistener, cBrickDestroyedEventData::m_Name);

	WaitToStart(true);
}

//  *******************************************************************************************************************
void cStatePlayGame::VOnUpdate(const TICK currentTick, const float deltaTime)
{
	if(m_WaitingToStart)
	{
		if(!IKeyboardController::Instance()->VIsKeyLocked(VK_SPACE) && IKeyboardController::Instance()->VIsKeyPressed(VK_SPACE))
		{
			IKeyboardController::Instance()->VLockKey(VK_SPACE);
			if(m_pOwner->m_GameOver)
			{
				if (m_pOwner && m_pOwner->m_pStateMachine)
				{
					m_pOwner->m_pStateMachine->RequestChangeState(cStateTitleScreen::Instance());
				}
			}
			else
			{
				m_WaitingToStart = false;
				if(m_pBeginLabel != NULL)
				{
					m_pBeginLabel->VSetVisible(false);
				}
				WaitToStart(false);
			}
		}
	}
	else 
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
}

//  *******************************************************************************************************************
void cStatePlayGame::VOnExit()
{
	m_pHUDScreen.reset();
	m_pTimerLabel.reset();
	m_pLivesLabel.reset();
	m_pBeginLabel.reset();
	m_pGameOverLabel.reset();

//	m_pOwner->VGetProcessManager()->VDetachProcesses(cRenderSystem::m_strType);
//	m_pOwner->VGetProcessManager()->VDetachProcesses(shared_ptr<Utilities::cProcess>(DEBUG_NEW cInputSystem()));
//	m_pOwner->VGetProcessManager()->VDetachProcesses(shared_ptr<Utilities::cProcess>(DEBUG_NEW cPhysicsSystem()))

	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("HUD");
	}

	SafeDelete(&m_pGameTimer);

	EventListenerCallBackFn listener = bind(&cStatePlayGame::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);

	EventListenerCallBackFn onLifeLostlistener = bind(&cStatePlayGame::OnLifeLost, this, _1);
	IEventManager::Instance()->VRemoveListener(onLifeLostlistener, cLifeLostEventData::m_Name);

	EventListenerCallBackFn onBrickDestroyedlistener = bind(&cStatePlayGame::OnBrickDestroyed, this, _1);
	IEventManager::Instance()->VRemoveListener(onBrickDestroyedlistener, cBrickDestroyedEventData::m_Name);


	IEntityManager::GetInstance()->VDeleteAllEntities();
}

//  *******************************************************************************************************************
void cStatePlayGame::VOnPause()
{
	cGameFlowStates::VOnPause();
	WaitToStart(true);
}

//  *******************************************************************************************************************
void cStatePlayGame::VOnResume()
{
	cGameFlowStates::VOnResume();
	WaitToStart(false);
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
void cStatePlayGame::OnLifeLost(IEventDataPtr pEventData)
{
	WaitToStart(true);

	m_pOwner->m_CurrentLives--;
	if(m_pLivesLabel != NULL)
	{
		m_pLivesLabel->VSetText(cString(20, "%01d", m_pOwner->m_CurrentLives));
	}

	if(m_pPaddle != NULL)
	{
		m_pPaddle->VOnRestart();
	}

	if(m_pBall != NULL)
	{
		m_pBall->VOnRestart();
	}

	if(m_pBeginLabel != NULL)
	{
		m_pBeginLabel->VSetVisible(true);
	}

	if(m_pOwner->m_CurrentLives == 0)
	{
		m_pOwner->OnGameOver();
		if(m_pGameOverLabel!= NULL)
		{
			m_pGameOverLabel->VSetVisible(true);
		}
	}
}

//  *******************************************************************************************************************
void cStatePlayGame::OnBrickDestroyed(IEventDataPtr pEventData)
{
	m_RemainingBricks--;
	shared_ptr<cBrickDestroyedEventData> pCastEventData = static_pointer_cast<cBrickDestroyedEventData>(pEventData);
	IEntityManager::GetInstance()->VDeleteEntity(pCastEventData->m_pDestroyedEntity);
	if(m_RemainingBricks == 0)
	{
		WaitToStart(true);
		
		m_pOwner->OnGameOver();
		if(m_pGameOverLabel!= NULL)
		{
			m_pGameOverLabel->VSetVisible(true);
		}
		if(m_pBeginLabel != NULL)
		{
			m_pBeginLabel->VSetVisible(true);
		}
	}
}

//  *******************************************************************************************************************
void cStatePlayGame::DisplayTimerOnHUD()
{
	if(m_pTimerLabel != NULL && m_pGameTimer != NULL)
	{
		int time = static_cast<int>(m_pGameTimer->VGetRunningTime());
		int hour = time / 3600;
		time = time % 3600;
		int min = time / 60;
		int sec = time % 60;
		m_pTimerLabel->VSetText(cString(30, "%02d:%02d:%02d", hour, min, sec));
	}
}

//  *******************************************************************************************************************
void cStatePlayGame::WaitToStart(bool Wait)
{
	m_WaitingToStart = Wait;
	
	if(m_pGameTimer != NULL)
	{
		if(Wait)
		{
			m_pGameTimer->VStopTimer();
		}
		else
		{
			m_pGameTimer->VStartTimer();
		}
	}
	m_pOwner->VGetProcessManager()->VSetProcessesPaused("PhysicsSystem", Wait);
	m_pOwner->VGetProcessManager()->VSetProcessesPaused("InputSystem", Wait);
}