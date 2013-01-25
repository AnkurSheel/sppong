// *****************************************************************************
//  GameElement   version:  1.0   Ankur Sheel  date: 05/14/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "GameElement.h"
#include "ObjModelLoader.hxx"
#include "Model.hxx"
#include "Vector3.h"

using namespace Graphics;
using namespace GameBase;
using namespace Base;
// *******************************************************************************************
cGameElement::cGameElement()
: m_pModel(NULL)
, m_bIsDirty(false)
{

}

// *******************************************************************************************
cGameElement::~cGameElement()
{
	Cleanup();
}

// *******************************************************************************************
void cGameElement::VInitialize(const cGameElementDef & def)
{
	if (!def.strModelName.IsEmpty())
	{
		m_pModel = IModel::CreateModel();
		IObjModelLoader::GetInstance()->VLoadModelFromFile(def.strModelName, m_pModel);
		SetPosition(def.vPosition);
		SetScale(def.vScale);
		SetRotation(def.vRotation);
	}
}

// *******************************************************************************************
void cGameElement::Render(const ICamera * const pCamera)
{
	if (m_pModel)
	{
		if(m_bIsDirty)
		{
			m_pModel->VRecalculateWorldMatrix(m_vPosition, m_vRotation, m_vScale);
			m_bIsDirty = false;
		}
		m_pModel->VRender(pCamera);
	}
}

// *******************************************************************************************
cVector3 cGameElement::GetRotation() const
{
	return m_vRotation;
}

// *******************************************************************************************
void cGameElement::SetRotation(const Base::cVector3 & vRadians)
{
	if(m_vRotation != vRadians)
	{
		m_bIsDirty = true;
		m_vRotation.x = ClampToTwoPi(vRadians.x);
		m_vRotation.y = ClampToTwoPi(vRadians.y);
		m_vRotation.z = ClampToTwoPi(vRadians.z);
	}
}

// ***************************************************************************************
void cGameElement::SetPosition(const Base::cVector3 & vPosition)
{
	if(m_vPosition != vPosition)
	{
		m_bIsDirty = true;
		m_vPosition = vPosition;
	}
}

// ***************************************************************************************
cVector3 cGameElement::GetPosition() const
{
	return m_vPosition;
}

// ***************************************************************************************
void cGameElement::SetScale(const Base::cVector3 & vScale)
{
	if(m_vScale!= vScale)
	{
		m_bIsDirty = true;
		m_vScale= vScale;
	}
}

// ***************************************************************************************
cVector3 cGameElement::GetScale() const
{
	return m_vScale;
}

// *******************************************************************************************
const IAABB * const cGameElement::GetAABB() const
{
	if(m_pModel)
	{
		return m_pModel->VGetAABB();
	}
	return NULL;
}

// *******************************************************************************************
void cGameElement::Cleanup()
{
	SAFE_DELETE(m_pModel);
}
