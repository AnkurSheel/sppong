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
	class cModel
		: public IModel 
		, public Base::cNonCopyable
	{
		enum VERTEXDATATYPE
		{
			VDT_NONE,
			VDT_VERTEXBUFFER,
			VDT_INDEXBUFFER,
		};
	public:
		cModel();
		~cModel();
		void VOnInitialization(const cVertex * const pVertexData, const UINT iNumberOfVertices, const UINT iPrimitiveCount);
		void VOnInitialization(const cVertex * const pVertexData, const short * const pIndexData, const UINT iNumberOfVertices, const UINT iNumberOfIndices, const UINT iPrimitiveCount);
		void VCleanup();
		void VRender();
		int GetVertexCount();

	private:
		LPDIRECT3DVERTEXBUFFER9 	m_pVertexBuffer;
		LPDIRECT3DINDEXBUFFER9		m_pIndexBuffer;
		UINT						m_iVertexCount;
		UINT						m_iPrimitiveCount;
		UINT						m_iVertexSize;
		VERTEXDATATYPE				m_type;
	};
}
#endif // Model_h__