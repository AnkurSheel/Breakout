//  *******************************************************************************************************************
template <class entity_type>
inline cStateMachine<entity_type>::cStateMachine(entity_type *owner)
: m_pOwner(owner)
, m_pCurrentState(NULL)
, m_pNextState(NULL)
, m_RequestedStateChange(false)
, m_RequestedPushState(false)
, m_RequestedPopState(false)
{
	m_PushedStates.clear();
}

//  *******************************************************************************************************************
template <class entity_type>
inline cStateMachine<entity_type>::~cStateMachine()
{
	if (m_pCurrentState)
	{
		m_pCurrentState->VOnExit();
	}
	m_pCurrentState = NULL;

	std::deque<cState<entity_type> *>::iterator it = m_PushedStates.begin();

	while (it != m_PushedStates.end())
	{
		cState<entity_type> * pState = (*it);
		pState->VOnExit();
		it++;
	}
	m_PushedStates.clear();
}

//  *******************************************************************************************************************
template<class entity_type>
inline void cStateMachine<entity_type>::SetCurrentState(cState<entity_type> * pState)
{
	// if there is an existing state, then call the current state exists and set it to the previous state 
	if (m_pCurrentState)
	{
		m_pCurrentState->VOnExit();
	}
	
	m_pCurrentState = pState;
	m_pCurrentState->VOnEnter(m_pOwner);
}

//  *******************************************************************************************************************
template<typename entity_type>
inline void cStateMachine<entity_type>::Update(const TICK currentTick, const float deltaTime)
{
	if(m_RequestedPushState)
	{
		PushState();
	}
	else if(m_RequestedPopState)
	{
		PopState();
	}
	else if(m_RequestedStateChange)
	{
		ChangeState();
	}
	else if(m_pCurrentState && !m_pCurrentState->IsPaused())
	{
		m_pCurrentState->VOnUpdate(currentTick, deltaTime);
	}
}

//  *******************************************************************************************************************
template<typename entity_type>
inline void cStateMachine<entity_type>::RequestChangeState(cState<entity_type> * pNewState)
{
	m_pNextState = pNewState;
	m_RequestedStateChange = true;
}

//  *******************************************************************************************************************
template<typename entity_type>
inline void cStateMachine<entity_type>::ChangeState()
{
	if(m_pNextState == NULL)
		return;

	m_RequestedStateChange = false;

	m_pCurrentState->VOnExit();
	m_pCurrentState = m_pNextState;
	m_pCurrentState->VOnEnter(m_pOwner);
}

//  *******************************************************************************************************************
template<typename entity_type>
inline cState<entity_type> * cStateMachine<entity_type>::GetCurrentState()
{
	return m_pCurrentState;
}
//  *******************************************************************************************************************

//  *******************************************************************************************************************
// returns true if it is in the state
//  *******************************************************************************************************************
template<typename entity_type>
inline bool cStateMachine<entity_type>::IsInState(const cState<entity_type>& state)
{
	return typeid(*m_pCurrentState) == typeid(state);
}

//  *******************************************************************************************************************
template<typename entity_type>
inline bool cStateMachine<entity_type>::HandleMessage(const Telegram & msg)
{
	if(m_pCurrentState && m_pCurrentState->VOnMessage(msg))
	{
		return true;
	}
	return false;
}

//  *******************************************************************************************************************
template <class entity_type>
void AI::cStateMachine<entity_type>::RequestPushState(cState<entity_type> * pNewState)
{
	m_pNextState = pNewState;
	m_RequestedPushState = true;
}

//  *******************************************************************************************************************
template <class entity_type>
void AI::cStateMachine<entity_type>::PushState()
{	
	m_RequestedPushState = false;
	if(m_pNextState == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Push for Null State");
		return;
	}

	if(m_pCurrentState == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Pushing Null State");
		return;
	}

	m_pCurrentState->VOnPause();
	m_PushedStates.push_back(m_pCurrentState);
	Log_Write(ILogger::LT_DEBUG, 2, "Pushed State : " + m_pCurrentState->GetName() + " New State : " + m_pNextState->GetName()); 
	m_pCurrentState = m_pNextState;
	m_pNextState = NULL;
	m_pCurrentState->VOnEnter(m_pOwner);
}


//  *******************************************************************************************************************
template <class entity_type>
void AI::cStateMachine<entity_type>::RequestPopState()
{
	m_RequestedPopState = true;
}

//  *******************************************************************************************************************
template <class entity_type>
void AI::cStateMachine<entity_type>::PopState()
{
	m_RequestedPopState = false;
	if (m_PushedStates.empty())
	{
		Log_Write(ILogger::LT_ERROR, 1, "Popping Null State");
		return;
	}
	cState<entity_type> * pNewState = m_PushedStates.back();
	m_PushedStates.pop_back();
	if (pNewState == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Popped state is Null");
		return;
	}
	
	Log_Write(ILogger::LT_DEBUG, 2, "Old State : " + m_pCurrentState->GetName() + " State : " + pNewState->GetName());
	if (m_pCurrentState != NULL)
	{
		m_pCurrentState->VOnExit();
	}
	m_pCurrentState = pNewState;
	m_pCurrentState->VOnResume();
}
