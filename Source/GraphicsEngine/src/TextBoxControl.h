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
	class cString;
}

namespace Graphics
{
	class IFont;
}
namespace Graphics
{
	class cTextBoxControl
		: public cBaseControl
	{
	public:
		cTextBoxControl();
		void Init(const Base::cString & strDefaultImage, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color);
	private:
		~cTextBoxControl();
		void VOnRender(const AppMsg & msg);
		void VOnLostDevice();
		HRESULT VOnResetDevice();
		bool VOnKeyDown(const AppMsg & msg );
		void VSetAbsolutePosition();
		bool InsertText(const Base::cString & strText);
		long RemoveText(const long iQuantity);
		int	GetStringWidth();
		int	GetStringWidth(const Base::cString & strText);
		int	GetStringHeight();
		void SetText(const Base::cString & strText);
		bool SetCaratPosition(const long iPos);
		void SetCaratAbsolutePosition();

	private:
		shared_ptr<IFont>		m_pFont;
		LPD3DXLINE				m_pCaretLine;
		D3DXVECTOR2				m_avCaretVector[2];
		bool					m_bIsCaretVisible;
		Base::cString			m_strText;
		int						m_iTextWidth;
		RECT					m_rectBoundary;
		long					m_iCaretPos;
		bool					m_bTextBoxFull;
		D3DXVECTOR2				m_vAbsoluteCaratPosition[2];
	};
}
#endif // TextBoxControl_h__s