// *************************************************************************
//  ShaderManager   version:  1.0   Ankur Sheel  date: 2012/10/26
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
	class IShader;
}

namespace Graphics
{
	class IShaderManager
	{
	public:
		virtual ~IShaderManager(){}
		virtual bool VGetShader(shared_ptr<IShader> & pShader, 
			const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath) = 0;

		GRAPHIC_API static IShaderManager * GetInstance();
		GRAPHIC_API static void Destroy();
	};
}