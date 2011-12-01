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
		GRAPHIC_API static IResourceManager* TheResourceManager();
		GRAPHIC_API virtual void Init() = 0;
		GRAPHIC_API virtual Utilities::IResCache * GetResourceCache() const = 0;
		GRAPHIC_API virtual void OnDestroyDevice() = 0;
		GRAPHIC_API virtual void Destroy() = 0;

	};
}
#endif // ResourceManager_hxx__