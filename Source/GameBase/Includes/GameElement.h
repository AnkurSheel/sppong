// ***************************************************************
//  GameElement   version:  1.0   Ankur Sheel  date: 05/14/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef GameElement_h__
#define GameElement_h__

#include "GameBaseDefines.h"
#include "Vector3.h"
#include "Vector2.h"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class IModel;
	class ICamera;
	class IAABB;
}

namespace GameBase
{
	class cGameElementDef
	{
	public:
		Base::cString	strModelPath;
		Base::cVector3	vPosition;
		Base::cVector3	vRotation;
		Base::cVector3	vScale;
		bool			bIsCollidable;		/*!< True if the game element is collidable */ 

		cGameElementDef()
			: vScale(1.0f, 1.0f, 1.0f)
			, bIsCollidable(false)

		{
		}
	};

	class cGameElement
		: public Base::cNonCopyable
	{
	public:
		GAMEBASE_API cGameElement();
		GAMEBASE_API virtual  ~cGameElement();
		GAMEBASE_API virtual void VInitialize(const cGameElementDef & def);
		GAMEBASE_API void Render(const Graphics::ICamera * const pCamera);
		/********************************************//**
 		 * @param[in] vRadians The angle in radians along the X,Y,Z axis
		 *
		 * Sets the rotation of the model
		 ***********************************************/
		GAMEBASE_API void SetRotation(const Base::cVector3 & vRadians);
		/********************************************//**
 		 * @return The current rotation of the model
		 *
		 * Returns the rotation of the model
		 ***********************************************/
		GAMEBASE_API Base::cVector3 GetRotation() const;
		/********************************************//**
 		 * @param[in] vPosition The position of the model
		 *
		 * Sets the position of the model.
		 ***********************************************/
		GAMEBASE_API void SetPosition(const Base::cVector3 & vPosition);
		/********************************************//**
 		 * @return The current position of the model
		 *
		 * Returns the position of the model
		 ***********************************************/
		GAMEBASE_API Base::cVector3 GetPosition() const;
		/********************************************//**
 		 * @param[in] vScale The scale of the model
		 *
		 * Sets the scale of the model.
		 ***********************************************/
		GAMEBASE_API void SetScale(const Base::cVector3 & vScale);
		/********************************************//**
 		 * @return The current scale of the model
		 *
		 * Returns the scale of the model
		 ***********************************************/
		GAMEBASE_API Base::cVector3 GetScale() const;
		GAMEBASE_API void Cleanup();
		GAMEBASE_API const Graphics::IAABB * const GetAABB() const;

	private:
		Base::cString		m_strFileName;
		Graphics::IModel *	m_pModel;	
		Base::cVector3		m_vRotation;	/*!< The rotation of the game element.*/
		Base::cVector3		m_vPosition;	/*!< The position of the game element.*/
		Base::cVector3		m_vScale;		/*!< The scale of the game element. */
		bool				m_bIsDirty;		/*!< Set to true if the position, scale or rotation is changed. */
	};
}
#endif