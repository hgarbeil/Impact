#if !defined(AFX_SELECTBAND_DLG_H__0A6B3360_8222_40DC_991C_BC0525C55C52__INCLUDED_)
#define AFX_SELECTBAND_DLG_H__0A6B3360_8222_40DC_991C_BC0525C55C52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectBand_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectBand_dlg dialog

class CSelectBand_dlg : public CDialog
{
// Construction
public:
	CSelectBand_dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectBand_dlg)
	enum { IDD = IDD_DIALOG5 };
	int		m_nBand;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectBand_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectBand_dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTBAND_DLG_H__0A6B3360_8222_40DC_991C_BC0525C55C52__INCLUDED_)
