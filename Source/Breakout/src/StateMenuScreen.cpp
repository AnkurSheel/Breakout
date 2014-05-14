//  *******************************************************************************************************************
//  StateMenuScreen   version:  1.0   Ankur Sheel  date: 2013/02/24
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "StateMenuScreen.h"
#include "Game.h"
#include "HumanView.h"
#include "ControlStructures.h"
#include "BaseControl.hxx"
#include "GameFlowStateMachine.h"
#include "StatePlayGame.h"
#include "StateHelpScreen.h"
#include "StateOptionScreen.h"
#include "StateHighScoreScreen.h"
//#include "RedefineControlsScreen.h"
#include "EventManager.hxx"
#include "UiManager.hxx"
#include "EscapePressedEventData.h"
#include "StateRedefineControlsScreen.h"


using namespace Base;
using namespace Graphics;
using namespace GameBase;
using namespace AI;

//  *******************************************************************************************************************
cStateMenuScreen::cStateMenuScreen()
	: m_pMenuScreen(NULL)
{
}

//  *******************************************************************************************************************
cStateMenuScreen::~cStateMenuScreen()
{
}

//  *******************************************************************************************************************
cStateMenuScreen* cStateMenuScreen::Instance()
{
	static cStateMenuScreen instance;
	return &instance;
}

//  *******************************************************************************************************************
void cStateMenuScreen::VOnEnter(cGame *pGame)
{
	cGameFlowStates::VOnEnter(pGame);

	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pMenuScreen = IUiManager::GetInstance()->VCreateUI("menuscreen");
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(m_pMenuScreen);

		shared_ptr<Graphics::IBaseControl> pPlayButton = m_pMenuScreen->VFindChildControl("btnPlay");
		if(pPlayButton != NULL)
		{
			UIEventCallBackFn callbackPlayBtn = bind(&cStateMenuScreen::PlayButtonPressed, this, _1);
			pPlayButton->VRegisterCallBack(UIET_BTNRELEASED, callbackPlayBtn);
		}

		shared_ptr<Graphics::IBaseControl> pHelpButton = m_pMenuScreen->VFindChildControl("btnHelp");
		if(pHelpButton != NULL)
		{
			UIEventCallBackFn callbackHelpBtn = bind(&cStateMenuScreen::HelpButtonPressed, this, _1);
			pHelpButton->VRegisterCallBack(UIET_BTNRELEASED, callbackHelpBtn);
		}
		
		shared_ptr<Graphics::IBaseControl> pOptionsButton = m_pMenuScreen->VFindChildControl("btnOption");
		if(pOptionsButton != NULL)
		{
			UIEventCallBackFn callbackOptionsBtn = bind(&cStateMenuScreen::OptionsButtonPressed, this, _1);
			pOptionsButton->VRegisterCallBack(UIET_BTNRELEASED, callbackOptionsBtn);
		}

		shared_ptr<Graphics::IBaseControl> pRedefineControlsButton = m_pMenuScreen->VFindChildControl("btnControls");
		if(pRedefineControlsButton != NULL)
		{
			UIEventCallBackFn callbackRedefineControlsBtn = bind(&cStateMenuScreen::ControlsButtonPressed, this, _1);
			pRedefineControlsButton->VRegisterCallBack(UIET_BTNRELEASED, callbackRedefineControlsBtn);
		}

		shared_ptr<Graphics::IBaseControl> pHighScoreButton = m_pMenuScreen->VFindChildControl("btnHighScore");
		if(pHighScoreButton != NULL)
		{
			UIEventCallBackFn callbackHighScoreBtn = bind(&cStateMenuScreen::HighScoreButtonPressed, this, _1);
			pHighScoreButton->VRegisterCallBack(UIET_BTNRELEASED, callbackHighScoreBtn);
		}
		shared_ptr<Graphics::IBaseControl> pQuitButton = m_pMenuScreen->VFindChildControl("btnQuit");
		if(pQuitButton != NULL)
		{
			UIEventCallBackFn callbackQuitBtn = bind(&cStateMenuScreen::QuitButtonPressed, this, _1);
			pQuitButton->VRegisterCallBack(UIET_BTNRELEASED, callbackQuitBtn);
		}
	}

	EventListenerCallBackFn listener = bind(&cStateMenuScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEscapePressedEventData::m_Name);
}

//  *******************************************************************************************************************
void cStateMenuScreen::VOnUpdate(const TICK currentTick, const float deltaTime)
{
}

//  *******************************************************************************************************************
void cStateMenuScreen::VOnExit()
{
	m_pMenuScreen.reset();
	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("menuscreen");
	}
	EventListenerCallBackFn listener = bind(&cStateMenuScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);
}

//  *******************************************************************************************************************
void cStateMenuScreen::VOnPause()
{
	cGameFlowStates::VOnPause();
	if (m_pMenuScreen != NULL)
	{
		m_pMenuScreen->VSetVisible(false);
	}
}

//  *******************************************************************************************************************
void cStateMenuScreen::VOnResume()
{
	cGameFlowStates::VOnResume();
	if (m_pMenuScreen != NULL)
	{
		m_pMenuScreen->VSetVisible(true);
	}
}

//  *******************************************************************************************************************
void cStateMenuScreen::PlayButtonPressed(const stUIEventCallbackParam & params)
{
	if (m_pOwner && m_pOwner->m_pStateMachine)
	{
		m_pOwner->m_pStateMachine->RequestChangeState(cStatePlayGame::Instance());
	}
}

//  *******************************************************************************************************************
void cStateMenuScreen::ControlsButtonPressed(const stUIEventCallbackParam & params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->m_pStateMachine->RequestPushState(cStateRedefineControlsScreen::Instance());
	}
}

//  *******************************************************************************************************************
void cStateMenuScreen::HelpButtonPressed(const stUIEventCallbackParam & params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->m_pStateMachine->RequestPushState(cStateHelpScreen::Instance());
	}
}

//  *******************************************************************************************************************
void cStateMenuScreen::OptionsButtonPressed(const stUIEventCallbackParam & params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->m_pStateMachine->RequestPushState(cStateOptionsScreen::Instance());
	}
}

//  *******************************************************************************************************************
void cStateMenuScreen::HighScoreButtonPressed(const stUIEventCallbackParam & params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->m_pStateMachine->RequestChangeState(cStateHighScoreScreen::Instance());
	}
}

//  *******************************************************************************************************************
void cStateMenuScreen::QuitButtonPressed(const stUIEventCallbackParam & params)
{
	PostQuitMessage(0);
}
