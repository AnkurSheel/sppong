// *****************************************************************************
//  FontShader   version:  1.0   Ankur Sheel  date: 2012/10/03
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

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
	/********************************************//**
     * @brief Constant buffer to be passed to the shader.
     ***********************************************/
		struct PixelBufferType
		{
			D3DXVECTOR4 pixelColor;		/*!< The color of the pixel that will be used to draw the font text. */
		};

	public:
		cFontShader();

	private:
		~cFontShader();
		void VSetShaderParameters( const D3DXMATRIX & inMatWorld,
			const D3DXMATRIX & inMatView, const D3DXMATRIX & inMatProjection);
	};
}