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
		bool VInitialize(const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath);
		void Render(const D3DXMATRIX & inMatWorld, const D3DXMATRIX & inMatView,
			const D3DXMATRIX & inMatProjection, const ITexture * const pTexture,
			const D3DXVECTOR4 & textColor);

	private:
		void VSetShaderParameters( const D3DXMATRIX & inMatWorld,
			const D3DXMATRIX & inMatView, const D3DXMATRIX & inMatProjection, 
			ID3D11ShaderResourceView * pTexture );
		void VSetShaderParameters( const D3DXMATRIX & inMatWorld,
			const D3DXMATRIX & inMatView, const D3DXMATRIX & inMatProjection, 
			ID3D11ShaderResourceView * pTexture, const D3DXVECTOR4 & textColor );
		void VCleanup();

	private:
		ID3D11Buffer *	m_pPixelBuffer;	/*!< The vertex shader constant buffer to store the pixel color data */
	};
}