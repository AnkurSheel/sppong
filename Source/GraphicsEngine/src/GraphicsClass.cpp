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

	vViewSpace.m_dX = ((2.0f * vScreenPos.x) / IDXBase::GetInstance()->VGetScreenWidth()) - 1.0f;
	vViewSpace.m_dY =  1 - ((2.0f * vScreenPos.y) / IDXBase::GetInstance()->VGetScreenHeight());
	vViewSpace.m_dZ = 1.0f;
	
	D3DXMATRIX matProjection = IDXBase::GetInstance()->VGetProjectionMatrix();
	vViewSpace.m_dX = vViewSpace.m_dX / matProjection._11;
	vViewSpace.m_dY = vViewSpace.m_dY / matProjection._22;
	vViewSpace.m_dZ = vViewSpace.m_dZ / matProjection._33;

	// Get the inverse of the view matrix to get the world matrix.
	D3DXMATRIX matView = pCamera->VGetViewMatrix();
	D3DXMATRIX matWorld;
	D3DXMatrixInverse(&matWorld, NULL, &matView);

	cVector3 vOrigin(matWorld._41, matWorld._42, matWorld._43);
	
	cVector3 direction;
	direction.m_dX = (vViewSpace.m_dX * matWorld._11) + (vViewSpace.m_dY * matWorld._21) + (vViewSpace.m_dZ * matWorld._31);
	direction.m_dY = (vViewSpace.m_dX * matWorld._12) + (vViewSpace.m_dY * matWorld._22) + (vViewSpace.m_dZ * matWorld._32);
	direction.m_dZ = (vViewSpace.m_dX * matWorld._13) + (vViewSpace.m_dY * matWorld._23) + (vViewSpace.m_dZ * matWorld._33);
	direction.Normalize();
	
	D3DXMATRIX matViewProjection;
	D3DXMatrixMultiply(&matViewProjection, &matView, &matProjection);
	
	cVector3 vPlaneNormal(matViewProjection._13, matViewProjection._23, matViewProjection._33);
	vPlaneNormal.Normalize();

	float fPlaneDistanceFromOrigin = 0;

	float fIncidentAngle = direction.Dot(vPlaneNormal);
	if (fIncidentAngle != 0)
	{
		float t = (-(fPlaneDistanceFromOrigin + vOrigin.Dot(vPlaneNormal))) / fIncidentAngle;
		vOrigin = vOrigin + (direction * t);
		return  vOrigin;
	}
	return cVector3::Zero();
}