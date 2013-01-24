// *****************************************************************************
//  ShaderManager   version:  1.0   Ankur Sheel  date: 2012/10/26
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

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
		/** Map of shaders. The key is the hash of the shader filename. Value is a shared_ptr to the actual shader*/
		typedef std::map<unsigned long, shared_ptr <IShader> > ShaderMap;
	
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
			const Base::cString & strShaderName);
		/********************************************//**
 		 * param[in] ulFontHash The hash of the name of the shader name
		 * @return Pointer to the texture if it is found in the texture list. NULL otherwise
		 *
		 * Checks if the shader has already been loaded. Returns a pointer to the shader if
		 * it is found. NULL otherwise.
		 ***********************************************/
		shared_ptr<IShader> Find(const unsigned long ulShaderHash);
	
	private:
		ShaderMap				m_pShaders;				/*!< map of the shaders that have already been loaded */
	
	public:
		static IShaderManager *	s_pShadermanager;		/*!< static object of this class */
	};
}