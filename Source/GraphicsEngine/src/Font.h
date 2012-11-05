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
	/********************************************//**
     * @brief Structure to hold the various parameters
	 * defining the character
     ***********************************************/
	struct CharDescriptor
	{
		unsigned short id;			/*!< The character id */
		unsigned short x;			/*!< The left position of the character image in the font texture */
		unsigned short y;			/*!< The top position of the character image in the font texture */
		unsigned short Width;		/*!< TThe width of the character image in the font texture */
		unsigned short Height;		/*!< The height of the character image in the font texture */
		unsigned short XOffset;		/*!< How much the current position should be offset when copying the image from the font texture to the screen */
		unsigned short YOffset;		/*!< How much the current position should be offset when copying the image from the font texture to the screen */
		unsigned short XAdvance;	/*!< How much the current position should be advanced after drawing the character */

		CharDescriptor() 
			: id(0)
			, x(0)
			, y(0)
			, Width(0)
			, Height(0)
			, XOffset(0)
			, YOffset(0)
			, XAdvance(0)
		{
		}
	};

	/********************************************//**
     * @brief Vertex Data description for a character
     ***********************************************/
	struct stVertexData
	{
		CharDescriptor	ch;		/*!< The parameters describing the character */
		float			fTexU;	/*!< The U position of this character in the texture map */
		float			fTexV;	/*!< The V position of this character in the texture map */
		float			fTexU1;	/*!< The U1 position of this character in the texture map */
		float			fTexV1;	/*!< The V1 position of this character in the texture map */

		stVertexData()
			: fTexU(0.0f)
			, fTexV(0.0f)
			, fTexU1(0.0f)
			, fTexV1(0.0f)
		{
		}
	};

	 /********************************************//**
     * @brief Class Declaration for \c IMyFont
     * interface
     ***********************************************/
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
		 * @param[in] textColor The color of the text
		 *
		 * Sets the shader parameters and then draws the model
		 * using the HLSL shader
		 ***********************************************/
		void Render(const D3DXMATRIX & inMatWorld, const D3DXMATRIX & inMatView,
			const D3DXMATRIX & inMatProjection, const Base::cColor & textColor);
		/********************************************//**
 		 * @param[in] iCharAsciiValue The ascii value of the character
		 * @return The vertex data
		 *
		 * Returns the vertex data for a character with the 
		 * given ascii vakue
		 ***********************************************/
		stVertexData GetCharVertexData(const int iCharAsciiValue);
		/********************************************//**
		 * @return The height of the a line using this font
		 *
		 * Returns the height of the a line using this font
		 ***********************************************/
		float GetFontHeight() const ;

	private:
		bool VInitialize(const Base::cString & strFontDirPath,
			const Base::cString & strFontDescFilename);
		/********************************************//**
 		 * @param[in] strFontDirPath The directory path from the font description file
		 * @param[in] strFontDescFilename The file name of the font description file
		 *
		 * Parses and stores the character defintions from the font
		 * description file name
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
		/** Map with key as ascii value of char. Value is the char descriptor for the character denoted by this ascii value */
		typedef std::map<int, const CharDescriptor> CharDescriptorMap;

		shared_ptr<cFontShader>				m_pShader;				/*!< The shader responsible for rendering the font. */
		shared_ptr<ITexture>				m_pTexture;				/*!< The Texture of the sprite */
		Base::cString						m_strFontTexPath;		/*!< The path of the font texture file */
		int									m_iTextureWidth;		/*!< The width of the texture file */
		int									m_iTextureHeight;		/*!< The height of the texture file */
		CharDescriptorMap					m_CharDescriptorMap;	/*!< The map contaning all the character descriptions with their ascii value as the key */
		int									m_iFontHeight;			/*!< The height of each line of text */
	};
}
#endif // Font_h__
