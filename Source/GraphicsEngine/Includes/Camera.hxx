// ***************************************************************
//  Camera   version:  1.0   Ankur Sheel  date: 2012/09/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include "GraphicEngineDefines.h"
namespace Base
{
	class cVector3;
}

namespace Graphics
{
/********************************************//**
 * @brief Interface to keep track of where the camera is
 * and its current rotation
 *
 ***********************************************/
	class ICamera
	{
	public:
		virtual ~ICamera(){}
		/********************************************//**
 		 * @param[in] vPosition The position of the camera
		 *
		 * Sets the position of the camera 
		 ***********************************************/
		virtual void VSetPosition(const Base::cVector3 & vPosition) = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		GRAPHIC_API static ICamera * CreateCamera();
	};
}