// ***************************************************************
//  Timer   version:  1.0   Ankur Sheel  date: 05/01/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Timer_h__
#define Timer_h__

#include "UtilitiesDefines.h"

class ITimer
{
public:
	virtual ~ITimer(){}
	UTILITIES_API virtual void Start() = 0;
	UTILITIES_API virtual void Stop() = 0;
	UTILITIES_API virtual void Update() = 0; 

	UTILITIES_API virtual bool IsStopped() const = 0;
	UTILITIES_API virtual float GetFPS() const = 0;
	UTILITIES_API virtual float GetRunningTime() const = 0;
	UTILITIES_API virtual float GetElapsedTime() const = 0; 
	UTILITIES_API static ITimer * CreateTimer();
};


#endif // Timer_h__