#include "stdafx.h"
#include "StateRedefineControlsScreen.h"
#include "Game.h"
#include "HumanView.h"
#include "UiManager.hxx"
#include "BaseControl.hxx"
#include "GameFlowStateMachine.h"
#include "EventManager.hxx"
#include "EscapePressedEventData.h"
#include "StateTitleScreen.h"
#include "GameControls.h"

using namespace Base;
using namespace Graphics;
using namespace GameBase;
using namespace AI;

// ***********************************************************************************************************************************************************
cStateRedefineControlsScreen::cStateRedefineControlsScreen()
{
}

// ***********************************************************************************************************************************************************
cStateRedefineControlsScreen::~cStateRedefineControlsScreen()
{

}

// ********************************************************************************************************************
cStateRedefineControlsScreen * cStateRedefineControlsScreen::Instance()
{
	static cStateRedefineControlsScreen instance;
	return &instance;
}

// ********************************************************************************************************************
void cStateRedefineControlsScreen::VOnEnter(cGame * pGame)
{
	cGameFlowStates::VOnEnter(pGame);

	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pRedefineControlsScreen = IUiManager::GetInstance()->VCreateUI("redefinecontrolsscreen");
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(m_pRedefineControlsScreen);
		pGame->m_pHumanView->m_pAppWindowControl->VMoveToFront(m_pRedefineControlsScreen.get());

		m_pLabelControlDisplayNameTemplate = m_pRedefineControlsScreen->VFindChildControl("LabelControlDisplayNameTemplate");
		m_pBtnControlKeyTemplate = m_pRedefineControlsScreen->VFindChildControl("btnControlKeyTemplate");

		cGameControls::KeyMapping keyMap = pGame->m_pGameControls->GetKeyMap();
		int i = 0;
		int currentPosY = 220;
		for(auto iter = keyMap.begin(); iter != keyMap.end(); iter++)
		{
			stGameControl gameControl = iter->second;

			shared_ptr<IBaseControl> pNameControl = m_pLabelControlDisplayNameTemplate->VDuplicate();
			pNameControl->VSetControlName(cString::MakeFormatted("Name%d", i));
			pNameControl->VSetText(gameControl.m_DisplayName);
			pNameControl->VSetPosition(cVector2(0.0f, currentPosY));
			pNameControl->VSetVisible(true);
			m_pRedefineControlsScreen->VAddChildControl(pNameControl);
			pNameControl.reset();

			shared_ptr<IBaseControl> pKeyControl = m_pBtnControlKeyTemplate->VDuplicate();
			pKeyControl->VSetControlName(cString::MakeFormatted("Key%d", i));
			pKeyControl->VSetText(pGame->m_pGameControls->GetKeyName(gameControl.m_KeyCode));
			pKeyControl->VSetPosition(cVector2(300.0f, currentPosY));
			pKeyControl->VSetVisible(true);
			m_pRedefineControlsScreen->VAddChildControl(pKeyControl);

			unsigned int id = iter->first;
			m_pKeyControls.push_back(pKeyControl);
			UIEventCallBackFn btnClick = [this, pKeyControl, id] (const stUIEventCallbackParam & params)
			{
				m_currentlyEditingID = id;
				m_pKeyControls[m_currentlyEditingID]->VSetText("Press Any Key");
			};
			pKeyControl->VRegisterCallBack(UIEVENTTYPE::BUTTONRELEASED, btnClick);

			UIEventCallBackFn  btnKeyDown = [this] (const stUIEventCallbackParam & params)
			{
				this->OnKeyChanged(params.uiCharId);
			};
			pKeyControl->VRegisterCallBack(UIEVENTTYPE::KEYDOWN, btnKeyDown);
			pKeyControl.reset();

			i++;
			currentPosY += 40;
		}
	}

	shared_ptr<Graphics::IBaseControl> pOkButton = m_pRedefineControlsScreen->VFindChildControl("btnOk");
	if(pOkButton != NULL)
	{
		UIEventCallBackFn callbackBackBtn = bind(&cStateRedefineControlsScreen::OKButtonPressed, this, _1);
		pOkButton->VRegisterCallBack(UIEVENTTYPE::BUTTONRELEASED, callbackBackBtn);
	}

	shared_ptr<Graphics::IBaseControl> pResetButton = m_pRedefineControlsScreen->VFindChildControl("btnReset");
	if(pResetButton != NULL)
	{
		UIEventCallBackFn callbackBackBtn = bind(&cStateRedefineControlsScreen::ResetButtonPressed, this, _1);
		pResetButton->VRegisterCallBack(UIEVENTTYPE::BUTTONRELEASED, callbackBackBtn);
	}

	shared_ptr<Graphics::IBaseControl> pCancelButton = m_pRedefineControlsScreen->VFindChildControl("btnCancel");
	if(pCancelButton != NULL)
	{
		UIEventCallBackFn callbackBackBtn = bind(&cStateRedefineControlsScreen::CancelButtonPressed, this, _1);
		pCancelButton->VRegisterCallBack(UIEVENTTYPE::BUTTONRELEASED, callbackBackBtn);
	}

	EventListenerCallBackFn listener = bind(&cStateRedefineControlsScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEscapePressedEventData::m_Name);
}

// ********************************************************************************************************************
void cStateRedefineControlsScreen::VOnUpdate(const TICK currentTick, const float deltaTime)
{
}

// ********************************************************************************************************************
void cStateRedefineControlsScreen::VOnExit()
{
	m_pRedefineControlsScreen.reset();
	m_pBtnControlKeyTemplate.reset();
	m_pLabelControlDisplayNameTemplate.reset();
	m_pKeyControls.clear();

	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("redefinecontrolsscreen");
	}

	EventListenerCallBackFn listener = bind(&cStateRedefineControlsScreen::EscapePressedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEscapePressedEventData::m_Name);
}

// ********************************************************************************************************************
void cStateRedefineControlsScreen::OKButtonPressed(const stUIEventCallbackParam & params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->VGetGameControls()->Save();
		m_pOwner->m_pStateMachine->RequestPopState();
	}
}

// ********************************************************************************************************************
void cStateRedefineControlsScreen::CancelButtonPressed(const Graphics::stUIEventCallbackParam & params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->m_pStateMachine->RequestPopState();
	}
}

//  *******************************************************************************************************************
void cStateRedefineControlsScreen::EscapePressedListener(IEventDataPtr pEventData)
{
	stUIEventCallbackParam params;
	OKButtonPressed(params);
}

//  *******************************************************************************************************************
void cStateRedefineControlsScreen::ResetButtonPressed(const stUIEventCallbackParam & params)
{
	if (m_pOwner != NULL && m_pOwner->m_pGameControls != NULL)
	{
		m_pOwner->m_pGameControls->VSetDefaults();
		SetAllKeyControlsText();
	}
}

//  *******************************************************************************************************************
void cStateRedefineControlsScreen::OnKeyChanged(unsigned int uiCharId)
{
	if (m_pOwner != NULL && m_pOwner->m_pGameControls != NULL)
	{
		m_pOwner->m_pGameControls->SetKey(m_currentlyEditingID, uiCharId);
		SetAllKeyControlsText();
	}
}

//  *******************************************************************************************************************
void cStateRedefineControlsScreen::SetAllKeyControlsText()
{
	cGameControls::KeyMapping keyMap = m_pOwner->m_pGameControls->GetKeyMap();
	for(int i=0; i<m_pKeyControls.size(); i++)
	{
		m_pKeyControls[i]->VSetText(m_pOwner->VGetGameControls()->GetKeyName(keyMap[i].m_KeyCode));
	}
}
