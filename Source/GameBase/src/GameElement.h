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
#include "Vector3.h"
#include "Vector2.h"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class ISprite;
	class IPolygon;
}

namespace GameBase
{
	class cGameElement
		: public Base::cNonCopyable
	{
	public:
		GAMEBASE_API virtual  ~cGameElement();
		GAMEBASE_API virtual void Init(const Base::cVector3& vInitialPos, const Base::cString & strFilename) = 0;
		GAMEBASE_API virtual void SetBoundingRectangle();
		GAMEBASE_API virtual Graphics::IPolygon& GetBoundingRectangle();
		GAMEBASE_API virtual void OnRestart(const Base::cVector3& vInitialPos);
		GAMEBASE_API virtual const Base::cVector3& GetPosition();
		GAMEBASE_API virtual void SetSprite(shared_ptr<Graphics::ISprite> const pSprite );
		GAMEBASE_API virtual const shared_ptr<Graphics::ISprite> GetSprite() const;
		GAMEBASE_API virtual void Cleanup();
		GAMEBASE_API virtual void OnUpdate(float fElapsedTime) = 0;

	protected:
		GAMEBASE_API cGameElement();
		GAMEBASE_API void OnBeginInit(const Base::cString & strFilename, const Base::cVector2 & vSize);
		GAMEBASE_API void OnEndInit(const Base::cVector3& vInitialPos);
		GAMEBASE_API void UpdatePosition();

	protected:
		shared_ptr<Graphics::ISprite>		m_pSprite;
		Base::cVector3						m_vPosition;
		Base::cVector3						m_vPrevPosition;
		Graphics::IPolygon *				m_pBoundingPolygon;
	
	private:
		Base::cString						m_strFileName;
	};
#include "GameElement.inl"
}
#endif