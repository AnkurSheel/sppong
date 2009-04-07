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

class cCollisionChecker
{
private:
	
	cCollisionChecker(const cCollisionChecker&){}
	cCollisionChecker operator = (const cCollisionChecker&){}

public:
	cCollisionChecker();
	~cCollisionChecker();
	GRAPHIC_API bool CheckFor2DCollisions(const D3DRECT &rectA, const D3DRECT &rectB) ;
	GRAPHIC_API static cCollisionChecker& GetInstance();
};
#endif // CollisionChecker_h__