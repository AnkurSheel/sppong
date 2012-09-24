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
	class ITexture;
}

namespace Graphics
{
/********************************************//**
 * @brief Interface to invoke the HLSL shaders
 * for drawing the 3D models
 *
 ***********************************************/
	class IShader
	{
	public:
		virtual ~IShader(){}
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
		 * @param[in] pTexture
		 *
		 * Sets the shader parameters and then draws the model
		 * using the HLSL shader
		 ***********************************************/
		virtual void VRender(const D3DXMATRIX & inMatWorld, const D3DXMATRIX & inMatView,
			const D3DXMATRIX & inMatProjection, const Graphics::ITexture * const pTexture) = 0;
		/********************************************//**
		 * @return An object to use a color shader
		 *
		 * Returns an object to use a color shader
		 ***********************************************/
		static IShader * CreateColorShader();
		/********************************************//**
		 * @return An object to use a texture shader
		 *
		 * Returns an object to use a texture shader
		 ***********************************************/
		static IShader * CreateTextureShader();
	};
}