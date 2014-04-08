//  *******************************************************************************************************************
//  StateHighScoreScreen   version:  1.0   Ankur Sheel  date: 2013/03/20
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "StateHighScoreScreen.h"
#include "Game.h"
#include "HumanView.h"
#include "UiManager.hxx"
#include "BaseControl.hxx"
#include "EventManager.hxx"
#include "EscapePressedEventData.h"
#include "GameFlowStateMachine.h"
#include "HighScoreTable.hxx"

using namespace Base;
using namespace Graphics;
using namespace GameBase;
using namespace AI;

cStateHighScoreScreen::cStateHighScoreScreen()
	: m_pHighScoreScreen(NULL)
{
}

//  *******************************************************************************************************************
cStateHighScoreScreen::~cStateHighScoreScreen()
{
}

//  *******************************************************************************************************************
cStateHighScoreScreen* cStateHighScoreScreen::Instance()
{
	static cStateHighScoreScreen instance;
	return &instance;
}

//  *******************************************************************************************************************
void cStateHighScoreScreen::VOnEnter(cGame *pGame)
{
	cGameFlowStates::VOnEnter(pGame);

	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pHighScoreScreen = IUiManager::GetInstance()->VCreateUI("highscorescreen");
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(m_pHighScoreScreen);
		pGame->m_pHumanView->m_pAppWindowControl->VMoveToFront(m_pHighScoreScreen.get());

		IHighScoreTable::ScoreSet highScores = pGame->m_pHighScoreTable->VGetScores();
		IHighScoreTable::ScoreSet::iterator iter;
		int i = 0;
		int currentPosY = 220;
		for(iter = highScores.begin(); iter != highScores.end(); iter++)
		{
			shared_ptr<cScore> pScore = (*iter);

			//def.strControlName = cString(100, "Name%d", i);
			//def.strFont = "licorice"; 
			//def.textColor = cColor::BLUE;
			//def.strText = pScore->GetPlayerName();
			//def.fTextHeight = 30;
			//def.vPosition = cVector2(0.0f, currentPosY);
			//def.vSize = cVector2(200.0f, 30.0f);
			//IBaseControl * pNameControl = IBaseControl::CreateLabelControl(def);
			//pHighScoreScreen->VAddChildControl(shared_ptr<IBaseControl>(pNameControl));

			//def.strControlName = cString(100, "Score%d", i);
			//def.strText = cString(50, "%d",pScore->GetScore());
			//def.vPosition = cVector2(250.0f, currentPosY);
			//IBaseControl * pScoreControl = IBaseControl::CreateLabelControl(def);
			//pHighScoreScreen->VAddChildControl(shared_ptr<IBaseControl>(pScoreControl));

			//i++;
			//currentPosY += 40;
		}
	}

	shared_ptr<Graphics::IBaseControl> pBackButton= m_pHighScoreScreen->VFindChildControl("btnBack");
	if(pBackButton != NULL)
	{
		UIEventCallBackFn callbackBackBtn = bind(&cStateHighScoreScreen::BackButtonPressed, this, _1);
		pBackButton->VRegisterCallBack(UIET_BTNRELEASED, callbackBackBtn);
	}

	EventListenerCallBackFn listener = bind(&cStateHighScoreScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEscapePressedEventData::m_Name);
}

//  *******************************************************************************************************************
void cStateHighScoreScreen::VOnUpdate(const TICK currentTick, const float deltaTime)
{

}

//  *******************************************************************************************************************
void cStateHighScoreScreen::VOnExit()
{
	m_pHighScoreScreen.reset();
	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("highscorescreen");
	}

	EventListenerCallBackFn listener = bind(&cStateHighScoreScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);
}

//  *******************************************************************************************************************
void cStateHighScoreScreen::BackButtonPressed(const stUIEventCallbackParam & params)
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
void cStateHighScoreScreen::EscapePressedListener(IEventDataPtr pEventData)
{
	stUIEventCallbackParam params;
	BackButtonPressed(params);
}
