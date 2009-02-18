// ***************************************************************
//  MouseZone   version:  1.0   Ankur Sheel  date: 05/28/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MouseZone_h__
#define MouseZone_h__

struct stHotSpot 
{
	UINT	m_iZoneXPos;
	UINT	m_iZoneYPos;
	UINT	m_iZoneWidth;
	UINT	m_iZoneHeight;
	bool	m_bActive;
	UINT	m_iClickType;
	LPTSTR	m_szZoneName;
};

class cMouseZone
{
private:
	UINT				m_iMaxZones;
	vector<stHotSpot>	m_vHotSpots;
public:
	cMouseZone();
	~cMouseZone();
	void Initialize(const UINT iMaxZones);
	void FreeZones();
	void AddZone(LPCTSTR szZoneName, const UINT iX, const UINT iY, const UINT iWidth, const UINT iHeight, const UINT iClickType) ;
	void RemoveZone(LPCTSTR szZoneName);
	bool CheckZones(const UINT iX, const UINT iY, LPCTSTR szZoneHit, const bool bLeftButtonDown, const bool bRightButtonDown);

};
#endif // MouseZone_h__