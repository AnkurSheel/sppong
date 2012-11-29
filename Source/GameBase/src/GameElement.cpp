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
#include "ObjModelLoader.hxx"
#include "Model.hxx"
#include "Vector3.h"

using namespace Graphics;
using namespace GameBase;
using namespace Base;
//// ***************************************************************
//
//// ***************************************************************
//
//void cGameElement::OnEndInit(const cVector3 & vInitialPos)
//{
//	m_vPosition = vInitialPos;
//	//m_pSprite->SetPosition(vInitialPos);
//	SetBoundingRectangle();
//}
//
//// ***************************************************************
//// Sets the bounding rectangle for the Game Element
//// ***************************************************************
//void cGameElement::SetBoundingRectangle()
//{
//	cVector2 v1[] = {
//		cVector2(m_vPosition.m_dX, m_vPosition.m_dY),
//		cVector2(m_vPosition.m_dX + m_pSprite->VGetSize().m_dX, m_vPosition.m_dY),
//		cVector2(m_vPosition.m_dX + m_pSprite->VGetSize().m_dX, m_vPosition.m_dY 
//		+ m_pSprite->VGetSize().m_dY),
//		cVector2(m_vPosition.m_dX, m_vPosition.m_dY + m_pSprite->VGetSize().m_dY)
//	};
//
//	//m_pBoundingPolygon = IPolygon::CreatePolygon(v1, 4);
//	
//}
//// ***************************************************************
//
//// ***************************************************************
//// Called when the game restarts
//// ***************************************************************
//void cGameElement::OnRestart( const cVector3 & vInitialPos )
//{
//	m_vPosition = vInitialPos;
//}
//// ***************************************************************
//
//void cGameElement::Cleanup()
//{
//	//SAFE_DELETE(m_pBoundingPolygon);
//}
//// ***************************************************************
//
//void cGameElement::UpdatePosition()
//{
//	//if(m_vPrevPosition != m_vPosition)
//	//{
//	//	m_pSprite->VSetPosition(cVector2(m_vPosition.m_dX, m_vPosition.m_dY));
//	//	cVector2 trans(m_vPosition.m_dX - m_vPrevPosition.m_dX, m_vPosition.m_dY - m_vPrevPosition.m_dY);
//	//	//m_pBoundingPolygon->Translate(trans);
//	//	m_vPrevPosition = m_vPosition;
//	//}
//}
//// ***************************************************************
//const Base::cVector3& cGameElement::GetPosition() const
//{
//	return m_vPosition;
//}

// *****************************************************************************
cGameElement::cGameElement()
: m_pModel(NULL)
{

}

// *****************************************************************************
cGameElement::~cGameElement()
{
	Cleanup();
}

// *****************************************************************************
void cGameElement::Initialize(const cGameElementDef & def)
{
	if (!def.strModelPath.IsEmpty())
	{
		m_pModel = IModel::CreateModel();
		IObjModelLoader::GetInstance()->VLoadModelFromFile(def.strModelPath, m_pModel);
		m_pModel->VSetPosition(def.vPosition);
		m_pModel->VSetScale(def.vScale);
	}
}

// *****************************************************************************
void cGameElement::Cleanup()
{
	SAFE_DELETE(m_pModel);
}
// *****************************************************************************
void cGameElement::Render(const ICamera * const pCamera)
{
	if (m_pModel)
	{
		m_pModel->VRender(pCamera);
	}
}
