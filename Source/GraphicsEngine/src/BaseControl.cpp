// ***************************************************************
//  BaseControl   version:  1.0   Ankur Sheel  date: 2011/07/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "BaseControl.h"
#include "Sprite.hxx"

using namespace Graphics;

cBaseControl::cBaseControl()
: m_dwWidth(0)
, m_dwHeight(0)
, m_bVisible(true)
, m_pCanvasSprite(NULL) 
, m_pChildControls(NULL) 
, m_pNextSibling(NULL) 
, m_pPreviousSibling(NULL) 
, m_pParentControl(NULL) 
, m_iNoOfChildren(0)
, m_vPosition(D3DXVECTOR2(0.0f, 0.0f))
{

}
cBaseControl::~cBaseControl()
{

}

cBaseControl * cBaseControl::AddChildControl( cBaseControl * pControl )
{
	pControl->SetParentControl(this);
	ISprite * pSprite = pControl->GetSprite();
	SAFE_DELETE(pSprite);
	pControl->SetSprite(m_pCanvasSprite);

	if (!m_pChildControls)
	{
		m_pChildControls = pControl;
	}
	else
	{
		cBaseControl * temp = GetFirstChild();

		while (temp->GetNextSibling())
		{
			temp = temp->GetNextSibling();
		}

		temp->SetNextSibling(pControl);
		pControl->SetPreviousSibling(temp);
	}
	m_iNoOfChildren++;
	return pControl;
}

cBaseControl * cBaseControl::RemoveChildControl( cBaseControl * pControl )
{
	cBaseControl * pNextControl = pControl->GetNextSibling();
	cBaseControl * pPreviousControl = pControl->GetPreviousSibling();
	SAFE_DELETE(pControl);
	pNextControl->SetPreviousSibling(pPreviousControl);
	pPreviousControl->SetNextSibling(pNextControl);
	pControl = pNextControl;

	m_iNoOfChildren--;

	return pControl;
}

void cBaseControl::RemoveAllChildren()
{
	cBaseControl * temp = GetFirstChild();

	while(temp)
	{
		cBaseControl * pNextControl = temp->GetNextSibling();
		SAFE_DELETE(temp);
		temp = pNextControl;
	}
	m_iNoOfChildren = 0;
}

void cBaseControl::GetAbsolutePosition( D3DXVECTOR2 & vPosition )
{
	vPosition.x += m_vPosition.x;
	vPosition.y += m_vPosition.y;

	if (m_pParentControl)
	{
		m_pParentControl->GetAbsolutePosition(vPosition);
	}
}