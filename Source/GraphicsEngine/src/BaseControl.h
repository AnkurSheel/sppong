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

namespace Graphics
{
	class ISprite;
	struct AppMsg;
}

namespace Graphics
{
	class cBaseControl
		: public IBaseControl
		, public Base::cNonCopyable
	{
	public:
		cBaseControl * GetNextSibling() const;
		void SetVisible(bool bIsVisible);

	protected:
		cBaseControl();
		virtual ~cBaseControl();
		virtual void VOnLostDevice();
		virtual HRESULT VOnResetDevice();
		virtual bool VOnLeftMouseButtonUp(const int X, const int Y);
		virtual bool VOnLeftMouseButtonDown(const int X, const int Y);
		virtual bool VOnMouseMove(const int X, const int Y);
		virtual bool VOnKeyDown(const AppMsg & msg);
		virtual void VSetSize(const float fNewWidth, const float fNewHeight);
		virtual void VSetAbsolutePosition();
		DWORD VGetHeight() const;
		void SetFocusControl(const cBaseControl * const pControl);
		cBaseControl * GetFirstChild() const;

	private:
		bool VPostMsg(const AppMsg & msg);
		virtual bool VOnKeyUp(const AppMsg & msg);
		void VSetPosition(const D3DXVECTOR3 & vPosition);
		//D3DXVECTOR3 VGetPosition() const;
		DWORD VGetWidth() const;
		IBaseControl * VAddChildControl( IBaseControl * const pChildControl);
		void VRemoveAllChildren();
		void VRegisterCallBack(function <void ()> callback){};
		void VUnregisterCallBack(){};
		bool AllowMovingControl();
		void ConstrainChildControl( float &x, float &y );
		const cBaseControl * RemoveChildControl(const cBaseControl * pChildControl);
		//int GetNoOfChildren() const;
		//cBaseControl * GetParentControl();
		//shared_ptr<ISprite> GetSprite() const;
		cBaseControl * GetPreviousSibling() const;
		//cBaseControl * GetFocusControl();
		//bool GetVisible() const;
		void SetParentControl( cBaseControl * pParentControl );
		//void SetSprite( shared_ptr<ISprite> pSprite );
		void SetNextSibling( cBaseControl * pControl );
		void SetPreviousSibling( cBaseControl * temp );
		bool IsCursorIntersect(const float fX, const float fY);
		cBaseControl * PostToAll(const AppMsg & msg);
		void PostToAllReverse(cBaseControl * const pControl, const AppMsg & msg);
		void MoveToFront(cBaseControl * const pControl);

	protected:
		shared_ptr<ISprite>			m_pCanvasSprite; 
		D3DXVECTOR3					m_vControlAbsolutePosition;
		DWORD						m_dwHeight; // Height of Canvas
		DWORD						m_dwWidth; // width of Canvas
		bool						m_bFocus;
		bool						m_bAllowMovingControls;
		D3DXVECTOR3					m_vPosition;		

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
		bool						m_bIsMouseDown;
	};
	#include "BaseControl.inl"
}
#endif // BaseControl_h__