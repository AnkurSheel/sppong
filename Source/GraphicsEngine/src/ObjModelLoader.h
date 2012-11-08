// *************************************************************************
//  ObjModelLoader   version:  1.0   Ankur Sheel  date: 2012/10/29
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "ObjModelLoader.hxx"

namespace Graphics
{
	class cObjModelLoader
		: public IObjModelLoader
	{
	public:
		cObjModelLoader();
		~cObjModelLoader();
		void VLoadModelFromFile(const Base::cString & strModelFile, IModel * pModel);

	private:
		float GetFloatValue(const Base::cString & strVal);
		int GetIntValue(const Base::cString & strVal);
	};
}