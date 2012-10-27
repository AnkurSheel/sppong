// *************************************************************************
//  ShaderManager   version:  1.0   Ankur Sheel  date: 2012/10/26
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "ShaderFactory.hxx"

namespace Graphics
{
	class IShader;
}

namespace Graphics
{
	class cShaderFactory
		: public IShaderFactory
	{
		typedef std::map<Base::cString, shared_ptr <IShader> > ShaderMap;
	
	public:
		static IShaderFactory * Create();

	private:
		cShaderFactory();
		~cShaderFactory();
		bool VGetShader(shared_ptr<IShader> & pShader, 
			const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath);
		shared_ptr<IShader> Find(const Base::cString & strVertexShaderPath,
			const Base::cString & strPixelShaderPath);
	private:
		ShaderMap	m_pShaders;
	
	public:
		static IShaderFactory * s_pShadermanager;		/*!< static object of this class */
	};
}