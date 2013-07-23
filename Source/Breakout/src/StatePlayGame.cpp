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
	pGame->m_pConfig = DEBUG_NEW cConfig();
	pGame->m_pConfig->Initialize("Entities");
	cLevel::Level.Initialize("level1");

	IEntityManager::GetInstance()->VRegisterEntity("paddle");
	IEntityManager::GetInstance()->VRegisterEntity("ball");
	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cRenderSystem()));
	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cInputSystem()));
	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cPhysicsSystem()));
}

// *****************************************************************************
void cStatePlayGame::VOnUpdate()
{
	IEntityManager::GetInstance()->VUpdate();
	if(m_pOwner != NULL && m_pOwner->m_pGameTimer != NULL)
	{
		m_pOwner->m_pHumanView->VOnUpdate(m_pOwner->m_pGameTimer->VGetRunningTicks(), m_pOwner->m_pGameTimer->VGetDeltaTime());
	}
}

// *****************************************************************************
void cStatePlayGame::VOnExit()
{

}

// *****************************************************************************
bool cStatePlayGame::VOnMessage(const Telegram & msg)
{
	if(msg.Msg == MSG_ESCAPE_PRESSED)
	{
		PostQuitMessage(0);
		return true;
	}
	return false;
}