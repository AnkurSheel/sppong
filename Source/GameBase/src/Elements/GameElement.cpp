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

// ***************************************************************
// Constructor
// ***************************************************************
cGameElement::cGameElement()
: m_pSprite(NULL)
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cGameElement::~cGameElement()
{
	Cleanup();
}
// ***************************************************************

// ***************************************************************
// Initializes the game element
// ***************************************************************
void cGameElement::Init( const D3DXVECTOR3& vInitialPos)
{
	m_vPosition = vInitialPos;
	m_pSprite = ISprite::CreateSprite();
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

void cGameElement::Render(LPDIRECT3DDEVICE9 const pDevice,
						  const DWORD dwFlags /*= NULL*/,
						  const D3DCOLOR& tint/* = WHITE*/,
						  const RECT* pSrcRect/* = NULL*/)
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

void cGameElement::Cleanup()
{
	SAFE_DELETE(m_pSprite);
}

void cGameElement::OnLostDevice()
{
	m_pSprite->Cleanup();
}