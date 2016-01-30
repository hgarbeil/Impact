#if !defined(AFX_FILESELECTDLG_H__47867B1A_F479_4FF3_98DE_FE4B7AFEEF95__INCLUDED_)
#define AFX_FILESELECTDLG_H__47867B1A_F479_4FF3_98DE_FE4B7AFEEF95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileSelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileSelectDlg dialog

class CFileSelectDlg : public CDialog
{
// Construction
public:
	CFileSelectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileSelectDlg)
	enum { IDD = IDD_FILESELECT_DLG };
	CString	m_AnalFile;
	CString	m_FeatFile;
	CString	m_SurfFile;
	CString	m_TabFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileSelectDlg)
	afx_msg void OnButtonStatselect();
	afx_msg void OnButtonFeatureselect();
	afx_msg void OnButtonAnalysisselect();
	afx_msg void OnBrowseTabfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESELECTDLG_H__47867B1A_F479_4FF3_98DE_FE4B7AFEEF95__INCLUDED_)
