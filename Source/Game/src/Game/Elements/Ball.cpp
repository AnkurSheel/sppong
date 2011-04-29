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
#include "Sprite.hxx"
#include "MainWindow.hxx"
#include "Polygon.hxx"
#include "RandomGenerator.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;
// ***************************************************************
// Constructor
// ***************************************************************
cBall::cBall()
: m_pRandomGenerator(NULL)
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cBall::~cBall()
{
	SAFE_DELETE(m_pRandomGenerator);
}
// ***************************************************************
// Initialize the ball
// ***************************************************************
void cBall::Init( const D3DXVECTOR3& vInitialPos, const cString & strFilename)
{
	cPongGameElement::Init(vInitialPos, strFilename);
	m_pRandomGenerator = IRandomGenerator::CreateRandomGenerator();
	if (m_pRandomGenerator)
	{
		Log_Write_L1(ILogger::LT_DEBUG, cString(100, "Random Generator created for Ball with seed %u", m_pRandomGenerator->GetRandomSeed()));
	}
	m_vSpeed = D3DXVECTOR3((float)m_siTableWidth/4, (float)m_siTableHeight/6, 0.0f);
}
// ***************************************************************

// ***************************************************************
// Renders the ball
// ***************************************************************
void cBall::Render(LPDIRECT3DDEVICE9 const pDevice, const DWORD dwFlags/* = NULL*/, const D3DCOLOR& tint /*= WHITE*/, const RECT* pSrcRect/* = NULL*/)
{
	m_vPosition += (m_vSpeed * IMainWindow::TheWindow()->GetElapsedTime());
	// update the position of the ball
	m_pSprite->DrawSprite(pDevice, m_vPosition, D3DXSPRITE_ALPHABLEND);

	if(m_vPrevPosition != m_vPosition)
	{
		D3DXVECTOR2 trans(m_vPosition.x - m_vPrevPosition.x, m_vPosition.y - m_vPrevPosition.y);
		m_pBoundingPolygon->Translate(trans);
		m_vPrevPosition = m_vPosition;
	}

}
// ***************************************************************

// ***************************************************************
// Function called when the device needs to be reset
// ***************************************************************
void cBall::OnResetDevice( LPDIRECT3DDEVICE9 const pDevice)
{
	m_pSprite->Init(pDevice, m_strFileName);
	m_pSprite->SetSize((float)m_siTableHeight/30, (float)m_siTableHeight/25);
	SetBoundingRectangle();
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

void cBall::OnRestart( const D3DXVECTOR3& vInitialPos )
{
	cPongGameElement::OnRestart(vInitialPos);
	int iSpeedDirection = m_pRandomGenerator->Random(2);
	if (iSpeedDirection == 1)
	{
		m_vSpeed.x = -m_vSpeed.x;
	}

	iSpeedDirection = m_pRandomGenerator->Random(2);
	if (iSpeedDirection == 1)
	{
		m_vSpeed.y = -m_vSpeed.y;
	}


}
// ***************************************************************

void cBall::Cleanup()
{
	SAFE_DELETE(m_pRandomGenerator);
	cGameElement::Cleanup();
}
// ***************************************************************

cBall * cBall::CastToBall()
{
	return this;
}
// ***************************************************************