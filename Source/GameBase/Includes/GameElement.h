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
	class IModel;
	class ICamera;
}

namespace GameBase
{
	class cGameElementDef
	{
	public:
		Base::cString	strModelPath;
		Base::cVector3	vPosition;
		Base::cVector3	vScale;
	};

	class cGameElement
		: public Base::cNonCopyable
	{
	public:
		GAMEBASE_API cGameElement();
		GAMEBASE_API virtual  ~cGameElement();
		GAMEBASE_API void Initialize(const cGameElementDef & def);
		GAMEBASE_API void Render(const Graphics::ICamera * const pCamera);
		GAMEBASE_API void Cleanup();

	private:
		Base::cString		m_strFileName;
		Graphics::IModel *	m_pModel;	
	};
}
#endif