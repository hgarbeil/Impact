#if !defined(AFX_PROFILEFORM_H__87EDCE72_71EF_4734_B0D2_89842C7C7C54__INCLUDED_)
#define AFX_PROFILEFORM_H__87EDCE72_71EF_4734_B0D2_89842C7C7C54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfileForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProfileForm form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif


#include "ImageFile.h"

class CProfileForm : public CFormView
{
protected:
	CProfileForm();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CProfileForm)

// Form Data
public:
	//{{AFX_DATA(CProfileForm)
	enum { IDD = IDD_PROFILEFORM_FORM };
	CStatic	m_cProfWindow;
	float	m_fOrientation;
	float	m_fMinHeight;
	float	m_fMaxHeight;
	int		m_fProfLength;
	int		m_nCentSamp;
	int		m_nCentLine;
	BOOL	m_nAutoState;
	CString	m_sYMax;
	CString	m_sYMin;
	CString	m_sXMax;
	CString	m_sXMin;
	CString	m_sYMid;
	//}}AFX_DATA

	CImageFile *cifdem ;
// Attributes
public:

// Operations
public:
	int m_nNumProfPts;
	POINT *m_nProfPts;
	void MakeCentProfile ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfileForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProfileForm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CProfileForm)
	afx_msg void OnUpdateButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILEFORM_H__87EDCE72_71EF_4734_B0D2_89842C7C7C54__INCLUDED_)
