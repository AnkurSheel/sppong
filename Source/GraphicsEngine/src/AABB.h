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

namespace Graphics
{
	class cAABB
		: public Base::cNonCopyable
	{
	public:
		cAABB();
		~cAABB();
		Base::cVector3 GetCenter() const;
		void SetCenter(const Base::cVector3 vCenter);
		Base::cVector3 GetHalfExtents() const;
		void SetHalfExtents(const Base::cVector3 vHalfExtents);
		bool Overlaps(const cAABB & other);

	private:
		Base::cVector3	m_vCenter;
		Base::cVector3	m_vHalfExtents;
	};
}
#endif // AABB_h__