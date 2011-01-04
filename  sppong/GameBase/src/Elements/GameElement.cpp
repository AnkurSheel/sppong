// ***************************************************************
//  GameElement   version:  1.0   Ankur Sheel  date: 05/14/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "GameElement.h"
#include "2D/Sprite.h"

UINT cGameElement::m_siTableHeight = 0;
UINT cGameElement::m_siTableWidth = 0; 

// ***************************************************************
// Constructor
// ***************************************************************
cGameElement::cGameElement()
: m_pSprite(NULL)
{
	int A = 5;
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cGameElement::~cGameElement()
{

}
// ***************************************************************

// ***************************************************************
// Initializes the game element
// ***************************************************************
void cGameElement::Init( const D3DXVECTOR3& vInitialPos, 
						const UINT iTableWidth /*=0 */, 
						const UINT iTableHeight/*=0*/ )
{
	m_vPosition = vInitialPos;
	if (iTableHeight >0 && iTableWidth > 0)
	{
		m_siTableHeight = iTableHeight;
		m_siTableWidth = iTableWidth;
	}
}
// ***************************************************************

// ***************************************************************
// Sets the bounding rectangle for the Game Element
// ***************************************************************
void cGameElement::SetBoundingRectangle()
{
	m_BoundingRect.x1 = (long)m_vPosition.x;
	m_BoundingRect.y1 = (long)m_vPosition.y;
	m_BoundingRect.x2 = (long)(m_vPosition.x + m_pSprite->GetScaledWidth());
	m_BoundingRect.y2 = (long)(m_vPosition.y + m_pSprite->GetScaledHeight());
}
// ***************************************************************

// ***************************************************************
// Called when the game restarts
// ***************************************************************
void cGameElement::OnRestart( const D3DXVECTOR3& vInitialPos )
{
	m_vPosition = vInitialPos;
	SetBoundingRectangle();
}
// ***************************************************************

void cGameElement::Render(LPDIRECT3DDEVICE9 const pDevice, const DWORD dwFlags /*= NULL*/, const D3DCOLOR& tint/* = WHITE*/, const RECT* pSrcRect/* = NULL*/)
{
	m_pSprite->DrawSprite(pDevice, m_vPosition, dwFlags);
}

void cGameElement::SetSprite(ISprite* const sprite )
{
	m_pSprite = sprite;
}

const ISprite * cGameElement::GetSprite() const
{
	return m_pSprite;
}