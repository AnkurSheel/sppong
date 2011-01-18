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
	SetBoundingRectangle();
}
// ***************************************************************

void cPongGameElement::SetTableHeight( UINT val )
{
	m_siTableHeight = val;
}

void cPongGameElement::SetTableWidth( UINT val )
{
	m_siTableWidth = val;
}