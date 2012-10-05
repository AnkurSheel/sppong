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
	class cBaseControl
		: public IBaseControl
		, public Base::cNonCopyable
	{
	public:
		void VSetVisible(bool bIsVisible);

		cBaseControl * GetNextSibling() const;

	protected:
		cBaseControl();
		virtual ~cBaseControl();
		void VRender(const ICamera * const pCamera );
		virtual bool VOnLeftMouseButtonUp(const int X, const int Y);
		virtual bool VOnLeftMouseButtonDown(const int X, const int Y);
		virtual void VSetPosition(const Base::cVector2 & vPosition);
		virtual void VSetSize(const Base::cVector2 vSize);

		virtual bool VOnMouseMove(const int X, const int Y);
		virtual bool VOnKeyDown(const Base::AppMsg & msg);
		virtual void VSetAbsolutePosition();
		float VGetWidth() const;
		float VGetHeight() const;
		void SetFocusControl(const cBaseControl * const pControl);
		cBaseControl * GetFirstChild() const;

	private:
		bool VPostMsg(const Base::AppMsg & msg);
		void VAddChildControl( IBaseControl * const pChildControl);
		void VRemoveAllChildren();
		void VRemoveChildControl(const IBaseControl * pChildControl);

		virtual bool VOnKeyUp(const Base::AppMsg & msg);
		bool AllowMovingControl();
		void ConstrainChildControl( double & dx, double & dy );
		cBaseControl * GetPreviousSibling() const;
		void SetParentControl( cBaseControl * pParentControl );
		void SetNextSibling( cBaseControl * pControl );
		void SetPreviousSibling( cBaseControl * temp );
		cBaseControl * PostToAll(const Base::AppMsg & msg);
		void PostToAllReverse(cBaseControl * const pControl, const Base::AppMsg & msg);
		void MoveToFront(cBaseControl * const pControl);
		bool IsCursorIntersect(const float fX, const float fY);
		void RenderInReverse(cBaseControl * const pControl, const ICamera * const pCamera);
	
	protected:
		shared_ptr<ISprite>			m_pCanvasSprite; 
		Base::cVector2				m_vControlAbsolutePosition;
		Base::cVector2				m_vSize;
		bool						m_bFocus;
		bool						m_bAllowMovingControls;
		Base::cVector2				m_vPosition;		
		bool						m_bIsMouseDown;
	
	private:
		cBaseControl *				m_pFocusControl;
		bool						m_bVisible;
		cBaseControl *				m_pChildControls;
		cBaseControl *				m_pNextSibling;
		cBaseControl *				m_pPreviousSibling;
		cBaseControl *				m_pParentControl;
		int							m_iNoOfChildren;
		int							m_iMouseDownXPos;
		int							m_iMouseDownYPos;
	};
}
#endif // BaseControl_h__