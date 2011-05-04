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
#include "Sprite.hxx"
#include "Polygon.hxx"
#include "DxBase.hxx"

using namespace Graphics;
using namespace GameBase;
using namespace Base;
// ***************************************************************
// Constructor
// ***************************************************************
cGameElement::cGameElement()
: m_pSprite(NULL)
, m_vPosition(D3DXVECTOR3(-1.0f, -1.0f, -1.0f))
, m_vPrevPosition(D3DXVECTOR3(-1.0f, -1.0f, -1.0f))
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
void cGameElement::OnBeginInit(const cString & strFilename, const D3DXVECTOR2 & vSize)
{
	m_pSprite = ISprite::CreateSprite();
	m_strFileName = strFilename;
	m_pSprite->Init(IDXBase::GetInstance()->GetDevice(), m_strFileName);
	m_pSprite->SetSize(vSize.x, vSize.y);
}
// ***************************************************************

void cGameElement::OnEndInit(const D3DXVECTOR3& vInitialPos)
{
	m_vPosition = vInitialPos;
	m_vPrevPosition = m_vPosition;
	m_pSprite->SetPosition(vInitialPos);
	SetBoundingRectangle();
}

// ***************************************************************
// Sets the bounding rectangle for the Game Element
// ***************************************************************
void cGameElement::SetBoundingRectangle()
{
	D3DXVECTOR2 v1[] = {
		D3DXVECTOR2(m_vPosition.x, m_vPosition.y),
		D3DXVECTOR2(m_vPosition.x + m_pSprite->GetScaledWidth(), m_vPosition.y),
		D3DXVECTOR2(m_vPosition.x + m_pSprite->GetScaledWidth(), m_vPosition.y + m_pSprite->GetScaledHeight()),
		D3DXVECTOR2(m_vPosition.x, m_vPosition.y + m_pSprite->GetScaledHeight())
	};

	m_pBoundingPolygon = IPolygon::CreatePolygon(v1, 4);
}
// ***************************************************************

// ***************************************************************
// Called when the game restarts
// ***************************************************************
void cGameElement::OnRestart( const D3DXVECTOR3& vInitialPos )
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

void cGameElement::Cleanup()
{
	//SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pBoundingPolygon);
}
// ***************************************************************

void cGameElement::UpdatePosition()
{
	if(m_vPrevPosition != m_vPosition)
	{
		m_pSprite->SetPosition(m_vPosition);
		D3DXVECTOR2 trans(m_vPosition.x - m_vPrevPosition.x, m_vPosition.y - m_vPrevPosition.y);
		m_pBoundingPolygon->Translate(trans);
		m_vPrevPosition = m_vPosition;
	}

}
// ***************************************************************