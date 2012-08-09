// ***************************************************************
//  ParamLoader   version:  1.0   Ankur Sheel  date: 2012/08/08
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ParamLoader_h__
#define ParamLoader_h__

#include "ParamLoaders.hxx"
#include "FileInput.h"


namespace Utilities
{
	class cParamLoader
		: public IParamLoader
		, public cFileInput
	{
	public:
		cParamLoader();
		~cParamLoader();
		bool VOpen(const Base::cString & strFileName);
		bool VClose();
		Base::tOptional<int> VGetNextParameterAsInt();
		Base::tOptional<float> VGetNextParameterAsFloat();
		Base::tOptional<bool> VGetNextParameterAsBool();
	private:
		void RemoveCommentsFromLine();
		void RemoveWhiteSpacesFromFront();
		void GetNextParameter();
		void GetParameterValueAsString();
	};
}
#endif // ParamLoader_h__