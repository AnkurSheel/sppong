// ***************************************************************
//  Camera   version:  1.0   Ankur Sheel  date: 2012/09/15
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Camera.h"
#include "GraphicUtils.h"

using namespace Graphics;
using namespace Base;

// ***************************************************************
cCamera::cCamera()
: m_vPosition(cVector3::Zero())
, m_vRotation(cVector3::Zero())
{
	CalculateViewMatrix();
}

// ***************************************************************
cCamera::~cCamera()
{

}

// *****************************************************************************
void cCamera::VUpdate()
{
	if (m_bIsDirty)
	{
		m_bIsDirty = false;
		CalculateViewMatrix();
	}
}

// *************************************************************************
cVector3 cCamera::VGetPosition() const
{
	return m_vPosition;
}

// ***************************************************************
void cCamera::VSetPosition( const cVector3 & vPosition )
{
	if (m_vPosition != vPosition)
	{
		m_vPosition = vPosition;
		m_bIsDirty = true;
	}	
}

// ***************************************************************
void cCamera::VSetRotation( const cVector3 & vRotation )
{
	if (m_vRotation != vRotation)
	{
		m_vRotation = vRotation;
		m_bIsDirty = true;
	}	
}

const D3DXMATRIX & cCamera::VGetViewMatrix() const 
{ 
	return m_matView; 
}

// ***************************************************************
void cCamera::CalculateViewMatrix()
{
	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	float fPitch = static_cast<float>(DegtoRad(m_vRotation.m_dX));
	float fYaw   = static_cast<float>(DegtoRad(m_vRotation.m_dY));
	float fRoll  = static_cast<float>(DegtoRad(m_vRotation.m_dZ));

	D3DXMATRIX matRotation;

	D3DXMatrixRotationYawPitchRoll(&matRotation, fYaw, fPitch, fRoll);

	D3DXVECTOR3 vLookAt;
	vLookAt.x = 0.0f;
	vLookAt.y = 0.0f;
	vLookAt.z = 1.0f;

	D3DXVec3TransformCoord(&vLookAt, &vLookAt, &matRotation);

	D3DXVECTOR3 up;
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	D3DXVec3TransformCoord(&up, &up, &matRotation);

	D3DXVECTOR3 vPosition = cGraphicUtils::Vector3ToD3DXVEC3(m_vPosition);
	vLookAt = vPosition + vLookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_matView, &vPosition, &vLookAt, &up);
}
// ***************************************************************
ICamera * ICamera::CreateCamera()
{
	return DEBUG_NEW cCamera();
}