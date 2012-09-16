// ***************************************************************
//  Camera   version:  1.0   Ankur Sheel  date: 2012/09/15
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Camera_h__
#define Camera_h__
#include <d3dx10math.h>
#include "Camera.hxx"

namespace Base
{
	class cVector3;
}

namespace Graphics
{
	class cCamera
		: public ICamera
		, public Base::cNonCopyable
	{
	public:
		cCamera();
		const D3DXMATRIX & GetViewMatrix() const;
	
	private:
		~cCamera();
		void VSetPosition(const Base::cVector3 & vPosition);
		void SetRotation(const Base::cVector3 & vRotation);

	private:
		void CalculateViewMatrix();
	private:
		Base::cVector3		m_vPosition;
		Base::cVector3		m_vRotation;
		D3DXMATRIX			m_matView;
	};
}
#endif // Camera_h__