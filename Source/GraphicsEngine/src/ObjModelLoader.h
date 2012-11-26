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

	private:
		~cObjModelLoader();
		void VLoadModelFromFile(const Base::cString & strModelFile, IModel * pModel);
		/********************************************//**
 		 * @param[in] strVal The value as a string
		 * @return The value as a float
		 *
		 * Parses the string value and returns it as a float. 
		 * If the value is invalid returns 0.
		 ***********************************************/
		float GetFloatValue(const Base::cString & strVal);
		/********************************************//**
 		 * @param[in] strVal The value as a string
		 * @return The value as a int
		 *
		 * Parses the string value and returns it as a int. 
		 * If the value is invalid returns 0.
		 ***********************************************/
		int GetIntValue(const Base::cString & strVal);
	};
}