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
	/********************************************//**
     * @brief Class Declaration for \c ISprite
     * interface
     ***********************************************/
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
		 * return True if the vertex buffer was created successfully
		 *
		 * Creates the vertex buffer using the vertex data
		 ***********************************************/
		bool CreateVertexBuffer();
		/********************************************//**
		 * return True if the index buffer was created successfully
		 * 
		 * Creates the index buffer using the indice data
		 ***********************************************/
		bool CreateIndexBuffer( );
		/********************************************//**
		 * return True if the vertex buffer was updated successfully
		 * 
		 * Recalculates the coordinates and updates the vertex data if the position has changed
		 ***********************************************/
		bool UpdateBuffers();

	private:
		ID3D11Buffer * 						m_pVertexBuffer;		/*!< The vertex buffer */
		ID3D11Buffer *						m_pIndexBuffer;			/*!< The index buffer */
		IShader *							m_pShader;				/*!< The shader responsible for rendering the model depending on the model vertex data type.*/
		shared_ptr<Graphics::ITexture>		m_pTexture;				/*!< The Texture of the sprite */
		Base::cVector2						m_vSize;				/*!< The size/scale in pixels */
		Base::cVector2						m_vPrevPosition;		/*!< The position at which the sprite was previously rendered */
		Base::cVector2						m_vPosition;			/*!< The current position of the sprite */
	};
}
#endif // Sprite_h__