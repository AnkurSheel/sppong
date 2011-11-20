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

namespace Graphics
{
	class ISprite;
}

namespace Graphics
{
	class cBaseControl
	{
	private :
		cBaseControl(const cBaseControl&){}
		cBaseControl operator =(const cBaseControl&){}

	public:
		cBaseControl();
		~cBaseControl();
		cBaseControl * AddChildControl(cBaseControl * pControl);
		cBaseControl * RemoveChildControl(cBaseControl * pControl);
		void RemoveAllChildren();
		int GetNoOfChildren() const;
		void SetParentControl( cBaseControl * pParentControl );
		ISprite * GetSprite() const;
		void SetSprite( ISprite * pSprite );
		cBaseControl * GetFirstChild() const;
		cBaseControl * GetNextSibling() const;
		void SetNextSibling( cBaseControl * pControl );
		cBaseControl * GetPreviousSibling() const;
		void SetPreviousSibling( cBaseControl * temp );
		void GetAbsolutePosition(D3DXVECTOR2 & vPosition) const;

		virtual void OnMouseUp(const int iButton, const int X, const int Y) = 0;
		virtual void OnMouseDown(const int iButton, const int X, const int Y) = 0;
		virtual void OnMouseMove(const int X, const int Y) = 0;
		
	private:
		DWORD				m_dwWidth; // width of Canvas
		DWORD				m_dwHeight; // Height of Canvas
		bool				m_bVisible;
		ISprite *			m_pCanvasSprite; 
		cBaseControl *		m_pChildControls;
		cBaseControl *		m_pNextSibling;
		cBaseControl *		m_pPreviousSibling;
		cBaseControl *		m_pParentControl;
		int					m_iNoOfChildren;
		D3DXVECTOR2			m_vPosition;		
	};
	#include "BaseControl.inl"
}
#endif // BaseControl_h__