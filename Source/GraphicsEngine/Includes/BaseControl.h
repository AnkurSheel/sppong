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
		cBaseControl();
		virtual ~cBaseControl();
		
		virtual bool VOnLeftMouseButtonUp(const int X, const int Y);
		virtual bool VOnLeftMouseButtonDown(const int X, const int Y);
		virtual bool VOnMouseMove(const int X, const int Y);
		virtual void VSetSize(const float fNewWidth, const float fNewHeight);
		virtual void VOnLostDevice();
		virtual HRESULT VOnResetDevice();
		cBaseControl * GetNextSibling() const;
		void SetVisible(bool bIsVisible);

	protected:
		virtual void RenderPrivate(D3DXVECTOR3 & vControlAbsolutePosition, bool & bIsPositionChanged);
		DWORD VGetHeight() const;
		void GetAbsolutePosition(D3DXVECTOR3 & vPosition) const;
		void SetFocusControl(const cBaseControl * const pControl);
		cBaseControl * GetFirstChild() const;
		void VRemoveAllChildren();
		void VRegisterCallBack(function <void ()> callback){};
		void VUnregisterCallBack(){};
		bool AllowMovingControl();
		virtual bool VOnKeyDown(const AppMsg & msg);
		virtual bool VOnKeyUp(const AppMsg & msg);
	private:
		bool IsPositionChanged(const D3DXVECTOR3 & vControlPosition);
		void ConstrainChildControl( float &x, float &y );
		IBaseControl * VAddChildControl( IBaseControl * const pChildControl);
		const cBaseControl * RemoveChildControl(const cBaseControl * pChildControl);
		
		int GetNoOfChildren() const;
		cBaseControl * GetParentControl();
		void SetParentControl( cBaseControl * pParentControl );
		shared_ptr<ISprite> GetSprite() const;
		void SetSprite( shared_ptr<ISprite> pSprite );
		void SetNextSibling( cBaseControl * pControl );
		cBaseControl * GetPreviousSibling() const;
		void SetPreviousSibling( cBaseControl * temp );
		cBaseControl * GetFocusControl();
		bool GetVisible() const;
		DWORD VGetWidth() const;
		D3DXVECTOR3 VGetPosition() const;
		void VSetPosition(const D3DXVECTOR3 & vPosition);
		bool IsCursorIntersect(const float fX, const float fY);
		bool VPostMsg(const AppMsg & msg);
		cBaseControl * PostToAll(const AppMsg & msg);
		void PostToAllReverse(cBaseControl * const pControl, const AppMsg & msg);
		void MoveToFront(cBaseControl * const pControl);

	protected:
		bool						m_bFocus;
		cBaseControl *				m_pFocusControl;
		DWORD						m_dwWidth; // width of Canvas
		DWORD						m_dwHeight; // Height of Canvas
		bool						m_bVisible;
		shared_ptr<ISprite>			m_pCanvasSprite; 
		cBaseControl *				m_pChildControls;
		cBaseControl *				m_pNextSibling;
		cBaseControl *				m_pPreviousSibling;
		cBaseControl *				m_pParentControl;
		int							m_iNoOfChildren;
		D3DXVECTOR3					m_vPosition;		
		int							m_iMouseDownXPos;
		int							m_iMouseDownYPos;
		bool						m_bIsMouseDown;
		D3DXVECTOR3					m_vPrevControlPosition;
		bool						m_bAllowMovingControls;
	};
	#include "BaseControl.inl"
}
#endif // BaseControl_h__