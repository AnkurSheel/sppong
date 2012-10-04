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
#include "Sprite.h"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class ITexture;
}

namespace Graphics
{
	/********************************************//**
     * @brief Class Declaration for \c ISprite
     * interface
     ***********************************************/
	class cMyFont
		: public IMyFont
		, public cSprite
	{
	private:
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

	public:
		cMyFont() ;
		~cMyFont() ;
	
	private:
		bool VInitialize(const Base::cString & strFontDirPath,
			const Base::cString & strFontDescFilename);
		void VRender(const ICamera * const pCamera);
		void VSetPosition(const Base::cVector2 & vPosition);
		void VSetText(const Base::cString & strText);
		bool VRecalculateVertexData();
		bool VCreateIndexBuffer( );
		void VCleanup();
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

	private:
		typedef std::map<int, const CharDescriptor> CharDescriptorMap;

		Base::cString						m_strFontTexPath;		/*!< The path of the font texture file */
		int									m_iTextureWidth;		/*!< The width of the texture file */
		int									m_iTextureHeight;		/*!< The height of the texture file */
		CharDescriptorMap					m_CharDescriptorMap;	/*!< The map contaning all the character descriptions with their ascii value as the key */
		Base::cString						m_strText;				/*!< The text that has to be displayed */
	};
}
#endif // Font_h__
