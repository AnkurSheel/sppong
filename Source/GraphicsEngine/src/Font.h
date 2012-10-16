// ***************************************************************
//  Font   version:  1.0   Ankur Sheel  date: 05/16/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Font_h__
#define Font_h__

#include "Font.hxx"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class ITexture;
	class cFontShader;
}

namespace Graphics
{
	struct CharDescriptor
	{
		unsigned short id;
		unsigned short x, y;
		unsigned short Width, Height;
		unsigned short XOffset, YOffset;
		unsigned short XAdvance;

		CharDescriptor() : id(0), x( 0 ), y( 0 ), Width( 0 ), Height( 0 ),
			XOffset( 0 ), YOffset( 0 ),	XAdvance( 0 )
		{ }
	};

	class cMyFont
		: public IMyFont
	{
	public:
		cMyFont() ;
		~cMyFont() ;
		/********************************************//**
 		 * @param[in] inMatWorld The world matrix
		 * @param[in] inMatView The View Matrix
		 * @param[in] inMatProjection The projection Matrix
		 * @param[in] pTexture
		 *
		 * Sets the shader parameters and then draws the model
		 * using the HLSL shader
		 ***********************************************/
		void Render(const D3DXMATRIX & inMatWorld, const D3DXMATRIX & inMatView,
			const D3DXMATRIX & inMatProjection, const D3DXVECTOR4 & textColor);
		void GetCharVertexData(const int iCharAsciiValue, CharDescriptor & ch,
			float & fTexU, float & fTexV, float & fTexU1, float & fTexV1);
		float GetFontHeight() const ;

	private:
		bool VInitialize(const Base::cString & strFontDirPath,
			const Base::cString & strFontDescFilename);
		/********************************************//**
 		 * @param[in] strFontDirPath The directory path from the font description file
		 * @param[in] strFontDescFilename The file name of the font description file
		 *
		 * Initializes the sprite with the texture
		 ***********************************************/
		void ParseFontDesc(const Base::cString & strFontDirPath,
			const Base::cString & strFontDescFilename);
		/********************************************//**
		 *
		 * Creates and Initializes the font shader for use
		 ***********************************************/
		bool InitializeShader();
		/********************************************//**
		 *
		 * Releases and destroys all the resources 
		 ***********************************************/
		void Cleanup();
	private:
		typedef std::map<int, const CharDescriptor> CharDescriptorMap;

		cFontShader *						m_pShader;				/*!< The shader responsible for rendering the font. */
		shared_ptr<ITexture>				m_pTexture;				/*!< The Texture of the sprite */
		Base::cString						m_strFontTexPath;		/*!< The path of the font texture file */
		int									m_iTextureWidth;		/*!< The width of the texture file */
		int									m_iTextureHeight;		/*!< The height of the texture file */
		CharDescriptorMap					m_CharDescriptorMap;	/*!< The map contaning all the character descriptions with their ascii value as the key */
		int									m_iFontHeight;
	};
}
#endif // Font_h__
