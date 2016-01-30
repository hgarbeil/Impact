#if !defined(AFX_ZOOMWINDOW_H__2B19F91F_26D4_4B87_A8D5_1A1010AD3E4C__INCLUDED_)
#define AFX_ZOOMWINDOW_H__2B19F91F_26D4_4B87_A8D5_1A1010AD3E4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DIB.h"
#include "NewestDoc.h"
// ZoomWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ZoomWindow frame

#define WM_ZMCLICK   WM_USER+7
#define WM_RTZMCLICK WM_USER+8

class ZoomWindow : public CMDIChildWnd
{
	DECLARE_DYNCREATE(ZoomWindow)
protected:
	//ZoomWindow();           
	// protected constructor used by dynamic creation

// Attributes
public:
	ZoomWindow () ;
	
// Operations
public:
	void SetImageSize (int xloc, int yloc);
	void SetParentView (CView *);
	BOOL status;
	CView *m_pView ;
	CNewestDoc *cnd ;
	int	 xstart, ystart, zmfac, xsize, ysize, nRimPts, imsize_x, imsize_y ;
	int  nInnPrime, nPrimeSec, nSec ;
	int	 *unaff_x, *unaff_y, unaff_pts ;

	void SetDIB (DIB *dib) ;
	
	void SetOrigin (CPoint cpt) ;
	void SetUnaffPts (int *, int*, int) ;
	void SetCraterPts (POINT *ctr, POINT *maxlobe, POINT *minlobe, int CraterMask) ; 
	void SetRimPts (POINT *, int npts) ;
	void SetInnPrimePts (POINT *, int npts) ;
	void SetPrimeSecPts (POINT *, int npts) ;
	void SetSecPts (POINT *, int npts) ;


	DIB  *dib ;
	CPoint origin ;
	POINT *RimPtLoc, *InnPrime, *PrimeSec, *Sec, *ctr, *maxlobe, *minlobe ;
	int	  Cratermask ;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZoomWindow)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	virtual ~ZoomWindow();

	// Generated message map functions
	//{{AFX_MSG(ZoomWindow)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMWINDOW_H__2B19F91F_26D4_4B87_A8D5_1A1010AD3E4C__INCLUDED_)
