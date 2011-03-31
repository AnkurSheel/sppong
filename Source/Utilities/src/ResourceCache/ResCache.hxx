// ***************************************************************
//  ResCache   version:  1.0   Ankur Sheel  date: 2011/04/01
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ResCache_hxx__
#define ResCache_hxx__

namespace Utilities
{
	class cResource;
}
namespace Utilities
{
	class IResourceFile
	{
	public:
		virtual ~IResourceFile() {}
		virtual bool Open()=0;
		virtual int GetResourceSize(const cResource &r) = 0;
		virtual void GetResource(const cResource &r, char *buffer) = 0;
	};
}
#endif // ResCache_hxx__