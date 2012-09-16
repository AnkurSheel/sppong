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
	class cColorShader;
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
		bool VOnInitialization(const stVertex * const pVertices, 
			const unsigned long * const pIndices, const UINT iNumberOfVertices, 
			const UINT iNumberOfIndices, const UINT iPrimitiveCount);

		void VCleanup();
		void VRender(const ICamera * const pCamera);

	private:
		bool CreateVertexBuffer( const stVertex * const pVertices);
		bool CreateIndexBuffer( const unsigned long * const pIndices );

	private:
		ID3D11Buffer * 				m_pVertexBuffer;
		ID3D11Buffer *				m_pIndexBuffer;
		UINT						m_iVertexCount;
		UINT						m_iIndexCount;
		UINT						m_iPrimitiveCount;
		UINT						m_iVertexSize;
		cColorShader *				m_pColorShader;
	};
}
#endif // Model_h__