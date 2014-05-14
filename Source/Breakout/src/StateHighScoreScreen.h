//  *******************************************************************************************************************
//  HighScoreScreen   version:  1.0   Ankur Sheel  date: 2013/03/20
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef StateHighScoreScreen_h__
#define StateHighScoreScreen_h__

#include "GameFlowStates.h"
#include "Optional.h"

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
	void SetNewScore(const int newScore) { m_NewScore = newScore; }

private:
	cStateHighScoreScreen();
	void DisplayScore(const shared_ptr<const GameBase::cScore> pScore, const int Index);
	void AddScoreLabel(const int inIndex, const int inScore, const int posY);
	void BackButtonPressed(const Graphics::stUIEventCallbackParam& params);
	void EscapePressedListener(GameBase::IEventDataPtr pEventData);
	void OnNameEntered(const Graphics::stUIEventCallbackParam & params);
	void SetNewScorePos(const int scorePos) { m_NewScorePos = scorePos; }

private:
	shared_ptr<Graphics::IBaseControl>	m_pHighScoreScreen;
	shared_ptr<Graphics::IBaseControl>	m_pLabelNameTemplate;
	shared_ptr<Graphics::IBaseControl>	m_pLabelScoreTemplate;
	Base::tOptional<int>	m_NewScorePos;
	Base::tOptional<int>	m_NewScore;
	Base::cString	m_PlayerName;

};

#endif // StateHighScoreScreen_h__