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
	/********************************************//**
	 * @brief Interface for texture manager.
	 *
	 * Use this class to create and use Shaders
	 * 
	 * Singleton class.\n
	 * Usage :
	 * \li Call \c GetInstance() to use this class.
	 * \li Call \c VOnDestroy() when the application quits
	 ***********************************************/
	class IShaderManager
	{
	public:
		virtual ~IShaderManager(){}
		/********************************************//**
 		 * @param[in] strVertexShaderPath The path for the vertex shader file
		 * @param[in] strPixelShaderPath The path for the pixel shader file
		 * @return Pointer to the shader
		 *
		 * Loads and creates the shader if it has not been created already.
		 * Adds the texture to the shader list
		 * Returns a pointer to the existing shader otherwise
		 ***********************************************/
		virtual bool VGetShader(shared_ptr<IShader> & pShader, 
			const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath) = 0;

		static IShaderManager * GetInstance();
		static void Destroy();
	};
}