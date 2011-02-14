// ***************************************************************
//  MouseZone   version:  1.0   Ankur Sheel  date: 06/13/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "MouseZone.h"

using namespace Graphics;
using namespace std;
// ***************************************************************
// Constructor
// ***************************************************************
cMouseZone::cMouseZone()
{

}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cMouseZone::~cMouseZone()
{
	FreeZones();
}
// ***************************************************************

// ***************************************************************
// Removes all the zones
// ***************************************************************
void cMouseZone::FreeZones()
{
	m_HotSpots.clear();
}
// ***************************************************************

// ***************************************************************
// Add a new zone
// ***************************************************************
void cMouseZone::AddZone( char const * const szZoneName, const int iPosX, const int iPosY, const int iWidth, const int iHeight, const eMouseClickType eClickType )
{

	stHotSpot hotSpot;
	hotSpot.m_szZoneName = const_cast<char *>(szZoneName);
	hotSpot.m_iZoneXPos = iPosX;
	hotSpot.m_iZoneYPos = iPosY;
	hotSpot.m_iZoneWidth = iWidth;
	hotSpot.m_iZoneHeight = iHeight;
	hotSpot.m_eClickType = eClickType;
	hotSpot.m_bActive = true;

	m_HotSpots.push_back(hotSpot);
}
// ***************************************************************

// ***************************************************************
// Deactivates a Zone as per the zone name
// ***************************************************************
void cMouseZone::RemoveZone( LPCTSTR szZoneName )
{
	list <stHotSpot>::iterator iter;
	for (iter = m_HotSpots.begin(); iter != m_HotSpots.end(); iter++)
	{
		if (strcmp(iter->m_szZoneName, szZoneName) == 0)
		{
			if (iter->m_bActive)
			{
				iter->m_bActive = false;
			}
		}
	}
}
// ***************************************************************

// ***************************************************************
// Checks if any zone is selected
// ***************************************************************
bool cMouseZone::CheckZones( const int iPosX, const int iPosY, const bool* const pbMouseButtons, char * szHitZoneName )
{
	// check if a click has taken place or not
	if (!(pbMouseButtons[RIGHTBUTTON] || pbMouseButtons[LEFTBUTTON]))
	{
		return false;
	}

	list <stHotSpot>::iterator iter;
	for (iter = m_HotSpots.begin(); iter != m_HotSpots.end(); iter++)
	{
		// check if the zone is active
		if (iter->m_bActive)
		{
			// check if the zone can handle the click that has taken place
			if ((pbMouseButtons[LEFTBUTTON] && iter->m_eClickType == 0)
				||(pbMouseButtons[RIGHTBUTTON] && iter->m_eClickType == 1)
				||(pbMouseButtons[RIGHTBUTTON] || pbMouseButtons[LEFTBUTTON] && iter->m_eClickType == 2))
			{
				// check if the click is in the zone
				if ((iter->m_iZoneXPos <= iPosX)
					&& (iter->m_iZoneXPos + iter->m_iZoneWidth >= iPosX)
					&& (iter->m_iZoneYPos <= iPosY)
					&& (iter->m_iZoneYPos + iter->m_iZoneHeight >= iPosY))
				{
					//_tcscpy_s(szHitZoneName, _tcslen(iter->m_szZoneName)+1, iter->m_szZoneName);
					strcpy_s(szHitZoneName, strlen(iter->m_szZoneName)+1, iter->m_szZoneName);
					return true;
				}
			}
		}
	}
	return false;
}
// ***************************************************************

IMouseZone * IMouseZone::CreateMouseZone()
{
	cMouseZone * pMouseZone = DEBUG_NEW cMouseZone();
	return pMouseZone;
}