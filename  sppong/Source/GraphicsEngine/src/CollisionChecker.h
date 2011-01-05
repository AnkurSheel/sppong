// ***************************************************************
//  CollisionCheck   version:  1.0   Ankur Sheel  date: 05/14/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef CollisionChecker_h__
#define CollisionChecker_h__

#include "GraphicEngineDefines.h"

class ICollisionChecker
{
public:
	GRAPHIC_API virtual bool CheckFor2DCollisions(const D3DRECT &rectA, const D3DRECT &rectB) = 0;
	GRAPHIC_API static ICollisionChecker * TheCollisionChecker();
	GRAPHIC_API virtual void Destroy() = 0;
	GRAPHIC_API static void CreateCollisionChecker();
};
#endif // CollisionChecker_h__