// ***************************************************************
//  Input   version:  1.0   Ankur Sheel  date: 05/12/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Input_hxx__
#define Input_hxx__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class IInput
	{
	public:
		virtual ~IInput(){}
		virtual void Init(const HINSTANCE hInst, const HWND hWnd, const UINT iTableWidth = 0 , const UINT iTableHeight= 0) = 0;
		virtual void DetectKeys() = 0;
		virtual void DetectMouseMovement() = 0;
		virtual const bool * const GetPressedKeys() const = 0;
		virtual const bool * const GetPressedButtons() const = 0;
		virtual long GetX() const = 0;
		virtual long GetY() const = 0;
		virtual long GetMouseXDelta() const = 0;
		virtual long GetMouseYDelta() const = 0;
		virtual long GetMouseZDelta() const = 0;
		virtual void LockKey(const DWORD dwKey) = 0;	
		virtual void Cleanup() = 0;
		GRAPHIC_API static IInput * CreateInputDevice();
	};
}
#endif // Input_h__