// *****************************************************************************
//  StatePlayGame   version:  1.0   Ankur Sheel  date: 2013/03/20
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "StatePlayGame.h"
#include "BaseEntity.hxx"
#include "ModelComponent.h"
#include "EntityManager.hxx"
#include "Paddle.h"

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
	IBaseEntity * pPaddle = DEBUG_NEW cPaddle("paddle");
	cModelComponent * pModelComponent = DEBUG_NEW cModelComponent();
	pModelComponent->m_strModelName = "cube";
	IEntityManager::GetInstance()->VRegisterEntity(pPaddle);
	IEntityManager::GetInstance()->VAddComponent(pPaddle, pModelComponent);

}

// *****************************************************************************
void cStatePlayGame::VOnUpdate()
{

}

// *****************************************************************************
void cStatePlayGame::VOnExit()
{

}

// *****************************************************************************
bool cStatePlayGame::VOnMessage(const Telegram &msg)
{
	return false;
}
