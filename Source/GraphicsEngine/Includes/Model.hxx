// ***************************************************************
//  Model   version:  1.0   Ankur Sheel  date: 2012/09/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Model_hxx__
#define Model_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	class cString;
}

namespace Graphics
{
	struct stVertex;
	struct stTexVertex;
	class ICamera;
}

namespace Graphics
{
	struct stModelDef
	{
		stTexVertex *		pVertices;						/*!< The vertex data of this model */ 
		unsigned long *		pIndices;						/*!< The index data of this model */ 
		unsigned int		iNumberOfVertices;				/*!< The number of vertices */ 
		unsigned int		iNumberOfIndices;				/*!< The number of indices */ 	
		Base::cString		strDiffuseTextureFilename;		/*!< Optional.The diffuse texture file name */ 	
		Base::cColor		diffuseColor;					/*!< Optional.The diffuse color */ 	

		stModelDef()
			: pVertices(NULL)
			, pIndices(NULL)
			, iNumberOfVertices(0)
			, iNumberOfIndices(0)
		{
		}
	};

/********************************************//**
 * @brief Interface to encapsulate the geometry 
 * for 3D models
 *
 ***********************************************/
	class IModel
	{
	public:
		GRAPHIC_API virtual ~IModel(){}
		/********************************************//**
 		 * @param[in] def The params to create the model
		 *
		 * Initializes the model
		 ***********************************************/
		virtual bool VOnInitialization(const stModelDef & def) = 0;
		/********************************************//**
		 *
		 * Releases and destroys all the resources 
		 ***********************************************/
		virtual void VCleanup() = 0;
		/********************************************//**
 		 * @param[in] pCamera The camera which contains the current view matrix
		 *
		 * Puts the model geometry on the video card to prepare it for drawing
		 * by the shader
		 ***********************************************/
		virtual void VRender(const ICamera * const pCamera) = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		GRAPHIC_API static IModel * CreateModel();
		virtual void VSetRotation(const float fRadians) = 0;
		virtual float VGetRotation() const = 0;
	};
}
#endif // Model_hxx__
