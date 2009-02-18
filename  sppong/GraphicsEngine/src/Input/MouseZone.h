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

struct stHotSpot
{
	int					m_iZoneXPos;
	int					m_iZoneYPos;
	int					m_iZoneHeight;
	int					m_iZoneWidth;
	bool				m_bActive;
	LPTSTR				m_szZoneName;
	eMouseClickType		m_eClickType;
};

class cMouseZone
{
private:
	list<stHotSpot>	m_HotSpots;
public:
	GRAPHIC_API cMouseZone();
	GRAPHIC_API ~cMouseZone();
	GRAPHIC_API void FreeZones();
	GRAPHIC_API void AddZone(LPTSTR const szZoneName, const int iPosX, const int iPosY, const int iWidth, const int iHeight, const eMouseClickType eClickType);
	GRAPHIC_API void RemoveZone(LPCTSTR szZoneName);
	GRAPHIC_API bool CheckZones(const int iPosX, const int iPosY, const bool* const pbMouseButtons, LPTSTR szHitZoneName);
};
#endif // MouseZone_h__