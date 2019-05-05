// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "touch.h"
#include "AboutDlg.h"
#include "afxdialogex.h"
#include "touchDlg.h"

extern CtouchDlg * g_dlg;
// CAboutDlg 对话框


CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CAboutDlg::IDD, pParent)
{
	m_dwBkResourceID = IDR_VERSION_BK;
	m_btnClose.SetImage( IDR_BTN_CLOSE_NORMAL, IDR_BTN_CLOSE_PRESS, IDR_BTN_CLOSE_HOVER, IDR_BTN_CLOSE_NORMAL);
	m_stPicLog.SetImage(IDB_PNG_LOG);

	m_staticName.SetFont(11, g_achDefaultFont);
	m_staticName.SetTextColor(Color(0,0,0));

	m_staticCompany.SetFont(9, g_achDefaultFont);
	m_staticCompany.SetTextColor(DEFAULT_FONT_COLOR);

	m_staticDes.SetFont(9, g_achDefaultFont);
	m_staticDes.SetTextColor(DEFAULT_FONT_COLOR);

	m_staticVer.SetFont(9, g_achDefaultFont);
	m_staticVer.SetTextColor(DEFAULT_FONT_COLOR);
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	//CDialogEx::DoDataExchange(pDX);
	CBaseDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_STATIC_LOG, m_stPicLog);
	DDX_Control(pDX, IDC_STATIC_NAME, m_staticName);
	DDX_Control(pDX, IDC_STATIC_COMPANY, m_staticCompany);
	DDX_Control(pDX, IDC_STATIC_DES, m_staticDes);
	DDX_Control(pDX, IDC_STATIC_VER_NAME, m_staticVer);

	DDX_Control(pDX, IDC_SYSLINK_COMPANY, m_linkCompany);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBaseDlg/*CDialogEx*/)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK_COMPANY, &CAboutDlg::OnNMClickSyslinkCompany)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CAboutDlg::OnBtnClose)
END_MESSAGE_MAP()


BOOL CAboutDlg::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	InitUI();
	return TRUE;
}

void CAboutDlg::InitUI()
{
	int width = (GetSystemMetrics ( SM_CXSCREEN )-400)/2; 
	int height= (GetSystemMetrics ( SM_CYSCREEN )-300)/2; 
	SetWindowPos( NULL, width, height, 400, 300, SWP_SHOWWINDOW/*SWP_NOMOVE*/ );
	
	m_btnClose.SetWindowPos( NULL, 363,1, 30, 35, SWP_SHOWWINDOW/*SWP_NOSIZE*/ );
	m_stPicLog.SetWindowPos( NULL, 43,86, 114, 16, SWP_NOSIZE );
	
	m_staticName.SetWindowPos( NULL, 194,136, 0, 0, SWP_NOSIZE );

	m_staticCompany.SetWindowPos( NULL, 43,198, 0, 0, SWP_NOSIZE );
	m_staticDes.SetWindowPos( NULL, 43,218, 0, 0, SWP_NOSIZE );
	m_staticVer.SetWindowPos( NULL, 43,238, 0, 0, SWP_NOSIZE );

	m_linkCompany.SetWindowPos( NULL, 170,238, 0, 0, SWP_NOSIZE );
	

	s8 achVersion[MAX_VER_LEN] = {0};
	GetBuildVersion(achVersion);
	CString strVer;
	strVer.Format(_T("V%s"), CA2W(achVersion));
	m_staticVer.SetWindowText(strVer);

}

void CAboutDlg::GetBuildVersion(s8 achVersion[MAX_VER_LEN])
{
	s8 achMon[16] = {0};
	u32 byDay = 0;
	u32 byMonth = 0;
	u32 wYear = 0;
	s8 achFullDate[24] = {0};

	s8 achDate[32] = {0};
	sprintf(achDate, "%s", __DATE__);

	sscanf(achDate, "%s %d %d", achMon, &byDay, &wYear );

	if ( 0 == stricmp( achMon, "JAN") )
		byMonth = 1;
	else if ( 0 == stricmp( achMon, "FEB") )
		byMonth = 2;
	else if ( 0 == stricmp( achMon, "MAR") )
		byMonth = 3;
	else if ( 0 == stricmp( achMon, "APR") )
		byMonth = 4;
	else if ( 0 == stricmp( achMon, "MAY") )
		byMonth = 5;
	else if ( 0 == stricmp( achMon, "JUN") )
		byMonth = 6;
	else if ( 0 == stricmp( achMon, "JUL") )
		byMonth = 7;
	else if ( 0 == stricmp( achMon, "AUG") )
		byMonth = 8;
	else if ( 0 == stricmp( achMon, "SEP") )
		byMonth = 9;
	else if ( 0 == stricmp( achMon, "OCT") )
		byMonth = 10;
	else if ( 0 == stricmp( achMon, "NOV") )
		byMonth = 11;
	else if ( 0 == stricmp( achMon, "DEC") )
		byMonth = 12;
	else
		byMonth = 0;

	sprintf( achFullDate, "%04d%02d%02d", wYear, byMonth, byDay );

	_snprintf( achVersion, MAX_VER_LEN, "%s%s", TOUCH_VERSION_ID, achFullDate );

	achVersion[strlen(achVersion) + 1] = '\0';
}

void CAboutDlg::OnNMClickSyslinkCompany(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	PNMLINK pNMLink = (PNMLINK) pNMHDR;  
	if (wcscmp(pNMLink->item.szUrl, _T("www.kedacom.com")) == 0) 
	{ 
		// 主要执行语句 
		ShellExecuteW(NULL, L"open", pNMLink->item.szUrl, NULL, NULL, SW_SHOWNORMAL); 
	}
	*pResult = 0;
}

void CAboutDlg::OnBtnClose()
{
	if (GetSafeHwnd())
	{
		CBaseDlg::OnOK();
	}
}
