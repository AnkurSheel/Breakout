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
#include "FSM\Telegram.h"
#include "HumanView.h"
#include "Timer.hxx"
#include "EventManager.hxx"
#include "EscapePressedEventData.h"
#include "UiManager.hxx"
#include "BaseControl.hxx"

using namespace Base;
using namespace GameBase;
using namespace AI;
using namespace Graphics;

//  *******************************************************************************************************************
cStatePlayGame::cStatePlayGame()
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
	}

	EventListenerCallBackFn listener = bind(&cStatePlayGame::EscapePressedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEscapePressedEventData::m_Name);
}

//  *******************************************************************************************************************
void cStatePlayGame::VOnUpdate(const TICK currentTick, const float deltaTime)
{
	if(m_pOwner != NULL && m_pOwner->m_pGameTimer != NULL)
	{
		IEntityManager::GetInstance()->VUpdate(deltaTime);
		m_pOwner->m_pHumanView->VOnUpdate(currentTick, deltaTime);
	}
}

//  *******************************************************************************************************************
void cStatePlayGame::VOnExit()
{
	m_pHUDScreen.reset();
	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("HUD");
	}
	EventListenerCallBackFn listener = bind(&cStatePlayGame::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);
}