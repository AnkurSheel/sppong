// ***************************************************************
//  CollisionChecker   version:  1.0   Ankur Sheel  date: 05/14/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "CollisionChecker.h"
#include "2D/Polygon.h"

namespace Graphics
{
	class cCollisionChecker 
		: public ICollisionChecker
	{
	private:

		cCollisionChecker(const cCollisionChecker&){}
		cCollisionChecker operator = (const cCollisionChecker&){}
		bool NoOverlap(const D3DXVECTOR2 &axis, const cPolygon &polygon1, const cPolygon &polygon2, float & fLengthSquared);
	public:
		cCollisionChecker();
		~cCollisionChecker();
		bool CheckFor2DCollisions(const cPolygon &polygonA, const cPolygon &polygonB);
		static ICollisionChecker * TheCollisionChecker();
		void Destroy();
	};

	static cCollisionChecker * s_pCollisionChecker = NULL;
}

using namespace Graphics;
// ***************************************************************
// Constructor
// ***************************************************************
cCollisionChecker::cCollisionChecker()
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cCollisionChecker::~cCollisionChecker()
{
	int a = 5;
	a += 10;
}
// ***************************************************************

// ***************************************************************
// Checks for collisions for 2D objects.
// returns true if there is a collision
// ***************************************************************
bool cCollisionChecker::CheckFor2DCollisions(const cPolygon &polygonA, const cPolygon &polygonB)
{
	//axis along the poly's edge
	D3DXVECTOR2 edge;

	// flag mtv as invalid
	float fLengthSquared = -1.0f; 

	//loop through all the m_pVertices in polygonA
	for (int i = 0; i < polygonA.m_nNoOfVertices; i++)
	{
		//Join the last vertex with the first
		if (i == polygonA.m_nNoOfVertices - 1)
		{
			edge = polygonA.m_pVertices[polygonA.m_nNoOfVertices - 1] - polygonA.m_pVertices[0];
		}
		//Join the m_pVertices
		else
		{
			edge = polygonA.m_pVertices[i + 1] - polygonA.m_pVertices[i];
		}

		//Get the normal and normalise 
		D3DXVECTOR2 axis(-edge.y, edge.x);
		D3DXVec2Normalize(&axis, &axis);

		//Check to see if the polygons overlap along the current axis
		if (NoOverlap(axis, polygonA, polygonB, fLengthSquared))
			return false;

		//Do the same for the other m_pVertices in this polygon
	}

	//Loop through all the m_pVertices in polygonB
	for (int i = 0; i < polygonB.m_nNoOfVertices; i++)
	{
		//Join the last vertex with the first 
		if (i == polygonB.m_nNoOfVertices - 1)
		{
			edge = polygonB.m_pVertices[polygonB.m_nNoOfVertices - 1] - polygonB.m_pVertices[0];
		}
		//Join the m_pVertices to make the edge
		else
		{
			edge = polygonB.m_pVertices[i + 1] - polygonB.m_pVertices[i];
		}

		//Get the normal and normalise 
		D3DXVECTOR2 axis(-edge.y, edge.x);
		D3DXVec2Normalize(&axis, &axis);

		//Check to see if the polygons overlap along the current axis
		if (NoOverlap(axis, polygonA, polygonB, fLengthSquared))
			return false;
	}

	//If no separation axis between the 2 polygons has been found by now, 
	//THERE IS A COLLISION
	return true;
}

bool cCollisionChecker::NoOverlap(const D3DXVECTOR2 &axis, const cPolygon &polygon1, const cPolygon &polygon2, float & fLengthSquared)
{
	float poly1Min, poly1Max;

	//Project the other m_pVertices onto the axis by using dot product
	//Initialise the min/max values with the first value
	poly1Min  = D3DXVec2Dot(&polygon1.m_pVertices[0], &axis);
	poly1Max = D3DXVec2Dot(&polygon1.m_pVertices[0], &axis);

	//Get the highest and lowest dot products
	for (int i = 1; i < polygon1.m_nNoOfVertices; i++)
	{
		float projection = D3DXVec2Dot(&polygon1.m_pVertices[i], &axis);

		if (projection < poly1Min)
		{
			poly1Min = projection;
		}

		else if (projection > poly1Max)
		{
			poly1Max = projection;
		}
	}

	//Now project the other polygon's m_pVertices onto the axis
	float poly2Min, poly2Max;
	poly2Min  = D3DXVec2Dot(&polygon2.m_pVertices[0], &axis);
	poly2Max = D3DXVec2Dot(&polygon2.m_pVertices[0], &axis);

	//Project onto the axis and get the min/max values
	for (int i = 1; i < polygon2.m_nNoOfVertices; i++)
	{
		//Project onto the axis
		float projection = D3DXVec2Dot(&polygon2.m_pVertices[i], &axis);

		if (projection < poly2Min)
		{
			poly2Min = projection;
		}

		else if (projection > poly2Max)
		{
			poly2Max = projection;
		}
	}

	float overlap1 = (poly2Max - poly1Min);
	float overlap2 = (poly2Min - poly1Max);

	// no overlap detected
	if(overlap1 < 0.0f || overlap2 > 0.0f) return true;

	// find out if we overlap on the 'right' or 'left' of the polygon.
	float overlap = (overlap1 < -overlap2)? overlap1 : overlap2;

	D3DXVECTOR2 sep = axis * overlap;

	// the mtv vector length squared.
	float sep_length_squared = D3DXVec2Dot(&sep, &sep);

	// if that vector is smaller than our computed mtv (or the mtv hasn't been computed yet)
	// use that vector as our current mtv.
	if(sep_length_squared < fLengthSquared || fLengthSquared < 0.0f)
	{
		fLengthSquared = sep_length_squared;
	}
	return false;
}


void cCollisionChecker::Destroy()
{
	delete this;
}
// ***************************************************************

// ***************************************************************
// returns the instance
// ***************************************************************
ICollisionChecker * ICollisionChecker::TheCollisionChecker()
{
	return s_pCollisionChecker;
}
// ***************************************************************

void ICollisionChecker::CreateCollisionChecker()
{
	s_pCollisionChecker = DEBUG_NEW cCollisionChecker();
}

