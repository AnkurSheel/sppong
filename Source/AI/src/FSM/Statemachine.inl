// ***************************************************************
// Construction and Destruction
// ***************************************************************
template <class entity_type>
inline cStateMachine<entity_type>::cStateMachine(entity_type *owner)
: m_pOwner(owner)
, m_pCurrentState(NULL)
, m_pNextState(NULL)
, m_bRequestedStateChange(false)
, m_bRequestedPushState(false)
, m_bRequestedPopState(false)
{
	m_vPushedStates.clear();
}
// ***************************************************************

template <class entity_type>
inline cStateMachine<entity_type>::~cStateMachine()
{
}
// ***************************************************************

// ***************************************************************
// Sets Current State
// ***************************************************************
template<class entity_type>
inline void cStateMachine<entity_type>::SetCurrentState(cState<entity_type>* state)
{
	// if there is an existing state, then call the current state exists and set it to the previous state 
	if (m_pCurrentState)
	{
		m_pCurrentState->VOnExit(m_pOwner);
	}
	
	m_pCurrentState = state;
	m_pCurrentState->VOnEnter(m_pOwner);

}
// ***************************************************************

// ***************************************************************
// Update
// ***************************************************************
template<typename entity_type>
inline void cStateMachine<entity_type>::Update()
{
	if(m_bRequestedPushState)
	{
		PushState();
	}
	else if(m_bRequestedPopState)
	{
		PopState();
	}
	else if(m_bRequestedStateChange)
	{
		ChangeState();
	}
	else if(m_pCurrentState && !m_pCurrentState->IsPaused())
	{
		m_pCurrentState->VOnUpdate(m_pOwner);
	}
}
// ***************************************************************

// ***************************************************************
// Changes the state of the owner
// ***************************************************************
template<typename entity_type>
inline void cStateMachine<entity_type>::RequestChangeState(cState<entity_type>* pNewState)
{
	m_pNextState = pNewState;
	m_bRequestedStateChange = true;
}
// ***************************************************************

// ***************************************************************
template<typename entity_type>
inline void cStateMachine<entity_type>::ChangeState()
{
	if(m_pNextState == NULL)
		return;

	m_bRequestedStateChange = false;

	m_pCurrentState->VOnExit(m_pOwner);
	m_pCurrentState = m_pNextState;
	m_pCurrentState->VOnEnter(m_pOwner);
}
// ***************************************************************

// ***************************************************************
// Returns the current state
// ***************************************************************
template<typename entity_type>
inline cState<entity_type>* cStateMachine<entity_type>::GetCurrentState()
{
	return m_pCurrentState;
}
// ***************************************************************

// ***************************************************************
// returns true if it is in the state
// ***************************************************************
template<typename entity_type>
inline bool cStateMachine<entity_type>::IsInState(const cState<entity_type>& state)
{
	return typeid(*m_pCurrentState) == typeid(state);
}
// ***************************************************************

// ***************************************************************
// Message Handler
// ***************************************************************
template<typename entity_type>
inline bool cStateMachine<entity_type>::HandleMessage(const Telegram &msg)
{
	if(m_pCurrentState && m_pCurrentState->VOnMessage(m_pOwner, msg))
	{
		return true;
	}
	return false;
}

// ***************************************************************
template <class entity_type>
void AI::cStateMachine<entity_type>::RequestPushState(cState<entity_type>* pNewState)
{
	m_pNextState = pNewState;
	m_bRequestedPushState = true;
}

// ***************************************************************
template <class entity_type>
void AI::cStateMachine<entity_type>::PushState()
{	
	m_bRequestedPushState = false;
	if(m_pNextState == NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Push for Null State");
		return;
	}

	if(m_pCurrentState == NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Pushing Null State");
		return;
	}

	m_pCurrentState->VOnPause(m_pOwner);
	m_vPushedStates.push_back(m_pCurrentState);
	m_pCurrentState = m_pNextState;
	m_pNextState = NULL;
	Log_Write_L1(ILogger::LT_DEBUG, "Pushed and Changed State");
	m_pCurrentState->VOnEnter(m_pOwner);
}


// ***************************************************************
template <class entity_type>
void AI::cStateMachine<entity_type>::RequestPopState()
{
	m_bRequestedPopState = true;
}

// ***************************************************************
template <class entity_type>
void AI::cStateMachine<entity_type>::PopState()
{
	m_bRequestedPopState = false;
	if (m_vPushedStates.empty())
	{
		Log_Write_L1(ILogger::LT_ERROR, "Popping Null State");
		return;
	}
	if (m_pCurrentState != NULL)
	{
		m_pCurrentState->VOnExit(m_pOwner);
	}
	m_pCurrentState = m_vPushedStates.back();
	m_vPushedStates.pop_back();
	if (m_pCurrentState == NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Popped state is Null");
		return;
	}
	Log_Write_L1(ILogger::LT_DEBUG, "Popped State");
	m_pCurrentState->VOnResume(m_pOwner);
}