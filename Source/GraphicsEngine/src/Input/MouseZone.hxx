// ***************************************************************
//  MouseZone   version:  1.0  Ankur Sheel  date: 06/13/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MouseZone_hxx__
#define MouseZone_hxx__

#include "GraphicEngineDefines.h"

enum eMouseClickType
{
	LEFTBUTTON  = 0,
	RIGHTBUTTON,
	WHEELBUTTON,
	LEFTANDRIGHTBUTTON,
	HOVER
};
namespace Base
{
	class cString;
}

namespace Graphics
{
	class IMouseZone
	{
	public:
		virtual ~IMouseZone(){}
		GRAPHIC_API virtual void FreeZones() = 0;
		GRAPHIC_API virtual void AddZone( const Base::cString & strZoneName, const int iPosX, const int iPosY, const int iWidth, const int iHeight, const eMouseClickType eClickType) = 0;
		GRAPHIC_API virtual void RemoveZone(const Base::cString &  strZoneName) = 0;
		GRAPHIC_API virtual bool CheckZones(const int iPosX, const int iPosY, const bool* const pbMouseButtons, Base::cString & strHitZoneName) = 0;
		GRAPHIC_API static IMouseZone * TheMouseZone();
		GRAPHIC_API static IMouseZone * CreateMouseZone();
	};
}
#endif // MouseZone_h__