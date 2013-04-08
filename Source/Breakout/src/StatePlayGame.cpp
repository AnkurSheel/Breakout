// *****************************************************************************
//  StatePlayGame   version:  1.0   Ankur Sheel  date: 2013/03/20
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "StatePlayGame.h"
#include "BaseEntity.hxx"
#include "EntityManager.hxx"
#include "Paddle.h"
#include "ModelComponent.h"
#include "TransformComponent.h"
#include "Game.h"
#include "ProcessManager.hxx"
#include "Render3DSystem.h"
#include "GraphicUtils.hxx"
#include "vector2.h"
#include "HumanView.h"

using namespace Base;
using namespace GameBase;
using namespace AI;
using namespace Graphics;

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
	IEntityManager::GetInstance()->VRegisterEntity(pPaddle);
	
	cModelComponent * pModelComponent = DEBUG_NEW cModelComponent();
	pModelComponent->m_strModelName = "cube";
	IEntityManager::GetInstance()->VAddComponent(pPaddle, pModelComponent);

	cVector3 vScreenBottomRightPos = IGraphicUtils::GetInstance()->ScreenToWorldSpace(cVector2(static_cast<float>(pGame->m_iDisplayWidth), static_cast<float>(pGame->m_iDisplayHeight)),
		pGame->m_pHumanView->GetCamera());
	cTransformComponent * pTransformComponent = DEBUG_NEW cTransformComponent();
	pTransformComponent->m_vPosition = cVector3(0, vScreenBottomRightPos.y, 0.0f);
	pTransformComponent->m_vScale = cVector3(2.0f, 0.25f, 1.0f);
	IEntityManager::GetInstance()->VAddComponent(pPaddle, pTransformComponent);

	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cRender3DSystem()));

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