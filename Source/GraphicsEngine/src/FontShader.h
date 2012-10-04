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

	private:
		bool VInitialize(const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath);
		void VSetShaderParameters( const D3DXMATRIX & inMatWorld,
			const D3DXMATRIX & inMatView, const D3DXMATRIX & inMatProjection, 
			ID3D11ShaderResourceView * pTexture );
		void VCleanup();

	private:
		ID3D11Buffer *	 m_pPixelBuffer;
	};
}