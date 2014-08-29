//  *******************************************************************************************************************
//  StateOptionScreen   version:  1.0   Ankur Sheel  date: 2014/02/26
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "StateOptionScreen.h"
#include "Game.h"
#include "HumanView.h"
#include "ControlStructures.h"
#include "BaseControl.hxx"
#include "GameFlowStateMachine.h"
#include "GameDirectories.h"
#include "HumanView.h"
#include "UiManager.hxx"

using namespace Base;
using namespace Graphics;
using namespace GameBase;
using namespace AI;
using namespace Utilities;

//  *******************************************************************************************************************
cStateOptionsScreen::cStateOptionsScreen()
	: m_pOptionsScreen(NULL)
{
}

//  *******************************************************************************************************************
cStateOptionsScreen::~cStateOptionsScreen()
{
}

//  *******************************************************************************************************************
cStateOptionsScreen* cStateOptionsScreen::Instance()
{
	static cStateOptionsScreen instance;
	return &instance;
}

//  *******************************************************************************************************************
void cStateOptionsScreen::VOnEnter(cGame *pGame)
{
	cGameFlowStates::VOnEnter(pGame);

	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOptionsScreen = IUiManager::GetInstance()->VCreateUI("optionscreen");
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(m_pOptionsScreen);

		shared_ptr<Graphics::IBaseControl> pMusicCheckBoxControl = m_pOptionsScreen->VFindChildControl("cbMusic");
		if(pMusicCheckBoxControl != NULL)
		{
			UIEventCallBackFn musicCheckBoxCallback = bind(&cStateOptionsScreen::MusicCheckBoxPressed, this, _1);
			pMusicCheckBoxControl->VRegisterCallBack(UIEVENTTYPE::BUTTONPRESSED, musicCheckBoxCallback);
		}

		shared_ptr<Graphics::IBaseControl> pMusicScrollBarControl = m_pOptionsScreen->VFindChildControl("hsbMusicVolume");
		if(pMusicScrollBarControl != NULL)
		{
			UIEventCallBackFn musicScrollbarcallback = bind(&cStateOptionsScreen::MusicScrollbarChanged, this, _1);
			pMusicScrollBarControl->VRegisterCallBack(UIEVENTTYPE::SCROLLBARCHANGED, musicScrollbarcallback);
		}

		shared_ptr<Graphics::IBaseControl> pSFXScrollBarControl = m_pOptionsScreen->VFindChildControl("hsbSFXVolume");
		if(pSFXScrollBarControl != NULL)
		{
			UIEventCallBackFn SFXScrollbarcallback = bind(&cStateOptionsScreen::SFXScrollbarChanged, this, _1);
			pSFXScrollBarControl->VRegisterCallBack(UIEVENTTYPE::SCROLLBARCHANGED, SFXScrollbarcallback);
		}

		shared_ptr<Graphics::IBaseControl> pBackButton = m_pOptionsScreen->VFindChildControl("hsbMusicVolume");
		if(pBackButton != NULL)
		{
			UIEventCallBackFn callBackBtn= bind(&cStateOptionsScreen::BackButtonPressed, this, _1);
			pBackButton->VRegisterCallBack(UIEVENTTYPE::BUTTONRELEASED, callBackBtn);
		}

		/*IBaseControl * pSfxCheckBoxControl = IBaseControl::CreateCheckBoxControl(checkboxControlDef);
		m_pOptionsScreen->VAddChildControl(shared_ptr<IBaseControl>(pSfxCheckBoxControl ));
		UIEventCallBackFn sfxCheckBoxCallback;
		sfxCheckBoxCallback = bind(&cHumanView::SfxCheckBoxPressed, m_pOwner->m_pHumanView, _1);
		pSfxCheckBoxControl->VRegisterCallBack(UIET_BTNPRESSED, sfxCheckBoxCallback);

		IBaseControl * pFullscreenCheckBoxControl = IBaseControl::CreateCheckBoxControl(checkboxControlDef);
		m_pOptionsScreen->VAddChildControl(shared_ptr<IBaseControl>(pFullscreenCheckBoxControl));
		UIEventCallBackFn fullScreenCheckBoxCallback;
		fullScreenCheckBoxCallback = bind(&cHumanView::FullScreenCheckBoxPressed, m_pOwner->m_pHumanView, _1);
		pFullscreenCheckBoxControl->VRegisterCallBack(UIET_BTNPRESSED, fullScreenCheckBoxCallback);
		*/
	}
}

//  *******************************************************************************************************************
void cStateOptionsScreen::VOnUpdate(const TICK currentTick, const float deltaTime)
{

}

//  *******************************************************************************************************************
void cStateOptionsScreen::VOnExit()
{
	m_pOptionsScreen.reset();
	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("OptionsScreen");
	}
}


//  *******************************************************************************************************************
void cStateOptionsScreen::BackButtonPressed(const stUIEventCallbackParam & params)
{
	if(m_pOwner != NULL)
	{
		if(m_pOwner->m_pStateMachine != NULL)
		{
			m_pOwner->m_pStateMachine->RequestPopState();
		}
		//cGameOptions::SaveGameOptions(cGameDirectories::GameDirectories().strMediaDirectory + "PlayerOptions.xml");
	}
}

//  *******************************************************************************************************************
void cStateOptionsScreen::MusicScrollbarChanged(const stUIEventCallbackParam & params)
{
	shared_ptr<IBaseControl> pMusicTextBox = m_pOptionsScreen->VFindChildControl("tbMusicVolume");
	//cGameOptions::GameOptions().iMusicVolume = params.iThumbPos * 5;
	pMusicTextBox->VSetText(cString::MakeFormatted("%d", params.iThumbPos));
	//m_pOwner->m_pHumanView->SetMusicVolume();
}

//  *******************************************************************************************************************
void cStateOptionsScreen::SFXScrollbarChanged(const Graphics::stUIEventCallbackParam& params)
{
	shared_ptr<IBaseControl> pSFXTextBox = m_pOptionsScreen->VFindChildControl("tbSFXVolume");
	//cGameOptions::GameOptions().iSFXVolume = params.iThumbPos * 5;
	pSFXTextBox->VSetText(cString::MakeFormatted("%d", params.iThumbPos));
	//m_pOwner->m_pHumanView->SetSFXVolume();
}

// *******************************************************************************************
void cStateOptionsScreen::MusicCheckBoxPressed(const stUIEventCallbackParam & params)
{
	//cGameOptions::GameOptions().bPlayMusic = params.bChecked;
	//m_pGame->VGetProcessManager()->VSetProcessesActive(m_hashMusicChannel, cGameOptions::GameOptions().bPlayMusic);
}