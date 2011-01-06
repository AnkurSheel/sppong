// ***************************************************************
// Construction and Destruction
// ***************************************************************
template <class entity_type>
inline cStateMachine<entity_type>::cStateMachine(entity_type *owner)
: m_pOwner(owner)
, m_pCurrentState(NULL)
, m_pPreviousState(NULL)
, m_pGlobalState(NULL)

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
inline void cStateMachine<entity_type>::SetCurrentState(IState<entity_type>* state)
{
	// if there is an existing state, then call the current state exists and set it to the previous state 
	if (m_pCurrentState)
	{
		m_pPreviousState= m_pCurrentState;
		m_pCurrentState->Exit(m_pOwner);
	}
	
	m_pCurrentState = state;
	m_pCurrentState->Enter(m_pOwner);

}
// ***************************************************************

// ***************************************************************
// Sets Previous State
// ***************************************************************
template<class entity_type>
inline void cStateMachine<entity_type>::SetPreviousState(IState<entity_type>* state)
{
	m_pPreviousState= state;
}
// ***************************************************************

// ***************************************************************
// Sets global State
// ***************************************************************
template<class entity_type>
inline void cStateMachine<entity_type>::SetGlobalState(IState<entity_type>* state)
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
		m_pGlobalState->Execute(m_pOwner);
	}
	if(m_pCurrentState)
	{
		m_pCurrentState->Execute(m_pOwner);
	}
}
// ***************************************************************

// ***************************************************************
// Changes the state of the owner
// ***************************************************************
template<typename entity_type>
inline void cStateMachine<entity_type>::ChangeState(IState<entity_type>* pNewState)
{
	m_pPreviousState= m_pCurrentState;
	m_pCurrentState->Exit(m_pOwner);
	m_pCurrentState = pNewState;
	m_pCurrentState->Enter(m_pOwner);
}
// ***************************************************************

// ***************************************************************
// Returns the current state
// ***************************************************************
template<typename entity_type>
inline IState<entity_type>* cStateMachine<entity_type>::GetCurrentState()
{
	return m_pCurrentState;
}
// ***************************************************************

// ***************************************************************
// Gets the previous state
// ***************************************************************
template<typename entity_type>
inline IState<entity_type>* cStateMachine<entity_type>::GetPreviousState()
{
	return m_pPreviousState;
}
// ***************************************************************

// ***************************************************************
// gets the global state
// ***************************************************************
template<typename entity_type>
inline IState<entity_type>* cStateMachine<entity_type>::GetGlobalState()
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
inline bool cStateMachine<entity_type>::IsInState(const IState<entity_type>& state)
{
	if(m_pCurrentState == state)
	{
		return true;
	}
	return false;
}
// ***************************************************************

// ***************************************************************
// Message Handler
// ***************************************************************
template<typename entity_type>
inline bool cStateMachine<entity_type>::HandleMessage(const Telegram &msg)
{
	if(m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg))
	{
		return true;
	}
	if(m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, msg))
	{
		return true;
	}
	return false;
}
// ***************************************************************