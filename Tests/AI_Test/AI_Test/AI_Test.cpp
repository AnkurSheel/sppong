// AI_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Entity.h"

using namespace Utilities;

void CheckForMemoryLeaks() 
{
#ifdef	_DEBUG
	// Get Current flag
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) ; 

	// Turn on leak-checking bit
	flag |= (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) ; 

	// Set flag to the new value
	_CrtSetDbgFlag(flag) ; 
#endif	_DEBUG
}


void main(int argc, char* argv[])
{
	CheckForMemoryLeaks() ;
	
	ILogger::TheLogger()->StartConsoleWin(80,60, "Log.txt");
	cEntity * pEntity = new cEntity(0);
	int iUpdateCycles = 0;
	while(iUpdateCycles < 15)
	{
		pEntity->Update();
		iUpdateCycles++;
	}
	SAFE_DELETE(pEntity);

	if (ILogger::TheLogger())
	{
		ILogger::TheLogger()->Destroy();
	}
}

