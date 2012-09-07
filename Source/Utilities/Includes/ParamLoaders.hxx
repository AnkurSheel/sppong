// ***************************************************************
//  ParamLoaders   version:  1.0   Ankur Sheel  date: 2012/08/08
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ParamLoaders_hxx__
#define ParamLoaders_hxx__

namespace Base
{
	template<class T>
	class tOptional;
}

namespace Utilities
{
	class IParamLoader
	{
	public:
		virtual ~IParamLoader(){}
		//UTILITIES_API virtual bool VOpen(const Base::cString & strFileName) = 0;
		//UTILITIES_API virtual bool VClose() = 0;
		UTILITIES_API virtual void VLoadParametersFromFile(const Base::cString & strFileName) = 0;
		
		UTILITIES_API virtual Base::tOptional<int> VGetParameterValueAsInt(const Base::cString & strParameter) = 0;
		UTILITIES_API virtual Base::tOptional<float> VGetParameterValueAsFloat(const Base::cString & strParameter) = 0;
		UTILITIES_API virtual Base::tOptional<bool> VGetParameterValueAsBool(const Base::cString & strParameter) = 0;
		UTILITIES_API virtual Base::tOptional<Base::cString> VGetParameterValueAsString(const Base::cString & strParameter) = 0;
		UTILITIES_API virtual int VGetParameterValueAsInt(const Base::cString & strParameter, const int iDefaultValue) = 0;
		UTILITIES_API virtual float VGetParameterValueAsFloat(const Base::cString & strParameter, const float fDefaultValue) = 0;
		UTILITIES_API virtual bool VGetParameterValueAsBool(const Base::cString & strParameter, const bool bDefaultValue) = 0;
		UTILITIES_API virtual Base::cString VGetParameterValueAsString(const Base::cString & strParameter, const Base::cString & strDefaultValue) = 0;
		UTILITIES_API virtual void VGetParameterValueAsIntList(const Base::cString & strParameter, std::vector<int> & vValue) = 0;
		UTILITIES_API virtual bool VIsParameter(const Base::cString & strParameter) = 0;
		//UTILITIES_API virtual Base::tOptional<int> VGetNextParameterAsInt() = 0;
		//UTILITIES_API virtual Base::tOptional<float> VGetNextParameterAsFloat() = 0;
		//UTILITIES_API virtual Base::tOptional<bool> VGetNextParameterAsBool() = 0;
		UTILITIES_API static IParamLoader * CreateParamLoader();
	};
}
#endif // ParamLoaders_hxx__