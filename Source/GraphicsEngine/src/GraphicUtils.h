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

namespace Base
{
	class cVector2;
	class cVector3;
}
namespace Graphics
{
	D3DXVECTOR3 cVector3ToD3DXVECTOR3( const Base::cVector3& inVec );
	Base::cVector3 D3DXVECTOR3TocVector3( const D3DXVECTOR3& inVec );
	D3DXVECTOR2 cVector2ToD3DXVECTOR2( const Base::cVector2& inVec );
	Base::cVector2 D3DXVECTOR2TocVector2( const D3DXVECTOR2& inVec );
}

#endif // GraphicUtils_h__