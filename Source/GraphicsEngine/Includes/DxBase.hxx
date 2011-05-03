// ***************************************************************
//  DxBase   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef DxBase_hxx__
#define DxBase_hxx__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class IDXBase
	{
	public:
		virtual ~IDXBase(){}
		virtual void Init(const HWND hWnd, const D3DCOLOR & bkColor, const bool bFullScreen)  = 0;
		virtual HRESULT ResetDevice()  = 0;
		virtual void Cleanup()  = 0;
		virtual HRESULT BeginRender() = 0;
		virtual void EndRender(const HRESULT hr) = 0;
		virtual LPDIRECT3DDEVICE9 GetDevice() const = 0;
		virtual UINT GetDisplayHeight() const = 0;
		virtual UINT GetDisplayWidth() const = 0;
		virtual HRESULT IsAvailable() const = 0;
		virtual void Destroy() = 0;
		GRAPHIC_API static IDXBase * GetInstance() ;

	};
}
#endif // DxBase_h__