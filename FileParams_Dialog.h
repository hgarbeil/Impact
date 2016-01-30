#if !defined(AFX_FILEPARAMS_DIALOG_H__0DF01C41_61C6_11D5_BAB5_005056986301__INCLUDED_)
#define AFX_FILEPARAMS_DIALOG_H__0DF01C41_61C6_11D5_BAB5_005056986301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileParams_Dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileParams_Dialog dialog

class CFileParams_Dialog : public CDialog
{
// Construction
public:
	int SetDefaults (char *filename, char *dtype, char *bform);
	CFileParams_Dialog(CWnd* pParent = NULL);   // standard constructor
	int bform, dt ;
// Dialog Data
	//{{AFX_DATA(CFileParams_Dialog)
	enum { IDD = IDD_DIALOG1 };
	CString	m_BFORM;
	int		m_nbands;
	CString	m_dtype;
	CString	m_Filename;
	int		m_samps;
	int		m_lines;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileParams_Dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileParams_Dialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEPARAMS_DIALOG_H__0DF01C41_61C6_11D5_BAB5_005056986301__INCLUDED_)
