// ***************************************************************
//  FPS   version:  1.0   Ankur Sheel  date: 05/23/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef FPS_h__
#define FPS_h__

#include "FPS.hxx"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class IFont;
}
namespace Graphics
{
	class cFPS
		: public IFPS
	{
	private:
		cFPS(const cFPS&){}
		cFPS operator = (const cFPS&){}
	public:
		cFPS();
		~cFPS();
		void Render(const float fFPSValue);
		void Init(LPDIRECT3DDEVICE9 const pDevice, const D3DXVECTOR3& vInitialPos, const D3DXCOLOR& color = BLACK);
		void OnResetDevice(LPDIRECT3DDEVICE9 const pDevice);
		void OnLostDevice();
		IFont * GetFont();
		void Cleanup();
	private:
		IFont *				m_pFont;
	};
}
#endif // FPS_h__