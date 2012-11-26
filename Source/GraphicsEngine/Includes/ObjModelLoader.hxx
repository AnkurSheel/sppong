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
	/********************************************//**
	 * @brief Interface for loading model files with extension .spdo
	 ***********************************************/
	class IObjModelLoader
	{
	public:
		virtual ~IObjModelLoader(){}
		/********************************************//**
 		 * @param[in] strModelFile The path of the model file
		 * @param[out] pModel The model
		 *
		 * Parses the strModelFile and loads the model in pModel
		 ***********************************************/
		virtual void VLoadModelFromFile(const Base::cString & strModelFile, IModel * pModel) = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		GRAPHIC_API static IObjModelLoader * GetObjModelLoader();
	};
}