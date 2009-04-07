// ***************************************************************
//  BaseApp   version:  1.0   Ankur Sheel  date: 04/30/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef BaseApp_h__
#define BaseApp_h__

class cBaseApp
{
public:
	virtual ~cBaseApp(){}
	virtual void Render() = 0;
	virtual void OnResetDevice() = 0;
	virtual void OnLostDevice() = 0;
	virtual void OnInit(LPDIRECT3DDEVICE9 const pDevice, const UINT iDisplayHeight, const UINT iDisplayWidth) = 0;
	virtual void ProcessInput(const long xDelta,const long yDelta, const long zDelta, const bool* const pbPressedKeys, const bool* const pbMouseButtons, const float fElapsedTime ) = 0;
	//virtual void ProcessInput(const bool* const pbPressedKeys, const float fElapsedTime) = 0;
	virtual void Restart() = 0;
} ;
#endif // BaseApp_h__