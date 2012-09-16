// ***************************************************************
//  GraphicsClass   version:  1.0   Ankur Sheel  date: 2012/09/13
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef GraphicsClass_h__
#define GraphicsClass_h__

#include "GraphicsClass.hxx"

namespace Graphics
{
	class IDXBase;
}

namespace Graphics
{
	class cGraphicsClass
		: public IGraphicsClass
		, public Base::cNonCopyable
	{
	public:
		static IGraphicsClass * Create();
		void VInitialize(const HWND hWnd, const Base::cColor & bkColor,
			const bool bFullScreen, const bool bVsyncEnabled, const int iWidth,
			const int iHeight, const float fScreenDepth, const float fScreenNear);
		void VBeginRender();
		void VEndRender();

		void Update();
		void Cleanup();
	
	private:
		cGraphicsClass();
		~cGraphicsClass();

	public:
		static IGraphicsClass * s_pGraphic;
	};
}
#endif // GraphicsClass_h__