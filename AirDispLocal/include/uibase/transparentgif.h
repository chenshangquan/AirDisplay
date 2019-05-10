#ifndef _TRANSPARENTGIF_H_
#define _TRANSPARENTGIF_H_

#include "Utility.h"
#include "uicommon.h"

class CTransparentGif : public CStatic
{
public:
	CTransparentGif();
	~CTransparentGif();

	void SetImage( UINT dwResID);
	void SetTimerDelay(UINT nDelay = 300);//设置定时器间隔，通过载入资源ID情况使用

	BOOL SetImage( LPCTSTR szFileName);
	
	void ShowGif();
	void StopGif();

protected:
	afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()

protected:
	void ThreadAnimation();
	static UINT WINAPI _ThreadAnimation(LPVOID pParam);
	void GetImageFromSource(UINT nID, Image*& image, LPCTSTR lpszType);


	HWND    m_hParent;
	UINT    m_dwResID;

	Image   *m_pImage;
	UINT    m_FrameCount;			//帧数
	int	    m_nFramePos;			//定义一个临时整型变量
	GUID    m_guid;
	Graphics *m_pGraphics;
	UINT	m_nDelay;			    //定时器间隔,参考PictureEx中的WaitForSingleObject设的

	HANDLE m_hThread;
	volatile BOOL m_bExitThread;
	HANDLE m_hExitEvent;
	POINT m_point;
	HGLOBAL m_hMem;
	bool m_bIsPlaying;//是否正在显示gif
	
};


#endif//_TRANSPARENTGIF_H_