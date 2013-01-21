// ****************************************************************************
//  ScrollBarControl   version:  1.0   Ankur Sheel  date: 2012/04/24
//  ---------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ****************************************************************************
// 
// ****************************************************************************
#ifndef ScrollBarControl_h__
#define ScrollBarControl_h__

#include "BaseControl.h"

namespace Graphics
{
	/********************************************//**
     * @brief Base Class for Horizontal and vertical scrollbar
	 * UI Control
     ***********************************************/
	class cScrollBarControl
		: public cBaseControl
	{
	public:
		void Initialize(const cScrollBarControlDef & def);

	protected:
		cScrollBarControl();
		virtual ~cScrollBarControl();
		/********************************************//**
		 * @param[in] iNewPosition The new position of the thumb
		 *
		 * Sets the position of the thumb to iNewPosition.
		 * Constrains the position between 0 and the no of increments
		 ***********************************************/
		virtual void VSetThumbPosition(const int iNewPosition) ;

	private:
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VRender(const ICamera * const pCamera);
		void VCleanup();
		/********************************************//**
		 * @param[in] params Not Used
		 *
		 * Increments the thumb position by 1 when the down/right button is released
		 ***********************************************/
		void IncrementArrowPressed(const Graphics::unUIEventCallbackParam & params);
		/********************************************//**
		 * @param[in] params Not Used
		 *
		 * Decrements the thumb position by 1 when the up/left button is released
		 ***********************************************/
		void DecrementArrowPressed(const Graphics::unUIEventCallbackParam & params);
		/********************************************//**
		 * @param[in] params Not Used
		 *
		 * Sets the drag mode
		 ***********************************************/
		void ThumbPressed(const Graphics::unUIEventCallbackParam & params);
		/********************************************//**
		 * @param[in] params Not Used
		 *
		 * Resets the drag mode
		 ***********************************************/
		void ThumbReleased(const Graphics::unUIEventCallbackParam & params);

	protected:
		int						m_iMinPos;							/*!< The minimum value that the scrollbar can go to. */ 
		int						m_iMaxPos;							/*!< The maximum value that the scrollbar can go to. */ 
		int						m_iThumbPos;						/*!< The current thumb position. */ 
		int						m_iNoOfIncrements;					/*!< The number of increments in the scrollbar. Equal to m_iMaxPos - m_iMinPos. */ 
		bool					m_bDragMode;						/*!< True if we are dragging the thumb. False otherwise. */ 
		IBaseControl *			m_pBtnThumb;						/*!< The thumb button. */ 
		IBaseControl *			m_pBtnDecrementArrow;				/*!< The up/left button. */ 
		IBaseControl *			m_pBtnIncrementArrow;				/*!< The bottom/right button. */ 	
		UIEventCallBackFn		m_callbackIncrementArrowPressed;	/*!< Callback function when the up/left button is pressed/released. */ 	
		UIEventCallBackFn		m_callbackDecrementArrowPressed;	/*!< Callback function when the bottom/right button is pressed/released. */ 	
		UIEventCallBackFn		m_callbackThumbPressed;				/*!< Callback function when the thumb button is pressed. */ 	
		UIEventCallBackFn		m_callbackThumbReleased;			/*!< Callback function when the thumb button is released. */
	};
}

#endif // ScrollBarControl_h__