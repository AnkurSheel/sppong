// ***************************************************************
//  ColorShader   version:  1.0   Ankur Sheel  date: 2012/09/15
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include "ColorShader.hxx"

namespace Utilities
{
	class IFileInput;
}
namespace Graphics
{
	class cColorShader
		: public IColorShader
		, public Base::cNonCopyable
	{
		struct MatrixBufferType
		{
			D3DXMATRIX world;
			D3DXMATRIX view;
			D3DXMATRIX projection;
		};
	public:
		cColorShader();
		~cColorShader();

	private:
		bool VInitialize(const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath, const int iNumberOfLayouts);

		void VRender(const D3DXMATRIX & inMatWorld, const D3DXMATRIX & inMatView,
			const D3DXMATRIX & inMatProjection);

		/********************************************//**
		 *
		 * Releases and destroys all the resources 
		 ***********************************************/
		void Cleanup();
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
		/********************************************//**
		 * @param[in] iNumberOfLayouts The number of elements in the vertex shader
		 * @param[in] pVertexShaderFile The compiled vertex shader file
		 * @return False if there is any error
		 *
		 * Creates the layout of the vertex data that will be processed by this shader
		 ***********************************************/
		bool CreateLayout( const int iNumberOfLayouts, const Utilities::IFileInput * const pVertexShaderFile );

	private:
		ID3D11VertexShader *	m_pVertexShader;	/*!< The vertex shader object */
		ID3D11PixelShader *		m_pPixelShader;		/*!< The pixel shader object */
		ID3D11InputLayout *		m_pLayout;			/*!< The input layout of the vertex shader */
		ID3D11Buffer *			m_pMatrixBuffer;	/*!< The vertex shader constant buffer */
	};
}