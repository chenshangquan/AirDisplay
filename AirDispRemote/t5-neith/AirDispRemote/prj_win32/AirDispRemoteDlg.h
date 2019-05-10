
// tpadDlg.h : header file
//

#pragma once


// CtpadDlg dialog
class CAirDispRemoteDlg : public CDialogEx
{
// Construction
public:
	CAirDispRemoteDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDI_ICON1 };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
