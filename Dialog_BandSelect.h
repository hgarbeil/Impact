#if !defined(AFX_DIALOG_BANDSELECT_H__AA33D623_708E_11D5_BABD_005056986301__INCLUDED_)
#define AFX_DIALOG_BANDSELECT_H__AA33D623_708E_11D5_BABD_005056986301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_BandSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog_BandSelect dialog

class CDialog_BandSelect : public CDialog
{
// Construction
public:
	int maxbands;
	int SetBandsTotal (int nb);
	CDialog_BandSelect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_BandSelect)
	enum { IDD = IDD_DIALOG5 };
	int		m_nBandnum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_BandSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_BandSelect)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_BANDSELECT_H__AA33D623_708E_11D5_BABD_005056986301__INCLUDED_)
