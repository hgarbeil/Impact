#if !defined(AFX_RESULTS_DLG_H__3DE79D68_2862_4EDF_AD29_488BDD2962DA__INCLUDED_)
#define AFX_RESULTS_DLG_H__3DE79D68_2862_4EDF_AD29_488BDD2962DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Results_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResults_dlg dialog

#define WM_WRITE_FILE WM_USER + 5
#include "CraterStats.h" 

class CResults_dlg : public CDialog
{
// Construction
public:
	CResults_dlg(CWnd* pParent = NULL);   // standard constructor
	CResults_dlg(CView *); //  modeless constructor
	BOOL Create() ;
	void update () ;



	CView *m_pView ;


// Dialog Data
	//{{AFX_DATA(CResults_dlg)
	enum { IDD = IDD_DIALOG7 };
	CStatic	m_RimProfile ;
	CString	m_xmax;
	CString	m_xmin;
	CString	m_ymax;
	CString	m_ymin;
	CString	m_RimText;
	CString	m_cratervol;
	CString	m_Primvol;
	CString	m_Rimvol;
	CString	m_Secvol;
	CString	m_outfilename;
	//}}AFX_DATA
	CString outfilename ;
	


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResults_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResults_dlg)
	afx_msg void OnBrowseOutput();
	afx_msg void OnWritefile();
	afx_msg void OnRimProf();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTS_DLG_H__3DE79D68_2862_4EDF_AD29_488BDD2962DA__INCLUDED_)
