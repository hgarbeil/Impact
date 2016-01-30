// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__39AFF77D_0A5D_4DA2_AF2D_CAE63ADBDB2C__INCLUDED_)
#define AFX_MAINFRM_H__39AFF77D_0A5D_4DA2_AF2D_CAE63ADBDB2C__INCLUDED_

#include "ImageFile.h"	// Added by ClassView
#include "PlotWin.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
	CStatusBar  m_wndStatusBar;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetDemPtr (CImageFile cifdemptr);
	void ShowResFormView ();
	void ShowProfileFormView ();
	void MessageOut (char *outstring);
	CPlotWin *cplotwin;
	CImageFile *cif, *cifout, *cifdemptr ;
	virtual ~CMainFrame();
	HCURSOR hcr ;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGenHdr();
	afx_msg void OnShade();
	afx_msg void OnStatisticsSummary();
	afx_msg void OnSlopemap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__39AFF77D_0A5D_4DA2_AF2D_CAE63ADBDB2C__INCLUDED_)
