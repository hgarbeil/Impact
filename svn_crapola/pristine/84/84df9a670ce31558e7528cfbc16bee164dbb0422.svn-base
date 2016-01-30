#if !defined(AFX_RESFORMVIEW1_H__E088FBB2_AFAF_4B03_9500_A1D8F2D5E3DC__INCLUDED_)
#define AFX_RESFORMVIEW1_H__E088FBB2_AFAF_4B03_9500_A1D8F2D5E3DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResFormView1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CResFormView : public CFormView
{
protected:
	CResFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CResFormView)

// Form Data
public:
	//{{AFX_DATA(CResFormView)
	enum { IDD = IDD_CFV_FORM };
	CStatic	m_statRimProf;
	CString	m_strLocationString;
	CString	m_strSurftext;
	CString	m_strCratRim;
	CString	m_strInner;
	CString	m_strOuter;
	CString	m_strXmax;
	CString	m_strXmin;
	CString	m_strYmax;
	CString	m_strYmin;
	//}}AFX_DATA

// Attributes
public:
	




// Operations
public:
	void MakeProfile ();
	void CleanUp () ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResFormView)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CResFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CResFormView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESFORMVIEW1_H__E088FBB2_AFAF_4B03_9500_A1D8F2D5E3DC__INCLUDED_)
