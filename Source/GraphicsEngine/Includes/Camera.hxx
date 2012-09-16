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
namespace Graphics
{
	class ICamera
	{
	public:
		virtual ~ICamera(){}
		virtual void VSetPosition(const Base::cVector3 & vPosition) = 0;
		GRAPHIC_API static ICamera * CreateCamera();
	};
}