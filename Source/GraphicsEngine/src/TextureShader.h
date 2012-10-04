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
		cTextureShader();
		~cTextureShader();

	protected:
		virtual bool VInitialize(const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath);
		bool VCreateLayout(const Utilities::IFileInput * const pVertexShaderFile );
		virtual void VSetShaderParameters( const D3DXMATRIX & inMatWorld,
			const D3DXMATRIX & inMatView, const D3DXMATRIX & inMatProjection, 
			ID3D11ShaderResourceView * pTexture );
		virtual void VRenderShader();
		virtual void VCleanup();

	private:
		ID3D11SamplerState *		m_pSampleState;		/*!< The sampler state pointer is used to interface with the texture shader */
	};
}
#endif // TextureShader_h__