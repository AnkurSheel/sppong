// *************************************************************************
//  AABB   version:  1.0   Ankur Sheel  date: 2012/11/25
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************
#ifndef AABB_h__
#define AABB_h__

#include "AABB.hxx"

namespace Graphics
{
	class cAABB
		: public IAABB
	{
	public:
		cAABB();
		~cAABB();
		cAABB(const cAABB & other);
		cAABB & operator =(const cAABB & other);
		
		Base::cVector3 GetCenter() const;
		void SetCenter(const Base::cVector3 vCenter);
		Base::cVector3 GetHalfExtents() const;
		void SetHalfExtents(const Base::cVector3 vHalfExtents);
		bool Overlaps(const cAABB & other) const;

	private:
		void VTransalate(const Base::cVector3 & vDeltaPos);

	private:
		Base::cVector3	m_vCenter;
		Base::cVector3	m_vHalfExtents;
	};
}
#endif // AABB_h__