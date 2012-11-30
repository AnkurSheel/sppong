// ***************************************************************
//  Wall   version:  1.0   Ankur Sheel  date: 05/15/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
//***************************************************************
#ifndef Wall_h__
#define Wall_h__

#include "PongGameElement.h"

namespace Base
{
	class cString;
}

class cWall 
	: public cPongGameElement
{
private:
	cWall(const cWall&){}
	cWall operator =(const cWall&){}
public:
	cWall();
	~cWall();
};
#endif // Wall_h__