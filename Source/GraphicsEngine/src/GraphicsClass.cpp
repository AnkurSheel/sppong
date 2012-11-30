// ***************************************************************
//  GraphicsClass   version:  1.0   Ankur Sheel  date: 2012/09/13
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "GraphicsClass.h"
#include "DxBase.hxx"
#include "ShaderManager.hxx"
#include "TextureManager.hxx"
#include "Camera.hxx"
#include "GraphicUtils.h"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

IGraphicsClass * cGraphicsClass::s_pGraphic= NULL;

// ***************************************************************
Graphics::cGraphicsClass::cGraphicsClass()
{

}

// ***************************************************************
Graphics::cGraphicsClass::~cGraphicsClass()
{
	Cleanup();
}

// ***************************************************************
void Graphics::cGraphicsClass::VInitialize( const HWND & hWnd,
										   const Base::cColor & bkColor, 
										   const bool bFullScreen, 
										   const bool bVsyncEnabled,
										   const int iWidth,
										   const int iHeight,
										   const float fScreenDepth,
										   const float fScreenNear )
{
	if (IDXBase::GetInstance() == NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, " Could not create DXBase");
		PostQuitMessage(0);
		return;
	}
	IDXBase::GetInstance()->VInitialize(hWnd, bkColor, bFullScreen, bVsyncEnabled, iWidth,
		iHeight, fScreenDepth, fScreenNear);
}

// *************************************************************************
void Graphics::cGraphicsClass::VSetFullScreenMode(const bool bIsFullScreen)
{
	IDXBase::GetInstance()->VSetFullScreenMode(bIsFullScreen);
}

// ***************************************************************
void Graphics::cGraphicsClass::Cleanup()
{
	IShaderManager::Destroy();
	ITextureManager::Destroy();
	IDXBase::Destroy();
}

// ***************************************************************
IGraphicsClass * Graphics::cGraphicsClass::Create()
{
	return DEBUG_NEW cGraphicsClass();
}

// ***************************************************************
void Graphics::cGraphicsClass::VBeginRender()
{
	IDXBase::GetInstance()->VBeginRender();
}

// ***************************************************************
void Graphics::cGraphicsClass::VEndRender()
{
	IDXBase::GetInstance()->VEndRender();
}

// ***************************************************************
IGraphicsClass * IGraphicsClass::GetInstance()
{
	if(cGraphicsClass::s_pGraphic == NULL)
		cGraphicsClass::s_pGraphic = cGraphicsClass::Create();
	return cGraphicsClass::s_pGraphic ;
}

// ***************************************************************
void IGraphicsClass::Destroy()
{
	SAFE_DELETE(cGraphicsClass::s_pGraphic);
}

// ***************************************************************
cVector3 cGraphicsClass::ScreenToWorldSpace(const cVector2 & vScreenPos,
	const ICamera * const pCamera)
{
	cVector3 vViewSpace;

	vViewSpace.m_dX = ((2.0f * vScreenPos.m_dX) / IDXBase::GetInstance()->VGetScreenWidth()) - 1.0f;
	vViewSpace.m_dY = -((2.0f * vScreenPos.m_dY) / IDXBase::GetInstance()->VGetScreenHeight() - 1.0f);
	vViewSpace.m_dZ = 1.0f;
	
	D3DXMATRIX matProjection = IDXBase::GetInstance()->VGetProjectionMatrix();
	vViewSpace.m_dX = vViewSpace.m_dX / matProjection._11;
	vViewSpace.m_dY = vViewSpace.m_dY / matProjection._22;

	// Get the inverse of the view matrix.
	D3DXMATRIX matView = pCamera->VGetViewMatrix();
	D3DXMATRIX matInverseView;
	D3DXMatrixInverse(&matInverseView, NULL, &matView);

	D3DXVECTOR3 vOrigin(matInverseView._41, matInverseView._42, matInverseView._43);
	
	D3DXVECTOR3 direction;
	direction.x = (vViewSpace.m_dX * matInverseView._11) + (vViewSpace.m_dY * matInverseView._21) + (vViewSpace.m_dZ * matInverseView._31);
	direction.y = (vViewSpace.m_dX * matInverseView._12) + (vViewSpace.m_dY * matInverseView._22) + (vViewSpace.m_dZ * matInverseView._32);
	direction.z = (vViewSpace.m_dX * matInverseView._13) + (vViewSpace.m_dY * matInverseView._23) + (vViewSpace.m_dZ * matInverseView._33);
	D3DXVec3Normalize(&direction, &direction);
	
	D3DXVECTOR3 vPlaneNormal(0,0,-1);
	float fPlaneDistanceFromOrigin = 0;

	float fIncidentAngle = D3DXVec3Dot(&direction, &vPlaneNormal);
	if (fIncidentAngle != 0)
	{
		float t = (-(fPlaneDistanceFromOrigin + D3DXVec3Dot(&vOrigin, &vPlaneNormal))) / fIncidentAngle;
		vOrigin = vOrigin + (direction * t);
		return  cGraphicUtils::D3DXVEC3ToVector3(vOrigin);
	}
	return cVector3::Zero();
}