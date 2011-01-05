// ***************************************************************
//  Ball   version:  1.0   Ankur Sheel  date: 05/13/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Ball.h"
#include "2D/Sprite.h"

// ***************************************************************
// Constructor
// ***************************************************************
cBall::cBall()
{
	int b= 5;
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cBall::~cBall()
{
}
// ***************************************************************
// Initialize the ball
// ***************************************************************
void cBall::Init( const D3DXVECTOR3& vInitialPos, 
				 const UINT iTableWidth,
				 const UINT iTableHeight )
{
	cGameElement::Init(vInitialPos, iTableWidth,iTableHeight);

	m_vSpeed = D3DXVECTOR3((float)m_siTableWidth/4, (float)m_siTableHeight/6, 0.0f);

}
// ***************************************************************

// ***************************************************************
// Renders the ball
// ***************************************************************
void cBall::Render( LPDIRECT3DDEVICE9 const pDevice, 
				   const float fElapsedTime )
{
	// update the position of the wall
	m_vPosition += (m_vSpeed * fElapsedTime);
	m_pSprite->DrawSprite(pDevice, m_vPosition, D3DXSPRITE_ALPHABLEND);

	SetBoundingRectangle();
}
// ***************************************************************

// ***************************************************************
// Function called when the device needs to be reset
// ***************************************************************
void cBall::OnResetDevice( ISprite* const sprite )
{
	m_pSprite = sprite;
	m_pSprite->SetSize((float)m_siTableHeight/30, (float)m_siTableHeight/30);
}
// ***************************************************************

// ***************************************************************
// Changes the speed in the X direction
// ***************************************************************
void cBall::ChangeSpeedX()
{
	m_vSpeed.x = -m_vSpeed.x;
}
// ***************************************************************

// ***************************************************************
// Changes the speed in the Y direction
// ***************************************************************
void cBall::ChangeSpeedY()
{
	m_vSpeed.y = - m_vSpeed.y;
}
// ***************************************************************