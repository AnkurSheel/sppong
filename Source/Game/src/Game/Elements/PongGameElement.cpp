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
#include "PongGameElement.h"
#include "2D/Polygon.h"

UINT cPongGameElement::m_siTableHeight = 0;
UINT cPongGameElement::m_siTableWidth = 0; 

// ***************************************************************
// Constructor
// ***************************************************************
cPongGameElement::cPongGameElement()
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cPongGameElement::~cPongGameElement()
{
}
// ***************************************************************

// ***************************************************************
// Called when the game restarts
// ***************************************************************
void cPongGameElement::OnRestart( const D3DXVECTOR3& vInitialPos )
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

void cPongGameElement::SetTableHeight( UINT val )
{
	m_siTableHeight = val;
}
// ***************************************************************

void cPongGameElement::SetTableWidth( UINT val )
{
	m_siTableWidth = val;
}
// ***************************************************************

cPaddle * cPongGameElement::CastToPaddle()
{
	return NULL;
}
// ***************************************************************

cBall * cPongGameElement::CastToBall()
{
	return NULL;
}
// ***************************************************************