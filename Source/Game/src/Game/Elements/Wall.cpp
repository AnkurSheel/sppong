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
#include "Sprite.hxx"

using namespace Base;
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
void cWall::Init( const cVector3& vPosition, const cString & strFilename )
{
	cPongGameElement::OnBeginInit(strFilename, cVector2((float)m_siTableWidth, (float)m_siTableHeight/25));
	cVector3 vPos(vPosition);
	if (vPos.m_dY > m_siTableHeight /2)
	{
		vPos.m_dY = (float)(m_siTableHeight - m_pSprite->VGetSize().m_dY);
	}
	cPongGameElement::OnEndInit(vPos);
}
// ***************************************************************