// ***************************************************************
//  GraphicUtils   version:  1.0   Ankur Sheel  date: 2012/08/29
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "GraphicUtils.h"
#include "DxBase.hxx"
#include "Camera.hxx"

using namespace Graphics;
using namespace Base;

IGraphicUtils * cGraphicUtils::s_pGraphicUtils = NULL;

// *****************************************************************************
cGraphicUtils::cGraphicUtils()
{

}
// *****************************************************************************
cGraphicUtils::~cGraphicUtils()
{

}
// *****************************************************************************
IGraphicUtils * cGraphicUtils::Create()
{
	return DEBUG_NEW cGraphicUtils();
}

// ***************************************************************
cVector3 cGraphicUtils::ScreenToWorldSpace(const cVector2 & vScreenPos,
											const ICamera * const pCamera)
{
	cVector3 vViewSpace;

	vViewSpace.x = ((2.0f * vScreenPos.x) / IDXBase::GetInstance()->VGetScreenWidth()) - 1.0f;
	vViewSpace.y =  1 - ((2.0f * vScreenPos.y) / IDXBase::GetInstance()->VGetScreenHeight());
	vViewSpace.z = 1.0f;

	D3DXMATRIX matProjection = IDXBase::GetInstance()->VGetProjectionMatrix();
	vViewSpace.x = vViewSpace.x / matProjection._11;
	vViewSpace.y = vViewSpace.y / matProjection._22;
	vViewSpace.z = vViewSpace.z / matProjection._33;

	// Get the inverse of the view matrix to get the world matrix.
	D3DXMATRIX matView = pCamera->VGetViewMatrix();
	D3DXMATRIX matWorld;
	D3DXMatrixInverse(&matWorld, NULL, &matView);

	cVector3 vOrigin(matWorld._41, matWorld._42, matWorld._43);

	cVector3 direction;
	direction.x = (vViewSpace.x * matWorld._11) + (vViewSpace.y * matWorld._21)
		+ (vViewSpace.z * matWorld._31);
	direction.y = (vViewSpace.x * matWorld._12) + (vViewSpace.y * matWorld._22)
		+ (vViewSpace.z * matWorld._32);
	direction.z = (vViewSpace.x * matWorld._13) + (vViewSpace.y * matWorld._23)
		+ (vViewSpace.z * matWorld._33);
	direction.Normalize();

	D3DXMATRIX matViewProjection = matView * matProjection;

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

// ***************************************************************
IGraphicUtils * IGraphicUtils::GetInstance()
{
	if(cGraphicUtils::s_pGraphicUtils == NULL)
		cGraphicUtils::s_pGraphicUtils = cGraphicUtils::Create();
	return cGraphicUtils::s_pGraphicUtils ;
}

// ***************************************************************
void IGraphicUtils::Destroy()
{
	SAFE_DELETE(cGraphicUtils::s_pGraphicUtils);
}
