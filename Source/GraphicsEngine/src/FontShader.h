// ***************************************************************
//  FontShader   version:  1.0   Ankur Sheel  date: 2012/10/03
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include "TextureShader.h"

namespace Graphics
{
    /********************************************//**
     * @brief Class use to invoke HLSL shaders for
	 * displaying text on screen
     ***********************************************/
	class cFontShader
		: public cTextureShader
	{
		struct PixelBufferType
		{
			D3DXVECTOR4 pixelColor;
		};

	public:
		cFontShader();
		~cFontShader();
		/********************************************//**
 		 * @param[in] colorText The text color
		 *
		 * Sets the color of the text
		 ***********************************************/
		void SetTextColor(const Base::cColor & colorText);

	private:
		bool VInitialize(const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath);
		void VSetShaderParameters( const D3DXMATRIX & inMatWorld,
			const D3DXMATRIX & inMatView, const D3DXMATRIX & inMatProjection, 
			ID3D11ShaderResourceView * pTexture );
		void VCleanup();
	
	private:
		ID3D11Buffer *	m_pPixelBuffer;	/*!< The vertex shader constant buffer to store the pixel color data */
		D3DXVECTOR4		m_pTextColor;	/*!< The text color */
	};
}