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
#include "Camera.hxx"

namespace Graphics
{
	/********************************************//**
     * @brief Class Declaration for \c ICamera
     * interface
     ***********************************************/
	class cCamera
		: public ICamera
		, public Base::cNonCopyable
	{
	public:
		cCamera();
	
	private:
		~cCamera();
		Base::cVector3 VGetPosition() const;
		void VSetPosition(const Base::cVector3 & vPosition);
		const D3DXMATRIX & VGetViewMatrix() const;
		/********************************************//**
 		 * @param[in] vRotation The rotation of the camera
		 *
		 * Sets the rotation of the camera 
		 ***********************************************/
		void SetRotation(const Base::cVector3 & vRotation);

	private:
		/********************************************//**
		 *
		 * Calculates the view matrix based on the current position
		 * and rotation
		 ***********************************************/
		void CalculateViewMatrix();
	
	private:
		Base::cVector3		m_vPosition;	/*!< The position of the camera */
		Base::cVector3		m_vRotation;	/*!< The rotation of the camera */
		D3DXMATRIX			m_matView;		/*!< The current view matrix */
	};
}
#endif // Camera_h__