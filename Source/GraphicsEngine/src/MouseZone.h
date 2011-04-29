// ***************************************************************
//  MouseZone   version:  1.0   Ankur Sheel  date: 06/13/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MouseZone_h__
#define MouseZone_h__

#include "MouseZone.hxx"
#include <list>

namespace Base
{
	class cString;
}

namespace Graphics
{
	struct stHotSpot
	{
		int					m_iZoneXPos;
		int					m_iZoneYPos;
		int					m_iZoneHeight;
		int					m_iZoneWidth;
		bool				m_bActive;
		Base::cString		m_strZoneName;
		eMouseClickType		m_eClickType;
	};

	class cMouseZone
		: public IMouseZone
	{
	private:
		std::list<stHotSpot>	m_HotSpots;
	public:
		cMouseZone();
		~cMouseZone();
		void FreeZones();
		void AddZone( const Base::cString & strZoneName, const int iPosX, const int iPosY, const int iWidth, const int iHeight, const eMouseClickType eClickType);
		void RemoveZone(const Base::cString & strZoneName);
		bool CheckZones(const int iPosX, const int iPosY, const bool* const pbMouseButtons, Base::cString & strHitZoneName);
	};
}
#endif // MouseZone_h__
