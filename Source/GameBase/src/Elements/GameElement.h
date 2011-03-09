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

namespace Base
{
	class cString;
}

namespace Graphics
{
	class ISprite;
	class cPolygon;
}

namespace GameBase
{
	class cGameElement
	{
	private :
		cGameElement(const cGameElement&){}
		cGameElement operator =(const cGameElement&){}
	protected:
		GAMEBASE_API cGameElement();
	public:
		GAMEBASE_API ~cGameElement();
		GAMEBASE_API virtual void Init(const D3DXVECTOR3& vInitialPos, const Base::cString & strFilename);
		GAMEBASE_API virtual void SetBoundingRectangle();
		GAMEBASE_API virtual Graphics::cPolygon& GetBoundingRectangle();
		GAMEBASE_API virtual void OnRestart(const D3DXVECTOR3& vInitialPos);
		GAMEBASE_API virtual const D3DXVECTOR3& GetPosition();
		GAMEBASE_API virtual void Render(LPDIRECT3DDEVICE9 const pDevice, const DWORD dwFlags = NULL, const D3DCOLOR& tint = Graphics::WHITE, const RECT* pSrcRect = NULL);
		GAMEBASE_API virtual void SetSprite(Graphics::ISprite* const sprite );
		GAMEBASE_API virtual const Graphics::ISprite * GetSprite() const;
		GAMEBASE_API virtual void Cleanup();
		GAMEBASE_API virtual void OnLostDevice();
		GAMEBASE_API virtual void OnResetDevice(LPDIRECT3DDEVICE9 const pDevice) = 0;

	protected:
		Graphics::ISprite *		m_pSprite;
		D3DXVECTOR3				m_vPosition;
		D3DXVECTOR3				m_vPrevPosition;
		Graphics::cPolygon *	m_pBoundingPolygon;
		Base::cString			m_strFileName;
	};
#include "GameElement.inl"
}
#endif