// ***************************************************************
//  Paddle   version:  1.0   Ankur Sheel  date: 05/12/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Paddle.h"
#include "Sprite.hxx"
#include "Polygon.hxx"

using namespace Base;
// ***************************************************************
// Constructor
// ***************************************************************
cPaddle::cPaddle()
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cPaddle::~cPaddle()
{
}
// ***************************************************************

// ***************************************************************
// Initializes the paddle
// ***************************************************************
void cPaddle::Init( const D3DXVECTOR3& vInitialPos, const cString & strFilename )
{
	cGameElement::OnBeginInit(strFilename, D3DXVECTOR2((float)m_siTableWidth/40, (float)m_siTableHeight/5));
	// align the paddle at the other end

	D3DXVECTOR3 vPos(vInitialPos);
	if (vPos.x > m_siTableWidth /2)
	{
		vPos.x = m_siTableWidth - m_pSprite->GetScaledWidth() - 10.0f ;
	}
	m_iMoveFactor = m_siTableHeight/3;
	cGameElement::OnEndInit(vPos);
}
// ***************************************************************

// ***************************************************************
// Move paddle down
// ***************************************************************
void cPaddle::MoveDown( const float fElapsedTime )
{
	m_vPosition.y += (m_iMoveFactor * fElapsedTime) ;
	
	if(m_vPrevPosition != m_vPosition)
	{
		D3DXVECTOR2 trans(m_vPosition.x - m_vPrevPosition.x, m_vPosition.y - m_vPrevPosition.y);
		m_pBoundingPolygon->Translate(trans);
		m_vPrevPosition = m_vPosition;
	}
}
// ***************************************************************

// ***************************************************************
// move paddle up
// ***************************************************************
void cPaddle::MoveUp( const float fElapsedTime )
{
	m_vPosition.y -= (m_iMoveFactor * fElapsedTime) ;
	if(m_vPrevPosition != m_vPosition)
	{
		D3DXVECTOR2 trans(m_vPosition.x - m_vPrevPosition.x, m_vPosition.y - m_vPrevPosition.y);
		m_pBoundingPolygon->Translate(trans);
		m_vPrevPosition = m_vPosition;
	}
}
// ***************************************************************

// ***************************************************************
// move paddle left
// ***************************************************************
void cPaddle::MoveLeft( const float fElapsedTime )
{
	m_vPosition.x -= (m_iMoveFactor * fElapsedTime) ;

	if(m_vPrevPosition != m_vPosition)
	{
		D3DXVECTOR2 trans(m_vPosition.x - m_vPrevPosition.x, m_vPosition.y - m_vPrevPosition.y);
		m_pBoundingPolygon->Translate(trans);
		m_vPrevPosition = m_vPosition;
	}
}
// ***************************************************************

// ***************************************************************
// move paddle left
// ***************************************************************
void cPaddle::MoveRight( const float fElapsedTime )
{
	m_vPosition.x += (m_iMoveFactor * fElapsedTime) ;

	if(m_vPrevPosition != m_vPosition)
	{
		D3DXVECTOR2 trans(m_vPosition.x - m_vPrevPosition.x, m_vPosition.y - m_vPrevPosition.y);
		m_pBoundingPolygon->Translate(trans);
		m_vPrevPosition = m_vPosition;
	}
}
// ***************************************************************

// ***************************************************************
// called when the game is restarted
// ***************************************************************
void cPaddle::OnRestart( const D3DXVECTOR3& vInitialPos )
{
	cGameElement::OnRestart(vInitialPos);
	if (m_vPosition.x > m_siTableWidth /2)
	{
		m_vPosition.x = m_siTableWidth - m_pSprite->GetScaledWidth()-10.0f ;
		if(m_vPrevPosition != m_vPosition)
		{
			D3DXVECTOR2 trans(m_vPosition.x - m_vPrevPosition.x, m_vPosition.y - m_vPrevPosition.y);
			m_pBoundingPolygon->Translate(trans);
			m_vPrevPosition = m_vPosition;
		}
	}
}
// ***************************************************************

cPaddle * cPaddle::CastToPaddle()
{
	return this;
}
// ***************************************************************