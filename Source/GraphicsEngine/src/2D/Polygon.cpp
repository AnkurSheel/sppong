// ***************************************************************
//  Polygon   version:  1.0   Ankur Sheel  date: 2011/01/31
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Polygon.h"

cPolygon::cPolygon( const D3DXVECTOR2 * const pVertices, int nNoOfVertices )
{
	m_pVertices = DEBUG_NEW D3DXVECTOR2[nNoOfVertices];
	for(int i=0; i < nNoOfVertices; i++)
	{
		m_pVertices[i] = pVertices[i];
	}
	m_nNoOfVertices = nNoOfVertices;
}

cPolygon::~cPolygon()
{
	SAFE_DELETE_ARRAY(m_pVertices);
}

void cPolygon::Translate( const D3DXVECTOR2 & trans )
{
	for(int i=0; i< m_nNoOfVertices; i++)
	{
		m_pVertices[i] += trans;
	}
}