// configmsgdlg.cpp : implementation file
//

#include "stdafx.h"
#include "touch.h"
#include "configmsgdlg.h"
#include "utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define MSGBOX_TIMER	300
/////////////////////////////////////////////////////////////////////////////
// CConfigMsgDlg dialog


CConfigMsgDlg::CConfigMsgDlg(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CConfigMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigMsgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
//     m_crTop = DLGBKCOLOR;
//     m_crBottom = DLGBKCOLOR;
//	m_bOpenInMainDlg=TRUE;

	m_bModalDlg = TRUE;
	m_nTimeOut=0;
	m_dwRes = 0;
	
	m_dwBkResourceID = IDR_MSGBOX_BK;
	m_bRedrawUIImediately = TRUE;

	m_btnOK.SetImage(IDR_POWEROFF_OK_NOM, IDR_POWEROFF_OK_PRS, 0);
	m_btnClose.SetImage(IDR_BTN_INFO_NORMAL, IDR_BTN_INFO_PRESS, 0);
	m_btnCancel.SetImage(IDR_POWEROFF_CACL_NOM, IDR_POWEROFF_CACL_PRS, 0);

	m_btnOK.ShowText( FALSE );
	m_btnClose.ShowText( TRUE );
	m_btnCancel.ShowText( FALSE );


	m_bCancelTxtChangge = FALSE;
	memset( m_achCancelText, 0, sizeof(m_achCancelText)) ;
}

// CConfigMsgDlg::CConfigMsgDlg(UINT uResourceID, CWnd* pParent /*=NULL*/)
// : CTransparentBaseDlg(uResourceID, pParent)
// {
// 	//{{AFX_DATA_INIT(CUtilityDlg)
// 	// NOTE: the ClassWizard will add member initialization here
// 	//}}AFX_DATA_INIT
// 
// }
void CConfigMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigMsgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here

	DDX_Control(pDX, IDC_CLOSE, m_btnClose);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_MESSAGE, m_stMessage);

	DDX_Control(pDX, IDC_BTN_ICON, m_btnICON);
	DDX_Text(pDX, IDC_MESSAGE, m_csMsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigMsgDlg, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CConfigMsgDlg)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigMsgDlg message handlers
BOOL CConfigMsgDlg::OnInitDialog() 
{
	CTransparentBaseDlg::OnInitDialog();
	
	
	m_btnICON.SetImage(m_dwRes, m_dwRes, m_dwRes);
	m_btnICON.EnableWindow( FALSE );

    CRgn rgnWnd;
    CRect rect;
    GetWindowRect(&rect);
    if (rgnWnd.m_hObject) rgnWnd.DeleteObject();
    rgnWnd.CreateRoundRectRgn(0, 0, rect.Width(), rect.Height(),
        DIALOG_RGN_WIDTH, DIALOG_RGN_WIDTH);
    SetWindowRgn(rgnWnd, TRUE);
    MoveWindow(&rect);

	if (m_byType == ID_NO)
    {
        m_btnCancel.ShowWindow(SW_HIDE);
        m_btnOK.ShowWindow(SW_HIDE);
        m_btnClose.ShowWindow(SW_HIDE);
    }
	else if (m_byType == ID_CANCEL)
	{
        m_btnCancel.ShowWindow(SW_SHOW);
        m_btnOK.ShowWindow(SW_HIDE);
        m_btnClose.ShowWindow(SW_HIDE);		
	}
    else if (m_byType == ID_OK || m_byType == ID_NOCANCEL) 
    {
        m_btnCancel.ShowWindow(SW_HIDE);
        CRect rcBtn;
        m_btnOK.GetWindowRect(&rcBtn);
        ScreenToClient(&rcBtn);
        CRect rcWin;
        GetClientRect(&rcWin);
// 		GetWindowRect(&rcWin);
// 		ScreenToClient(&rcWin);
        
        s32 nLeft = (rcWin.Width() - rcBtn.Width()) / 2;
        rcBtn.OffsetRect(nLeft - rcBtn.left - 10, 0);
        m_btnOK.MoveWindow(rcBtn);
        if (m_byType == ID_NOCANCEL)
        {
            m_btnClose.ShowWindow(SW_HIDE);
        }
    }
	else  //m_byType == ID_YESNO
	{
		if( m_bCancelTxtChangge )
		{
			m_btnCancel.SetWindowText( CA2T(m_achCancelText) );
		}
		m_btnCancel.ShowWindow(SW_SHOW);
        m_btnOK.ShowWindow(SW_SHOW);
	}
	
    if (!m_csTitle.IsEmpty()) 
    {
        SetWindowText(m_csTitle);
    }
	
    CString csTitle = _T("");
    csTitle += m_csTitle;

/*	CRect cTemp1, cTemp2;
	Image *pImage = CUtility::GetImage( m_dwRes, "PNG" );
	m_btnOK.GetWindowRect( &cTemp1 );
	this->GetWindowRect( &cTemp2 );
	s32  nHeight =cTemp1.top - cTemp2.top;

	cTemp2.top = (nHeight - pImage->GetHeight()) / 2 + 10;
	cTemp2.left = 20;
	cTemp2.bottom = cTemp2.top + pImage->GetHeight();
	cTemp2.right = cTemp2.left + pImage->GetWidth();
	m_btnICON.MoveWindow( &cTemp2 );
		//mp.top


	pImage->GetHeight();*/
	
    UpdateData(FALSE);
    //自动关闭定时器
	if (m_nTimeOut != 0)
	{
		SetTimer(MSGBOX_TIMER, m_nTimeOut, NULL);
	}

	CenterWindow(GetDesktopWindow());
	SetWindowPos(&wndTopMost, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW  );

	SendMessage(WM_REDRAW_UI, 0, 0);

	return TRUE;  
}



void CConfigMsgDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == MSGBOX_TIMER)
    {
		m_bTimeOut=TRUE;
        KillTimer( MSGBOX_TIMER );

		if( m_bModalDlg )
		{
			CTransparentBaseDlg::OnCancel();
		}
		else
		{
			DELETE_WND_PTR(this);
			return;//已经删除 所以退出
		}
    }
	CTransparentBaseDlg::OnTimer(nIDEvent);
}

BOOL CConfigMsgDlg::DestroyWindow()
{
// 	g_pcMainWnd->CloseChildDlg(m_hWnd);
// 
//     // 字体回收
//     g_cChangeLan.DeleteWindowFont( m_hWnd );

	return CTransparentBaseDlg::DestroyWindow();
}


void CConfigMsgDlg::OnDestroy() 
{
	CTransparentBaseDlg::OnDestroy();
	if( !m_bModalDlg )
		delete this; //删除对象本身
}

LRESULT CConfigMsgDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == MSGBOX_CLOSE_ALL)
	{
		KillTimer( MSGBOX_TIMER );
		if( m_bModalDlg )
		{
		//	EndDialog( (u32)wParam );
			CTransparentBaseDlg::OnCancel();
		}
		else
		{
			DELETE_WND_PTR(this)
		}

	}
	return CTransparentBaseDlg::DefWindowProc(message, wParam, lParam);
}

// void CConfigMsgDlg::SetTitleName(CString strTitle)
// {
// 	m_strTitle = strTitle;
// }

void CConfigMsgDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
//	PaintBK(&dc);
}

void CConfigMsgDlg::PaintBK(CDC* pDC)
{
/*
	CRect rc;
	GetClientRect(&rc);
	
	//fill rgn//
	//	CRgn rgn;
	//	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 
	//		0, 0);
	//    pDC->FillRgn(&rgn, &CBrush(DLGBKCOLOR));
	//    
	
    //draw line
    CPen bluePen;
    bluePen.CreatePen(PS_SOLID, 2, DLGTEXTCOLOR);
    CPen *pOldPen = pDC->SelectObject(&bluePen);
    POINT pt;
    pt.x = pt.y = DIALOG_RGN_WIDTH;
    rc.left = rc.left +1;
    rc.right = rc.right -1;
    rc.bottom = rc.bottom -1;
    rc.top = rc.top +1;
    CBrush brushBlue(DLGBKCOLOR);
    CBrush* pOldBrush = pDC->SelectObject(&brushBlue);
    
    pDC->RoundRect(&rc, pt);
    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldPen);
	
	//load bmp
	CBitmap bmp;
	if (bmp.LoadBitmap(IDB_DIRECTION))
	{
		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);
		
		CDC dcMemory;
		dcMemory.CreateCompatibleDC(pDC);
		
		CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);
		
		//pDC->BitBlt(9, 6, bmpInfo.bmWidth , bmpInfo.bmHeight, &dcMemory, 
		//	0, 0, SRCCOPY);
        pDC->StretchBlt(2, 0, rc.Width()-4 , bmpInfo.bmHeight, &dcMemory, 
            0, 0,  bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
		
		dcMemory.SelectObject(pOldBitmap);
		dcMemory.DeleteDC();
	}
	
	//out title text
	CFont font;
	LOGFONT lf;
    // 根据当前的语言来选择标题字体
    if(strcmp(MTC_RESOURCE_LANG, g_cChangeLan.GetCurrentLan()) == 0)
    {
        ::GetObject(g_cChangeLan.GetEnglishFont(), sizeof(LOGFONT), &lf);
    }
    else
    {
        ::GetObject(g_cChangeLan.GetChineseFont(), sizeof(LOGFONT), &lf);
    }
    lf.lfWeight  = FW_BOLD;
	font.CreateFontIndirect(&lf);

	CFont *pOldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(DLGTEXTCOLOR);
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(DIALOG_RGN_WIDTH, DIALOG_RGN_WIDTH, m_strTitle);
	pDC->SelectObject(pOldFont);

    font.DeleteObject();
*/	
}

//xsl 0430
//客户区拖动
LRESULT CConfigMsgDlg::OnNcHitTest(CPoint point) 
{
	UINT uHitType = CTransparentBaseDlg::OnNcHitTest(point);
  /*  ScreenToClient (&point) ;
	if(uHitType == HTCLIENT && point.y < DIALOG_TITLE_HEIGHT)
		return HTCAPTION;
	*/
	return uHitType;
}

void CConfigMsgDlg::OnCancel() 
{
	KillTimer( MSGBOX_TIMER );
	if( m_bModalDlg )
		CTransparentBaseDlg::OnCancel();
	else
		DELETE_WND_PTR(this)
}

void CConfigMsgDlg::OnOK() 
{
	KillTimer( MSGBOX_TIMER );
	if( m_bModalDlg )	
		CTransparentBaseDlg::OnOK();
	else
		DELETE_WND_PTR(this)
}


void CConfigMsgDlg::OnClose()
{
	KillTimer( MSGBOX_TIMER );
	if( m_bModalDlg )
		CTransparentBaseDlg::OnCancel();
	else
		DELETE_WND_PTR(this)
}


void CConfigMsgDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
// 	if( !m_bModalDlg )
// 		delete this; //删除对象本身
// 	else
		CTransparentBaseDlg::PostNcDestroy();
}
