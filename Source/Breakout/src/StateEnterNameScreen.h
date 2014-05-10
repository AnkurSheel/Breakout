//  *******************************************************************************************************************
//  StateEnterNameScreen version: 1.0 Ankur Sheel  date: 2014/04/24
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef StateEnterNameScreen_h__
#define StateEnterNameScreen_h__

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

class cStateEnterNameScreen 
	: public cGameFlowStates
{
public:
	virtual ~cStateEnterNameScreen();
	static cStateEnterNameScreen *Instance();
	void VOnEnter(cGame * pGame);
	void VOnUpdate();
	void VOnUpdate(const TICK currentTick, const float deltaTime);
	void VOnExit();
	void SetNewScorePos(const int scorePos) { m_NewScorePos = scorePos; }
	void SetNewScore(const int newScore) { m_NewScore = newScore; }

private:
	cStateEnterNameScreen();
	void EscapePressedListener(GameBase::IEventDataPtr pEventData);
	void BackButtonPressed(const Graphics::stUIEventCallbackParam & params);
	void NameEntered(const Graphics::stUIEventCallbackParam & params);
	void DisplayScore(const shared_ptr<const GameBase::cScore> pScore, const int index);
	void AddScoreLabel(const int index, const Base::cString & score, const int posY);

private:
	int	m_NewScore;
	Base::tOptional<int>	m_NewScorePos;
	Base::cString	m_PlayerName;
	shared_ptr<Graphics::IBaseControl>	m_pEnterNameScreen;
};

#endif // StateEnterNameScreen_h__
