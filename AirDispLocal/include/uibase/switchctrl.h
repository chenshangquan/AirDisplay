#if !defined(AFX_MYSTATIC_H__E627A6D1_F406_4073_9FB4_656440DBFEF2__INCLUDED_)
#define AFX_MYSTATIC_H__E627A6D1_F406_4073_9FB4_656440DBFEF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SwitchCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSwitchCtrl window
//#include "TriangleBtn.h"

#include "ControlButton.h"
#include "centerst.h"
#include "TransparentBtn.h"
#include "transparentbasedlg.h"
#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#include <map>





typedef struct tagIndexVal 
{
	DWORD	dwVal;			//数字值 比如枚举等
	CString cstrVal;		//对应的显示文字
}tIndVal;

class CSwitchCtrl : public CStatic 
{
// Construction
public:
	CSwitchCtrl();
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSwitchCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSwitchCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	LRESULT OnClickBtn(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

public:
	void ZeroMember();
	BOOL Create( CRect &rect, UINT TxtBoxLen, CWnd *pwnd );
//	void SetColors(COLORREF  rolloverclr, COLORREF  downclr, COLORREF  normalclr ,  COLORREF  focusclr);
	void SetBMP();
	void SetText(CString &str, BOOL bShowNothing = FALSE);
	s32  GetCurSel();
	u32	 GetDataItem( s32 index );
	s32	 SetCurSel( s32 pos);
	s32  GetCountItem();

	void EnableUse(BOOL bUse = TRUE);

protected:
	s32				m_nCurInd;			//当前的索引值
	vector<tIndVal> m_vctIndVal;
private:
	CRect m_cRectLeft;
	CRect m_cRectRight;
	CRect m_cRectST;
	
// 	CControlButton	*m_pcBtnLeft;
// 	CControlButton	*m_pcBtnRight;
protected:
 	CTransparentBtn	*m_pcBtnLeft;
 	CTransparentBtn	*m_pcBtnRight;
public:
	CTransparentStatic/*CCenterST*/		*m_pcSt;

	HWND	 		m_hParent;
	
//	static UINT		m_sdwBtnID;
//	static UINT		m_sdwSTID;
	
// 	UINT			m_dwBtnLeft_ID;
// 	UINT			m_dwBtnRight_ID;
// 	UINT			m_dwST_ID;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__E627A6D1_F406_4073_9FB4_656440DBFEF2__INCLUDED_)
