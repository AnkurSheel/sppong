// *************************************************************************
//  ObjModelLoader   version:  1.0   Ankur Sheel  date: 2012/10/29
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class IModel;
}

namespace Graphics
{
	class IObjModelLoader
	{
	public:
		virtual ~IObjModelLoader(){}
		virtual void VLoadModelFromFile(const Base::cString & strModelFile, IModel * pModel) = 0;
		GRAPHIC_API static IObjModelLoader * GetObjModelLoader();
	};
}