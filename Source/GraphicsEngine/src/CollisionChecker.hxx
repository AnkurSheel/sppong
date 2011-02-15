// ***************************************************************
//  CollisionCheck   version:  1.0   Ankur Sheel  date: 05/14/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef CollisionChecker_hxx__
#define CollisionChecker_hxx__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class cPolygon;
}

namespace Graphics
{
	class ICollisionChecker
	{
	public:
		GRAPHIC_API ~ICollisionChecker(){}
		GRAPHIC_API virtual bool CheckFor2DCollisions(const Graphics::cPolygon &polygonA, const Graphics::cPolygon &polygonB) = 0;
		GRAPHIC_API static ICollisionChecker * TheCollisionChecker();
		GRAPHIC_API virtual void Destroy() = 0;
		GRAPHIC_API static void CreateCollisionChecker();
	};
}
#endif // CollisionChecker_h__