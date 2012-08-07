// AI_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include "Entity1.h"
#include "Entity2.h"
#include "EntityManager.hxx"
#include "MessageDispatchManager.hxx"
#include "BaseEntity.hxx"

using namespace Utilities;
using namespace GameBase;

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

	ILogger::GetInstance()->StartConsoleWin(80,60, "Log.txt");
	IBaseEntity * pEntity1 = new cEntity1(0, "Entity1");
	IBaseEntity * pEntity2 = new cEntity2(1, "Entity2");

	IEntityManager::GetInstance()->VRegisterEntity(pEntity1);
	IEntityManager::GetInstance()->VRegisterEntity(pEntity2);

	int iUpdateCycles = 0;
	while(iUpdateCycles < 50)
	{
		pEntity1->VOnUpdate();
		pEntity2->VOnUpdate();
		IMessageDispatchManager::GetInstance()->VOnUpdate();
		Sleep(200);
		iUpdateCycles++;
	}
	SAFE_DELETE(pEntity1);
	SAFE_DELETE(pEntity2);

	IEntityManager::Destroy();
	IMessageDispatchManager::Destroy();
	ILogger::Destroy();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	printf("Press Any Key to continue");
	while (!_kbhit())
	{
	}
}

