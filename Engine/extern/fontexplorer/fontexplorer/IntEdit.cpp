/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  8-May-08 | Created change log
*  8-May-08 | REQ #042: Unicode conversion
*****************************************************************************/
// IntEdit.cpp : implementation file
//

#include "stdafx.h"
#include "IntEdit.h"
#include "stdlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntEdit

CIntEdit::CIntEdit()
{
}

CIntEdit::~CIntEdit()
{
}


BEGIN_MESSAGE_MAP(CIntEdit, CEdit)
        //{{AFX_MSG_MAP(CIntEdit)
                // NOTE - the ClassWizard will add and remove mapping macros here.
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntEdit message handlers

/****************************************************************************
*                           CIntEdit::GetVal
* Result: int
*       
* Effect: 
*       The int value of the edit control
****************************************************************************/

int CIntEdit::GetVal()
    {
     CString s;
     CEdit::GetWindowText(s);
     return (int)_ttoi(s);                                          // REQ #042
    }

/****************************************************************************
*                           CIntEdit::SetVal
* Inputs:
*       int f: int value
* Result: void
*       
* Effect: 
*       Sets the int value of the edit control
****************************************************************************/

void CIntEdit::SetVal(int f)
    {
     CString s;
     s.Format(_T("%d"), f);
     SetWindowText(s);
    }

/****************************************************************************
*                             CIntEdit::IsBlank
* Result: BOOL
*       TRUE if control is completely blank
*       FALSE if control is nonblank
****************************************************************************/

BOOL CIntEdit::IsBlank()
    {
     CString s;
     CEdit::GetWindowText(s);
     int len = s.GetLength();
     if(len == 0)
        return TRUE;
     for(int i = 0; i < len; i++)
        if(s[i] != _T(' ') && s[i] != _T('\t'))
           return FALSE;

     return TRUE;
    }


/****************************************************************************
*                            CIntEdit::GetReadOnly
* Result: BOOL
*       TRUE if control is readonly
*       FALSE if it is read/write
****************************************************************************/

BOOL CIntEdit::GetReadOnly()
    {
     return ((::GetWindowLong(m_hWnd, GWL_STYLE) & ES_READONLY) != 0);
    }
