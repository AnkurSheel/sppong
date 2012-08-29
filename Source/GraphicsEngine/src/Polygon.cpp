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
#include "Vector2.h"

using namespace Graphics;
using namespace Base;
cPolygon::cPolygon( const cVector2 * const pVertices, int nNoOfVertices )
{
	m_pVertices = DEBUG_NEW cVector2[nNoOfVertices];
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

void cPolygon::Translate( const cVector2 & trans )
{
	for(int i=0; i< m_nNoOfVertices; i++)
	{
		m_pVertices[i] += trans;
	}
}

IPolygon * IPolygon::CreatePolygon(const cVector2 * const pVertices, int nNoOfVertices)
{
	IPolygon * pPolygon = DEBUG_NEW cPolygon(pVertices, nNoOfVertices);
	return pPolygon;
}