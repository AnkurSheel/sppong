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
#include "Essentials/MainWindow.h"

// ***************************************************************
// Constructor
// ***************************************************************
cBall::cBall()
{
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
void cBall::Init( const D3DXVECTOR3& vInitialPos, const char * const strFilename)
{
	cPongGameElement::Init(vInitialPos, strFilename);

	m_vSpeed = D3DXVECTOR3((float)m_siTableWidth/4, (float)m_siTableHeight/6, 0.0f);

}
// ***************************************************************

// ***************************************************************
// Renders the ball
// ***************************************************************
void cBall::Render(LPDIRECT3DDEVICE9 const pDevice, const DWORD dwFlags/* = NULL*/, const D3DCOLOR& tint /*= WHITE*/, const RECT* pSrcRect/* = NULL*/)
{
	// update the position of the ball
	m_vPosition += (m_vSpeed * IMainWindow::TheWindow()->GetElapsedTime());
	m_pSprite->DrawSprite(pDevice, m_vPosition, D3DXSPRITE_ALPHABLEND);

	SetBoundingRectangle();
}
// ***************************************************************

// ***************************************************************
// Function called when the device needs to be reset
// ***************************************************************
void cBall::OnResetDevice( LPDIRECT3DDEVICE9 const pDevice)
{
	m_pSprite->Init(pDevice, m_strFileName);
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