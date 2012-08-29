// ***************************************************************
//  Polygon   version:  1.0   Ankur Sheel  date: 2011/01/31
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Polygon_h__
#define Polygon_h__

#include "Polygon.hxx"
namespace Graphics
{
	class cPolygon 
		: public IPolygon
	{
	public:
		cPolygon(const Base::cVector2 * const pVertices, int nNoOfVertices);
		~cPolygon();
		void Translate(const Base::cVector2 & trans);

	public:
		Base::cVector2 *	m_pVertices;
		int					m_nNoOfVertices;
	};
}
#endif // Polygon_h__