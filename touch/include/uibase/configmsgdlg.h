#if !defined(AFX_CONFIGMSGDLG_H__AAD13790_194D_4FA7_892D_D0C5C8D213CF__INCLUDED_)
#define AFX_CONFIGMSGDLG_H__AAD13790_194D_4FA7_892D_D0C5C8D213CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// configmsgdlg.h : header file
//
#define DIALOG_LEFT_MARGIN 15
#define DIALOG_TOP_MARGIN  13
#define DIALOG_TITLE_HEIGHT 26
#define DIALOG_RECT_ANGLE 10
#define DIALOG_RGN_WIDTH  5

#define MSGBOX_CLOSE_ALL		WM_USER + 1125
/////////////////////////////////////////////////////////////////////////////
// CConfigMsgDlg dialog
#define DLGBKCOLOR                  RGB(234, 236, 239)
#define DLGTEXTCOLOR                RGB(80, 114, 170)


const u8 ID_YESNO = 0;
const u8 ID_OK = 1;
const u8 ID_NO = 2;
const u8 ID_NOCANCEL = 3;
const u8 ID_CANCEL   = 4;
//#include "uilibhead.h"
#include "transparentbasedlg.h"
#include "transparentbtn.h"

class CConfigMsgDlg: public CTransparentBaseDlg
{
// Construction
public:
	CConfigMsgDlg(CWnd* pParent = NULL);   // standard constructor
	//CConfigMsgDlg(UINT uResourceID, CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CConfigMsgDlg)
	enum { IDD = IDD_CFG_MSG_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

 //   virtual void SetTitleName(CString strTitle);//设置标题名
	virtual void PaintBK(CDC* pDC);
	virtual BOOL DestroyWindow();

    void SetInfo(LPCTSTR lpMsg, LPCTSTR lpTitle = NULL, u8 byType = ID_OK)
    {
        m_csMsg = lpMsg;
        m_csTitle = lpTitle;
        m_byType = byType;
    }
	void SetInterVal(UINT nTimeOut)
	{
		m_nTimeOut=nTimeOut;
	}
	void SetModal(BOOL bModal)
	{
		m_bModalDlg = bModal;
	}
	void SetIcon(u32 Res)
	{
		m_dwRes = Res;
	}
	void SetCancelText(char *pch){ m_bCancelTxtChangge = TRUE; strcpy( m_achCancelText, pch ); }

	BOOL m_bTimeOut;
	UINT m_nTimeOut;
	BYTE m_byType;
	u32	 m_dwRes;
	BOOL m_bCancelTxtChangge;
	s8	 m_achCancelText[256] ;

	CTransparentBtn/*CFlatButton*/	m_btnClose;
	CTransparentBtn/*CFlatButton*/	m_btnCancel;
	CTransparentBtn/*CFlatButton*/	m_btnOK;
	CTransparentStatic/*CStatic*/	m_stMessage;
	CTransparentBtn/*CStatic*/	m_btnICON;
	CString		m_csMsg;
    CString     m_csTitle;
    CBrush      m_brushBk;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigMsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);


	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strTitle;
//	BOOL  m_bOpenInMainDlg;  //是否由主窗口关闭
	BOOL  m_bModalDlg;		//是否是模式对话框
	// Generated message map functions
	//{{AFX_MSG(CConfigMsgDlg)
    afx_msg void OnPaint();
    afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancel();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//	dlg.SetModal(TRUE);					\
//错误提示
#define ErrorMsg(str)                   \
{									    \
    CConfigMsgDlg dlg;					\
    CString szTemp, szPrompt;			\
    szTemp = str;						\
	szPrompt  = "提示";					\
    dlg.SetInfo(szTemp, szPrompt, ID_OK);	\
	dlg.SetInterVal( 6000 );				\
	dlg.SetModal(TRUE);					\
    dlg.DoModal();						\
}	

#define ShowMsgBox(str)                   \
{									    \
    CConfigMsgDlg dlg;					\
    CString szTemp, szPrompt;			\
    szTemp = str;						\
	szPrompt  = "提示";					\
    dlg.SetInfo(szTemp, szPrompt, ID_OK);	\
	dlg.SetInterVal( 6000 );				\
	dlg.SetModal(TRUE);					\
    dlg.DoModal();						\
}	
//	pWnd->SetModal(FALSE);								\
//
#define MsgBox_Modalless(str, pParentWnd , pWnd, Flag , Icon)			\
{														\
    pWnd = new CConfigMsgDlg();							\
    CString szTemp, szPrompt;							\
    szTemp = str;										\
	szPrompt  = "提示";									\
    pWnd->SetInfo(szTemp, szPrompt, Flag);				\
	pWnd->SetIcon( Icon );								\
	pWnd->SetInterVal( 6000 );							\
	pWnd->SetModal(FALSE);								\
    pWnd->Create(IDD_CFG_MSG_DLG,pParentWnd);			\
														\
}


#define DELETE_WND_PTR(pWnd)	\
	if (pWnd != NULL)			\
{								\
	pWnd->DestroyWindow();		\
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_CONFIGMSGDLG_H__AAD13790_194D_4FA7_892D_D0C5C8D213CF__INCLUDED_)
