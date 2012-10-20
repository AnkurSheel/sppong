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
#include <list>

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
		void VAddChildControl(shared_ptr<IBaseControl> pChildControl);
		void VSetSize(const Base::cVector2 & vSize);
		float VGetWidth() const;
		float VGetHeight() const;

		virtual void VSetAbsolutePosition();
		virtual void VCleanup();

	private:
		typedef std::list<shared_ptr<cBaseControl> >  ControlList;

		bool VOnKeyUp(const Base::AppMsg & msg);
		bool VOnKeyDown(const Base::AppMsg & msg);

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
		void SetFocusControl(const cBaseControl * const pControl);
		
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