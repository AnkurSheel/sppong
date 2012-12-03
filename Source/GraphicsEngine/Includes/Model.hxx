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
     * @brief Structure to hold the various parameters
	 * defining the model
     ***********************************************/
	struct stModelDef
	{
		/********************************************//**
		 * @brief Structure to hold the various parameters
		 * defining each subset of the model
		 ***********************************************/
		struct stSubsetDef
		{
			unsigned int		iNumberOfIndicesinSubset;	/*!< The number of indices in the subset */ 	
			unsigned int		iStartIndexNo;				/*!< The start index for this subset*/ 	
			Base::cString		strDiffuseTextureFilename;	/*!< Optional.The diffuse texture file name */ 	
			Base::cColor		diffuseColor;				/*!< Optional.The diffuse color */ 	
			Base::cVector3		vBoundingBoxMinPos;
			Base::cVector3		vBoundingBoxMaxPos;

			stSubsetDef()
				: iNumberOfIndicesinSubset(0)
				, iStartIndexNo(0)
			{
			}

		};

		stTexVertex *				pVertices;			/*!< The vertex data of this model */ 
		unsigned long *				pIndices;			/*!< The index data of this model */ 
		unsigned int				iNumberOfIndices;	/*!< The total number of indices */ 	
		unsigned int				iNumberOfVertices;	/*!< The number of vertices */ 
		std::vector<stSubsetDef>	vSubsetsDef;		/*!< Vector of subset definitions */ 
		Base::cVector3				vBoundingBoxMinPos;
		Base::cVector3				vBoundingBoxMaxPos;

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
 		 * @param[in] pCamera The camera which contains the current view matrix
		 *
		 * Puts the model geometry on the video card to prepare it for drawing
		 * by the shader
		 ***********************************************/
		virtual void VRender(const ICamera * const pCamera) = 0;
		/********************************************//**
		 * @param[in] vPosition The position of the model
		 * @param[in] vRotation The rotation of the model
		 * @param[in] vScale The scale of the model
		 *
		 * Recalculates the transformation matrix of this model if the scale,
		 * rotation or the position of the model changes in the world
		 ***********************************************/
		virtual void VReCalculateTransformMatrix(const Base::cVector3 vPosition,
			const Base::cVector3 vRotation, const Base::cVector3 vScale) = 0;
		/********************************************//**
		 *
		 * Releases and destroys all the resources 
		 ***********************************************/
		virtual void VCleanup() = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		GRAPHIC_API static IModel * CreateModel();
	};
}
#endif // Model_hxx__
