// *****************************************************************************
//  StatePlayGame   version:  1.0   Ankur Sheel  date: 2013/03/20
// *****************************************************************************
//  purpose:	
// *****************************************************************************
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

using namespace Base;
using namespace GameBase;
using namespace AI;

// *****************************************************************************
cStatePlayGame::cStatePlayGame()
{
}

// *****************************************************************************
cStatePlayGame::~cStatePlayGame()
{
}

// *****************************************************************************
cStatePlayGame* cStatePlayGame::Instance()
{
	static cStatePlayGame instance;
	return &instance;
}

// *****************************************************************************
void cStatePlayGame::VOnEnter(cGame *pGame)
{
	IGameFlowStates::VOnEnter(pGame);
	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cRenderSystem()));
	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cInputSystem()));
	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cPhysicsSystem()));

	pGame->m_pConfig = DEBUG_NEW cConfig();
	pGame->m_pConfig->Initialize("Entities");
	cLevel::Level.Initialize("level1");

	IEntityManager::GetInstance()->VAddEntity("paddle");
	IEntityManager::GetInstance()->VAddEntity("ball");

	EventListenerCallBackFn listener = bind(&cStatePlayGame::EscapePressedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEscapePressedEventData::m_Name);
}

// *****************************************************************************
void cStatePlayGame::VOnUpdate()
{
	if(m_pOwner != NULL && m_pOwner->m_pGameTimer != NULL)
	{
		IEntityManager::GetInstance()->VUpdate(m_pOwner->m_pGameTimer->VGetDeltaTime());
		m_pOwner->m_pHumanView->VOnUpdate(m_pOwner->m_pGameTimer->VGetRunningTicks(), m_pOwner->m_pGameTimer->VGetDeltaTime());
	}
}

// *****************************************************************************
void cStatePlayGame::VOnExit()
{
	EventListenerCallBackFn listener = bind(&cStatePlayGame::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);
}

// *****************************************************************************
bool cStatePlayGame::VOnMessage(const Telegram & msg)
{
	return false;
}

// *****************************************************************************
void cStatePlayGame::EscapePressedListener(IEventDataPtr pEventData)
{
	PostQuitMessage(0);
}
