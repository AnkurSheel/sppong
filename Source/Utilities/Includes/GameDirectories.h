// *****************************************************************************
//  GameDirectories   version:  1.0   Ankur Sheel  date: 2013/01/22
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef GameDirectories_h__
#define GameDirectories_h__

#include "UtilitiesDefines.h"

namespace Utilities
{
	class IParamLoader;
}

namespace Utilities
{
	struct stGameDirectories
	{
		Base::cString	strMediaDirectory;
		Base::cString	strFontDirectory;

		UTILITIES_API static const stGameDirectories & GameDirectories();
		UTILITIES_API static void Initialize(const IParamLoader * const pParamLoader);
	};
}
#endif // GameDirectories_h__