#pragma once
#include "dynamicwnd.h"
#include "transtatic.h"
#include "afxwin.h"
#include "afxcmn.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CBaseDlg//CDialogEx
{
public:
	//CAboutDlg();
	CAboutDlg(CWnd* pParent = NULL); 

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };
	
	static void GetBuildVersion(s8 achVersion[MAX_VER_LEN]);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickSyslinkCompany(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBtnClose();
	DECLARE_MESSAGE_MAP()

	void InitUI();

private:
	CTransparentBtn	m_btnClose;

	CTransparentStatic m_stPicLog;

	CTransparentStatic m_staticName;
	CTransparentStatic m_staticCompany;
	CTransparentStatic m_staticDes;
	CTransparentStatic m_staticVer;
	CTransparentSysLink m_linkCompany;
	
};