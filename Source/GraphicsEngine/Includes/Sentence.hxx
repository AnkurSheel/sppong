// *************************************************************************
//  Sentence   version:  1.0   Ankur Sheel  date: 2012/10/10
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************
#ifndef Sentence_hxx__
#define Sentence_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	class cString;
	class cColor;
}

namespace Graphics
{
	class ICamera;
	class IMyFont;
}

namespace Graphics
{
	class ISentence
	{
	public:
		virtual ~ISentence(){}
		/********************************************//**
 		 * @param[in] pCamera The camera which contains the current view matrix
		 *
		 * Puts the text on the video card to prepare it for drawing
		 * by the shader
		 ***********************************************/
		virtual void VRender(const ICamera * const pCamera) = 0;
		/********************************************//**
 		 * @param[in] vPosition The new position at which the sprite should be shown
		 *
		 * Sets the position of the sprite
		 ***********************************************/
		virtual void VSetPosition(const Base::cVector2 & vPosition) = 0;
		/********************************************//**
 		 * @param[in] vPosition The text that needs to be displayed
		 *
		 * Sets the text that needs to be shown
		 ***********************************************/
		virtual void VSetText(const Base::cString & strText) = 0;
		/********************************************//**
 		 * @param[in] colorText The text color
		 *
		 * Sets the color of the text
		 ***********************************************/
		virtual void VSetTextColor(const Base::cColor & colorText) = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		GRAPHIC_API static ISentence * CreateSentence();
		virtual bool VInitialize(shared_ptr<IMyFont> pFont, 
			const Base::cString & strText, const Base::cColor & textColor) = 0;
		virtual float VGetWidth() const = 0;
		virtual float VGetHeight() const = 0;
		virtual void VSetHeight(const float fTextHeight) = 0;
	};
}
#endif // Sentence_hxx__