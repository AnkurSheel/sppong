// ***************************************************************
//  ColorShader   version:  1.0   Ankur Sheel  date: 2012/09/15
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

namespace Graphics
{
/********************************************//**
 * @brief Interface to invoke the HLSL shaders
 * for drwaing the 3D models
 *
 ***********************************************/
	class IColorShader
	{
	public:
		virtual ~IColorShader(){}
		/********************************************//**
 		 * @param[in] strVertexShaderPath The path for the vertex shader file
		 * @param[in] strPixelShaderPath The path for the pixel shader file
		 * @param[in] iNumberOfLayouts
		 * @return False if there is any error
		 *
		 * Creates the vertex and pixel shader objects. Creates the layout of the vertex
		 * data that will be processed by this shader
		 ***********************************************/
		virtual bool VInitialize(const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath, const int iNumberOfLayouts) = 0;
		/********************************************//**
 		 * @param[in] inMatWorld The world matrix
		 * @param[in] inMatView The View Matrix
		 * @param[in] inMatProjection The projection Matrix
		 *
		 * Sets the shader parameters and then draws the model
		 * using the HLSL shader
		 ***********************************************/
		virtual void VRender(const D3DXMATRIX & inMatWorld, const D3DXMATRIX & inMatView,
			const D3DXMATRIX & inMatProjection) = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		static IColorShader * CreateColorShader();
	};
}