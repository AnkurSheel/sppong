// ***************************************************************
//  GameElement   version:  1.0   Ankur Sheel  date: 05/14/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef GameElement_h__
#define GameElement_h__

#include "GameBaseDefines.h"
#include "Constants.h"

class ISprite;

class cGameElement
{
private :
	cGameElement(const cGameElement&){}
	cGameElement operator =(const cGameElement&){}
public:
	cGameElement();
	~cGameElement();
	void Init(const D3DXVECTOR3& vInitialPos);
	void SetBoundingRectangle();
	D3DRECT& GetBoundingRectangle();
	void OnRestart(const D3DXVECTOR3& vInitialPos);
	const D3DXVECTOR3& GetPosition();
	void Render(LPDIRECT3DDEVICE9 const pDevice, const DWORD dwFlags = NULL, const D3DCOLOR& tint = WHITE, const RECT* pSrcRect = NULL);
	void SetSprite(ISprite* const sprite );
	const ISprite * GetSprite() const;
	static void SetTableHeight(UINT val);
	static void SetTableWidth(UINT val);
	virtual void Cleanup();
	virtual void OnLostDevice();
	virtual void OnResetDevice(LPDIRECT3DDEVICE9 const pDevice, const char * const strFilename) = 0;


protected:
	ISprite*		m_pSprite;
	D3DXVECTOR3		m_vPosition;
	static UINT		m_siTableHeight;
	static UINT		m_siTableWidth;
	D3DRECT			m_BoundingRect;

};

#include "GameElement.inl"
#endif