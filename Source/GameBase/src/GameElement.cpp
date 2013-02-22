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
#include "BaseApp.h"

using namespace Graphics;
using namespace GameBase;
using namespace Base;

const cBaseApp * cGameElement::m_pBaseApp = NULL;

// *******************************************************************************************
cGameElement::cGameElement()
: m_pModel(NULL)
, m_bIsDirty(false)
, m_bActive(true)
, m_fReactivateTime(0.0f)
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
		if(m_pModel)
		{
			m_pModel->VRecalculateWorldMatrix(m_vPosition, m_vRotation, m_vScale);
		}
	}
}

// *******************************************************************************************
void cGameElement::OnUpdate(float fElapsedTime)
{
	if(!m_bActive)
	{
		if(m_fReactivateTime > 0.0f && m_fReactivateTime <= m_pBaseApp->GetRunningTime())
		{
			m_bActive = true;
			m_fReactivateTime = 0.0f;
			OnRestart();
		}
	}
	if(m_bIsDirty)
	{
		m_pModel->VRecalculateWorldMatrix(m_vPosition, m_vRotation, m_vScale);
		m_bIsDirty = false;
	}
}

// *******************************************************************************************
void cGameElement::Render(const ICamera * const pCamera)
{
	if (m_bActive && m_pModel)
	{
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

// *****************************************************************************
bool cGameElement::IsActive() const
{
	return m_bActive;
}

// *****************************************************************************
void cGameElement::VSetActive(const bool bActive)
{
	m_bActive = bActive;
}

// *******************************************************************************************
void cGameElement::MakeInactiveFor(const float fSeconds)
{
	if(m_bActive)
	{
		m_bActive = false;
		m_fReactivateTime = m_pBaseApp->GetRunningTime() + fSeconds;
	}
}

// *******************************************************************************************
void cGameElement::OnRestart()
{

}

// *****************************************************************************
void cGameElement::SetApp(const IBaseApp * const pApp)
{
	m_pBaseApp = dynamic_cast<const cBaseApp *>(pApp);
}


// *******************************************************************************************
void cGameElement::Cleanup()
{
	SAFE_DELETE(m_pModel);
}
