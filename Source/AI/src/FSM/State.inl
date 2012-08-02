
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
