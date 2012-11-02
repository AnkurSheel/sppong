// ***************************************************************
//  BaseControl   version:  1.0   Ankur Sheel  date: 2011/07/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef BaseControl_h__
#define BaseControl_h__

#include "BaseControl.hxx"

namespace Base
{
	struct AppMsg;
}

namespace Graphics
{
	class ISprite;
}

namespace Graphics
{
	/********************************************//**
     * @brief Encapsulates all the base functionality 
	 * reequired by all th UI controls
     ***********************************************/
	class cBaseControl
		: public IBaseControl
		, public Base::cNonCopyable
	{
	public:
		void VSetVisible(bool bIsVisible);

	protected:

		cBaseControl();
		virtual ~cBaseControl();
		void VRender(const ICamera * const pCamera );
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		bool VOnMouseMove(const int X, const int Y);
		bool VOnKeyDown(const unsigned int iCharID);
		bool VOnCharPress(const unsigned int iCharID);
		void VAddChildControl(shared_ptr<IBaseControl> pChildControl);
		void VSetSize(const Base::cVector2 & vSize);
		float VGetWidth() const;
		float VGetHeight() const;

		virtual void VSetAbsolutePosition();
		virtual void VOnFocusChanged();
		virtual void VCleanup();

		void SetFocusControl(const cBaseControl * const pControl);
		void SetFocus(const bool bFocus);

	private:
		typedef std::list<shared_ptr<cBaseControl> >  ControlList;

		bool VOnKeyUp(const unsigned int iCharID);

		bool VPostMsg(const Base::AppMsg & msg);
		void VRemoveAllChildren();
		void VRemoveChildControl(shared_ptr<IBaseControl> pChildControl);
		void VSetText(const Base::cString & strText);
		void VSetPosition(const Base::cVector2 & vPosition);
		void VRegisterCallBack(function <void (bool)> callback);;
		void VUnregisterCallBack();
		
		bool AllowMovingControl();
		void ConstrainChildControl( double & dx, double & dy );
		void SetParentControl( cBaseControl * pParentControl );
		bool PostToAll(const Base::AppMsg & msg);
		void MoveToFront(const cBaseControl * const pControl);
		bool IsCursorIntersect(const float fX, const float fY);
		ControlList::const_iterator GetChildControlIterator(const cBaseControl * const pChildControl);
		
	protected:
		shared_ptr<ISprite>			m_pCanvasSprite; 
		Base::cVector2				m_vControlAbsolutePosition;
		Base::cVector2				m_vSize;
		bool						m_bFocus;
		bool						m_bAllowMovingControls;
		Base::cVector2				m_vPosition;		
		bool						m_bIsMouseDown;
		function<void (bool)>		m_pfnCallBack;
		ControlList					m_pChildControl;
	
	private:
		cBaseControl *				m_pFocusControl;
		bool						m_bVisible;
		cBaseControl *				m_pParentControl;
		int							m_iMouseDownXPos;
		int							m_iMouseDownYPos;
	};
}
#endif // BaseControl_h__