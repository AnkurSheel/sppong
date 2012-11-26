// ***************************************************************
//  TextureShader   version:  1.0   Ankur Sheel  date: 2012/09/24
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef TextureShader_h__
#define TextureShader_h__

#include "BaseShader.h"

namespace Graphics
{
    /********************************************//**
     * @brief Class use to invoke HLSL shaders for
	 * drawing 3D models with position and texture vertex data
     ***********************************************/
	class cTextureShader
		: public cBaseShader
	{
	public:
		struct stPixelBufferData
		{
			D3DXVECTOR4		pixelColor;		/*!< The color of the pixel that will be used to draw the font text. */
			int				hasTexture;		/*!< True if rendering a texture. This should be int because HLSL packs things into 4 bytes. */
		};

		cTextureShader();
		~cTextureShader();
		void SetTextColor(const Base::cColor colorText);

	protected:
		virtual bool VInitialize(const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath);
		bool VCreateLayout(const Utilities::IFileInput * const pVertexShaderFile );
		virtual void VSetShaderParameters( const D3DXMATRIX & inMatWorld,
			const D3DXMATRIX & inMatView, const D3DXMATRIX & inMatProjection);
		virtual void VRenderShader();
		virtual void VCleanup();

		bool CreatePixelBuffer(const unsigned int bufferSize);
		bool CreateSampleState();

	protected:
		ID3D11Buffer *				m_pPixelBuffer;		/*!< The pixel shader constant buffer */
		D3DXVECTOR4					m_DiffuseColor;		/*!< The diffuse color */

	private:
		ID3D11SamplerState *		m_pSampleState;		/*!< The sampler state pointer is used to interface with the texture shader */
	};
}
#endif // TextureShader_h__