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
	class ICamera;
}

namespace Graphics
{
	/********************************************//**
	 * @brief Class to convert between Base classes and 
	 * DirectX classes
	 ***********************************************/
	class cGraphicUtils
	{
	public:
		/********************************************//**
 		 * @param[in] inVec The vector to be converted
		 *
		 * Converts cVector3 to D3DXVector3
		 ***********************************************/
		static D3DXVECTOR3 Vector3ToD3DXVEC3(const Base::cVector3 & inVec);
		/********************************************//**
 		 * @param[in] inVec The vector to be converted
		 *
		 * Converts D3DXVector3 to cVector3
		 ***********************************************/
		static Base::cVector3 D3DXVEC3ToVector3(const D3DXVECTOR3 & inVec);
		/********************************************//**
 		 * @param[in] inVec The vector to be converted
		 *
		 * Converts cVector2 to D3DXVector2
		 ***********************************************/
		static D3DXVECTOR2 Vector2ToD3DXVEC2(const Base::cVector2 & inVec);
		/********************************************//**
 		 * @param[in] inVec The vector to be converted
		 *
		 * Converts D3DXVector2 to cVector2
		 ***********************************************/
		static Base::cVector2 D3DXVEC2ToVector2(const D3DXVECTOR2 & inVec);
	};
}

#endif // GraphicUtils_h__