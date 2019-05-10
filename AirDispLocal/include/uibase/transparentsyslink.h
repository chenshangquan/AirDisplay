#ifndef _TRANSPARENTSYSLINK_H_
#define _TRANSPARENTSYSLINK_H_

class CTransparentSysLink : public CLinkCtrl
{
public:
	CTransparentSysLink();
	~CTransparentSysLink();


	void SetFont( const u32 dwFontSize = 18 , const s8* achFontFamlyName = ("Arial") )
	{
		m_dwFontSize = dwFontSize;

		if ( achFontFamlyName == NULL )
		{
			return;
		}
		ZeroMemory( m_awszFontName, sizeof(m_awszFontName) );
		MultiByteToWideChar(CP_ACP, 0, achFontFamlyName, -1, m_awszFontName, strlen(achFontFamlyName) );
	}

	void    SetTextColor( Color color )
	{
		m_cTextColor = color;
	}

protected:
	afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()
protected:
	HWND    m_hParent;

	WCHAR	m_awszFontName[64];
	u32		m_dwFontSize;
	Color   m_cTextColor;

};





#endif//_TRANSPARENTSYSLINK_H_