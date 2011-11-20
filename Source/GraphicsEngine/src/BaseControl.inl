cBaseControl * cBaseControl::GetFirstChild() const
{
	return m_pChildControls;
}

cBaseControl * cBaseControl::GetNextSibling() const
{
	return m_pNextSibling;
}

void cBaseControl::SetParentControl( cBaseControl * pParentControl )
{
	m_pParentControl = pParentControl;
}

ISprite * cBaseControl::GetSprite() const
{
	return m_pCanvasSprite;
}

void cBaseControl::SetSprite( ISprite * pSprite )
{
	m_pCanvasSprite = pSprite;
}

void cBaseControl::SetNextSibling( cBaseControl * pControl )
{
	m_pNextSibling = pControl;
}

cBaseControl * cBaseControl::GetPreviousSibling() const
{
	return m_pPreviousSibling;
}

int cBaseControl::GetNoOfChildren() const
{
	return m_iNoOfChildren;
}

void cBaseControl::SetPreviousSibling( cBaseControl * pControl )
{
	m_pPreviousSibling = pControl;
}
