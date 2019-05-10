#pragma once
#include "dynamicwnd.h"
#include "transtatic.h"


// 用于应用程序“关于”菜单项的 CBannerDlg 对话框

class CBannerDlg : public CBaseDlg//CDialogEx
{
public:
	//CBannerDlg();
	CBannerDlg(CWnd* pParent = NULL); 

	// 对话框数据
	enum { IDD = IDD_BANNER_DLG };
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void DoHide();
	void StopAutoHide();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual void OnBannerClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	
	BOOL SetWindowPos(const CWnd* pWndInsertAfter,LPCRECT pCRect, UINT nFlags = SWP_SHOWWINDOW);
	void Hide();
	void Show();

	DECLARE_MESSAGE_MAP()

private:
	void InitUI();

private:
	CTransparentBtn m_btnBannerClose;
	CTransparentStatic m_staticBanner;

	BOOL m_bIsSetTimer;      //是否设置了检测鼠标的Timer
	int  m_dwEdgeHeight;     //边缘高度
	int  m_dwEdgeWidth;      //边缘宽度
	BOOL m_bIsFinished;      //隐藏或显示过程是否完成
	BOOL m_bIsHiding;        //该参数只有在!m_hsFinished才有效,真:正在隐藏,假:正在显示
};