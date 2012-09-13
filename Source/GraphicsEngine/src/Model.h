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
	public:
		cModel();
		~cModel();
		void VOnInitialization(const cVertex * const pVertexData, const UINT iNumberOfVertices, const UINT iPrimitiveCount);
		void VCleanup();
		void VRender();
		int GetVertexCount();

	private:
		LPDIRECT3DVERTEXBUFFER9 	m_pVertexBuffer;
		UINT						m_iVertexCount;
		UINT						m_iPrimitiveCount;
		UINT						m_iVertexSize;
	};
}
#endif // Model_h__