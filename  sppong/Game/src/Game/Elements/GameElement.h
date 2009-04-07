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


class cSprite;

class cGameElement
{
protected:
	cSprite*		m_pSprite;
	D3DXVECTOR3		m_vPosition;
	static UINT		m_siTableHeight;
	static UINT		m_siTableWidth;
	D3DRECT			m_BoundingRect;

public:
	cGameElement();
	~cGameElement();
	void Init(const D3DXVECTOR3& vInitialPos, const UINT iTableWidth =0 , const UINT iTableHeight=0);
	void SetBoundingRectangle();
	D3DRECT& GetBoundingRectangle();
	void OnRestart(const D3DXVECTOR3& vInitialPos);
	const D3DXVECTOR3& GetPosition();
};

#include "GameElement.inl"

#endif // GameElement_h__