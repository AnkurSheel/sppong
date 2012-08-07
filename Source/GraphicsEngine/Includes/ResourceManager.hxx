// ***************************************************************
//  ResourceManager   version:  1.0   Ankur Sheel  date: 2011/11/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ResourceManager_hxx__
#define ResourceManager_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IResCache;
}
namespace Graphics
{
	class IResourceManager
	{
	public:
		virtual ~IResourceManager(){}
		GRAPHIC_API virtual void Init(const Base::cString strPath) = 0;
		GRAPHIC_API virtual Utilities::IResCache * GetResourceCache() const = 0;
		GRAPHIC_API static IResourceManager* GetInstance();
		GRAPHIC_API static void Destroy();
	};
}
#endif // ResourceManager_hxx__