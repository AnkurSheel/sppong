// ***************************************************************
//  BaseShader   version:  1.0   Ankur Sheel  date: 2012/09/24
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef BaseShader_h__
#define BaseShader_h__

#include "Shader.hxx"

namespace Utilities
{
	class IFileInput;
}

namespace Graphics
{
	class cBaseShader
		: public IShader
		, public Base::cNonCopyable
	{
		struct MatrixBufferType
		{
			D3DXMATRIX world;
			D3DXMATRIX view;
			D3DXMATRIX projection;
		};

	protected:
		cBaseShader();
		virtual ~cBaseShader();
		bool VInitialize(const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath, const int iNumberOfLayouts);
		/********************************************//**
 		 * @param[in] inMatWorld The world matrix
		 * @param[in] inMatView The View Matrix
		 * @param[in] inMatProjection The projection Matrix
		 *
		 * Sets the shader parameters
		 ***********************************************/
		virtual void VSetShaderParameters( const D3DXMATRIX & inMatWorld,
			const D3DXMATRIX & inMatView, const D3DXMATRIX & inMatProjection,
			ID3D11ShaderResourceView * pTexture);
		/********************************************//**
		  *
		  * Renders the shader
		  ***********************************************/
		virtual void VRenderShader();
		/********************************************//**
		  *
		  * Releases and destroys all the resources 
		  ***********************************************/
		virtual void VCleanup();

	private:
		void VRender(const D3DXMATRIX & inMatWorld, const D3DXMATRIX & inMatView,
			const D3DXMATRIX & inMatProjection, const ITexture * const pTexture);
		/********************************************//**
		  * @param[in] iNumberOfLayouts The number of elements in the vertex shader
		  * @param[in] pVertexShaderFile The compiled vertex shader file
		  * @return False if there is any error
		  *
		  * Creates the layout of the vertex data that will be processed by this shader
		  ***********************************************/
		virtual bool VCreateLayout( const int iNumberOfLayouts,
			const Utilities::IFileInput * const pVertexShaderFile ) = 0;
		/********************************************//**
		  * @param[in] strVertexShaderPath The path for the vertex shader file
		  * @return False if there is any error
		  *
		  * Creates the vertex shader objectsand the layout of the vertex
		  * data that will be processed by this shader
		  ***********************************************/
		bool CreateVertexShader( const Base::cString & strVertexShaderPath);
		/********************************************//**
		  * @param[in] strPixelShaderPath The path for the pixel shader file
		  *
		  * Creates the pixel shader object
		  ***********************************************/
		bool CreatePixelShader( const Base::cString & strPixelShaderPath);

	protected:
		ID3D11InputLayout *		m_pLayout;			/*!< The input layout of the vertex shader */

	private:
		ID3D11VertexShader *	m_pVertexShader;	/*!< The vertex shader object */
		ID3D11PixelShader *		m_pPixelShader;		/*!< The pixel shader object */
		ID3D11Buffer *			m_pMatrixBuffer;	/*!< The vertex shader constant buffer */
	};
}
#endif // BaseShader_h__
