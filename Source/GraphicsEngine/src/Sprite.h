// ***************************************************************
//  Sprite   version:  1.0   Ankur Sheel  date: 05/09/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Sprite_h__
#define Sprite_h__

#include "Sprite.hxx"
namespace Graphics
{
	class ITexture;
	class IShader;
}

namespace Graphics 
{
	class cSprite
		: public ISprite
		, public Base::cNonCopyable
	{
	public:
		cSprite();
		~cSprite();
	
	private:
		bool VOnInitialization(shared_ptr<ITexture> const pTexture);
		bool VOnInitialization(const Base::cString & strTextureFilename);
		void VRender(const ICamera * const pCamera);
		void VCleanup();
		void VSetPosition(const Base::cVector2 & vPosition);
		void VSetSize(const Base::cVector2 & vSize);
		/********************************************//**
		 *
		 * Creates the vertex buffer using the vertex data
		 ***********************************************/
		bool CreateVertexBuffer();
		/********************************************//**
		 * 
		 * Creates the index buffer using the indice data
		 ***********************************************/
		bool CreateIndexBuffer( );
		bool UpdateBuffers();

	private:
		ID3D11Buffer * 						m_pVertexBuffer;		/*!< The vertex buffer */
		ID3D11Buffer *						m_pIndexBuffer;			/*!< The index buffer */
		IShader *							m_pShader;				/*!< The shader responsible for rendering the model depending on the model vertex data type.*/
		shared_ptr<Graphics::ITexture>		m_pTexture;				/*!< The Texture of the model */
		Base::cVector2						m_vSize;
		Base::cVector2						m_vPrevPosition;
		Base::cVector2						m_vPosition;
		Base::cString						m_strFilename;
	};
}
#endif // Sprite_h__