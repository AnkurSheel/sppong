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
#include "GameElement.h"
//#include "Polygon.hxx"
#include "Sprite.hxx"
//#include "DxBase.hxx"
#include "Vector2.h"

using namespace Graphics;
using namespace GameBase;
using namespace Base;
// ***************************************************************
// Constructor
// ***************************************************************
cGameElement::cGameElement()
: m_vPosition(-1.0f, -1.0f, -1.0f)
, m_vPrevPosition(-1.0f, -1.0f, -1.0f)
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cGameElement::~cGameElement()
{
	Cleanup();
}
// ***************************************************************

// ***************************************************************
// Initializes the game element
// ***************************************************************
void cGameElement::OnBeginInit(const cString & strFilename, const cVector2 & vSize)
{
	m_pSprite = ISprite::CreateSprite();
	m_strFileName = strFilename;
	m_pSprite->VInitialize(m_strFileName);
	m_pSprite->VSetSize(cVector2(vSize.m_dX, vSize.m_dY));
}
// ***************************************************************

void cGameElement::OnEndInit(const cVector3 & vInitialPos)
{
	m_vPosition = vInitialPos;
	m_vPrevPosition = m_vPosition;
	//m_pSprite->SetPosition(vInitialPos);
	SetBoundingRectangle();
}

// ***************************************************************
// Sets the bounding rectangle for the Game Element
// ***************************************************************
void cGameElement::SetBoundingRectangle()
{
	cVector2 v1[] = {
		cVector2(m_vPosition.m_dX, m_vPosition.m_dY),
		cVector2(m_vPosition.m_dX + m_pSprite->VGetSize().m_dX, m_vPosition.m_dY),
		cVector2(m_vPosition.m_dX + m_pSprite->VGetSize().m_dX, m_vPosition.m_dY 
		+ m_pSprite->VGetSize().m_dY),
		cVector2(m_vPosition.m_dX, m_vPosition.m_dY + m_pSprite->VGetSize().m_dY)
	};

	//m_pBoundingPolygon = IPolygon::CreatePolygon(v1, 4);
	
}
// ***************************************************************

// ***************************************************************
// Called when the game restarts
// ***************************************************************
void cGameElement::OnRestart( const cVector3 & vInitialPos )
{
	m_vPosition = vInitialPos;
	
	if(m_vPrevPosition != m_vPosition)
	{
		cVector2 trans(m_vPosition.m_dX - m_vPrevPosition.m_dX, m_vPosition.m_dY - m_vPrevPosition.m_dY);
		//m_pBoundingPolygon->Translate(trans);
		m_vPrevPosition = m_vPosition;
	}
}
// ***************************************************************

void cGameElement::Cleanup()
{
	//SAFE_DELETE(m_pBoundingPolygon);
}
// ***************************************************************

void cGameElement::UpdatePosition()
{
	if(m_vPrevPosition != m_vPosition)
	{
		m_pSprite->VSetPosition(cVector2(m_vPosition.m_dX, m_vPosition.m_dY));
		cVector2 trans(m_vPosition.m_dX - m_vPrevPosition.m_dX, m_vPosition.m_dY - m_vPrevPosition.m_dY);
		//m_pBoundingPolygon->Translate(trans);
		m_vPrevPosition = m_vPosition;
	}
}
// ***************************************************************
const Base::cVector3& cGameElement::GetPosition() const
{
	return m_vPosition;
}