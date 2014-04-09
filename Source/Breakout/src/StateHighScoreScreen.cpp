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
#include "Score.h"

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

		shared_ptr<Graphics::IBaseControl> pLabelNameTemplate = m_pHighScoreScreen->VFindChildControl("LabelNameTemplate");
		shared_ptr<Graphics::IBaseControl> pScoreNameTemplate = m_pHighScoreScreen->VFindChildControl("LabelScoreTemplate");

		IHighScoreTable::ScoreSet highScores = pGame->m_pHighScoreTable->VGetScores();
		int index = 0;
		
		if(pGame->m_pHighScoreTable->VIsAscendingOrder())
		{
			for(IHighScoreTable::ScoreSet::reverse_iterator iter = highScores.rbegin(); iter != highScores.rend(); iter++)
			{
				DisplayScore(*iter, index);
				index++;
			}
		}
		else
		{
			for(IHighScoreTable::ScoreSet::iterator iter = highScores.begin(); iter != highScores.end(); iter++)
			{
				DisplayScore(*iter, index);
				index++;
			}
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
void cStateHighScoreScreen::DisplayScore(const shared_ptr<const cScore> pScore, const int Index)
{
	int posY = 220 + (40 * Index);

	cLabelControlDef def;
	def.strControlName = cString(50, "Name%d", Index);
	def.strFont = "licorice"; 
	def.textColor = cColor::TURQUOISE;
	def.strText = pScore->GetPlayerName();
	def.fTextHeight = 30;
	def.vPosition = cVector2(0.0f, posY);
	def.vSize = cVector2(200.0f, 30.0f);
	IBaseControl * pNameControl = IBaseControl::CreateLabelControl(def);
	m_pHighScoreScreen->VAddChildControl(shared_ptr<IBaseControl>(pNameControl));

	def.strControlName = cString(50, "Score%d", Index);
	int hour, minutes, seconds;
	GetTimeAsHHMMSS(pScore->GetScore(), hour, minutes, seconds);
	def.strText = cString(30, "%02d : %02d : %02d", hour, minutes, seconds);
	def.vPosition = cVector2(250.0f, posY);
	IBaseControl * pScoreControl = IBaseControl::CreateLabelControl(def);
	m_pHighScoreScreen->VAddChildControl(shared_ptr<IBaseControl>(pScoreControl));
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
