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
	{
	public:
		cBaseControl();
		virtual ~cBaseControl();
		IBaseControl * AddChildControl(IBaseControl * pControl);
		cBaseControl * RemoveChildControl(cBaseControl * pControl);
		void RemoveAllChildren();
		int GetNoOfChildren() const;
		cBaseControl * GetParentControl();
		void SetParentControl( cBaseControl * pParentControl );
		ISprite * GetSprite() const;
		void SetSprite( ISprite * pSprite );
		cBaseControl * GetFirstChild() const;
		cBaseControl * GetNextSibling() const;
		void SetNextSibling( cBaseControl * pControl );
		cBaseControl * GetPreviousSibling() const;
		void SetPreviousSibling( cBaseControl * temp );
		void GetAbsolutePosition(D3DXVECTOR3 & vPosition) const;
		cBaseControl * GetFocusControl();
		void SetFocusControl(const cBaseControl * const pControl);
		bool GetVisible() const;
		void SetVisible(bool bIsVisible);
		DWORD GetHeight();
		void SetHeight(DWORD dwHeight);
		DWORD GetWidth();
		void SetWidth(DWORD dwWidth);
		D3DXVECTOR3 GetPosition() const;
		void SetPosition(const D3DXVECTOR3 & vPosition);

		bool IsCursorIntersect(const float fX, const float fY);
		bool PostMsg(const AppMsg & msg);
		cBaseControl * PostToAll(const AppMsg & msg);
		void PostToAllReverse(cBaseControl * const pControl, const AppMsg & msg);
		void MoveToFront(cBaseControl * const pControl);
		
		virtual void OnMouseUp(const int iButton, const int X, const int Y) = 0;
		virtual void OnMouseDown(const int iButton, const int X, const int Y) = 0;
		virtual void OnMouseMove(const int X, const int Y) = 0;
		virtual void OnKeyDown(const AppMsg & msg ) = 0;
		virtual void OnKeyUp(const AppMsg & msg ) = 0;
		virtual void OnRender(const AppMsg & msg) = 0;

	protected:
		bool				m_bFocus;
		cBaseControl *		m_pFocusControl;
		DWORD				m_dwWidth; // width of Canvas
		DWORD				m_dwHeight; // Height of Canvas
		bool				m_bVisible;
		ISprite *			m_pCanvasSprite; 
		cBaseControl *		m_pChildControls;
		cBaseControl *		m_pNextSibling;
		cBaseControl *		m_pPreviousSibling;
		cBaseControl *		m_pParentControl;
		int					m_iNoOfChildren;
		D3DXVECTOR3			m_vPosition;		
	};
	#include "BaseControl.inl"
}
#endif // BaseControl_h__