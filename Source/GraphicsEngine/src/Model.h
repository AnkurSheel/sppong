// ***************************************************************
//  Model   version:  1.0   Ankur Sheel  date: 2012/09/13
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Model_h__
#define Model_h__

#include "Model.hxx"
namespace Graphics
{
	class cTextureShader;
	class ITexture;
}

namespace Graphics
{
	/********************************************//**
     * @brief Class Declaration for \c IModel
     * interface
     ***********************************************/
	class cModel
		: public IModel 
		, public Base::cNonCopyable
	{
	public:
		cModel();
		~cModel();

	private:
		bool VOnInitialization(const stModelDef & def);
		void VRender(const ICamera * const pCamera);
		void VSetRotation(const float fRadians);
		float VGetRotation() const;
		void VCleanup();
		/********************************************//**
 		 * @param[in] pVertices The vertex data of this model
		 * return True if the vertex buffer was created successfully
		 *
		 * Creates the vertex buffer using the vertex data
		 ***********************************************/
		bool CreateVertexBuffer( const stVertex * const pVertices);
		/********************************************//**
 		 * @param[in] pVertices The vertex data of this model
		 * return True if the vertex buffer was created successfully
		 * Creates the vertex buffer using the vertex data
		 ***********************************************/
		bool CreateVertexBuffer( const stTexVertex * const pVertices);
		/********************************************//**
		 * @param[in] pIndices The indices data of this model
		 * return True if the index buffer was created successfully
		 *
		 * Creates the index buffer using the indice data
		 ***********************************************/
		bool CreateIndexBuffer( const unsigned long * const pIndices );

	private:
		ID3D11Buffer * 						m_pVertexBuffer;		/*!< The vertex buffer */
		ID3D11Buffer *						m_pIndexBuffer;			/*!< The index buffer */
		UINT								m_iVertexCount;			/*!< The number of vertices in this model */
		UINT								m_iIndexCount;			/*!< The number of indices in this model */
		UINT								m_iPrimitiveCount;		/*!< The number of primitives that need to be drawn*/
		UINT								m_iVertexSize;			/*!< The size of the vertex structure */
		shared_ptr<cTextureShader>			m_pShader;				/*!< The shader responsible for rendering the model depending on the model vertex data type.*/
		shared_ptr<Graphics::ITexture>		m_pTexture;				/*!< The Texture of the model */
		Base::cColor						m_diffuseColor;
		float								m_fRotation;
	};
}
#endif // Model_h__