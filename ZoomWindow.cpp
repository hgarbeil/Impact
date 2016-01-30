// ZoomWindow.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "Newest.h"
#include "ZoomWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZoomWindow

IMPLEMENT_DYNCREATE(ZoomWindow, CMDIChildWnd)

ZoomWindow::ZoomWindow()
{
	status = true ;
	dib=NULL ;
	zmfac = 4 ;
	xsize = 16 ;
	ysize = 16 ;
	origin.x = 0 ;
	origin.y = 0 ;
	nRimPts = 0 ;
	nInnPrime = 0 ;
	nPrimeSec = 0 ;
	unaff_pts = 0 ;
	nSec = 0 ;
	Cratermask = 0 ;
	cnd = NULL ;
}

ZoomWindow::~ZoomWindow()
{
	


}


BEGIN_MESSAGE_MAP(ZoomWindow, CMDIChildWnd)
	//{{AFX_MSG_MAP(ZoomWindow)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZoomWindow message handlers

void ZoomWindow::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	status = false ;
	CMDIChildWnd::PostNcDestroy();
}

void ZoomWindow::OnPaint() 
{
	CRect     rect ;
	int       i, is, x0, y0, wndwidth, wndht, xcent, ycent ;
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CMDIChildWnd::OnPaint() for painting messages

	GetClientRect (rect) ;
        //TRACE ("Rect is %d %d\n", rect->right - rect->left, rect->bottom - rect->top) ;
    rect.bottom -= rect.top ;
    rect.right -= rect.left ;
    if (rect.bottom < 1)  
        TRACE ("rect less than 0\n") ;
    rect.left = 0 ;
    rect.top = 0 ;

	
	

	x0 = origin.x ;
	y0 = origin.y ;
	wndwidth = rect.right ;
	wndht = rect.bottom ;
	xsize = wndwidth / zmfac ;
	ysize = wndht / zmfac ;
	if (dib) {
		TRACE ("%d   %d \n", y0, wndht) ;
		::StretchDIBits (dc, 0, 0, wndwidth, wndht, 
		 x0, y0 + ysize+1, xsize, -ysize, dib->m_data,
		dib->bi, DIB_RGB_COLORS, SRCCOPY) ;
	}
	
	if (cnd)
	if (cnd->m_nNumHitCraters && dib) {
		CPen hitPen ;
		int val_x, val_y ;
		hitPen.CreatePen (PS_SOLID, 1, RGB (255, 0, 255)) ;
		CPen *oldPen = dc.SelectObject (&hitPen) ;
		for (i = 0; i<cnd->m_nNumHitCraters; i++) 
		{
			val_x = (cnd->HitCraters [i].x - origin.x ) * zmfac ;
			val_y = (cnd->HitCraters [i].y - origin.y ) * zmfac ;
			dc.MoveTo (val_x, val_y-2) ;
			for (is = -1; is<3 ; is++) {
				dc.LineTo (val_x, val_y +is) ;
			}
			dc.MoveTo (val_x-2, val_y) ;
			for (is = -1; is<3 ; is++) {
				dc.LineTo (val_x+is, val_y ) ;
			}	
		}
		dc.SelectObject (&oldPen) ;
		DeleteObject (&hitPen) ;
					
	}

	if (cnd && cnd->Rimflag) {
		float xdist, ydist, rimRad, angle ;
		CPen rimPen1 ;
		rimRad = cnd->radius_rim ;
			
		rimPen1.CreatePen (PS_SOLID,1, RGB(255, 255, 0)) ;
		CPen *oldPen = 	dc.SelectObject (&rimPen1) ;
			if (cnd->Rimflag) 
			for (i=0; i<360; i++){
				angle = i * .01745329 ;
				xdist =(cos(angle) * rimRad / cnd->xsize_meters) + cnd->centroid_x ;
				xdist = zmfac * (xdist - origin.x) ;
				ydist =(sin(angle) * rimRad / cnd->ysize_meters) + cnd->centroid_y ;
				ydist = zmfac * (ydist - origin.y) ;
				if (i==0) 
					dc.MoveTo ((int)xdist, (int)ydist) ;
				else 
					dc.LineTo ((int)xdist, (int)ydist) ;
			}
			xcent = (cnd->centroid_x - origin.x) * zmfac ;
			ycent = (cnd->centroid_y - origin.y) * zmfac ;
			dc.Ellipse (xcent-4, ycent-4, xcent+4, ycent+4) ;
		dc.SelectObject (&oldPen) ;
		DeleteObject (&rimPen1) ;
	}

	if (Cratermask) 
	{
		if (Cratermask & 0x00000001) 
		{
			CPen surfPen ;
		
		
			x0 = zmfac * (ctr->x  - origin.x) ;
			y0 = zmfac * (ctr->y  - origin.y) ;
				
			
			surfPen.CreatePen (PS_SOLID,1, RGB(255, 255, 0)) ;
			CPen *oldPen = dc.SelectObject (&surfPen) ;
		
		
			
			dc.MoveTo (x0, y0-2) ;
			for (is=-1 ; is<3; is++) 
			{
				
				dc.LineTo (x0, y0+is) ;
			}
			dc.MoveTo (x0-2, y0) ;
			
			for (is=-1 ; is<3; is++) 
			{
				
				dc.LineTo (x0+is, y0) ;
			}
		
		
			dc.SelectObject (&oldPen) ;
			DeleteObject (&surfPen) ;
			
		}
		if (Cratermask & 0x00000002) 
		{
			CPen surfPen ;
		
		
			x0 = zmfac * (maxlobe->x  - origin.x) ;
			y0 = zmfac * (maxlobe->y  - origin.y) ;
				
			
			surfPen.CreatePen (PS_SOLID,1, RGB(255, 255, 0)) ;
			CPen *oldPen = dc.SelectObject (&surfPen) ;
		
		
			
			dc.MoveTo (x0, y0-2) ;
			for (is=-1 ; is<3; is++) 
			{
				
				dc.LineTo (x0, y0+is) ;
			}
			dc.MoveTo (x0-2, y0) ;
			
			for (is=-1 ; is<3; is++) 
			{
				
				dc.LineTo (x0+is, y0) ;
			}
		
			dc.SelectObject (&oldPen) ;
			DeleteObject (&surfPen) ;
			
		}
		if (Cratermask & 0x00000004) 
		{
			CPen surfPen ;
		
		
			x0 = zmfac * (minlobe->x  - origin.x) ;
			y0 = zmfac * (minlobe->y  - origin.y) ;
				
			
			surfPen.CreatePen (PS_SOLID,1, RGB(255, 255, 0)) ;
			CPen *oldPen = dc.SelectObject (&surfPen) ;
		
		
			
			dc.MoveTo (x0, y0-2) ;
			for (is=-1 ; is<3; is++) 
			{
				
				dc.LineTo (x0, y0+is) ;
			}
			dc.MoveTo (x0-2, y0) ;
			
			for (is=-1 ; is<3; is++) 
			{
				
				dc.LineTo (x0+is, y0) ;
			}
		
			dc.SelectObject (&oldPen) ;
			DeleteObject (&surfPen) ;
			
		}
	}

	if (unaff_pts) {
		CPen surfPen ;
		
		int npts = unaff_pts ;
		CPoint *ZmRimPt = new CPoint [npts] ;
		for (i=0; i<npts; i++) {
			x0 = zmfac * (unaff_x [i] - origin.x) ;
			y0 = zmfac * (unaff_y [i] - origin.y) ;
			ZmRimPt [i]= CPoint (x0, y0) ;
		}
		surfPen.CreatePen (PS_SOLID,1, RGB(255, 0, 0)) ;
		CPen *oldPen = dc.SelectObject (&surfPen) ;
		
		for (i=0; i<unaff_pts; i++) 
		{
			
			dc.MoveTo (ZmRimPt [i].x, ZmRimPt[i].y-2) ;
			for (is=-1 ; is<3; is++) 
			{
				
				dc.LineTo (ZmRimPt [i].x, ZmRimPt[i].y+is) ;
			}
			dc.MoveTo (ZmRimPt [i].x-2, ZmRimPt[i].y) ;
			
			for (is=-1 ; is<3; is++) 
			{
				
				dc.LineTo (ZmRimPt [i].x+is, ZmRimPt[i].y) ;
			}
		}
		dc.SelectObject (&oldPen) ;
		DeleteObject (&surfPen) ;
		delete [] ZmRimPt ;
		

	}


	if (nRimPts) {
		CPen rimPen ;
		int npts = nRimPts ;
		CPoint *ZmRimPt = new CPoint [npts] ;
		for (int i=0; i<npts; i++) {
			x0 = zmfac * (RimPtLoc[i].x - origin.x) ;
			y0 = zmfac * (RimPtLoc[i].y - origin.y) ;
			ZmRimPt [i]= CPoint (x0, y0) ;
		}
		rimPen.CreatePen (PS_SOLID,1, RGB(200, 0, 200)) ;
		CPen *oldPen = dc.SelectObject (&rimPen) ;
		dc.MoveTo (ZmRimPt [0]) ;
		if (npts> 1) 
		{
		for (i=1 ; i<npts; i++) 
		{
			dc.LineTo (ZmRimPt [i]) ;
		}
		}
		dc.SelectObject (&oldPen) ;
		DeleteObject (&rimPen) ;
		delete [] ZmRimPt ;
		

	}

	if (nInnPrime) {
		CPen innPrimePen ;
		int npts = nInnPrime ; ;
		CPoint *ZmRimPt = new CPoint [npts] ;
		for (i=0; i<npts; i++) {
			x0 = zmfac * (InnPrime[i].x - origin.x) ;
			y0 = zmfac * (InnPrime[i].y - origin.y) ;
			ZmRimPt [i]= CPoint (x0, y0) ;
		}
		innPrimePen.CreatePen (PS_SOLID,1, RGB(0, 0, 200)) ;
		CPen *oldPen = dc.SelectObject (&innPrimePen) ;
		dc.MoveTo (ZmRimPt [0]) ;
		if (npts> 1) 
		{
		for (i=1 ; i<npts; i++) 
		{
			dc.LineTo (ZmRimPt [i]) ;
		}
		}
		dc.SelectObject (&oldPen) ;
		DeleteObject (&innPrimePen) ;
		delete [] ZmRimPt ;
		

	}

	if (nPrimeSec) {
		CPen PrimeSecPen ;
		int npts = nPrimeSec ;
		CPoint *ZmRimPt = new CPoint [npts] ;
		for (int i=0; i<npts; i++) {
			x0 = zmfac * (PrimeSec[i].x - origin.x) ;
			y0 = zmfac * (PrimeSec[i].y - origin.y) ;
			ZmRimPt [i]= CPoint (x0, y0) ;
		}
		PrimeSecPen.CreatePen (PS_SOLID,1, RGB(0, 200, 200)) ;
		CPen *oldPen = dc.SelectObject (&PrimeSecPen) ;
		dc.MoveTo (ZmRimPt [0]) ;
		if (npts> 1) 
		{
		for (i=1 ; i<npts; i++) 
		{
			dc.LineTo (ZmRimPt [i]) ;
		}
		}
		dc.SelectObject (&oldPen) ;
		DeleteObject (&PrimeSecPen) ;
		delete [] ZmRimPt ;
		

	}

	if (nSec) {
		CPen SecPen ;
		int npts = nSec ;
		CPoint *ZmRimPt = new CPoint [npts] ;
		for (int i=0; i<npts; i++) {
			x0 = zmfac * (Sec[i].x - origin.x) ;
			y0 = zmfac * (Sec[i].y - origin.y) ;
			ZmRimPt [i]= CPoint (x0, y0) ;
		}
		SecPen.CreatePen (PS_SOLID,1, RGB(200, 0, 0)) ;
		CPen *oldPen = dc.SelectObject (&SecPen) ;
		dc.MoveTo (ZmRimPt [0]) ;
		if (npts> 1) 
		{
		for (i=1 ; i<npts; i++) 
		{
			dc.LineTo (ZmRimPt [i]) ;
		}
		}
		dc.SelectObject (&oldPen) ;
		DeleteObject (&SecPen) ;
		delete [] ZmRimPt ;
		

	}
	


}


void ZoomWindow::SetDIB (DIB *dibmap) 
{
	dib = dibmap ;
	InvalidateRect (NULL, true) ;
}

void ZoomWindow::SetOrigin (CPoint cpt)
{
	
	
	float redge, bedge ;

	CRect rect ;
	GetClientRect (rect) ;
	rect.bottom -= rect.top ;
    rect.right -= rect.left ;
	xsize = rect.right / zmfac ;
	ysize = rect.bottom / zmfac ;
	origin = cpt ;
	if (origin.x + xsize/2 > imsize_x -1) origin.x = imsize_x - xsize/2 -1 ;
	if (origin.y + ysize/2 > imsize_y -1) origin.y = imsize_y - ysize/2 -1 ;
	
	origin.x -= xsize / 2 ;
	origin.y -= ysize / 2 ;
	

	origin.x = (origin.x <0) ? origin.x = 0:origin.x ;
	origin.y = (origin.y <0) ? origin.y = 0:origin.y ;


	InvalidateRect (NULL, true) ;

}

void ZoomWindow::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCursor (LoadCursor (NULL, IDC_CROSS) ) ;
	CMDIChildWnd::OnMouseMove(nFlags, point);
		int xloc, yloc ;
	yloc = GetScrollPos (SB_VERT) ;
	xloc = GetScrollPos (SB_HORZ) ;

	xloc =  point.x/zmfac + origin.x ;
	yloc =  point.y/zmfac + origin.y ;

	return ;

	CString cstr ;
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar ;
	if (pStatus) {
		cstr.Format ("X : %5d     Y : %5d", xloc, yloc ) ;
		pStatus->SetPaneText (0, cstr, true) ;
	}

}

void ZoomWindow::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	int retval=0 ;

	CMDIChildWnd::OnLButtonDown(nFlags, point);
	//CMDIChildWnd::OnMouseMove(nFlags, point);
		int xloc, yloc ;
	yloc = GetScrollPos (SB_VERT) ;
	xloc = GetScrollPos (SB_HORZ) ;

	xloc =  point.x/zmfac + origin.x ;
	yloc =  point.y/zmfac + origin.y ;
	
	retval = xloc ;
	retval = retval << 16 ;
	retval += yloc ;

	CString cstr ;
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar ;
	if (pStatus) {
		cstr.Format ("X : %5d     Y : %5d", xloc, yloc ) ;
		pStatus->SetPaneText (0, cstr, true) ;
	}

	m_pView->PostMessage (WM_ZMCLICK, retval) ;
}

void ZoomWindow::SetParentView(CView *pview)
{
	m_pView = pview ;
}

void ZoomWindow::SetUnaffPts (int *x, int *y, int npts) 
{
	unaff_x = x ;
	unaff_y = y ;
	unaff_pts = npts ;
}

void ZoomWindow::SetRimPts (POINT *cpt, int npts) 
{
	RimPtLoc = cpt ;
	nRimPts = npts ;
}
void ZoomWindow::SetInnPrimePts (POINT *cpt, int npts) 
{
	InnPrime = cpt ;
	nInnPrime = npts ;
}
void ZoomWindow::SetPrimeSecPts (POINT *cpt, int npts) 
{
	PrimeSec = cpt ;
	nPrimeSec = npts ;
}
void ZoomWindow::SetSecPts (POINT *cpt, int npts) 
{
	Sec = cpt ;
	nSec = npts ;
}

void ZoomWindow::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int retval=0 ;

	
	int xloc, yloc ;
	yloc = GetScrollPos (SB_VERT) ;
	xloc = GetScrollPos (SB_HORZ) ;

	xloc =  point.x/zmfac + origin.x ;
	yloc =  point.y/zmfac + origin.y ;
	
	retval = xloc ;
	retval = retval << 16 ;
	retval += yloc ;

	CString cstr ;
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar ;
	if (pStatus) {
		cstr.Format ("X : %5d     Y : %5d", xloc, yloc ) ;
		pStatus->SetPaneText (0, cstr, true) ;
	}

	m_pView->PostMessage (WM_RTZMCLICK, retval) ;

	CMDIChildWnd::OnRButtonDown(nFlags, point);
	//m_pView->SetActiveView () ;
}


void ZoomWindow::SetCraterPts (POINT *c0, POINT *c1, POINT *c2, int mask)
{
	Cratermask = mask ;
	ctr = c0 ;
	maxlobe = c1 ;
	minlobe = c2 ;
}

void ZoomWindow::SetImageSize(int xloc, int yloc)
{
	imsize_x = xloc ;
	imsize_y = yloc ;
}
