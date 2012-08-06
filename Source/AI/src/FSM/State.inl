
// ***************************************************************
template <class entity_type>
AI::cState<entity_type>::cState()
: m_bIsPaused(false)
{

}

// ***************************************************************
template <class entity_type>
bool AI::cState<entity_type>::IsPaused() const
{
	return m_bIsPaused;
}

// ***************************************************************
template <class entity_type>
void AI::cState<entity_type>::VOnPause( entity_type * pEntity )
{
	m_bIsPaused = true;
}

// ***************************************************************
template <class entity_type>
void AI::cState<entity_type>::VOnResume( entity_type * pEntity )
{
	m_bIsPaused = false;
}

// ***************************************************************
template <class entity_type>
Base::cString AI::cState<entity_type>::GetName() const
{
	cString str = typeid(*this).name();
	str.Remove(0, 6);
	return str;
}
