// ***************************************************************
//  TextBoxControl   version:  1.0   Ankur Sheel  date: 2011/12/01
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef TextBoxControl_h__
#define TextBoxControl_h__

#include "BaseControl.h"

namespace Base
{
	struct AppMsg;
}

namespace Graphics
{
	class ISentence;
	class ISprite;
}

namespace Utilities
{
	class ITimer;
}

namespace Graphics
{
	/********************************************//**
     * @brief Class Declaration for a TextBox UI Control
     ***********************************************/
	class cTextBoxControl
		: public cBaseControl
	{
	public:
		cTextBoxControl();
		/********************************************//**
		 * @param[in] def The parameter definition to create a textbox control
		 *
		 * Initializes the textbox control as per the parameters
		 ***********************************************/
		void Initialize(const cTextBoxControlDef & def);
	
	private:
		~cTextBoxControl();
		void VRender(const ICamera * const pCamera);
		bool VOnKeyDown(const unsigned int iCharID);
		bool VOnCharPress(const unsigned int iCharID);
		void VSetAbsolutePosition();
		void VOnFocusChanged();
		void VCleanup();
		/********************************************//**
		 * @param[in] strText The text to be inserted
		 *
		 * Inserts the text at the carat position
		 ***********************************************/
		bool InsertText(const Base::cString & strText);
		/********************************************//**
		 * @param[in] uiQuantity The number of characters to be removed
		 *
		 * Removes the uiQuantity characters at the carat position
		 ***********************************************/
		void RemoveText(const unsigned int uiQuantity);
		/********************************************//**
		 * @return The width in pixels of the text in the textbox.
		 *
		 * Returns the width in pixels of the text in the textbox.
		 ***********************************************/
		int	GetStringWidth();
		 /********************************************//**
		 * @param[in] strText The text for which the width is needed
		 * @return The width of the text that has been passed
		 *
		 * Gets the width of the sentence thats has been passed
		 * in strText
		 ***********************************************/
		int	GetStringWidth(const Base::cString & strText);
		/********************************************//**
		 * @param[in] strText The text to be set
		 *
		 * Sets the text of the textbox
		 ***********************************************/
		void SetText(const Base::cString & strText);
		/********************************************//**
		 * @param[in] iPos The new position of the carat
		 * @return True if the carat was set to iPos. False otherwise
		 *
		 * Sets the position of the carat. The position is
		 * constrained between 0 and the sentence length
		 ***********************************************/
		bool SetCaratPosition(const unsigned int iPos);
		/********************************************//**
		 *
		 * Sets the absolute position of the carat on the
		 * screen
		 ***********************************************/
		void SetCaratAbsolutePosition();

	private:
		ISentence *				m_pSentence;			/*!< The text in the textbox. */
		shared_ptr<ISprite>		m_pCaretSprite;			/*!< The sprite of the caret line. */
		float 					m_fCaretPosInTextBox;	/*!< The position (in pixles) of the caret in the textbox. */
		float					m_fLastCaretUpdateTime;	/*!< The time at which the caret visibility was last updated. */
		unsigned int			m_iCaretPosInText;		/*!< The position of the carat in the text. */
		bool					m_bTextBoxFull;			/*!< True if textbox cannot contain any more characters. False otherwise. */
		float					m_fCaretUpdateTime;		/*!< The time after which the caret visibility should be updated. */
		Utilities::ITimer *		m_pTimer;				/*!< The timer for updating the caret visibility. */
		bool					m_bIsCaretVisible;		/*!< True if the caret is currently visible. False otherwise. */
	};
}
#endif // TextBoxControl_h__s