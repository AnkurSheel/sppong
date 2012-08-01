// ***************************************************************
// Construction and Destruction
// ***************************************************************
template <class entity_type>
inline cStateMachine<entity_type>::cStateMachine(entity_type *owner)
: m_pOwner(owner)
, m_pCurrentState(NULL)
, m_pNextState(NULL)
, m_pPreviousState(NULL)
, m_pGlobalState(NULL)
, m_bRequestedStateChange(false)
{
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
		m_pPreviousState= m_pCurrentState;
		m_pCurrentState->VOnExit(m_pOwner);
	}
	
	m_pCurrentState = state;
	m_pCurrentState->VOnEnter(m_pOwner);

}
// ***************************************************************

// ***************************************************************
// Sets Previous State
// ***************************************************************
template<class entity_type>
inline void cStateMachine<entity_type>::SetPreviousState(cState<entity_type>* state)
{
	m_pPreviousState= state;
}
// ***************************************************************

// ***************************************************************
// Sets global State
// ***************************************************************
template<class entity_type>
inline void cStateMachine<entity_type>::SetGlobalState(cState<entity_type>* state)
{
	m_pGlobalState = state;
}
// ***************************************************************

// ***************************************************************
// Update
// ***************************************************************
template<typename entity_type>
inline void cStateMachine<entity_type>::Update()
{
	if(m_pGlobalState)
	{
		m_pGlobalState->VOnUpdate(m_pOwner);
	}
	if(m_bRequestedStateChange)
	{
		DoStateReplacement();
	}
	else if(m_pCurrentState)
	{
		m_pCurrentState->VOnUpdate(m_pOwner);
	}
}
// ***************************************************************

// ***************************************************************
// Changes the state of the owner
// ***************************************************************
template<typename entity_type>
inline void cStateMachine<entity_type>::ChangeState(cState<entity_type>* pNewState)
{
	m_pNextState = pNewState;
	m_bRequestedStateChange = true;
}
// ***************************************************************

// ***************************************************************
template<typename entity_type>
inline void cStateMachine<entity_type>::DoStateReplacement()
{
	if(m_pNextState == NULL)
		return;

	m_bRequestedStateChange = false;

	m_pPreviousState= m_pCurrentState;
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
// Gets the previous state
// ***************************************************************
template<typename entity_type>
inline cState<entity_type>* cStateMachine<entity_type>::GetPreviousState()
{
	return m_pPreviousState;
}
// ***************************************************************

// ***************************************************************
// gets the global state
// ***************************************************************
template<typename entity_type>
inline cState<entity_type>* cStateMachine<entity_type>::GetGlobalState()
{
	return m_pGlobalState;
}
// ***************************************************************

// ***************************************************************
// Reverts to previous state
// ***************************************************************
template<typename entity_type>
inline void cStateMachine<entity_type>::RevertToPreviousState()
{
	ChangeState(m_pPreviousState);
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
	if(m_pGlobalState && m_pGlobalState->VOnMessage(m_pOwner, msg))
	{
		return true;
	}
	return false;
}
// ***************************************************************