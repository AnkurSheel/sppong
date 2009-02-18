// ***************************************************************
//  MouseZone   version:  1.0   Ankur Sheel  date: 05/28/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "MouseZone.h"

cMouseZone::cMouseZone()
: m_iMaxZones(0)
{

}

cMouseZone::~cMouseZone()
{
	FreeZones();
}

void cMouseZone::Initialize( const UINT iMaxZones )
{
	FreeZones();
	m_iMaxZones = iMaxZones;
}

void cMouseZone::FreeZones()
{
	m_vHotSpots.clear();
}

void cMouseZone::AddZone( LPCTSTR szZoneName, const UINT iX, const UINT iY, const UINT iWidth, const UINT iHeight, const UINT iClickType )
{
	stHotSpot	hotSpot;
	hotSpot.m_iZoneXPos = iX;
	hotSpot.m_iZoneYPos = iY;
	hotSpot.m_iZoneWidth = iWidth;
	hotSpot.m_iZoneHeight = iHeight;
	hotSpot.m_szZoneName = const_cast<LPTSTR>szZoneName;
	hotSpot.m_bActive = true;
	hotSpot.m_iClickType = iClickType;

	m_vHotSpots.push_back(hotSpot);
}

void cMouseZone::RemoveZone( LPCTSTR szZoneName )
{
	int iMaxZones = m_vHotSpots.size();

	for (int iCount = 0; iCount< iMaxZones; iCount++)
	{
		if (strcmp(szZoneName, m_vHotSpots[iCount].m_szZoneName))
		{
			m_vHotSpots.erase(iCount);
			break;
		}
	}
}