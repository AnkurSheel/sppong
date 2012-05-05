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
		cBaseControl * GetNextSibling() const;
		void VSetVisible(bool bIsVisible);

	protected:
		cBaseControl();
		virtual ~cBaseControl();
		void VOnRender( const AppMsg & msg );
		virtual void VOnLostDevice();
		virtual HRESULT VOnResetDevice();
		virtual bool VOnLeftMouseButtonUp(const int X, const int Y);
		virtual bool VOnLeftMouseButtonDown(const int X, const int Y);
		virtual bool VOnMouseMove(const int X, const int Y);
		virtual bool VOnKeyDown(const AppMsg & msg);
		virtual void VSetSize(const float fNewWidth, const float fNewHeight);
		virtual void VSetPosition(const D3DXVECTOR3 & vPosition);
		virtual void VSetAbsolutePosition();
		//D3DXVECTOR3 VGetPosition() const;
		float VGetWidth() const;
		float VGetHeight() const;
		void SetFocusControl(const cBaseControl * const pControl);
		bool VIsVisible() const;
		cBaseControl * GetFirstChild() const;

	private:
		bool VPostMsg(const AppMsg & msg);
		virtual bool VOnKeyUp(const AppMsg & msg);
		IBaseControl * VAddChildControl( IBaseControl * const pChildControl);
		void VRemoveAllChildren();
		void VRegisterCallBack(function <void (bool)> callback){};
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
		cBaseControl * PostToAll(const AppMsg & msg);
		void PostToAllReverse(cBaseControl * const pControl, const AppMsg & msg);
		void MoveToFront(cBaseControl * const pControl);
		bool IsCursorIntersect(const float fX, const float fY);

	protected:
		shared_ptr<ISprite>			m_pCanvasSprite; 
		D3DXVECTOR3					m_vControlAbsolutePosition;
		float						m_fHeight; // Height of Canvas
		float						m_fWidth; // width of Canvas
		bool						m_bFocus;
		bool						m_bAllowMovingControls;
		D3DXVECTOR3					m_vPosition;		
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
	#include "BaseControl.inl"
}
#endif // BaseControl_h__