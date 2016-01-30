#if !defined(AFX_TOPOPARAMS_DLG_H__E9B95E31_7161_11D5_BABE_005056986301__INCLUDED_)
#define AFX_TOPOPARAMS_DLG_H__E9B95E31_7161_11D5_BABE_005056986301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TopoParams_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTopoParams_dlg dialog

class CTopoParams_dlg : public CDialog
{
// Construction
public:
	CTopoParams_dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTopoParams_dlg)
	enum { IDD = IDD_DIALOG6 };
	float	m_nMinVal;
	float	m_nPixDim;
	float	m_nSunAz;
	float	m_nSunElev;
	float	m_nMaxVal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTopoParams_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTopoParams_dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPOPARAMS_DLG_H__E9B95E31_7161_11D5_BABE_005056986301__INCLUDED_)
