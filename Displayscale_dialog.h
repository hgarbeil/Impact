#if !defined(AFX_DISPLAYSCALE_DIALOG_H__9354AF46_876F_4675_B24A_50AB426EBDC6__INCLUDED_)
#define AFX_DISPLAYSCALE_DIALOG_H__9354AF46_876F_4675_B24A_50AB426EBDC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Displayscale_dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDisplayscale_dialog dialog

class CDisplayscale_dialog : public CDialog
{
// Construction
public:
	float m_nMin [3];
	float m_nMax [3];
	int SetBands (int nb,  int *bands);
	int ParseData ();
	~CDisplayscale_dialog();
	int bandarr [3];
	int nbands;
	int InitForByte();
	CDisplayscale_dialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDisplayscale_dialog)
	enum { IDD = IDD_DIALOG3 };
	int		m_nUsersel;
	int		m_nVal;
	int		useVal ;
	int		useUser ;
	CString	m_bandstring;
	CString	m_nMaxString;
	CString	m_nMinString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayscale_dialog)
	public:
	//virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDisplayscale_dialog)
	afx_msg void OnPercent();
	virtual void OnOK();
	afx_msg void OnVal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYSCALE_DIALOG_H__9354AF46_876F_4675_B24A_50AB426EBDC6__INCLUDED_)
