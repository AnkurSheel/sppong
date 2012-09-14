// ***************************************************************
//  GraphicsClass   version:  1.0   Ankur Sheel  date: 2012/09/13
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef GraphicsClass_hxx__
#define GraphicsClass_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	class cColor;
}

namespace Graphics
{
	class IGraphicsClass
	{
	public:
		/********************************************//**
		 * @return Returns a pointer to the singleton object
		 *
		 * Creates and returns a pointer to a singleton object of this interface
		 ***********************************************/
		GRAPHIC_API static IGraphicsClass * GetInstance();
		/********************************************//**
		 *
		 * Releases the DirectX object and deletes the singleton object
		 ***********************************************/
		GRAPHIC_API static void Destroy();

		virtual void VInitialize(const HWND hWnd, const Base::cColor & bkColor,
			const bool bFullScreen, const bool bVsyncEnabled, const int iWidth,
			const int iHeight, const float fScreenDepth, const float fScreenNear) = 0;
		virtual void VBeginRender() = 0;
		virtual void VEndRender() = 0;
	protected:
		virtual ~IGraphicsClass(){}
	};
	//typedef IGraphicsClass::GetInstance() SingletonGraphicsClass;

}
#endif // GraphicsClass_hxx__