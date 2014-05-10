//  *******************************************************************************************************************
//  HighScoreScreen   version:  1.0   Ankur Sheel  date: 2013/03/20
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef StateHighScoreScreen_h__
#define StateHighScoreScreen_h__

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

class cStateHighScoreScreen 
	: public cGameFlowStates
{
public:
	virtual ~cStateHighScoreScreen();
	static cStateHighScoreScreen *Instance();
	virtual void VOnEnter(cGame *pGame);
	virtual void VOnUpdate(const TICK currentTick, const float deltaTime);
	virtual void VOnExit();

private:
	cStateHighScoreScreen();
	void DisplayScore(const shared_ptr<const GameBase::cScore> pScore, const int Index);
	void BackButtonPressed(const Graphics::stUIEventCallbackParam& params);
	void EscapePressedListener(GameBase::IEventDataPtr pEventData);

private:
	shared_ptr<Graphics::IBaseControl>	m_pHighScoreScreen;
	shared_ptr<Graphics::IBaseControl>	m_pLabelNameTemplate;
	shared_ptr<Graphics::IBaseControl>	m_pLabelScoreTemplate;
};

#endif // StateHighScoreScreen_h__