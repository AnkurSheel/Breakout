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
#include "StateTitleScreen.h"

using namespace Base;
using namespace Graphics;
using namespace GameBase;
using namespace AI;

cStateHighScoreScreen::cStateHighScoreScreen()
	: m_pHighScoreScreen(NULL)
	, m_pLabelNameTemplate(NULL)
	, m_pLabelScoreTemplate(NULL)
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

		m_pLabelNameTemplate = m_pHighScoreScreen->VFindChildControl("LabelNameTemplate");
		m_pLabelScoreTemplate = m_pHighScoreScreen->VFindChildControl("LabelScoreTemplate");

		if(m_NewScore.IsValid())
		{
			m_NewScorePos.clear();
			tOptional<int> scorePos = m_pOwner->m_pHighScoreTable->VGetScorePositionInTable(m_NewScore.GetValue());
			if(scorePos.IsValid())
			{
				SetNewScorePos(scorePos.GetValue());
			}
		}
		IHighScoreTable::ScoreSet highScores = pGame->m_pHighScoreTable->VGetScores();
		int index = 0;
		if(pGame->m_pHighScoreTable->VIsAscendingOrder())
		{
			for(auto iter = highScores.rbegin(); iter != highScores.rend(); iter++)
			{
				DisplayScore(*iter, index);
				index++;
			}
		}
		else
		{
			for(auto iter = highScores.begin(); iter != highScores.end(); iter++)
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
		pBackButton->VRegisterCallBack(UIEVENTTYPE::BUTTONRELEASED, callbackBackBtn);
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
	m_pLabelNameTemplate.reset();
	m_pLabelScoreTemplate.reset();

	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("highscorescreen");
	}

	EventListenerCallBackFn listener = bind(&cStateHighScoreScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);
	m_NewScorePos.clear();
	m_NewScore.clear();
}

//  *******************************************************************************************************************
void cStateHighScoreScreen::DisplayScore(const shared_ptr<const cScore> pScore, const int inIndex)
{
	int posY = 220 + (40 * inIndex);
	if (m_NewScorePos.IsValid() && inIndex == m_NewScorePos.GetValue())
	{
		shared_ptr<Graphics::IBaseControl> ptbNewHighScoreName = m_pHighScoreScreen->VFindChildControl("tbNewHighScoreName");
		ptbNewHighScoreName->VSetPosition(cVector2(0.0f, posY));
		ptbNewHighScoreName->VSetVisible(true);
		UIEventCallBackFn callBackTextBox;
		callBackTextBox = bind(&cStateHighScoreScreen::OnNameEntered, this, _1);
		ptbNewHighScoreName->VRegisterCallBack(UIEVENTTYPE::FOCUSLOST, callBackTextBox);
		AddScoreLabel(inIndex, m_NewScore.GetValue(), posY);
	}
	else
	{
		shared_ptr<IBaseControl> pNameControl = m_pLabelNameTemplate->VDuplicate();
		pNameControl->VSetControlName(cStringUtilities::MakeFormatted("Name%d", inIndex));
		pNameControl->VSetText(pScore->GetPlayerName());
		pNameControl->VSetPosition(cVector2(0.0f, posY));
		pNameControl->VSetVisible(true);
		m_pHighScoreScreen->VAddChildControl(pNameControl);
		AddScoreLabel(inIndex, pScore->GetScore(), posY);

	}
}

//  *******************************************************************************************************************
void cStateHighScoreScreen::BackButtonPressed(const stUIEventCallbackParam & params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		if(m_NewScorePos.IsValid())
		{
			shared_ptr<cScore> pScore(DEBUG_NEW cScore());
			pScore->SetPlayerName(m_PlayerName);
			pScore->SetScore(m_NewScore.GetValue());
			m_pOwner->m_pHighScoreTable->VAddNewScore(pScore);
			m_pOwner->m_pHighScoreTable->VSave();
		}
		m_pOwner->m_pStateMachine->RequestChangeState(cStateTitleScreen::Instance());
	}
}

//  *******************************************************************************************************************
void cStateHighScoreScreen::EscapePressedListener(IEventDataPtr pEventData)
{
	stUIEventCallbackParam params;
	BackButtonPressed(params);
}

//  *******************************************************************************************************************
void cStateHighScoreScreen::OnNameEntered(const Graphics::stUIEventCallbackParam & params)
{
	m_PlayerName = params.strText;
}

//  *******************************************************************************************************************
void cStateHighScoreScreen::AddScoreLabel(const int inIndex, const int inScore, const int posY)
{
	shared_ptr<IBaseControl> pScoreControl = m_pLabelScoreTemplate->VDuplicate();
	pScoreControl->VSetControlName(cStringUtilities::MakeFormatted("Score%d", inIndex));
	int hour, minutes, seconds;
	GetTimeAsHHMMSS(inScore, hour, minutes, seconds);
	pScoreControl->VSetText(cStringUtilities::MakeFormatted("%02d : %02d : %02d", hour, minutes, seconds));
	pScoreControl->VSetPosition(cVector2(250.0f, posY));
	pScoreControl->VSetVisible(true);
	m_pHighScoreScreen->VAddChildControl(pScoreControl);
}
