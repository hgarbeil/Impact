// NewestView.h : interface of the CNewestView class
//
/////////////////////////////////////////////////////////////////////////////C

#if !defined(AFX_NEWESTVIEW_H__29AC9F6D_5214_4954_B2C1_AA3DE6D36FC5__INCLUDED_)
#define AFX_NEWESTVIEW_H__29AC9F6D_5214_4954_B2C1_AA3DE6D36FC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZoomWindow.h"
#include "Dib.h"
#include "ImageFile.h"
#include "Fitres_dlg.h"
#include "Results_dlg.h" 
#include "CraterStats.h"

class CNewestView : public CScrollView
{
protected: // create from serialization only
	CNewestView();
	DECLARE_DYNCREATE(CNewestView)

// Attributes
public:
	CNewestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	int DefineMode;
	DWORD m_TabFilePosition;
	BOOL m_bDefFiles;
	void		CNewestView::WriteResultsFile (BOOL initflag, int analphase) ;
	void		WriteTabulatedFile () ;
	LRESULT		AppendFile (WPARAM, LPARAM) ;
	LRESULT		LeftZoom   (WPARAM, LPARAM) ;
	LRESULT		RightZoom   (WPARAM, LPARAM) ;
	int			MakeProfile (POINT *, int npts);
	int			DEMloaded, HITloaded ;
	CImageFile *cif, *cifdem, *cifhit, *cifalt ;
	CMenu		*cmenu ;
	char		Shadefilename  [420], AltShadefilename [420] ;
	BYTE		*bdata, *bdata_alt ;
	CRect		zm_rect;
	ZoomWindow	*czm;
	DIB			*dib ;
	BOOL		ShowAlt ;
	
	virtual		~CNewestView();
	int			DefUnaffCur, Unaff_pts, DefRimCur, Rim_pts, DefLobesCur ;
	int			DefInnPrimeCur, DefInnPrime, Inn_Prime_Pts ;
	int			DefPrimeSecCur, DefPrimeSec, Prime_Sec_Pts ;
	int			DefSecCur, DefSec, Sec_Pts ;
	int			DefUnaff, DefRim ;
	int			DefCraterCur, DefCrater, DefCraterMask ;
	POINT		CraterMinLobe, CraterCtr, CraterMaxLobe ;
	int			unaff_x [2400], unaff_y [2400] ;
	int			ShowCrater ;
	float		m_nValMin ;
	float		m_nValMax ;
	double		 unaff_z [2400] ;
	POINT		RimPtLoc [2400], InnPrime [2400], PrimeSec [2400], Sec[2400] ;
	CFitres_dlg *cfitres ;
//	CResults_dlg *cres_dlg ;
	CString		profstring, cratername, outdir ;
	//CCraterStats *ccs ;
	

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNewestView)
	afx_msg void OnDisplayGrayscale();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRgb();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDispoptions();
	afx_msg void OnDefDem();
	afx_msg void OnDefUnaffect();
	afx_msg void OnDispShade();
	afx_msg void OnDefShade();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDefRim();
	afx_msg void OnDefInnerprimary();
	afx_msg void OnDefineprimarysecondaryboundary();
	afx_msg void OnDefSecondary();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDefcraterctr();
	afx_msg void OnNewcrater();
	afx_msg void OnUpdateDefUnaffect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDefineprimarysecondaryboundary(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDefSecondary(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDefInnerprimary(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDefRim(CCmdUI* pCmdUI);
	afx_msg void OnDeflobes();
	afx_msg void OnUpdateDeflobes(CCmdUI* pCmdUI);
	afx_msg void OnShowHits();
	afx_msg void OnUpdateShowHits(CCmdUI* pCmdUI);
	afx_msg void OnDefineHitfile();
	afx_msg void OnDefAltshadefile();
	afx_msg void OnShowAltShade();
	afx_msg void OnUpdateDefAltshadefile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowAltShade(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToggleAlt(CCmdUI* pCmdUI);
	afx_msg void OnToggleAlt();
	afx_msg void OnUpdateDefcraterctr(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in NewestView.cpp
inline CNewestDoc* CNewestView::GetDocument()
   { return (CNewestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWESTVIEW_H__29AC9F6D_5214_4954_B2C1_AA3DE6D36FC5__INCLUDED_)
