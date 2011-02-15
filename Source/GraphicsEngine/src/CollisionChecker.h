// ***************************************************************
//  CollisionChecker   version:  1.0   Ankur Sheel  date: 05/14/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef CollisionChecker_h__
#define CollisionChecker_h__

#include "CollisionChecker.hxx"

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
#endif // CollisionChecker_h__
