// ***************************************************************
//  MouseZone   version:  1.0  Ankur Sheel  date: 06/13/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MouseZone_h__
#define MouseZone_h__

#include "GraphicEngineDefines.h"

enum eMouseClickType
{
	LEFTBUTTON  = 0,
	RIGHTBUTTON,
	WHEELBUTTON,
	LEFTANDRIGHTBUTTON,
	HOVER
};

class IMouseZone
{
public:
	virtual ~IMouseZone(){}
	GRAPHIC_API virtual void FreeZones() = 0;
	GRAPHIC_API virtual void AddZone( char const * const  szZoneName, const int iPosX, const int iPosY, const int iWidth, const int iHeight, const eMouseClickType eClickType) = 0;
	GRAPHIC_API virtual void RemoveZone(LPCTSTR szZoneName) = 0;
	GRAPHIC_API virtual bool CheckZones(const int iPosX, const int iPosY, const bool* const pbMouseButtons, char * szHitZoneName) = 0;
	GRAPHIC_API static IMouseZone * TheMouseZone();
	GRAPHIC_API static IMouseZone * CreateMouseZone();
};
#endif // MouseZone_h__