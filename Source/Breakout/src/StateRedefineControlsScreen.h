//  *******************************************************************************************************************
//  StateRedefineControlsScreen version: 1.0 Ankur Sheel  date: 2014/05/09
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef StateRedefineControlsScreen_h__
#define StateRedefineControlsScreen_h__

#include "GameFlowStates.h"

namespace Graphics
{
	class IBaseControl;
	struct stUIEventCallbackParam;
}

namespace GameBase
{
	class cScore;
}

class cGame;

class cStateRedefineControlsScreen 
	: public cGameFlowStates
{
public:
	virtual ~cStateRedefineControlsScreen();
	static cStateRedefineControlsScreen *Instance();
	void VOnEnter(cGame * pGame);
	void VOnUpdate(const TICK currentTick, const float deltaTime);
	void VOnExit();

private:
	cStateRedefineControlsScreen();
	void OKButtonPressed(const Graphics::stUIEventCallbackParam & params);
	void CancelButtonPressed(const Graphics::stUIEventCallbackParam & params);
	void ResetButtonPressed(const Graphics::stUIEventCallbackParam & params);
	void EscapePressedListener(GameBase::IEventDataPtr pEventData);
	void OnKeyChanged(unsigned int uiCharId);
	void SetAllKeyControlsText();

private:
	shared_ptr<Graphics::IBaseControl>	m_pRedefineControlsScreen;
	shared_ptr<Graphics::IBaseControl>	m_pLabelControlDisplayNameTemplate;
	shared_ptr<Graphics::IBaseControl>	m_pBtnControlKeyTemplate;
	unsigned int	m_currentlyEditingID;
	std::vector<shared_ptr<Graphics::IBaseControl> >	m_pKeyControls;
};

#endif // StateRedefineControlsScreen_h__
