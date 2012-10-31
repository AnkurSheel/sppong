// *************************************************************************
//  ShaderManager   version:  1.0   Ankur Sheel  date: 2012/10/26
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "ShaderManager.hxx"

namespace Graphics
{
	class IShader;
}

namespace Graphics
{
	/********************************************//**
     * @brief Class Declaration for \c IShaderManager
     * interface
     ***********************************************/
	class cShaderManager
		: public IShaderManager
	{
		typedef std::map<Base::cString, shared_ptr <IShader> > ShaderMap;
	
	public:
		/********************************************//**
 		 * @return An Object of this class
		 *
		 * Creates an object of this class and returns it
		 ***********************************************/
		static IShaderManager * Create();

	private:
		cShaderManager();
		~cShaderManager();
		bool VGetShader(shared_ptr<IShader> & pShader, 
			const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath);
		/********************************************//**
 		 * @param[in] strVertexShaderPath The path for the vertex shader file
		 * @param[in] strPixelShaderPath The path for the pixel shader file
		 * @return Pointer to the texture if it is found in the texture list. NULL otherwise
		 *
		 * Checks if the shader has already been loaded. Returns a pointer to the shader if
		 * it is found. NULL otherwise.
		 ***********************************************/
		shared_ptr<IShader> Find(const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath);
	private:
		ShaderMap	m_pShaders;							/*!< map of the shaders that have already been loaded */
	
	public:
		static IShaderManager * s_pShadermanager;		/*!< static object of this class */
	};
}