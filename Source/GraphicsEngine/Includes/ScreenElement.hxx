// ***************************************************************
//  ScreenElement   version:  1.0   Ankur Sheel  date: 2011/05/05
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ScreenElement_hxx__
#define ScreenElement_hxx__

#include "GraphicEngineDefines.h"
#include "Constants.h"

namespace Graphics
{
	class IScreenElement : public Base::cNonCopyable
	{
	public:
		virtual ~IScreenElement(){};
		GRAPHIC_API virtual void OnLostDevice() = 0;
		GRAPHIC_API virtual void OnResetDevice() = 0;
		GRAPHIC_API virtual bool IsVisible() = 0;
		GRAPHIC_API virtual void OnRender(LPDIRECT3DDEVICE9 const pDevice) = 0;
		GRAPHIC_API virtual void Cleanup() = 0;
		GRAPHIC_API virtual void SetVisible(const bool bVisible) = 0;
	};
}
#endif // ScreenElement_hxx__