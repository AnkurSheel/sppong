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
 		 * @param[in] pVertices The vertices of this model
		 * @param[in] pIndices The indices of this model
		 * @param[in] iNumberOfVertices The number of vertices
		 * @param[in] iNumberOfIndices The number of indices
		 * @param[in] iPrimitiveCount The number of primitives
		 * @return False if there is any error
		 *
		 * Initializes the vertex buffer, index buffer and shader for this model
		 ***********************************************/
		GRAPHIC_API virtual bool VOnInitialization(const stVertex * const pVertices, 
			const unsigned long * const pIndices, const UINT iNumberOfVertices, 
			const UINT iNumberOfIndices, const UINT iPrimitiveCount) = 0;
		/********************************************//**
 		 * @param[in] pVertices The vertices of this model
		 * @param[in] pIndices The indices of this model
		 * @param[in] iNumberOfVertices The number of vertices
		 * @param[in] iNumberOfIndices The number of indices
		 * @param[in] iPrimitiveCount The number of primitives
		 * @param[in] strTextureFilename The name of the texture file
		 * @return False if there is any error
		 *
		 * Initializes the vertex buffer, index buffer and shader for this model
		 ***********************************************/
		GRAPHIC_API virtual bool VOnInitialization(const stTexVertex * const pVertices, 
			const unsigned long * const pIndices, const UINT iNumberOfVertices, 
			const UINT iNumberOfIndices, const UINT iPrimitiveCount,
			const Base::cString & strTextureFilename) = 0;
		/********************************************//**
		 *
		 * Releases and destroys all the resources 
		 ***********************************************/
		GRAPHIC_API virtual void VCleanup() = 0;
		/********************************************//**
 		 * @param[in] pCamera The camera which contains the current view matrix
		 *
		 * Puts the model geometry on the video card to prepare it for drawing
		 * by the shader
		 ***********************************************/
		GRAPHIC_API virtual void VRender(const ICamera * const pCamera) = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		GRAPHIC_API static IModel * CreateModel();
	};
}
#endif // Model_hxx__
