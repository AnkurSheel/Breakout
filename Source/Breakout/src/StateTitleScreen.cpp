//  *******************************************************************************************************************
//  TitleScreen   version:  1.0   Ankur Sheel  date: 2013/03/20
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#include "stdafx.h"
#include "StateTitleScreen.h"
#include "Game.h"
#include "HumanView.h"
#include "ControlStructures.h"
#include "BaseControl.hxx"
#include "Color.h"
#include "EventManager.hxx"
#include "EscapePressedEventData.h"
#include "UiManager.hxx"

using namespace Base;
using namespace Graphics;
using namespace GameBase;
using namespace AI;
using namespace Utilities;

//  *******************************************************************************************************************
cStateTitleScreen::cStateTitleScreen()
{
}

//  *******************************************************************************************************************
cStateTitleScreen::~cStateTitleScreen()
{
}

//  *******************************************************************************************************************
cStateTitleScreen* cStateTitleScreen::Instance()
{
	static cStateTitleScreen instance;
	return &instance;
}

//  *******************************************************************************************************************
void cStateTitleScreen::VOnEnter(cGame *pGame)
{
	IGameFlowStates::VOnEnter(pGame);

	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		const shared_ptr<IBaseControl> pTitleScreen = IUiManager::GetInstance()->VCreateUI("titlescreen");
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(pTitleScreen);
	}

	EventListenerCallBackFn listener = bind(&cStateTitleScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEscapePressedEventData::m_Name);

	//IMessageDispatchManager::GetInstance()->VDispatchMessage(2.0f, pGame->VGetID(), pGame->VGetID(), MSG_SHOW_MENU, NULL);
}

//  *******************************************************************************************************************
void cStateTitleScreen::VOnUpdate()
{
}

//  *******************************************************************************************************************
void cStateTitleScreen::VOnExit()
{
	EventListenerCallBackFn listener = bind(&cStateTitleScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);
}

//  *******************************************************************************************************************
bool cStateTitleScreen::VOnMessage(const Telegram &msg)
{
	//if(msg.Msg == MSG_SHOW_MENU)
	//{
	//	m_pOwner->m_pStateMachine->RequestChangeState(cStateMenuScreen::Instance());
	//	return true;
	//}
	return false;
}

//  *******************************************************************************************************************
void cStateTitleScreen::EscapePressedListener(IEventDataPtr pEventData)
{
	m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("TitleScreen");
	PostQuitMessage(0);
}
