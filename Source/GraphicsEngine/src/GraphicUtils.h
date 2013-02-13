// ***************************************************************
//  GraphicUtils   version:  1.0   Ankur Sheel  date: 2012/08/29
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef GraphicUtils_h__
#define GraphicUtils_h__

#include "GraphicUtils.hxx"

namespace Base
{
	class cVector2;
	class cVector3;
}

namespace Graphics
{
	class ICamera;
}

namespace Graphics
{
	class cGraphicUtils
		: public IGraphicUtils
		, public Base::cNonCopyable
	{
	private:
		cGraphicUtils();
		~cGraphicUtils();
		Base::cVector3 ScreenToWorldSpace(const Base::cVector2 & vPos,
			const Graphics::ICamera * const pCamera);

	private:
		static IGraphicUtils* s_pGraphicUtils;		/*!< static object of this class */

	private:
		friend static IGraphicUtils * IGraphicUtils::GetInstance();
		friend static void IGraphicUtils::Destroy();

	};
}

#endif // GraphicUtils_h__