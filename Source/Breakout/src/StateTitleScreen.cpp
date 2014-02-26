//  *******************************************************************************************************************
//  StateTitleScreen   version:  1.0   Ankur Sheel  date: 2013/03/20
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
#include "GameFlowStateMachine.h"
#include "StateMenuScreen.h"

using namespace Base;
using namespace Graphics;
using namespace GameBase;
using namespace AI;
using namespace Utilities;

//  *******************************************************************************************************************
cStateTitleScreen::cStateTitleScreen()
	: m_DelayTime(0.0f)
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
	cGameFlowStates::VOnEnter(pGame);

	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pTitleScreen = IUiManager::GetInstance()->VCreateUI("titlescreen");
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(m_pTitleScreen);
		m_Position = cVector2(0.0f, m_pOwner->m_iDisplayHeight);
	}

	EventListenerCallBackFn listener = bind(&cStateTitleScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEscapePressedEventData::m_Name);
	m_DelayTime = 2.0f;
}

//  *******************************************************************************************************************
void cStateTitleScreen::VOnUpdate(const TICK currentTick, const float deltaTime)
{
	if(m_DelayTime > 0.0f)
	{
		m_DelayTime -= deltaTime;
		m_pTitleScreen->VSetPosition(cVector2::Lerp(cVector2(0.0f, 0.0f), m_Position, m_DelayTime/2.0f));

		if(m_DelayTime <= 0.0f)
		{
			m_pOwner->m_pStateMachine->RequestChangeState(cStateMenuScreen::Instance());
		}
	}
}

//  *******************************************************************************************************************
void cStateTitleScreen::VOnExit()
{
	m_pTitleScreen.reset();
	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("TitleScreen");
	}
	EventListenerCallBackFn listener = bind(&cStateTitleScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);
}