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

class cCollisionChecker 
	: public ICollisionChecker
{
private:

	cCollisionChecker(const cCollisionChecker&){}
	cCollisionChecker operator = (const cCollisionChecker&){}

public:
	cCollisionChecker();
	~cCollisionChecker();
	bool CheckFor2DCollisions(const D3DRECT &rectA, const D3DRECT &rectB) ;
	static ICollisionChecker * TheCollisionChecker();
};

static cCollisionChecker * s_pCollisionChecker = NULL;

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
bool cCollisionChecker::CheckFor2DCollisions( const D3DRECT &rectA, 
											 const D3DRECT &rectB )
{
	// check if any of sides are outside
	if (rectA.x1 > rectB.x2)
	{
		return false;
	}

	if (rectA.y1 > rectB.y2)
	{
		return false;
	}

	if (rectA.x2 < rectB.x1)
	{
		return false;
	}

	if (rectA.y2 < rectB.y1)
	{
		return false;
	}

	return true;
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

ICollisionChecker * CreateCollisionChecker()
{
	s_pCollisionChecker = new cCollisionChecker();
	return s_pCollisionChecker;
}