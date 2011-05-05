// ***************************************************************
//  Score   version:  1.0   Ankur Sheel  date: 05/15/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Score_h__
#define Score_h__

namespace Base
{
	class cString;
}

namespace Graphics
{
	class IFont ;
}
class cScore
{
private:
	cScore(const cScore&){}
	cScore operator = (const cScore&){}
public:
	cScore();
	~cScore();
	void Render();
	void Init(const D3DXVECTOR3& vInitialPos);
	void OnResetDevice(LPDIRECT3DDEVICE9 const pDevice);
	void OnLostDevice();
	void Cleanup();
	void IncrementScore();

private:
	Graphics::IFont *	m_pFont;
	RECT				m_BoundingRect;
	DWORD				m_dwFormat;
	UINT				m_iValue;
	Base::cString		m_strValue;

};
#endif // Score_h__