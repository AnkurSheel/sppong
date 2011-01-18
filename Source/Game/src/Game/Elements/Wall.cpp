// ***************************************************************
//  Wall   version:  1.0   Ankur Sheel  date: 05/15/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Wall.h"
#include "2D/Sprite.h"

// ***************************************************************
// Constructor
// *************************************************************** 	
cWall::cWall()
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// *************************************************************** 	
cWall::~cWall()
{
}
// ***************************************************************

// ***************************************************************
// Initialize the wall
// *************************************************************** 	
void cWall::Init( const D3DXVECTOR3& vPosition )
{
	cPongGameElement::Init(vPosition);
}
// ***************************************************************

// ***************************************************************
// Render the wall
// *************************************************************** 	
void cWall::Render( LPDIRECT3DDEVICE9 const pDevice )
{
	cPongGameElement::Render(pDevice, D3DXSPRITE_ALPHABLEND);
}
// ***************************************************************

// ***************************************************************
// called when the device is reset
// *************************************************************** 	
void cWall::OnResetDevice(LPDIRECT3DDEVICE9 const pDevice, const char * const strFilename)
{
	m_pSprite->Init(pDevice, strFilename);
	m_pSprite->SetSize((float)m_siTableWidth, (float)m_siTableHeight/30);

	// align the paddle at the other end
	if (m_vPosition.y > m_siTableHeight /2)
	{
		m_vPosition.y = (float)(m_siTableHeight - m_pSprite->GetScaledHeight());
	}
	SetBoundingRectangle();
}
// ***************************************************************