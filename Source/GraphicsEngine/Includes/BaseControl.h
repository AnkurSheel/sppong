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
		int GetNoOfChildren();
		void SetParentControl( cBaseControl * pParentControl );
		ISprite * GetSprite();
		void SetSprite( ISprite * pSprite );
		cBaseControl * GetFirstChild();
		cBaseControl * GetNextSibling();
		void SetNextSibling( cBaseControl * pControl );
		void SetPreviousSibling( cBaseControl * temp );
		cBaseControl * GetPreviousSibling();
		void GetAbsolutePosition(D3DXVECTOR2 & vPosition);
	
	private:
		DWORD			m_dwWidth; // width of Canvas
		DWORD			m_dwHeight; // Height of Canvas
		bool			m_bVisible;
		ISprite *		m_pCanvasSprite; 
		cBaseControl *	m_pChildControls;
		cBaseControl *	m_pNextSibling;
		cBaseControl *	m_pPreviousSibling;
		cBaseControl *	m_pParentControl;
		int				m_iNoOfChildren;
		D3DXVECTOR2		m_vPosition;		
	};
	#include "BaseControl.inl"
}
#endif // BaseControl_h__