#include "stdafx.h"
#include "StateEnterNameScreen.h"
#include "Game.h"
#include "HumanView.h"
#include "UiManager.hxx"
#include "BaseControl.hxx"
#include "GameFlowStateMachine.h"
#include "EventManager.hxx"
#include "EscapePressedEventData.h"
#include "StateTitleScreen.h"
#include "HighScoreTable.hxx"
#include "Score.h"

using namespace Base;
using namespace Graphics;
using namespace GameBase;
using namespace AI;

// ***********************************************************************************************************************************************************
cStateEnterNameScreen::cStateEnterNameScreen()
	: m_NewScore(0)
{
}

// ***********************************************************************************************************************************************************
cStateEnterNameScreen::~cStateEnterNameScreen()
{

}

// ********************************************************************************************************************
cStateEnterNameScreen * cStateEnterNameScreen::Instance()
{
	static cStateEnterNameScreen instance;
	return &instance;
}

// ********************************************************************************************************************
void cStateEnterNameScreen::VOnEnter(cGame * pGame)
{
	cGameFlowStates::VOnEnter(pGame);

	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pEnterNameScreen = IUiManager::GetInstance()->VCreateUI("enternamescreen");
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(m_pEnterNameScreen);
		pGame->m_pHumanView->m_pAppWindowControl->VMoveToFront(m_pEnterNameScreen.get());

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

	shared_ptr<Graphics::IBaseControl> pBackButton= m_pEnterNameScreen->VFindChildControl("btnBack");
	if(pBackButton != NULL)
	{
		UIEventCallBackFn callbackBackBtn = bind(&cStateEnterNameScreen::BackButtonPressed, this, _1);
		pBackButton->VRegisterCallBack(UIET_BTNRELEASED, callbackBackBtn);
	}

	EventListenerCallBackFn listener = bind(&cStateEnterNameScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEscapePressedEventData::m_Name);
}

// ********************************************************************************************************************
void cStateEnterNameScreen::VOnUpdate(const TICK currentTick, const float deltaTime)
{
}

// ********************************************************************************************************************
void cStateEnterNameScreen::VOnExit()
{
	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("EnterNameScreen");
	}

	EventListenerCallBackFn listener = bind(&cStateEnterNameScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);
}

// ********************************************************************************************************************
void cStateEnterNameScreen::BackButtonPressed(const Graphics::stUIEventCallbackParam & params)
{
	if(m_NewScorePos.IsValid())
	{
		shared_ptr<cScore> pScore(DEBUG_NEW cScore());
		pScore->SetPlayerName(m_PlayerName);
		pScore->SetScore(m_NewScore);
		m_pOwner->m_pHighScoreTable->VAddNewScore(pScore);
		m_pOwner->m_pHighScoreTable->VSave();
	}
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->m_pStateMachine->RequestChangeState(cStateTitleScreen::Instance());
	}
}

//  *******************************************************************************************************************
void cStateEnterNameScreen::EscapePressedListener(IEventDataPtr pEventData)
{
	stUIEventCallbackParam params;
	BackButtonPressed(params);
}

//  *******************************************************************************************************************
void cStateEnterNameScreen::NameEntered(const Graphics::stUIEventCallbackParam & params)
{
	m_PlayerName = params.strText;
}

//  *******************************************************************************************************************
void cStateEnterNameScreen::DisplayScore(const shared_ptr<const cScore> pScore, const int index)
{
	int posY = 220 + (40 * index);

	if (m_NewScorePos.IsValid() && index == *m_NewScorePos)
	{
		shared_ptr<Graphics::IBaseControl> ptbNewHighScoreName = m_pEnterNameScreen->VFindChildControl("tbNewHighScoreName");
		ptbNewHighScoreName->VSetPosition(cVector2(0.0f, posY));
		ptbNewHighScoreName->VSetVisible(true);
		UIEventCallBackFn callBackTextBox;
		callBackTextBox = bind(&cStateEnterNameScreen::NameEntered, this, _1);
		ptbNewHighScoreName->VRegisterCallBack(UIET_FOCUSLOST, callBackTextBox);

		int hour, minutes, seconds;
		GetTimeAsHHMMSS(m_NewScore, hour, minutes, seconds);
		AddScoreLabel(index, cString(30, "%02d : %02d : %02d", hour, minutes, seconds), posY);
	}
	else
	{
		cLabelControlDef def;
		def.strControlName = cString(50, "Name%d", index);
		def.strFont = "licorice"; 
		def.textColor = cColor::TURQUOISE;
		def.strText = pScore->GetPlayerName();
		def.fTextHeight = 30;
		def.vPosition = cVector2(0.0f, posY);
		def.vSize = cVector2(200.0f, 30.0f);
		IBaseControl * pNameControl = IBaseControl::CreateLabelControl(def);
		m_pEnterNameScreen->VAddChildControl(shared_ptr<IBaseControl>(pNameControl));

		int hour, minutes, seconds;
		GetTimeAsHHMMSS(pScore->GetScore(), hour, minutes, seconds);
		AddScoreLabel(index, cString(30, "%02d : %02d : %02d", hour, minutes, seconds), posY);
	}
}

//  *******************************************************************************************************************
void cStateEnterNameScreen::AddScoreLabel(const int index, const Base::cString & score, const int posY)
{
	cLabelControlDef def;
	def.strFont = "licorice"; 
	def.textColor = cColor::TURQUOISE;
	def.fTextHeight = 30;
	def.vSize = cVector2(200.0f, 30.0f);
	def.strControlName = cString(50, "Score%d", index);
	
	def.strText = score;
	def.vPosition = cVector2(250.0f, posY);
	IBaseControl * pScoreControl = IBaseControl::CreateLabelControl(def);
	
	m_pEnterNameScreen->VAddChildControl(shared_ptr<IBaseControl>(pScoreControl));
}
