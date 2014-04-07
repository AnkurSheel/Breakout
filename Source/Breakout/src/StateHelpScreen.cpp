#include "stdafx.h"
#include "StateHelpScreen.h"
#include "Game.h"
#include "HumanView.h"
#include "UiManager.hxx"
#include "BaseControl.hxx"
#include "GameFlowStateMachine.h"
#include "EventManager.hxx"
#include "EscapePressedEventData.h"

using namespace Base;
using namespace Graphics;
using namespace GameBase;
using namespace AI;

//  *******************************************************************************************************************
cStateHelpScreen::cStateHelpScreen()
{
}

//  *******************************************************************************************************************
cStateHelpScreen::~cStateHelpScreen()
{
}

//  *******************************************************************************************************************
cStateHelpScreen* cStateHelpScreen::Instance()
{
	static cStateHelpScreen instance;
	return &instance;
}

//  *******************************************************************************************************************
void cStateHelpScreen::VOnEnter(cGame *pGame)
{
	cGameFlowStates::VOnEnter(pGame);

	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pHelpScreen = IUiManager::GetInstance()->VCreateUI("helpscreen");
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(m_pHelpScreen);
		pGame->m_pHumanView->m_pAppWindowControl->VMoveToFront(m_pHelpScreen.get());

		shared_ptr<Graphics::IBaseControl> pBackButton= m_pHelpScreen->VFindChildControl("btnBack");
		if(pBackButton != NULL)
		{
			UIEventCallBackFn callbackBackBtn = bind(&cStateHelpScreen::BackButtonPressed, this, _1);
			pBackButton->VRegisterCallBack(UIET_BTNRELEASED, callbackBackBtn);
		}

		EventListenerCallBackFn listener = bind(&cStateHelpScreen::EscapePressedListener, this, _1);
		IEventManager::Instance()->VAddListener(listener, cEscapePressedEventData::m_Name);
	}
}

//  *******************************************************************************************************************
void cStateHelpScreen::VOnUpdate(const TICK currentTick, const float deltaTime)
{

}

//  *******************************************************************************************************************
void cStateHelpScreen::VOnExit()
{
	m_pHelpScreen.reset();
	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("helpscreen");
	}
	EventListenerCallBackFn listener = bind(&cStateHelpScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);
}

//  *******************************************************************************************************************
void cStateHelpScreen::BackButtonPressed(const stUIEventCallbackParam & params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->m_pStateMachine->RequestPopState();
	}
}

//  *******************************************************************************************************************
void cStateHelpScreen::EscapePressedListener(IEventDataPtr pEventData)
{
	stUIEventCallbackParam params;
	BackButtonPressed(params);
}