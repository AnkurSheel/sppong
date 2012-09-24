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
	class IShader;
	class ITexture;
}

namespace Graphics
{
	class cModel
		: public IModel 
		, public Base::cNonCopyable
	{
	public:
		cModel();
		~cModel();

	private:
		bool VOnInitialization(const stVertex * const pVertices, 
			const unsigned long * const pIndices, const UINT iNumberOfVertices, 
			const UINT iNumberOfIndices, const UINT iPrimitiveCount);
		bool VOnInitialization(const stTexVertex * const pVertices, 
			const unsigned long * const pIndices, const UINT iNumberOfVertices, 
			const UINT iNumberOfIndices, const UINT iPrimitiveCount,
			const Base::cString & strTextureFilename);
		void VRender(const ICamera * const pCamera);
		void VCleanup();
		/********************************************//**
 		 * @param[in] pVertices The vertex data of this model
		 *
		 * Creates the vertex buffer using the vertex data
		 ***********************************************/
		bool CreateVertexBuffer( const stVertex * const pVertices);
		/********************************************//**
 		 * @param[in] pVertices The vertex data of this model
		 *
		 * Creates the vertex buffer using the vertex data
		 ***********************************************/
		bool CreateVertexBuffer( const stTexVertex * const pVertices);
		/********************************************//**
		 * @param[in] pIndices The indices data of this model
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
		IShader *							m_pShader;				/*!< */
		shared_ptr<Graphics::ITexture>		m_pTexture;
	};
}
#endif // Model_h__