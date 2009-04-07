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

class cMyFont ;

class cFPS
{
private:
	cMyFont*	m_pFont;
	RECT		m_BoundingRect;
	DWORD		m_dwFormat;
	//TCHAR		m_strValue[20];
	char		m_strValue[20];
	D3DCOLOR	m_FontColor;

	cFPS(const cFPS&){}
	cFPS operator = (const cFPS&){}
public:
	cFPS();
	~cFPS();
	void Render(LPDIRECT3DDEVICE9 const pDevice, const float fFPSValue);
	void Init(LPDIRECT3DDEVICE9 const pDevice, const D3DXVECTOR3& vInitialPos, const D3DXCOLOR& color = BLACK);
	void OnResetDevice(LPDIRECT3DDEVICE9 const pDevice);
	void OnLostDevice();
	void Cleanup();
};
#endif // FPS_h__