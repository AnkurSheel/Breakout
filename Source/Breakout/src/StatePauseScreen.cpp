//  *******************************************************************************************************************
//  StatePauseScreen   version:  1.0   Ankur Sheel  date: 2013/03/20
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "StatePauseScreen.h"
#include "Game.h"
#include "HumanView.h"
#include "UiManager.hxx"
#include "BaseControl.hxx"
//#include "OptionScreen.h"
//#include "HelpScreen.h"
#include "EventManager.hxx"
#include "EscapePressedEventData.h"
#include "GameFlowStateMachine.h"
#include "StateOptionScreen.h"

using namespace Base;
using namespace Graphics;
using namespace GameBase;
using namespace AI;

cStatePauseScreen::cStatePauseScreen()
	: m_pPauseScreen(NULL)
{
}

//  *******************************************************************************************************************
cStatePauseScreen::~cStatePauseScreen()
{
}

//  *******************************************************************************************************************
cStatePauseScreen* cStatePauseScreen::Instance()
{
	static cStatePauseScreen instance;
	return &instance;
}

//  *******************************************************************************************************************
void cStatePauseScreen::VOnEnter(cGame *pGame)
{
	cGameFlowStates::VOnEnter(pGame);

	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pPauseScreen = IUiManager::GetInstance()->VCreateUI("pausescreen");
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(m_pPauseScreen);
		pGame->m_pHumanView->m_pAppWindowControl->VMoveToFront(m_pPauseScreen.get());
	}

	shared_ptr<Graphics::IBaseControl> pOptionsButton= m_pPauseScreen->VFindChildControl("btnOptions");
	if(pOptionsButton != NULL)
	{
		UIEventCallBackFn callbackOptionsBtn = bind(&cStatePauseScreen::OptionsButtonPressed, this, _1);
		pOptionsButton->VRegisterCallBack(UIET_BTNRELEASED, callbackOptionsBtn);
	}
	
	shared_ptr<Graphics::IBaseControl> pHelpButton= m_pPauseScreen->VFindChildControl("btnHelp");
	if(pHelpButton != NULL)
	{
		UIEventCallBackFn callbackHelpBtn = bind(&cStatePauseScreen::HelpButtonPressed, this, _1);
		pHelpButton->VRegisterCallBack(UIET_BTNRELEASED, callbackHelpBtn);
	}

	shared_ptr<Graphics::IBaseControl> pQuitButton= m_pPauseScreen->VFindChildControl("btnQuit");
	if(pQuitButton != NULL)
	{
		UIEventCallBackFn callbackQuitBtn = bind(&cStatePauseScreen::QuitButtonPressed, this, _1);
		pQuitButton->VRegisterCallBack(UIET_BTNRELEASED, callbackQuitBtn);
	}

	shared_ptr<Graphics::IBaseControl> pBackButton= m_pPauseScreen->VFindChildControl("btnBack");
	if(pBackButton != NULL)
	{
		UIEventCallBackFn callbackBackBtn = bind(&cStatePauseScreen::BackButtonPressed, this, _1);
		pBackButton->VRegisterCallBack(UIET_BTNRELEASED, callbackBackBtn);
	}

	EventListenerCallBackFn listener = bind(&cStatePauseScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEscapePressedEventData::m_Name);
}

//  *******************************************************************************************************************
void cStatePauseScreen::VOnUpdate(const TICK currentTick, const float deltaTime)
{

}

//  *******************************************************************************************************************
void cStatePauseScreen::VOnExit()
{
	m_pPauseScreen.reset();
	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("PauseScreen");
	}

	EventListenerCallBackFn listener = bind(&cStatePauseScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);
}

//  *******************************************************************************************************************
void cStatePauseScreen::VOnPause()
{
	cGameFlowStates::VOnPause();
	if (m_pPauseScreen != NULL)
	{
		m_pPauseScreen->VSetVisible(false);
	}
}

//  *******************************************************************************************************************
void cStatePauseScreen::VOnResume()
{
	cGameFlowStates::VOnResume();
	if (m_pPauseScreen != NULL)
	{
		m_pPauseScreen->VSetVisible(true);
	}
}

//  *******************************************************************************************************************
void cStatePauseScreen::BackButtonPressed(const stUIEventCallbackParam & params)
{
	if(m_pOwner != NULL)
	{
		if(m_pOwner->m_pStateMachine != NULL)
		{
			m_pOwner->m_pStateMachine->RequestPopState();
		}
	}
}
//  *******************************************************************************************************************
void cStatePauseScreen::OptionsButtonPressed(const Graphics::stUIEventCallbackParam& params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->m_pStateMachine->RequestPushState(cStateOptionsScreen::Instance());
	}
}

//  *******************************************************************************************************************
void cStatePauseScreen::HelpButtonPressed(const Graphics::stUIEventCallbackParam& params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		//m_pOwner->m_pStateMachine->RequestPushState(cStateHelpScreen::Instance());
	}
}

//  *******************************************************************************************************************
void cStatePauseScreen::QuitButtonPressed(const Graphics::stUIEventCallbackParam& params)
{
	PostQuitMessage(0);
}

//  *******************************************************************************************************************
void cStatePauseScreen::EscapePressedListener(IEventDataPtr pEventData)
{
	stUIEventCallbackParam params;
	BackButtonPressed(params);
}
