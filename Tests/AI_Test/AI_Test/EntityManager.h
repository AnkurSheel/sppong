// ***************************************************************
//  EnityManager   version:  1.0   Ankur Sheel  date: 2012/07/27
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#ifndef EntityManager_h__
#define EntityManager_h__

class cEntity;

class cEntityManager
	: public Base::cNonCopyable
{
private:
	typedef std::map<int, cEntity * const > EntityMap;

public:
	~cEntityManager();
	static cEntityManager * Instance();
	void RegisterEntity(cEntity * const pNewEntity);
	void UnRegisterEntity(cEntity * const pNewEntity);
	cEntity * GetEntityFromID(const int iID);

private:
	cEntityManager();

private:
	EntityMap		m_EntityMap;
	
};
#endif // EnityManager_h__
