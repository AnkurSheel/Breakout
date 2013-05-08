// *****************************************************************************
//  StatePlayGame   version:  1.0   Ankur Sheel  date: 2013/03/20
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "StatePlayGame.h"
//#include "BaseEntity.hxx"
#include "EntityManager.hxx"
//#include "ModelComponent.h"
//#include "Transform3DComponent.h"
//#include "Transform2DComponent.h"
#include "Game.h"
#include "ProcessManager.hxx"
#include "Render2DSystem.h"
//#include "Render3DSystem.h"
//#include "Render2DSystem.h"
//#include "GraphicUtils.hxx"
//#include "vector2.h"
//#include "HumanView.h"
//#include "SpriteComponent.h"

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
	IEntityManager::GetInstance()->VRegisterEntity("paddle");
	//
	//cModelComponent * pModelComponent = DEBUG_NEW cModelComponent();
	//pModelComponent->m_strModelName = "cube";
	//IEntityManager::GetInstance()->VAddComponent(pPaddle, pModelComponent);

	//cVector3 vScreenBottomRightPos = IGraphicUtils::GetInstance()->ScreenToWorldSpace(cVector2(static_cast<float>(pGame->m_iDisplayWidth), static_cast<float>(pGame->m_iDisplayHeight)),
	//	pGame->m_pHumanView->GetCamera());
	//cTransform3DComponent * pTransformComponent = DEBUG_NEW cTransform3DComponent();
	//pTransformComponent->m_vPosition = cVector3(0, vScreenBottomRightPos.y, 0.0f);
	//pTransformComponent->m_vScale = cVector3(2.0f, 0.25f, 1.0f);
	//IEntityManager::GetInstance()->VAddComponent(pPaddle, pTransformComponent);

	//m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cRender3DSystem()));

	////

	//IBaseEntity * pPaddle1 = DEBUG_NEW cPaddle("paddle2");
	//IEntityManager::GetInstance()->VRegisterEntity(pPaddle1);
	//
	//cSpriteComponent * pSpriteComponent = DEBUG_NEW cSpriteComponent();
	//pSpriteComponent->m_strSpriteName = "cursor.png";
	//IEntityManager::GetInstance()->VAddComponent(pPaddle1, pSpriteComponent);

	//cTransform2DComponent * pTransform2DComponent = DEBUG_NEW cTransform2DComponent();
	//pTransform2DComponent->m_vPosition = cVector2(0, 0);
	//pTransform2DComponent->m_vSize = cVector2(100, 100);
	//IEntityManager::GetInstance()->VAddComponent(pPaddle1, pTransform2DComponent);

	m_pOwner->VGetProcessManager()->VAttachProcess(shared_ptr<Utilities::cProcess>(DEBUG_NEW cRender2DSystem()));

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