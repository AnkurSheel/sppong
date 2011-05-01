// ***************************************************************
//  FPS   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef FPS_hxx__
#define FPS_hxx__

namespace Graphics
{
	class IFPS
	{
	public:
		virtual ~IFPS(){}
		virtual void Render(LPDIRECT3DDEVICE9 const pDevice, const float fFPSValue) = 0;
		virtual void Init(LPDIRECT3DDEVICE9 const pDevice, const D3DXVECTOR3& vInitialPos, const D3DXCOLOR& color) = 0;
		virtual void OnResetDevice(LPDIRECT3DDEVICE9 const pDevice) = 0;
		virtual void OnLostDevice() = 0;
		virtual void Cleanup() = 0;
		static IFPS * CreateFPS();
	};
}
#endif // FPS_h__