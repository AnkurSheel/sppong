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
#include <vector>

namespace Utilities
{
	class cParamLoader
		: public IParamLoader
		, public cFileInput
	{
	public:
		cParamLoader();
		~cParamLoader();
		Base::tOptional<int> VGetNextParameterAsInt();
		Base::tOptional<float> VGetNextParameterAsFloat();
		Base::tOptional<bool> VGetNextParameterAsBool();
		void VLoadParametersFromFile(const Base::cString & strFileName);
		float VGetParameterAsFloat(const Base::cString & strArgument);
		Base::tOptional<int> VGetParameterValueAsInt(const Base::cString & strParameter);
		Base::tOptional<float> VGetParameterValueAsFloat(const Base::cString & strParameter);
		Base::tOptional<bool> VGetParameterValueAsBool(const Base::cString & strParameter);
		Base::tOptional<Base::cString> VGetParameterValueAsString(const Base::cString & strParameter);
		Base::tOptional<int> VGetParameterValueAsInt(const Base::cString & strParameter, const int iDefaultValue);
		Base::tOptional<float> VGetParameterValueAsFloat(const Base::cString & strParameter, const float fDefaultValue);
		Base::tOptional<bool> VGetParameterValueAsBool(const Base::cString & strParameter, const bool bDefaultValue);
		Base::tOptional<Base::cString> VGetParameterValueAsString(const Base::cString & strParameter, const Base::cString & strDefaultValue);

		bool VIsParameter(const Base::cString & strParameter);
	private:
		void RemoveCommentsFromLine();
		void GetNextParameter();
		void GetParameterValueAsString();

	private:
		std::vector<Base::cString> m_vCommandLineArguments;
	};
}
#endif // ParamLoader_h__