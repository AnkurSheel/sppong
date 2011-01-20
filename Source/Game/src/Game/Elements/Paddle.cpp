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
#include "2D/Sprite.h"

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
void cPaddle::Init( const D3DXVECTOR3& vInitialPos, const char * const strFilename )
{
	cGameElement::Init(vInitialPos, strFilename);

	m_iMoveFactor = m_siTableHeight/3;
}
// ***************************************************************

// ***************************************************************
// Renders the paddle
// ***************************************************************
void cPaddle::Render(LPDIRECT3DDEVICE9 const pDevice, const DWORD dwFlags/* = NULL*/, const D3DCOLOR& tint/* = WHITE*/, const RECT* pSrcRect/* = NULL*/)
{
	m_pSprite->DrawSprite(pDevice, m_vPosition, D3DXSPRITE_ALPHABLEND);
}
// ***************************************************************

// ***************************************************************
// called when the device is reset
// ***************************************************************
void cPaddle::OnResetDevice(LPDIRECT3DDEVICE9 const pDevice)
{
	m_pSprite->Init(pDevice, m_strFileName);
	m_pSprite->SetSize((float)m_siTableWidth/50, (float)m_siTableHeight/5);

	// align the paddle at the other end
	if (m_vPosition.x > m_siTableWidth /2)
	{
		m_vPosition.x = m_siTableWidth - m_pSprite->GetScaledWidth()-10.0f ;
	}

	SetBoundingRectangle();
}
// ***************************************************************

// ***************************************************************
// Move paddle down
// ***************************************************************
void cPaddle::MoveDown( const float fElapsedTime )
{
	m_vPosition.y += (m_iMoveFactor * fElapsedTime) ;

	SetBoundingRectangle();
}
// ***************************************************************

// ***************************************************************
// move paddle up
// ***************************************************************
void cPaddle::MoveUp( const float fElapsedTime )
{
	m_vPosition.y -= (m_iMoveFactor * fElapsedTime) ;

	SetBoundingRectangle();
}
// ***************************************************************

// ***************************************************************
// move paddle left
// ***************************************************************
void cPaddle::MoveLeft( const float fElapsedTime )
{
	m_vPosition.x -= (m_iMoveFactor * fElapsedTime) ;

	SetBoundingRectangle();
}
// ***************************************************************

// ***************************************************************
// move paddle left
// ***************************************************************
void cPaddle::MoveRight( const float fElapsedTime )
{
	m_vPosition.x += (m_iMoveFactor * fElapsedTime) ;

	SetBoundingRectangle();
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
		SetBoundingRectangle();
	}
}
// ***************************************************************