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
#include "Sprite.hxx"
#include "Polygon.hxx"

using namespace Graphics;
using namespace GameBase;
using namespace Base;
// ***************************************************************
// Constructor
// ***************************************************************
cGameElement::cGameElement()
: m_pSprite(NULL)
, m_vPosition(D3DXVECTOR3(-1.0f, -1.0f, -1.0f))
, m_vPrevPosition(D3DXVECTOR3(-1.0f, -1.0f, -1.0f))
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
void cGameElement::Init( const D3DXVECTOR3& vInitialPos, const cString & strFilename)
{
	m_vPosition = vInitialPos;
	m_vPrevPosition = m_vPosition;
	m_pSprite = ISprite::CreateSprite();
	m_strFileName = strFilename;
}
// ***************************************************************

// ***************************************************************
// Sets the bounding rectangle for the Game Element
// ***************************************************************
void cGameElement::SetBoundingRectangle()
{
	D3DXVECTOR2 v1[] = {
		D3DXVECTOR2(m_vPosition.x, m_vPosition.y),
		D3DXVECTOR2(m_vPosition.x + m_pSprite->GetScaledWidth(), m_vPosition.y),
		D3DXVECTOR2(m_vPosition.x + m_pSprite->GetScaledWidth(), m_vPosition.y + m_pSprite->GetScaledHeight()),
		D3DXVECTOR2(m_vPosition.x, m_vPosition.y + m_pSprite->GetScaledHeight())
	};

	m_pBoundingPolygon = IPolygon::CreatePolygon(v1, 4);
}
// ***************************************************************

// ***************************************************************
// Called when the game restarts
// ***************************************************************
void cGameElement::OnRestart( const D3DXVECTOR3& vInitialPos )
{
	m_vPosition = vInitialPos;
	
	if(m_vPrevPosition != m_vPosition)
	{
		D3DXVECTOR2 trans(m_vPosition.x - m_vPrevPosition.x, m_vPosition.y - m_vPrevPosition.y);
		m_pBoundingPolygon->Translate(trans);
		m_vPrevPosition = m_vPosition;
	}
}
// ***************************************************************

void cGameElement::Render(LPDIRECT3DDEVICE9 const pDevice,
						  const DWORD dwFlags /*= NULL*/,
						  const D3DCOLOR& tint/* = WHITE*/,
						  const RECT* pSrcRect/* = NULL*/)
{
	m_pSprite->SetPosition(m_vPosition);
	m_pSprite->DrawSprite(pDevice, dwFlags);
}

void cGameElement::Cleanup()
{
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pBoundingPolygon);
}

void cGameElement::OnLostDevice()
{
	m_pSprite->Cleanup();
}