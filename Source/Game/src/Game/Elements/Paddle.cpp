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
void cPaddle::Init( const cVector3& vInitialPos, const cString & strFilename )
{
	//cGameElement::OnBeginInit(strFilename, cVector2((float)m_siTableWidth/40, (float)m_siTableHeight/5));
	//// align the paddle at the other end

	//cVector3 vPos(vInitialPos);
	//if (vPos.m_dX > m_siTableWidth /2)
	//{
	//	vPos.m_dX = m_siTableWidth - m_pSprite->VGetSize().m_dX - 10.0f ;
	//}
	//m_iMoveFactor = m_siTableHeight/3;
	//cGameElement::OnEndInit(vPos);
}
// ***************************************************************

// ***************************************************************
// Move paddle down
// ***************************************************************
void cPaddle::MoveDown( const float fElapsedTime )
{
	//m_vPosition.m_dY += (m_iMoveFactor * fElapsedTime) ;
	//UpdatePosition();
}
// ***************************************************************

// ***************************************************************
// move paddle up
// ***************************************************************
void cPaddle::MoveUp( const float fElapsedTime )
{
	//m_vPosition.m_dY -= (m_iMoveFactor * fElapsedTime);
	//UpdatePosition();
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