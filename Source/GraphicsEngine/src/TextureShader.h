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
	class cTextureShader
		: public cBaseShader
	{
	public:
		cTextureShader();
		~cTextureShader();

	private:
		bool VInitialize(const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath, const int iNumberOfLayouts);
		bool VCreateLayout( const int iNumberOfLayouts,
			const Utilities::IFileInput * const pVertexShaderFile );
		virtual void VSetShaderParameters( const D3DXMATRIX & inMatWorld,
			const D3DXMATRIX & inMatView, const D3DXMATRIX & inMatProjection, 
			ID3D11ShaderResourceView * pTexture );
		void VRenderShader();
		void VCleanup();

	private:
		ID3D11SamplerState *		m_pSampleState;
	};
}
#endif // TextureShader_h__