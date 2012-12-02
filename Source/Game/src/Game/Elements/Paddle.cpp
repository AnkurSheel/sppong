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

using namespace Base;
using namespace GameBase;
// ***************************************************************
// Constructor
// ***************************************************************
cPaddle::cPaddle()
: m_iMoveFactor(0)
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
void cPaddle::VInitialize(const cGameElementDef & def )
{
	cPongGameElement::VInitialize(def);
	m_iMoveFactor = 5;
}
// ***************************************************************

// ***************************************************************
// Move paddle down
// ***************************************************************
void cPaddle::MoveDown( const float fElapsedTime )
{
	cVector3 vPos = GetPosition();
	vPos.m_dY -= m_iMoveFactor * fElapsedTime;
	SetPosition(vPos);
}
// ***************************************************************

// ***************************************************************
// move paddle up
// ***************************************************************
void cPaddle::MoveUp( const float fElapsedTime )
{
	cVector3 vPos = GetPosition();
	vPos.m_dY += m_iMoveFactor * fElapsedTime;
	SetPosition(vPos);
}
// ***************************************************************

// ***************************************************************
// move paddle left
// ***************************************************************
void cPaddle::MoveLeft( const float fElapsedTime )
{
	//m_vPosition.m_dX -= (m_iMoveFactor * fElapsedTime) ;
	//UpdatePosition();
}
// ***************************************************************

// ***************************************************************
// move paddle left
// ***************************************************************
void cPaddle::MoveRight( const float fElapsedTime )
{
	//m_vPosition.m_dX += (m_iMoveFactor * fElapsedTime) ;

	//UpdatePosition();
}
// ***************************************************************

// ***************************************************************
// called when the game is restarted
// ***************************************************************
void cPaddle::OnRestart( const Base::cVector3& vInitialPos )
{
	//cGameElement::OnRestart(vInitialPos);
	//if (m_vPosition.m_dX > m_siTableWidth /2)
	//{
	//	m_vPosition.m_dX = m_siTableWidth - m_pSprite->VGetSize().m_dX - 10.0f ;
	//	UpdatePosition();
	//}
}
// ***************************************************************

cPaddle * cPaddle::CastToPaddle()
{
	return this;
}
// ***************************************************************