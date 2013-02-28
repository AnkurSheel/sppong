// *****************************************************************************
//  ParamLoader   version:  1.0   Ankur Sheel  date: 2012/08/08
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
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

	private:
		void VLoadParametersFromFile(const Base::cString & strFileName);
		float VGetParameterAsFloat(const Base::cString & strArgument) const;
		Base::tOptional<int> VGetParameterValueAsInt(const Base::cString & strParameter) const;
		Base::tOptional<float> VGetParameterValueAsFloat(const Base::cString & strParameter) const;
		Base::tOptional<bool> VGetParameterValueAsBool(const Base::cString & strParameter) const;
		Base::tOptional<Base::cString> VGetParameterValueAsString(const Base::cString & strParameter) const;
		int VGetParameterValueAsInt(const Base::cString & strParameter, const int iDefaultValue) const;
		float VGetParameterValueAsFloat(const Base::cString & strParameter, const float fDefaultValue) const;
		bool VGetParameterValueAsBool(const Base::cString & strParameter, const bool bDefaultValue) const;
		Base::cString VGetParameterValueAsString(const Base::cString & strParameter, const Base::cString & strDefaultValue) const;
		void VGetParameterValueAsIntList(const Base::cString & strParameter, std::vector<int> & vValue) const;
		void VGetParameterValueAsFloatList(const Base::cString & strParameter, std::vector<float> & vValue) const;
		void VGetParameterValueAsBoolList(const Base::cString & strParameter, std::vector<bool> & vValue) const;
		void VGetParameterValueAsStringList(const Base::cString & strParameter, std::vector<Base::cString> & vValue) const;
		bool VIsParameter(const Base::cString & strParameter) const;

		void RemoveCommentsFromLine();
		void GetNextParameter();
		void GetParameterValueAsString();
		Base::tOptional<int> GetNextParameterAsInt();
		Base::tOptional<float> GetNextParameterAsFloat();
		Base::tOptional<bool> GetNextParameterAsBool();

	private:
		std::vector<Base::cString> m_vCommandLineArguments;
	};
}
#endif // ParamLoader_h__