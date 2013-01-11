// *****************************************************************************
template <class entity_type>
AI::cState<entity_type>::cState()
: m_bIsPaused(false)
, m_pOwner(NULL)
{

}

// *****************************************************************************
template <class entity_type>
void AI::cState<entity_type>::VOnEnter(entity_type * pOwner)
{
	m_pOwner = pOwner;
}

// *****************************************************************************
template <class entity_type>
bool AI::cState<entity_type>::IsPaused() const
{
	return m_bIsPaused;
}

// *****************************************************************************
template <class entity_type>
void AI::cState<entity_type>::VOnPause()
{
	m_bIsPaused = true;
}

// *****************************************************************************
template <class entity_type>
void AI::cState<entity_type>::VOnResume()
{
	m_bIsPaused = false;
}

// *****************************************************************************
template <class entity_type>
Base::cString AI::cState<entity_type>::GetName() const
{
	cString str = typeid(*this).name();
	str.Remove(0, 6);
	return str;
}
