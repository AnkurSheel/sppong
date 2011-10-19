cBaseControl * cBaseControl::GetFirstChild()
{
	return m_pChildControls;
}

cBaseControl * cBaseControl::GetNextSibling()
{
	return m_pNextSibling;
}

void cBaseControl::SetParentControl( cBaseControl * pParentControl )
{
	m_pParentControl = pParentControl;
}

ISprite * cBaseControl::GetSprite()
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

cBaseControl * cBaseControl::GetPreviousSibling()
{
	return m_pPreviousSibling;
}

int cBaseControl::GetNoOfChildren()
{
	return m_iNoOfChildren;
}

void cBaseControl::SetPreviousSibling( cBaseControl * pControl )
{
	m_pPreviousSibling = pControl;
}
