// NewestView.cpp : implementation of the CNewestView class
//

#include "stdafx.h"
#include "math.h"
#include "Newest.h"

#include "NewestDoc.h"
#include "NewestView.h"

#include "RGB_Dialog.h"
#include "Displayscale_dialog.h"
#include "DisplayOptions_dlg.h"
#include "CraterID_Dlg.h"
#include "ImageFile.h"
#include "FileSelectDlg.h"
#include "Array.h"
#include <fstream>
#include <iostream>
#define  PI 3.14159265


extern "C" 
{
#include "nr.h"
#include "nrutil.h"
void funct (float x, float p[], int np) ;
void funct_d (double x, double p[], int np) ;
}
 

float *xyarr  ;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CNewestView

IMPLEMENT_DYNCREATE(CNewestView, CScrollView)

BEGIN_MESSAGE_MAP(CNewestView, CScrollView)
	//{{AFX_MSG_MAP(CNewestView)
	ON_COMMAND(ID_DISPLAY_GRAYSCALE, OnDisplayGrayscale)
	ON_WM_MOUSEMOVE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_COMMAND(IDC_RGB, OnRgb)
	ON_WM_LBUTTONUP()
	ON_COMMAND(IDC_DISPOPTIONS, OnDispoptions)
	ON_COMMAND(ID_DEF_DEM, OnDefDem)
	ON_COMMAND(ID_DEF_UNAFFECT, OnDefUnaffect)
	ON_COMMAND(ID_DISP_SHADE, OnDispShade)
	ON_COMMAND(ID_DEF_SHADE, OnDefShade)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDC_DEF_RIM, OnDefRim)
	ON_COMMAND(ID_DEF_INNERPRIMARY, OnDefInnerprimary)
	ON_COMMAND(ID_DEFINEPRIMARYSECONDARYBOUNDARY, OnDefineprimarysecondaryboundary)
	ON_COMMAND(ID_DEF_SECONDARY, OnDefSecondary)
	ON_WM_SETFOCUS()
	ON_COMMAND(IDC_DEFCRATERCTR, OnDefcraterctr)
	ON_COMMAND(IDC_NEWCRATER, OnNewcrater)
	ON_UPDATE_COMMAND_UI(ID_DEF_UNAFFECT, OnUpdateDefUnaffect)
	ON_UPDATE_COMMAND_UI(ID_DEFINEPRIMARYSECONDARYBOUNDARY, OnUpdateDefineprimarysecondaryboundary)
	ON_UPDATE_COMMAND_UI(ID_DEF_SECONDARY, OnUpdateDefSecondary)
	ON_UPDATE_COMMAND_UI(ID_DEF_INNERPRIMARY, OnUpdateDefInnerprimary)
	ON_UPDATE_COMMAND_UI(IDC_DEF_RIM, OnUpdateDefRim)
	ON_COMMAND(IDC_DEFLOBES, OnDeflobes)
	ON_UPDATE_COMMAND_UI(IDC_DEFLOBES, OnUpdateDeflobes)
	ON_COMMAND(ID_SHOW_HITS, OnShowHits)
	ON_UPDATE_COMMAND_UI(ID_SHOW_HITS, OnUpdateShowHits)
	ON_COMMAND(ID_DEFINE_HITFILE, OnDefineHitfile)
	ON_COMMAND(ID_DEF_ALTSHADEFILE, OnDefAltshadefile)
	ON_COMMAND(ID_SHOW_ALT_SHADE, OnShowAltShade)
	ON_UPDATE_COMMAND_UI(ID_DEF_ALTSHADEFILE, OnUpdateDefAltshadefile)
	ON_UPDATE_COMMAND_UI(ID_SHOW_ALT_SHADE, OnUpdateShowAltShade)
	ON_UPDATE_COMMAND_UI(ID_TOGGLE_ALT, OnUpdateToggleAlt)
	ON_COMMAND(ID_TOGGLE_ALT, OnToggleAlt)
	ON_UPDATE_COMMAND_UI(IDC_DEFCRATERCTR, OnUpdateDefcraterctr)
	//}}AFX_MSG_MAP
	ON_MESSAGE (WM_WRITE_FILE, AppendFile )
	ON_MESSAGE (WM_ZMCLICK, LeftZoom) 
	ON_MESSAGE (WM_RTZMCLICK, RightZoom) 
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewestView construction/destruction

CNewestView::CNewestView()
{
	// TODO: add construction code here
	czm = new ZoomWindow ;
	zm_rect.SetRect (0, 0, 256,256) ;
	czm->Create (NULL, "Zoom", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		zm_rect) ;
	czm->MDIActivate () ;
	czm->SetParentView (this) ;
	

	//ccs = new CCraterStats ;

	dib=NULL ;
	cif = NULL ;
	cifhit = NULL ;
	cifalt = NULL ;
	HITloaded = 0 ;

	bdata = NULL ;
	bdata_alt = NULL ;


	CSize sizeTotal (1025, 800) ;
	CSize sizePage  (512,512) ;
	CSize sizeLine   (50,50) ;
	SetScrollSizes (MM_TEXT, sizeTotal, sizePage, sizeLine) ;

	m_nValMin = -1.E6 ;
	m_nValMax = 1.E6 ;
	cifdem = NULL ;
	DEMloaded = 0 ;
	DefUnaffCur = 0 ;
	DefUnaff = 0 ;
	DefInnPrime = 0 ;
	DefInnPrimeCur = 0 ;
	Unaff_pts = 0 ;
	DefRimCur = 0 ;
	DefRim = 0 ;
	DefPrimeSec = 0 ;
	DefPrimeSecCur = 0 ;
	DefSec = 0 ;
	DefSecCur = 0 ;
	Rim_pts = 0 ;
	ShowCrater = 0 ;
	DefCrater = 0 ;
	DefCraterCur = 0 ;
	DefCraterMask = 0 ;
	DefLobesCur = 0 ;
	DefineMode = 0 ;
	cfitres = NULL ;
	//cres_dlg = new CResults_dlg (this) ;
	//cres_dlg->Create () ;

	cratername = "" ;
	strcpy (Shadefilename,"\0") ;

	outdir = getenv ("TEMP") ;
	outdir += _T("\\") ; 

	m_bDefFiles = FALSE ;
	ShowAlt = FALSE ;
	


	//::SetCursor (::LoadCursor (NULL, IDC_WAIT) ) ;

}

CNewestView::~CNewestView()
{
	if (czm && czm->status) czm->MDIDestroy () ;
	if (dib) delete dib ;
	if (cif) delete cif ;
	if (cifdem) delete cifdem ;
	if (cifhit) delete cifhit ;
	if (cifalt) delete cifalt ;
	if (bdata) delete [] bdata ;
	if (bdata_alt) delete [] bdata_alt ;
	
	if (cfitres) delete cfitres ;
	//if (cres_dlg) delete cres_dlg ;

	//if (ccs) delete ccs ;
}

BOOL CNewestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}
/////////////////////////////////////////////////////////////////////////////
// CNewestView drawing

void CNewestView::OnDraw(CDC* pDC)
{


	int		i, is, wndwidth, wndht, x0, y0;
	CNewestDoc* pDoc = GetDocument();
	CPen      rimPen, rimPen1, innPrimePen, primeSecPen, secPen ;
	float xdist, ydist, rimRad, angle ;

	 
	
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	CNewestDoc *cnd = (CNewestDoc *) GetDocument() ;

	HDC hdc =pDC->GetSafeHdc () ;
	CRect	crect_winsize ;
	CPoint	cpnt_scrollpos ;
	cpnt_scrollpos = GetScrollPosition() ;
	GetClientRect (crect_winsize) ;
	wndwidth=crect_winsize.right ;
	wndht = crect_winsize.bottom ;
	x0 = cpnt_scrollpos.x ;
	y0 = cpnt_scrollpos.y ;
	
	if (dib)
	{
		TRACE ("%d   %d \n", y0, wndht) ;
		::StretchDIBits (hdc, x0, y0, wndwidth, wndht, 
		 x0, y0 + wndht+1, wndwidth, -wndht, dib->m_data,
		dib->bi, DIB_RGB_COLORS, SRCCOPY) ;
	}

	if (pDoc->Ctrprof_show) 
	{
		CPen surfPen ;
		surfPen.CreatePen (PS_SOLID, 1, RGB (255, 255, 0)) ;
		CPen *oldPen = pDC->SelectObject (&surfPen) ;
		pDC->MoveTo (pDoc->Ctrprof [0]) ;
		for (i = 0; i<pDoc->Ctrprof_pts; i++) 
		{
			
			
			
				pDC->LineTo (pDoc->Ctrprof [i]) ;
			
			
		}
		pDC->SelectObject (&oldPen) ;
		DeleteObject (&surfPen) ;
					
	}


	if (DefUnaff) {
		CPen surfPen ;
		surfPen.CreatePen (PS_SOLID, 1, RGB (255, 0, 0)) ;
		CPen *oldPen = pDC->SelectObject (&surfPen) ;
		for (i = 0; i<Unaff_pts; i++) 
		{
			
			pDC->MoveTo (unaff_x [i], unaff_y[i]-2) ;
			for (is = -1; is<3 ; is++) {
				pDC->LineTo (unaff_x [i], unaff_y[i] +is) ;
			}
			pDC->MoveTo (unaff_x [i]-2, unaff_y[i]) ;
			for (is = -1; is<3 ; is++) {
				pDC->LineTo (unaff_x [i]+is, unaff_y[i] ) ;
			}	
		}
		pDC->SelectObject (&oldPen) ;
		DeleteObject (&surfPen) ;
					
	}
	
	if (cnd->m_nNumHitCraters && dib) {
		CPen hitPen ;
		hitPen.CreatePen (PS_SOLID, 1, RGB (255, 0, 255)) ;
		CPen *oldPen = pDC->SelectObject (&hitPen) ;
		for (i = 0; i<cnd->m_nNumHitCraters; i++) 
		{
			
			pDC->MoveTo (cnd->HitCraters [i].x, cnd->HitCraters[i].y-2) ;
			for (is = -1; is<3 ; is++) {
				pDC->LineTo (cnd->HitCraters [i].x, cnd->HitCraters[i].y +is) ;
			}
			pDC->MoveTo (cnd->HitCraters [i].x-2, cnd->HitCraters[i].y) ;
			for (is = -1; is<3 ; is++) {
				pDC->LineTo (cnd->HitCraters [i].x+is, cnd->HitCraters[i].y ) ;
			}	
		}
		pDC->SelectObject (&oldPen) ;
		DeleteObject (&hitPen) ;
					
	}

	if (DefCrater) {
		CPen surfPen ;
		surfPen.CreatePen (PS_SOLID, 1, RGB (255, 255, 0)) ;
		CPen *oldPen = pDC->SelectObject (&surfPen) ;

			
		
			if (DefCraterMask &1) 
			{
			pDC->MoveTo (CraterCtr.x, CraterCtr.y-2) ;
			for (is = -1; is<3 ; is++) {
				pDC->LineTo (CraterCtr.x, CraterCtr.y +is) ;
			}
				pDC->MoveTo (CraterCtr.x-2, CraterCtr.y) ;
			for (is = -1; is<3 ; is++) {
				pDC->LineTo (CraterCtr.x+is, CraterCtr .y ) ;
			}

			}
			if (DefCraterMask & 2) 
			{
			pDC->MoveTo (CraterMaxLobe .x, CraterMaxLobe.y-2) ;
			for (is = -1; is<3 ; is++) {
				pDC->LineTo (CraterMaxLobe .x, CraterMaxLobe.y +is) ;
			}
				pDC->MoveTo (CraterMaxLobe .x-2, CraterMaxLobe.y) ;
			for (is = -1; is<3 ; is++) {
				pDC->LineTo (CraterMaxLobe .x+is, CraterMaxLobe .y ) ;
			}

			}

			if (DefCraterMask & 4) 
			{
			pDC->MoveTo (CraterMinLobe .x, CraterMinLobe.y-2) ;
			for (is = -1; is<3 ; is++) {
				pDC->LineTo (CraterMinLobe .x, CraterMinLobe.y +is) ;
			}
				pDC->MoveTo (CraterMinLobe .x-2, CraterMinLobe.y) ;
			for (is = -1; is<3 ; is++) {
				pDC->LineTo (CraterMinLobe .x+is, CraterMinLobe .y ) ;
			}

			}
		
			
			rimRad = cnd->radius_rim ;
			
			rimPen1.CreatePen (PS_SOLID,1, RGB(255, 255, 0)) ;
			pDC->SelectObject (&rimPen1) ;
			if (cnd->Rimflag) {
			for (i=0; i<360; i++){
				angle = i * .01745329 ;
				xdist =(cos(angle) * rimRad / cnd->xsize_meters) + cnd->centroid_x ;
				ydist =(sin(angle) * rimRad / cnd->ysize_meters) + cnd->centroid_y ;
				if (i==0) 
					pDC->MoveTo ((int)xdist, (int)ydist) ;
				else 
					pDC->LineTo ((int)xdist, (int)ydist) ;
			}
			pDC->Ellipse (cnd->centroid_x-4, cnd->centroid_y-4, cnd->centroid_x+4, cnd->centroid_y+4) ;
			}
		pDC->SelectObject (&oldPen) ;
		DeleteObject (&rimPen1) ;
		DeleteObject (&surfPen) ;
					
	}

	if (DefRim) {
		rimPen.CreatePen (PS_SOLID,1, RGB(200, 0, 200)) ;
		CPen *oldPen = pDC->SelectObject (&rimPen) ;
		pDC->MoveTo (RimPtLoc [0]) ;
		if (Rim_pts> 1) 
		{
		for ( i=1 ; i<Rim_pts; i++) 
		{
			pDC->LineTo (RimPtLoc [i]) ;
		}
			
			

		}
		pDC->SelectObject (&oldPen) ;
		DeleteObject (&rimPen) ;
		
		

	}

	if (DefInnPrime) {
		innPrimePen.CreatePen (PS_SOLID, 1, RGB(0, 0, 200) ) ;
		CPen *oldPen = pDC->SelectObject (&innPrimePen) ;
		pDC->MoveTo (InnPrime [0]) ;
		if (Inn_Prime_Pts> 1) 
		{
		for (int i=1 ; i<Inn_Prime_Pts; i++) 
		{
			pDC->LineTo (InnPrime [i]) ;
		}
		}
		pDC->SelectObject (&oldPen) ;
		DeleteObject (&innPrimePen) ;
		

	}

	if (DefPrimeSec) {
		primeSecPen.CreatePen (PS_SOLID, 1, RGB(0, 200, 200) ) ;
		CPen *oldPen = pDC->SelectObject (&primeSecPen) ;
		pDC->MoveTo (PrimeSec [0]) ;
		if (Prime_Sec_Pts> 1) 
		{
		for (int i=1 ; i<Prime_Sec_Pts; i++) 
		{
			pDC->LineTo (PrimeSec [i]) ;
		}
		}
		pDC->SelectObject (&oldPen) ;
		DeleteObject (&primeSecPen) ;
		

	}

	if (DefSec) {
		secPen.CreatePen (PS_SOLID, 1, RGB(200, 0, 0) ) ;
		CPen *oldPen = pDC->SelectObject (&secPen) ;
		pDC->MoveTo (Sec [0]) ;
		if (Prime_Sec_Pts> 1) 
		{
		for (int i=1 ; i<Sec_Pts; i++) 
		{
			pDC->LineTo (Sec [i]) ;
		}
		}
		pDC->SelectObject (&oldPen) ;
		DeleteObject (&secPen) ;
		

	}

	
}

void CNewestView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	SetActiveWindow() ;
	
	 
}

/////////////////////////////////////////////////////////////////////////////
// CNewestView printing

BOOL CNewestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CNewestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CNewestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CNewestView diagnostics

#ifdef _DEBUG
void CNewestView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CNewestView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CNewestDoc* CNewestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNewestDoc)));
	return (CNewestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNewestView message handlers

void CNewestView::OnDisplayGrayscale() 
{
	// TODO: Add your command handler code here
	char temppath[240], tempfile [240] ;
	OPENFILENAME   m_ofn ;
	float scale=0., offset=0., min=127, max=127 ;
	CMArray ca ;
	
	int status ;
	
	CDC *cdc=GetDC () ;

	// set valid min and max for calculations
	ca.SetValid (m_nValMin, m_nValMax) ;



	m_ofn.lpstrInitialDir = "H:\\harold\\pinatubo\\tm" ;
	CFileDialog cfd (true, NULL, NULL, NULL, NULL, NULL) ;
	cfd.m_ofn.lpstrInitialDir = "H:\\harold\\pinatubo\\tm" ;
	status = cfd.DoModal() ;
	if (status == IDCANCEL) return ;
	// filename is now in cfd.m_szFileName ;

	// if extension is not .hdr then need to get file info
	TRACE ("File extension is %s\n", cfd.GetFileExt()) ;
	if (!strcmp (cfd.GetFileExt(), "hdr")) TRACE("file is hdr\n") ; 

	strcpy (tempfile, cfd.GetFileName()) ;
	strcpy (temppath, cfd.GetPathName()) ;
	if (cif) delete cif ;
	cif = new CImageFile  ;
	cif->ReadEnviHeader (temppath,tempfile) ;

	CDisplayscale_dialog cdd ;
	if (cif->dtype == 0)
		cdd.InitForByte () ;
	cdd.DoModal() ;
	cdd.ParseData() ;

	cif->GetData (cif->samps, cif->lines, cif->dtype, cdd.bandarr[0]) ;

	// get the values from the cdd class and decide how to display the data
	if (cdd.useUser) {
		if (cdd.useVal) {
			min = cdd.m_nMin [0] ;
			max = cdd.m_nMax [0] ;
		}
		else {
			int i, nbins ;
			long nvalid, val ;
			float lowval, highval,minperc, maxperc, binsize ;
			ca.minmax (cif->rawdata, long(cif->samps) * cif->lines, cif->dtype, &min, &max) ;
			if (cif->dtype <3) {
				nbins = int(max - min + 1) ;
				TRACE ("Nbins is %d\n", nbins); 
				long *histo = new long [nbins+1] ;
				nvalid = ca.histo (cif->rawdata, histo, cif->samps, cif->lines, cif->dtype, 1, min, 
					1., nbins, 1) ;
				minperc = cdd.m_nMin [0] * nvalid * .01f ;
				maxperc = cdd.m_nMax [0]* nvalid * .01f ;
				lowval = min ;
				highval = min ;
				for (i=0; i<nbins; i++) {
					val = histo [i] ;
					if (val < minperc) lowval = i ;
					if (val < maxperc) highval = i ;
				}
				lowval += min ;
				highval += min ;

				TRACE ("Total pixels %d   top level %d\n", nvalid, histo[255]) ;
				delete [] histo ;
			}
			if (cif->dtype ==3) {
				nbins = 10001  ;
				binsize = float((max -min) / 10000.) ;
				long *histo = new long [nbins] ;
				nvalid = ca.histo (cif->rawdata, histo, cif->samps, cif->lines, cif->dtype, 1, min, 
					binsize, nbins, 1) ;
				minperc = cdd.m_nMin [0] * nvalid * .01f ;
				maxperc = cdd.m_nMax [0]* nvalid * .01f ;
				lowval = min ;
				highval = min ;
				for (i=0; i<nbins; i++) {
					val = histo [i] ;
 					if (val < minperc) lowval = i ;
					if (val < maxperc) highval = i ;
				}
				lowval = min + binsize * lowval ;
				highval = min + binsize * highval ;

				TRACE ("Total pixels %d   top level %d\n", nvalid, histo[nbins-1]) ;
				delete [] histo ;
			}
			min = lowval ;
			max = highval ;
		}
		
	}
	else ca.minmax (cif->rawdata, long(cif->samps) * cif->lines, cif->dtype, &min, &max) ;
		
	if (bdata) delete [] bdata ;
	bdata = new unsigned char [cif->samps * cif->lines] ;
	ca.bytescale (cif->rawdata, bdata, long(cif->samps) * cif->lines, cif->dtype, min, max, &scale, &offset) ;

	CSize sizeTotal (cif->samps, cif->lines) ;
	CSize sizePage  (512,512) ;
	CSize sizeLine   (50,50) ;
	SetScrollSizes (MM_TEXT, sizeTotal, sizePage, sizeLine) ;
	
	if (dib) delete dib ;
	dib = new DIB (cif->samps, cif->lines, bdata) ;
	czm->SetDIB (dib) ;
	InvalidateRect (NULL, true) ;

}

void CNewestView::OnRgb() 
{
	// TODO: Add your command handler code here
	char temppath[240], tempfile [240], cbuf [240] ;
	OPENFILENAME   m_ofn ;
	float scale=0., offset=0., min=127, max=127 ;
	CMArray ca ;
	
	int status, bandarr [3] ;
	
	CDC *cdc=GetDC () ;
	
	// set valid min and max for calculations
	ca.SetValid (m_nValMin, m_nValMax) ;

	m_ofn.lpstrInitialDir = "H:\\harold\\pinatubo\\tm" ;
	CFileDialog cfd (true, NULL, NULL, NULL, NULL, NULL) ;
	cfd.m_ofn.lpstrInitialDir = "H:\\harold\\pinatubo\\tm" ;
	status = cfd.DoModal() ;
	if (status == IDCANCEL) return ;
	// filename is now in cfd.m_szFileName ;

	// if extension is not .hdr then need to get file info
	TRACE ("File extension is %s\n", cfd.GetFileExt()) ;
	if (!strcmp (cfd.GetFileExt(), "hdr")) TRACE("file is hdr\n") ; 

	strcpy (tempfile, cfd.GetFileName()) ;
	strcpy (temppath, cfd.GetPathName()) ;
	cif = new CImageFile  ;
	cif->ReadEnviHeader (temppath,tempfile) ;

		
	// then get the bands
	CRGB_Dialog crgb ;
	crgb.DoModal() ;

	bandarr [2] = crgb.m_nBband ;
	bandarr [1] = crgb.m_nGband ;
	bandarr [0] = crgb.m_nRband ;
	sprintf (cbuf, "%d %d %d\n", bandarr[0], bandarr[1], bandarr[2]) ; 
	

	
	
	
	



	CDisplayscale_dialog cdd ;
	
	if (cif->dtype == 0)
		cdd.InitForByte () ;
	cdd.SetBands (3, bandarr) ;
	cdd.DoModal() ;
	cdd.ParseData() ;
	bdata = new unsigned char [cif->samps * cif->lines *3] ;
	//cif->GetData (cif->samps, cif->lines, cif->dtype, 0) ;
	//cif->GetData_3(cif->samps, cif->lines,0,3, bandarr) ;
	// get the values from the cdd class and decide how to display the data
	
	
	for (int ib=0;ib<3; ib++)
	{
	cif->GetData (cif->samps, cif->lines, cif->dtype, cdd.bandarr[ib]) ;
	if (cdd.useUser) {
		if (cdd.useVal) {
			min = cdd.m_nMin [ib] ;
			max = cdd.m_nMax [ib];
		}
		else {
			int i, nbins ;
			long nvalid, val ;
			float lowval, highval,minperc, maxperc, binsize ;
			ca.minmax (cif->rawdata, long(cif->samps) * cif->lines, cif->dtype, &min, &max) ;
			if (cif->dtype <3) {
				nbins = int(max - min + 1) ;
				TRACE ("Nbins is %d\n", nbins); 
				long *histo = new long [nbins+1] ;
				nvalid = ca.histo (cif->rawdata, histo, cif->samps, cif->lines, cif->dtype, 1, min, 
					1., nbins, 1) ;
				minperc = cdd.m_nMin [ib]* nvalid * .01f ;
				maxperc = cdd.m_nMax [ib]* nvalid * .01f ;
				lowval = min ;
				highval = min ;
				for (i=0; i<nbins; i++) {
					val = histo [i] ;
					if (val < minperc) lowval = i ;
					if (val < maxperc) highval = i ;
				}
				lowval += min ;
				highval += min ;

				TRACE ("Total pixels %d   top level %d\n", nvalid, histo[255]) ;
				delete [] histo ;
			}
			if (cif->dtype ==3) {
				nbins = 10001  ;
				binsize = float((max -min) / 10000.) ;
				long *histo = new long [nbins] ;
				nvalid = ca.histo (cif->rawdata, histo, cif->samps, cif->lines, cif->dtype, 1, min, 
					binsize, nbins, 1) ;
				minperc = cdd.m_nMin [ib]* nvalid * .01f ;
				maxperc = cdd.m_nMax [ib]* nvalid * .01f ;
				lowval = min ;
				highval = min ;
				for (i=0; i<nbins; i++) {
					val = histo [i] ;
					if (val < minperc) lowval = i ;
					if (val < maxperc) highval = i ;
				}
				lowval = min + binsize * lowval ;
				highval = min + binsize * highval ;

				TRACE ("Total pixels %d   top level %d\n", nvalid, histo[nbins-1]) ;
				delete [] histo ;
			}
			min = lowval ;
			max = highval ;
		}
		
	}
	else ca.minmax (cif->rawdata, long(cif->samps) * cif->lines, cif->dtype, &min, &max) ;
		

	
	ca.bytescale (cif->rawdata, bdata + ib *cif->samps *cif->lines, long(cif->samps) * cif->lines, cif->dtype, min, max, &scale, &offset) ;
	}
	CSize sizeTotal (cif->samps, cif->lines) ;
	CSize sizePage  (512,512) ;
	CSize sizeLine   (50,50) ;
	SetScrollSizes (MM_TEXT, sizeTotal, sizePage, sizeLine) ;
	

	
	
	
	dib = new DIB (cif->samps, cif->lines, 3, bdata) ;
	czm->SetDIB (dib) ;
	InvalidateRect (NULL, true) ;

}



void CNewestView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO:0 Add your message handler code here and/or call default
	int xloc=0, yloc=0 ;
	SetCursor (LoadCursor (NULL, IDC_CROSS) ) ;
	/*
	if (dib)
	{
	yloc = GetScrollPos (SB_VERT) ;
	xloc = GetScrollPos (SB_HORZ) ;
	}
	xloc += point.x ;
	yloc += point.y ;
	
	CString cstr ;
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar ;
	if (pStatus) {
		cstr.Format ("X : %5d     Y : %5d", xloc, yloc ) ;
		pStatus->SetPaneText (0, cstr, true) ;
	}
	*/
	CScrollView::OnMouseMove(nFlags, point);
}

void CNewestView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);

}

void CNewestView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar); 
	
	
}

void CNewestView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCursor (LoadCursor (NULL, IDC_CROSS) ) ;
	CNewestDoc *cnd=(CNewestDoc *) GetDocument() ;
	CScrollView::OnLButtonUp(nFlags, point);
	int		xloc=0, yloc=0 ;
	float	zval, lat=0., lon=0. ;

	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	cmenu = pFrame->GetMenu ()  ;
	
	if (nFlags != 200)
	{
		yloc = GetScrollPos (SB_VERT) ;
		xloc = GetScrollPos (SB_HORZ) ;
	}
	

	point.x += xloc ;
	point.y += yloc ;
	
	
	if (czm && nFlags != 200) czm->SetOrigin (point) ;

	CString cstr ;
	
	CStatusBar *pStatus = &pFrame->m_wndStatusBar ;

	
	if (DEMloaded) {
		zval = cifdem->GetVal (point.x, point.y) ;
		cifdem->GetLatLon (point.x, point.y, &lon, &lat) ;
	if (pStatus) {
		
		cstr.Format ("X : %5d     Y : %5d   Lon : %f  Lat : %f  Elev : %f", point.x, point.y, lon, lat, zval ) ;
		if (DefUnaff && !DefUnaffCur)
		{
		cstr.Format ("X : %5d     Y : %5d   Lon : %f  Lat : %f Elev : %f  Corr Elev : %f", point.x, point.y,
			lon, lat, 
			zval, cifdem->GetVal_Corr(point.x, point.y) ) ;
		}
		pStatus->SetPaneText (0, cstr, true) ;
		
	}
	}

	//
	
	if (DefUnaffCur) 
	{
		unaff_x [Unaff_pts] = point.x ;
		unaff_y [Unaff_pts] = point.y ;
		unaff_z [Unaff_pts] = zval ;
		Unaff_pts++ ;
		Invalidate (FALSE) ;
		czm->SetUnaffPts (unaff_x, unaff_y, Unaff_pts) ;
		czm->Invalidate (FALSE) ;
	} 
	if (nFlags != 200) return ;
	
	if (DefCraterCur)
	{
		int getmask = DefCraterMask & 0x00FF ;
		// nothing has been defined yet 
		// this is the routine for defining the location of the center of
		// the crater, lobes follow
			DefineMode = 0 ;
			DefCraterMask = 1 ;
			DefCrater = 1 ;
			DefCraterCur = 0 ;
			CraterCtr.x = point.x ;
			CraterCtr.y = point.y ;
			cnd->HitCraters[cnd->m_nNumHitCraters].x = point.x ;
			cnd->HitCraters[cnd->m_nNumHitCraters++].y = point.y ;
			czm->SetCraterPts (&CraterCtr, NULL, NULL, DefCraterMask) ;
			czm->Invalidate (FALSE) ;
			Invalidate (FALSE) ; 
			
			cnd->center = point ;
			cnd->Centerflag = 1 ;
			cifdem->GetLatLon (point.x, point.y, &cnd->center_lon, &cnd->center_lat) ; 
			
			cnd->GetGeom () ;
			
			//MessageBox (_T("Define maximum lobe range on zoom window"), _T("Information") ) ;
			cnd->UpdateAllViews(this) ;
			WriteResultsFile (TRUE, 0) ;
			cnd->WriteFeatFile (0) ;
			UINT status = cmenu->CheckMenuItem (IDC_DEFCRATERCTR, MF_BYCOMMAND | MF_CHECKED) ;

		// center has been defined but nothing else
	
	}

	if (DefLobesCur)
	{
		int getmask = DefCraterMask & 0x00FF ;
		if (getmask == 1) 
		{
			DefCraterMask |= 2 ;
			CraterMaxLobe.x = point.x ;
			CraterMaxLobe.y = point.y ;
			czm->SetCraterPts (&CraterCtr, &CraterMaxLobe, NULL, DefCraterMask) ;
			czm->Invalidate (FALSE) ;
			Invalidate (FALSE) ; 
			
			cnd->range_to_max.cx = point.x - cnd->center.x ;
			cnd->range_to_max.cy = point.y - cnd->center.y ;
			cnd->range_max_z = cifdem->GetVal_Corr (point.x, point.y) ; 
			MessageBox (_T("Define minimum lobe range on zoom window"), _T("Information") ) ;
			cnd->UpdateAllViews (this) ;
		}
		if (getmask == 3) 
		{
			DefCraterMask |= 4 ;
			CraterMinLobe.x = point.x ;
			CraterMinLobe.y = point.y ;
			

			cnd->range_min_z = cifdem->GetVal_Corr (point.x, point.y) ;
			cnd->range_to_min.cx = point.x - cnd->center.x ;
			cnd->range_to_min.cy = point.y - cnd->center.y ;

			czm->SetCraterPts (&CraterCtr, &CraterMaxLobe, &CraterMinLobe, DefCraterMask) ;
			czm->Invalidate (FALSE) ;
			Invalidate (FALSE) ;
			cnd->Centerflag = 1 ;
			cnd->UpdateAllViews(this) ;
			
			MessageBox (_T("Ranges have been defined"), _T("Information") ) ;
			DefLobesCur = 0 ;
			WriteResultsFile (FALSE, 6) ;
			
			UINT status = cmenu->CheckMenuItem (IDC_DEFLOBES, MF_BYCOMMAND | MF_CHECKED) ;

		}
	}	


	if (DefRimCur) 
	{
		RimPtLoc [Rim_pts++] = point ;
		czm->SetRimPts (RimPtLoc, Rim_pts) ;
		Invalidate (FALSE) ;
		
		czm->Invalidate (FALSE) ;
	}


	if (DefInnPrimeCur) 
	{
		InnPrime [Inn_Prime_Pts++] = point ;
		czm->SetInnPrimePts (InnPrime, Inn_Prime_Pts) ;
		
		czm->Invalidate (FALSE) ;
		Invalidate (FALSE) ;
	}

	if (DefPrimeSecCur) 
	{
		PrimeSec [Prime_Sec_Pts++] = point ;
		czm->SetPrimeSecPts (PrimeSec, Prime_Sec_Pts) ;
	
		czm->Invalidate (FALSE) ;
		Invalidate (FALSE) ;
	}

	if (DefSecCur) 
	{
		Sec [Sec_Pts++] = point ;
		czm->SetSecPts (Sec, Sec_Pts) ;
		czm->Invalidate(FALSE) ;

		Invalidate (FALSE) ;
	}



}

void CNewestView::OnDispoptions() 
{
	// TODO: Add your command handler code here
	// Create a dialog to prompt user with the display options 
	// Some are set already

	int status ;
	
	CDisplayOptions_dlg cdo_dlg ;
	cdo_dlg.m_nMin = m_nValMin  ;
	cdo_dlg.m_nMax = m_nValMax ;
	status = cdo_dlg.DoModal () ;
	if (status == IDOK) {
		m_nValMin = cdo_dlg.m_nMin ;
		m_nValMax = cdo_dlg.m_nMax ;
	}

}

void CNewestView::OnDefDem() 
{
	// TODO: Add your command handler code here
	
	char temppath [420], tempfile [420] ;
	OPENFILENAME m_ofn ;
	


	CNewestDoc *cnd = (CNewestDoc *) GetDocument () ;
	cnd->m_nNumHitCraters = 0 ;
	
	m_ofn.lpstrInitialDir = "C:\\HG" ;
	CFileDialog cfd (true, "*.hdr", "*.hdr", NULL, NULL, NULL) ;
	cfd.m_ofn.lpstrInitialDir = "C:\\HG" ;
	cfd.m_ofn.lpstrTitle = "Define DEM File" ;
	cfd.m_ofn.lpstrFilter = ("Envi Header Files", "*.hdr") ;
	int status = cfd.DoModal() ;
	if (status == IDCANCEL) return ;
	// filename is now in cfd.m_szFileName ;

	// if extension is not .hdr then need to get file info
	TRACE ("File extension is %s\n", cfd.GetFileExt()) ;
	if (!strcmp (cfd.GetFileExt(), "hdr")) TRACE("file is hdr\n") ; 

	strcpy (tempfile, cfd.GetFileName()) ;
	strcpy (temppath, cfd.GetPathName()) ;
	if (cifdem) delete cifdem ;
	cifdem = new CImageFile  ;
	cifdem->ReadEnviHeader (temppath,tempfile) ;
	cifdem->SetCDocument (cnd) ;
	::SetCursor (::LoadCursor (NULL, IDC_WAIT) ) ;
	cifdem->GetData () ;
	cifdem->DefMask () ;
	cnd->nsamps = cifdem->samps ;
	cnd->nlines = cifdem->lines ;
	czm->SetImageSize (cnd->nsamps, cnd->nlines) ;
	for (int i=0; i<4; i++) {
		
		cnd->grid_ll [i] = cifdem->grid_ll [i] ;
	}
	// read in the data 
	
	DEMloaded = 1 ;
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	cmenu = pFrame->GetMenu ()  ;
	pFrame->cifdemptr = cifdem ;
	status = cmenu->CheckMenuItem (ID_DEF_DEM, MF_BYCOMMAND | MF_CHECKED) ;

	int hg=0 ;
	
}

void CNewestView::OnDefUnaffect() 
{
	// TODO: Add your command handler code here
	DefineMode = 1 ;
	if (cifdem==NULL) {
		MessageBox (TEXT ("Define DEM before selecting surface"),
			TEXT ("Information only"), MB_OK) ;
			return ;
	}

	MessageBox (TEXT ("Click on > 8 points with left button\nRight click when done"),
			TEXT ("Information only"), MB_OK) ;
	
//	SetCapture () ;

	SetCursor (LoadCursor (NULL, IDC_CROSS) ) ;
	DefUnaffCur = 1 ;
	DefUnaff = 1 ;
	Unaff_pts = 0 ;

	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	cmenu = pFrame->GetMenu ()  ;
	UINT status = cmenu->CheckMenuItem (ID_DEF_UNAFFECT, MF_BYCOMMAND | MF_CHECKED) ;

	
}

void CNewestView::OnDispShade() 
{
	// TODO: Add your command handler code here
	char temppath[240], tempfile [240] ;
	OPENFILENAME   m_ofn ;
	float scale=0., offset=0., min=127, max=127 ;
	CMArray ca ;
	
	int status ;
	
	if (!strcmp(Shadefilename,"")) {
		MessageBox (TEXT ("Define Shaded Relief before displaying"),
			TEXT ("Information only"), MB_OK) ;
			return ;
	}

	CDC *cdc=GetDC () ;


	// set valid min and max for calculations
	ca.SetValid (m_nValMin, m_nValMax) ;



	
	if (cif) delete cif ;
	cif = new CImageFile  ;
	//cif->ReadEnviHeader (temppath,tempfile) ;
	cif->ReadEnviHeader (Shadefilename) ;

	CDisplayscale_dialog cdd ;
	if (cif->dtype == 0)
		cdd.InitForByte () ;
	cdd.DoModal() ;
	cdd.ParseData() ;

	cif->GetData (cif->samps, cif->lines, cif->dtype, cdd.bandarr[0]) ;

	// get the values from the cdd class and decide how to display the data
	if (cdd.useUser) {
		if (cdd.useVal) {
			min = cdd.m_nMin [0] ;
			max = cdd.m_nMax [0] ;
		}
		else {
			int i, nbins ;
			long nvalid, val ;
			float lowval, highval,minperc, maxperc, binsize ;
			ca.minmax (cif->rawdata, long(cif->samps) * cif->lines, cif->dtype, &min, &max) ;
			if (cif->dtype <3) {
				nbins = int(max - min + 1) ;
				TRACE ("Nbins is %d\n", nbins); 
				long *histo = new long [nbins+1] ;
				nvalid = ca.histo (cif->rawdata, histo, cif->samps, cif->lines, cif->dtype, 1, min, 
					1., nbins, 1) ;
				minperc = cdd.m_nMin [0] * nvalid * .01f ;
				maxperc = cdd.m_nMax [0]* nvalid * .01f ;
				lowval = min ;
				highval = min ;
				for (i=0; i<nbins; i++) {
					val = histo [i] ;
					if (val < minperc) lowval = i ;
					if (val < maxperc) highval = i ;
				}
				lowval += min ;
				highval += min ;

				TRACE ("Total pixels %d   top level %d\n", nvalid, histo[255]) ;
				delete [] histo ;
			}
			if (cif->dtype ==3) {
				nbins = 10001  ;
				binsize = float((max -min) / 10000.) ;
				long *histo = new long [nbins] ;
				nvalid = ca.histo (cif->rawdata, histo, cif->samps, cif->lines, cif->dtype, 1, min, 
					binsize, nbins, 1) ;
				minperc = cdd.m_nMin [0] * nvalid * .01f ;
				maxperc = cdd.m_nMax [0]* nvalid * .01f ;
				lowval = min ;
				highval = min ;
				for (i=0; i<nbins; i++) {
					val = histo [i] ;
					if (val < minperc) lowval = i ;
					if (val < maxperc) highval = i ;
				}
				lowval = min + binsize * lowval ;
				highval = min + binsize * highval ;

				TRACE ("Total pixels %d   top level %d\n", nvalid, histo[nbins-1]) ;
				delete [] histo ;
			}
			min = lowval ;
			max = highval ; 
		}
		
	}
	else ca.minmax (cif->rawdata, long(cif->samps) * cif->lines, cif->dtype, &min, &max) ;
		
	if (bdata) delete [] bdata ;
	bdata = new unsigned char [cif->samps * cif->lines] ;
	ca.bytescale (cif->rawdata, bdata, long(cif->samps) * cif->lines, cif->dtype, min, max, &scale, &offset) ;

	CSize sizeTotal (cif->samps, cif->lines) ;
	CSize sizePage  (512,512) ;
	CSize sizeLine   (50,50) ;
	SetScrollSizes (MM_TEXT, sizeTotal, sizePage, sizeLine) ;
	
	if (dib) delete dib ;
	dib = new DIB (cif->samps, cif->lines, bdata) ;
	czm->cnd = (CNewestDoc *) GetDocument () ;
	czm->SetDIB (dib) ;

	InvalidateRect (NULL, true) ;


	
}

void CNewestView::OnDefShade() 
{
	// TODO: Add your command handler code here
		
	char temppath [420], tempfile [420] ;
	OPENFILENAME m_ofn ;
	m_ofn.lpstrInitialDir = "C:\\HG" ;
	CFileDialog cfd (true, "*.hdr", "*.hdr", NULL, NULL, NULL) ;
	cfd.m_ofn.lpstrInitialDir = "C:\\HG" ;
	cfd.m_ofn.lpstrTitle = "Define Shaded Relief File" ;
	int status = cfd.DoModal() ;
	if (status == IDCANCEL) return ;
	// filename is now in cfd.m_szFileName ;

	// if extension is not .hdr then need to get file info
	TRACE ("File extension is %s\n", cfd.GetFileExt()) ;
	if (!strcmp (cfd.GetFileExt(), "hdr")) TRACE("file is hdr\n") ; 

	//strcpy (tempfile, cfd.GetFileName()) ;
	strcpy (temppath, cfd.GetPathName()) ;
	strcpy (Shadefilename, cfd.GetPathName ()) ;

	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	cmenu = pFrame->GetMenu ()  ;
	status = cmenu->CheckMenuItem (ID_DEF_SHADE, MF_BYCOMMAND | MF_CHECKED) ;


	
}

void CNewestView::OnRButtonDown (UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	// calculate the unaffected surface and save coefs....
	char results [1900] ;
	int  i, *ia, ncoefs ;
	float medval = 0. ;
	double chisq = 0. ;
	double *indarr, *deparr, *coefs, *wt, **covar ;
	double x, y, z ;

	CNewestDoc *cnd = GetDocument () ;
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	cmenu = pFrame->GetMenu ()  ;

	DefineMode = 0 ;
	SetCursor (LoadCursor (NULL, IDC_CROSS) ) ;

	
	if (DefUnaffCur) 
	{
		if (Unaff_pts < 8) {
			MessageBox (TEXT ("You need to select at least 8 points"),  TEXT ("HELP"),
				MB_OK) ;
			return ;
		}

		double **u, **v, *w ;

		DefUnaffCur = 0 ;
		double totalelev = 0. ;
		ncoefs = 6 ;
		ia = new int [ncoefs] ;
		for (i=0; i<ncoefs; i++) ia[i]=1 ;
		indarr = new double [Unaff_pts] ;
		deparr = new double [Unaff_pts] ;
		xyarr = new float [Unaff_pts * 2] ;
		wt = new double [Unaff_pts] ;
		coefs  = new double [ncoefs] ;
		covar = dmatrix (1, ncoefs, 1, ncoefs) ;
		u = dmatrix (1, Unaff_pts, 1, ncoefs) ;
		v = dmatrix (1, ncoefs, 1, ncoefs) ;
		w = dvector (1, ncoefs) ;


		for (i=0; i<Unaff_pts; i++) 
		{
			x = unaff_x [i] ;
			y = unaff_y [i] ;
			z = unaff_z [i] ;
			totalelev+= z ;
			wt [i] = 1. ;
			xyarr [i * 2 ] = x ;
			xyarr [i * 2 + 1] = y ;
			
			indarr [i] = i ;
	
			deparr [i] = z ;


		}
		
		

	//svdfit (indarr-1, deparr-1, wt-1, Unaff_pts, coefs - 1, ncoefs, u, v, w, &chisq, funct) ;
	//svdvar (v, ncoefs, w, covar) ;
		
		
		int okflag = 0 ;
	
		//while (!okflag) {
		//	okflag = 1 ;
			lfit_d (indarr-1, deparr-1, wt-1, Unaff_pts, coefs -1, ia -1, ncoefs, covar, &chisq, funct_d) ;
		//	for (i=0; i<6; i++) if (covar [i+1][i+1] < 0) okflag = 0 ; 
		//}
		sprintf (results, "2D Surface Coefficients\r\nA0 : %9.4f\nX  : %9.4f\nY  : %9.4f\nXY : %9.6e\nXX : %9.6e\nYY : %9.6e",
			coefs [0], coefs[1], coefs[2], coefs[3], coefs[4], coefs [5]) ;
		cifdem->LoadSurfCoefs (&coefs [0]) ;

		// Before we get too far, get the elevations of the crater, corrected and not
		float crater_elev, crater_elev_corr ;

		cnd->center_elev = cifdem->GetVal (CraterCtr.x, CraterCtr.y) ;
		cnd->center_elev_corr = cifdem->GetVal_Corr (CraterCtr.x, CraterCtr.y) ;
		

		FILE *fstats = fopen (cnd->m_strSurfFile, "w") ;
		
		fprintf (fstats, "\r\n\r\nVALUES AND STANDARD DEVIATIONS OF COEFFICIENTS\r\n") ;
		fprintf (fstats, "\r\nCoeff       Value       Std Dev\r\n") ;  
		float std ;
		for (i=0; i<ncoefs; i++) {
			std = sqrt (covar [i+1][i+1]) ;
			
			fprintf (fstats, "%4d  %+9.4e  %+9.4e\r\n", i, coefs [i], std ) ;
		}


		fprintf (fstats, "\r\n\r\n******TIEPOINT SUMMARY********\r\n") ;
		
		fprintf (fstats, "Tiept    x           y         z        z-zfit      (z - zfit)^2    sqrt ((z-zfit)^2) \r\n") ;  
		


		double newz, stdev=0., sumdiff=0,  zbar = 0., num=0., den=0., r2, diff, diff2 ;
		double xytot=0., xxtot=0., yytot=0., hg_r2 ;
		double resids_mean=0., resids_stdev =0., resids_rms=0. ;
		double stdarr [6], *resids ;

		

		resids = new double [Unaff_pts] ;
		for (i=0; i<Unaff_pts; i++) {
			x = unaff_x [i] ;
			y = unaff_y [i] ;
			z = unaff_z [i] ;


			xytot += x * y ;
			xxtot += x * x ;
			yytot += y * y ;
			newz = double(coefs [0]) + coefs [1] * x + coefs [2] * y + coefs [3] * x * y + 
				coefs [4] * x * x + coefs [5] * y * y ;
			diff = newz - z ;
			sumdiff += diff ;
			diff2 = diff * diff ;
			stdev += diff2 ;
			fprintf (fstats, "%4d  %4f  %4f  %7.1f   %9f    %9f    %9f\r\n", i, x, y, z,  diff, diff2, sqrt (diff2)) ;
			zbar += z ;
			resids [i] = diff ;
			resids_mean += diff ;
			resids_rms += diff2 ;

		}
		resids_mean /= Unaff_pts ;

		hg_r2 = xytot / sqrt (xxtot * yytot) ;
		zbar /= Unaff_pts ;
		fprintf (fstats,"Sum of z - zfit : %f\r\n", sumdiff) ; 
		// Calculate the r2
		for (i=0; i<Unaff_pts; i++) {
			x = unaff_x [i] ;
			y = unaff_y [i] ;
			z = unaff_z [i] ;

			newz = double (coefs [0]) + coefs [1] * x + coefs [2] * y + coefs [3] * x * y + 
				coefs [4] * x * x + coefs [5] * y * y ;
			num += pow(newz - zbar,2.) ;
			den += pow(z - zbar, 2.) ;
		
			resids_stdev += (((newz-z) - resids_mean) * ((newz-z) - resids_mean)) ;
		
		}

		resids_rms /= Unaff_pts ;
		resids_rms = sqrt (resids_rms) ;
		r2 = num / den ;
		resids_stdev /= Unaff_pts ;
		resids_stdev = sqrt (resids_stdev) ;
		
		


		fprintf (fstats, "\r\nNumber of points : %d\r\nMean Elevations : %6.1f", Unaff_pts, zbar) ;
		fprintf (fstats, "\r\nMean of residuals : %9.2f", resids_mean) ;
		fprintf (fstats, "\r\nResids RMS :%9.2f", resids_rms) ;
		fprintf (fstats, "\r\nStandard Deviation : %9.2f", resids_stdev ) ;
		fprintf (fstats, "\r\nR2 : %f\r\n", r2) ;
		fprintf (fstats, "\r\nCorr' : %f\r\n", hg_r2) ;
		fprintf (fstats, "\r\n*********COEFFICIENTS********\r\n") ;
		fprintf (fstats , "\r\nCovariance Matrix \r\n") ;
		for (i=0; i<6; i++) {
			for (int j=0; j<6; j++) {
				fprintf (fstats, "%+9.3e ", covar [i+1][j+1] ) ;
			}
			fprintf (fstats, "\r\n") ;
		}
		fprintf (fstats, "\r\nCOEFFICIENT    VALUE       LOWER BOUND   UPPER BOUND \r\n") ;
			
		
		for (i=0; i<ncoefs; i++) {
			std = sqrt (covar [i+1][i+1]) ;
			
			fprintf (fstats, "%4d      %+09.6e  %+09e %+09.6e\r\n", i, coefs [i], coefs[i] - 3. * std, coefs [i] + 3. * std ) ;
			stdarr [i] = std ;
		}
		
		// Set the values in the CNewestDoc 
		cnd->SetSurfaceCoefs (coefs, stdarr, r2) ;
		cnd->SetSurfaceTiepts (unaff_x, unaff_y, unaff_z, resids, Unaff_pts) ;
		cnd->SetSurfaceTieptsStats (resids_mean, resids_stdev) ;
		cnd->SFitflag = 1 ;

		fclose (fstats) ;

		//CLEAN UP	
		if (cfitres) delete cfitres ; 
		
		cfitres = new CFitres_dlg (this) ;
		cfitres->m_FitResults = results ;
		
		cnd->surf_ave_elev = totalelev / Unaff_pts ;
		int status = cfitres->Create () ;
	
	
		int hg = 0 ;
		free_dmatrix (covar, 1, ncoefs, 1, ncoefs) ;
		free_dmatrix (u, 1, Unaff_pts, 1, ncoefs) ;
		free_dmatrix (v, 1, ncoefs, 1, ncoefs) ;
		free_dvector (w, 1, ncoefs) ;
		
		WriteResultsFile (FALSE, 1) ;
		cnd->WriteFeatFile (1) ;


		delete [] resids ;
		delete [] ia ;
		delete [] coefs ;
		delete [] indarr ;
		delete [] deparr ;
		delete [] wt ;
		delete [] xyarr ;
		
	}

	// this allows for measurement of the crater but not rim, we need boundary
	// of rim and ejecta blanket to be defined.
	if (DefRimCur) 
	{
		CNewestDoc *cnd = GetDocument () ;

		RimPtLoc [Rim_pts++] = RimPtLoc [0] ;
		DefRimCur = 0 ;
		ShowCrater = 1 ;
		
		cifdem->CalcCraterVolume(RimPtLoc, Rim_pts) ;
		// set the array to the document rim array pointer
		// along with the number of points 
		MakeProfile (RimPtLoc, Rim_pts) ;
		// we also want to get the crater median depth, 
		// this is a good function to do this as all points within are collected
		cnd->Rimflag = 1 ;
		cnd->UpdateAllViews (this) ;

		dib->AddRegion (cifdem->CPM, cifdem->samps) ;
		czm->SetRimPts (RimPtLoc, Rim_pts) ;
		czm->Invalidate (TRUE) ;
		Invalidate (TRUE) ;
		
		
		WriteResultsFile (FALSE, 2) ;

		// For writing to feature file
		cnd->SetRimVertices (RimPtLoc, Rim_pts) ;
		cnd->WriteFeatFile (2) ;
		cmenu->CheckMenuItem (IDC_DEF_RIM, MF_BYCOMMAND | MF_CHECKED) ;
	}

	// Inner Primary Ejecta Blanket definition will turn all points above
	// unaffected surface to a rim volume measurement and allow exclusion
	// from subsequent ejecta blanket measurements.

	if (DefInnPrimeCur)
	{
		InnPrime [Inn_Prime_Pts++] = InnPrime [0] ;
		DefInnPrimeCur = 0 ;
		//cifdem->DefInnPrime (InnPrime, Inn_Prime_Pts) ;
		cifdem->CalcRimVolume (InnPrime, Inn_Prime_Pts) ;
	
		dib->AddRegion (cifdem->CPM, cifdem->samps) ;
		czm->SetInnPrimePts (InnPrime, Inn_Prime_Pts) ;
		cnd->SetInnPrimeVertices (InnPrime, Inn_Prime_Pts) ;
		czm->Invalidate(TRUE) ;
		cnd->RimInnerflag = 1 ;
		WriteResultsFile (FALSE, 3) ;
		cnd->WriteFeatFile (3) ;
		cmenu->CheckMenuItem (ID_DEF_INNERPRIMARY, MF_BYCOMMAND | MF_CHECKED) ;
		Invalidate (TRUE) ;
	}
		
	if (DefPrimeSecCur)
	{
		PrimeSec [Prime_Sec_Pts++] = PrimeSec [0] ;
		DefPrimeSecCur = 0 ;
		//cifdem->DefInnPrime (InnPrime, Inn_Prime_Pts) ;
		cifdem->CalcPrimaryVolume (PrimeSec, Prime_Sec_Pts) ;
		dib->AddRegion (cifdem->CPM, cifdem->samps) ;
		czm->SetPrimeSecPts (PrimeSec, Prime_Sec_Pts) ;
		cnd->SetPrimeSecVertices(PrimeSec, Prime_Sec_Pts) ;
		czm->Invalidate(TRUE) ;
		cnd->Innerflag = 1 ;
		WriteResultsFile (FALSE, 4) ;
		cnd->WriteFeatFile (4) ;
		cmenu->CheckMenuItem (ID_DEFINEPRIMARYSECONDARYBOUNDARY, MF_BYCOMMAND | MF_CHECKED) ;
		Invalidate (TRUE) ;
	}

	if (DefSecCur)
	{
		Sec [Sec_Pts++] = Sec [0] ;
		DefSecCur = 0 ;
		//cifdem->DefInnPrime (InnPrime, Inn_Prime_Pts) ;
		cifdem->CalcSecondaryVolume (Sec, Sec_Pts) ;
		dib->AddRegion (cifdem->CPM, cifdem->samps) ;
		czm->SetSecPts (Sec, Sec_Pts) ;
		cnd->SetSecVertices (Sec, Sec_Pts) ;
		Invalidate (TRUE) ;
		cnd->Outerflag = 1 ;
		czm->Invalidate(TRUE) ;
		cnd->WriteFeatFile (5) ;
		cmenu->CheckMenuItem (ID_DEF_SECONDARY, MF_BYCOMMAND | MF_CHECKED) ;
		WriteResultsFile (FALSE, 5) ;
	}

	cnd->UpdateAllViews (this) ;
	CScrollView::OnRButtonDown(nFlags, point);
}


void CNewestView::OnDefRim() 
{
	// TODO: Add your command handler code here
	MessageBox (TEXT ("Click on vertices of rim with left button in Zoom Window\nRight click when done"),
			TEXT ("Information only"), MB_OK) ;
	
	DefRimCur = 1 ;
	DefRim = 1 ;
	Rim_pts = 0 ;
	DefineMode = 1 ;


}


void funct (float x, float p[], int np) 
{
	int ind;
	double xval, yval  ;


	ind = int (x + .1) ;

	p [1] = 1. ;
	
	
	xval = *(xyarr + ind * 2) ;
	yval = *(xyarr + ind * 2 + 1) ;
	p [2] = xval ;
	p [3] = yval ;
	p [4] = xval * yval ;
	p [5] = xval * xval ;
	p [6] = yval * yval ;
//for (i=6; i<=6; i++) p[i]=0. ;
	return ;
}


void funct_d (double x, double p[], int np) 
{
	int ind;
	double xval, yval  ;


	ind = int (x + .1) ;

	p [1] = 1. ;
	
	
	xval = *(xyarr + ind * 2) ;
	yval = *(xyarr + ind * 2 + 1) ;
	p [2] = xval ;
	p [3] = yval ;
	p [4] = xval * yval ;
	p [5] = xval * xval ;
	p [6] = yval * yval ;
//for (i=6; i<=6; i++) p[i]=0. ;
	return ;
}

 


void CNewestView::OnDefInnerprimary() 
{
	// TODO: Add your command handler code here
	DefInnPrimeCur = 1 ;
	DefInnPrime = 1 ;
	Inn_Prime_Pts = 0 ;
	DefineMode = 1 ;
	
}



void CNewestView::OnDefineprimarysecondaryboundary() 
{
	// TODO: Add your command handler code here
	DefPrimeSecCur = 1;
	DefPrimeSec = 1 ;
	Prime_Sec_Pts = 0 ;
	DefineMode = 1 ;
	
}

void CNewestView::OnDefSecondary() 
{
	// TODO: Add your command handler code here
	DefSecCur =1 ;
	DefSec =1 ;
	Sec_Pts = 0 ;
	DefineMode =1 ;
}

LRESULT CNewestView::AppendFile (WPARAM wp, LPARAM lp)
{
	float tempval, xval, yval  ;

	


	// get the output filename from the document 
	CNewestDoc *cnd =  (CNewestDoc *) GetDocument () ;
	CFile cfil (cnd->m_strAnalFile, CFile::modeWrite |
		CFile::modeCreate ) ;
	
	CString outstr, outstr1 ;
	//outstr1.Format ("%8f %8f %8f %8f ", cifdem->crater_volume, cifdem->rim_volume,
	//	cifdem->primary_volume, cifdem->secondary_volume) ;
	//outstr =  profstring + outstr1 + cres_dlg->m_Cratername+_T("\r\n") ;

	
	outstr.Format ("Crater ID                         :\t") ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr = cnd->cratername + "\r\n\r\n" ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Surrounding surface avg elevation :\t%9.0ff\r\n\r\n", cnd->surf_ave_elev) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	
	outstr.Format ("Crater center location (X Y)      :\t%d   %d\r\n",cnd->center.x, cnd->center.y) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater center location (Lon  Lat) :\t%9.2ff   %9.2f\r\n",cnd->center_lon, cnd->center_lat) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Pixel size in meters (x y)        :\t%9.0f  %9.0f\r\n", cnd->xsize_meters, cnd->ysize_meters) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater average depth              :\t%9.0f\r\n",cnd->ctr_ave_depth) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater median depth               :\t%9.0f\r\n",cnd->ctr_median_depth) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater maximum depth              :\t%9.0f\r\n",cnd->ctr_max_depth) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	
	outstr.Format ("Crater diameter (pixels)          :\t%f\r\n",cnd->ctr_diam) ;
	cfil.Write (outstr, outstr.GetLength()) ;

	tempval = 2. * sqrt(cnd->ctr_npix * cnd->pixsize / PI) ;
	outstr.Format ("Crater diameter (m)               :\t%f\r\n",tempval) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater area (pixels)              :\t%d\r\n",cnd->ctr_npix) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater area (km^2)                 :\t%e\r\n", cnd->ctr_npix * cnd->pixsize/ 1.E6) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater volume                     :\t%e\r\n", cnd->ctr_vol) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater volume (km^3)               :\t%e\r\n\r\n\r\n", cnd->ctr_vol * cnd->pixsize / 1.E9) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	
	

	// max and min lobe measurements
	xval = cnd->range_to_max.cx * cnd->xsize_meters ;
	yval = cnd->range_to_max.cy * cnd->ysize_meters ;
	outstr.Format ("Distance to max lobe (x y)        :\t%d %d\r\n", cnd->range_to_max.cx, cnd->range_to_max.cy ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Distance to max lobe (meters)     :\t%e\r\n", sqrt (xval * xval + yval * yval)     ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Height at max lobe                :\t%f\r\n", cnd->range_max_z     ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Distance to min lobe (x y)        :\t%d %d\r\n", cnd->range_to_min.cx, cnd->range_to_min.cy ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	xval = cnd->range_to_min.cx * cnd->xsize_meters ;
	yval = cnd->range_to_min.cy * cnd->ysize_meters ;
	outstr.Format ("Distance to min lobe (meters)     :\t%f\r\n\r\n\r\n", sqrt (xval * xval + yval * yval ));
	outstr.Format ("Height at min lobe                :\t%f\r\n", cnd->range_min_z     ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	cfil.Write (outstr, outstr.GetLength()) ;

	// rim measurements 
	outstr.Format ("Rim maximum height                :\t%f\r\n", cnd->rim_max ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Rim average height                :\t%f\r\n", cnd->rim_avg ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Rim median height                 :\t%f\r\n", cnd->rim_median ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Rim diameter (pixels)             :\t%f\r\n", cnd->rim_diam ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	
	outstr.Format ("Rim diameter (pixels)             :\t%f\r\n", cnd->rim_diam) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Rim area                          :\t%d\r\n", cnd->rim_npix) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Rim area (km^2)                    :\t%f\r\n", cnd->rim_npix * cnd->pixsize / 1.E6) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Rim volume                        :\t%f\r\n", cnd->rim_avg * cnd->rim_npix) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Rim volume (km^3)                  :\t%f\r\n\r\n", cnd->rim_avg * cnd->rim_npix
		* cnd->pixsize / 1.E9) ;
	cfil.Write (outstr, outstr.GetLength()) ;

	outstr.Format ("Rim avg ht to crater max depth    :\t%f\r\n\r\n\r\n", cnd->rim_avg - cnd->ctr_max_depth ) ;
	cfil.Write (outstr, outstr.GetLength()) ;

	// inner lobe measurements 
	outstr.Format ("Inner lobe avg thickness          :\t%f\r\n", cnd->inner_avg) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Inner lobe median thickness       :\t%f\r\n", cnd->inner_median) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Inner lobe max thickness          :\t%f\r\n", cnd->inner_max) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Inner lobe area                   :\t%d\r\n", cnd->inner_npix) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Inner lobe area (km^2)             :\t%e\r\n", cnd->inner_npix * cnd->pixsize / 1.E6) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Inner lobe volume                 :\t%e\r\n", cnd->inner_vol) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	
	outstr.Format ("Inner lobe volume (km^3)           :\t%e\r\n", cnd->inner_vol * cnd->pixsize / 1.E9) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Pixels below surrounding surface  :\t%d\r\n\r\n\r\n", cnd->inner_npix_below) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	

	// outer lobe measurements 
	outstr.Format ("Outer lobe avg thickness          :\t%f\r\n", cnd->outer_avg) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Outer lobe med thickness          :\t%f\r\n", cnd->outer_median) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Outer lobe max thickness          :\t%f\r\n", cnd->outer_max) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Outer lobe area                   :\t%d\r\n", cnd->outer_npix) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Outer lobe area (km^2)             :\t%e\r\n", cnd->outer_npix * cnd->pixsize/ 1.E6) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Outer lobe volume                 :\t%e\r\n", cnd->outer_vol) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Outer lobe volume (km^3)           :\t%e\r\n", cnd->outer_vol * cnd->pixsize / 1.E9) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Pixels below surrounding surface  :\t%d\r\n\r\n\r\n", cnd->outer_npix_below) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	





	cfil.Close () ;

	return (0) ;
}


// AppendFile is button driven and being put out to pasture,
// new output mode is to automatically write as information 
// is gathered. Can't wait for crater analysis to be complete
// though as some craters only certain stages are reached


void CNewestView::WriteResultsFile (BOOL initflag, int analphase)
{
	float tempval, xval, yval  ;

	


	// get the output filename from the document 

	CNewestDoc *cnd =  (CNewestDoc *) GetDocument () ;
	CFile cfil ;

	if (analphase==0) {
		TRY {
			cfil.Open (cnd->m_strAnalFile, CFile::modeWrite |
			CFile::modeCreate ) ;
		}
		CATCH (CFileException, e) 		{
		}
		END_CATCH 
	}
	else {
		cfil.Open (cnd->m_strAnalFile, CFile::modeWrite |
			CFile::modeNoTruncate | CFile::modeCreate ) ;
		cfil.SeekToEnd () ;
	}

	CString outstr, outstr1 ;
	//outstr1.Format ("%8f %8f %8f %8f ", cifdem->crater_volume, cifdem->rim_volume,
	//	cifdem->primary_volume, cifdem->secondary_volume) ;
	//outstr =  profstring + outstr1 + cres_dlg->m_Cratername+_T("\r\n") ;



	if (analphase==0)
	{
	outstr.Format ("Crater ID                         :\t") ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr = cnd->cratername + "\r\n\r\n" ;
	cfil.Write (outstr, outstr.GetLength()) ;
	}

	if (analphase ==1) 
	{
	outstr.Format ("Surrounding surface avg elevation :\t%f\r\n\r\n", cnd->surf_ave_elev) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	}

	if (analphase ==2) 
	{
	outstr.Format ("Crater center location (X Y)       :\t%9d   %9d\r\n",cnd->center.x, cnd->center.y) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater center location (Lon  Lat)  :\t%9.2f   %9.2f\r\n",cnd->center_lon, cnd->center_lat) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Pixel size in meters (x y)         :\t%9.0f  %9.0f\r\n", cnd->xsize_meters, cnd->ysize_meters) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater average depth               :\t%9.0f\r\n",-cnd->ctr_ave_depth) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater ave depth for all pixels    :\t%9.0f\r\n",-cnd->ctr_ave_depth_all) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater median depth                :\t%9.0f\r\n", -cnd->ctr_median_depth) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater maximum depth               :\t%9.0f\r\n",-cnd->ctr_max_depth_all) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	
	outstr.Format ("Crater diameter (km)           :\t%9.0f\r\n",cnd->ctr_diam/1.E3) ;
	cfil.Write (outstr, outstr.GetLength()) ;

	//tempval = cnd->ctr_diam * cnd->pixdim_avg / 1000. ;
	//outstr.Format ("Crater diameter (km)               :\t%9.1f\r\n",tempval) ;
	//cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater area (pixels)               :\t%9.1f\r\n",cnd->ctr_area) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater area (km^2)                 :\t%9.1f\r\n", cnd->ctr_area * cnd->pixsize / 1.E6) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater volume                      :\t%9.1f\r\n", cnd->ctr_vol) ;
	cfil.Write (outstr, outstr.GetLength()) ; 
	outstr.Format ("Crater volume (km^3)               :\t%9.1f\r\n\r\n\r\n", cnd->ctr_vol * cnd->pixsize / 1.E9) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	
	
	


	// rim measurements 
	outstr.Format ("Rim prof max height                :\t%f\r\n", cnd->rimprof_max ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Rim prof ave height                :\t%f\r\n", cnd->rimprof_avg ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Rim median height                  :\t%f\r\n", cnd->rimprof_med ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	
	}

	if (analphase == 3) 
	{
	outstr.Format ("Rim area                           :\t%d\r\n", cnd->rim_npix) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Rim area (km^2)                    :\t%f\r\n", cnd->rim_npix * cnd->pixsize / 1.E6) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Rim volume                         :\t%f\r\n", cnd->rim_vol) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Rim volume (km^3)                  :\t%f\r\n\r\n", cnd->rim_vol  * cnd->pixsize / 1.E9) ;
	cfil.Write (outstr, outstr.GetLength()) ;

	
	}

	if (analphase == 6) 
	{
		

	// max and min lobe measurements
	
	xval = cnd->range_to_max.cx * cnd->xsize_meters ;
	yval = cnd->range_to_max.cy * cnd->ysize_meters ;
	outstr.Format ("Distance to max lobe (x y)        :\t%d %d\r\n", cnd->range_to_max.cx, cnd->range_to_max.cy ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Distance to max lobe (meters)     :\t%e\r\n", sqrt (xval * xval + yval * yval)     ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Height at max lobe                :\t%f\r\n", cnd->range_max_z     ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Distance to min lobe (x y)        :\t%d %d\r\n", cnd->range_to_min.cx, cnd->range_to_min.cy ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	xval = cnd->range_to_min.cx * cnd->xsize_meters ;
	yval = cnd->range_to_min.cy * cnd->ysize_meters ;
	outstr.Format ("Distance to min lobe (meters)     :\t%f\r\n", sqrt (xval * xval + yval * yval ));
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Height at min lobe                :\t%f\r\n\r\n", cnd->range_min_z     ) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	}

	// inner lobe measurements 
	if (analphase ==4 )
	{
	outstr.Format ("Inner lobe avg thickness          :\t%f\r\n", cnd->inner_avg) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Inner lobe med thickness          :\t%f\r\n", cnd->inner_median) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Inner lobe max thickness          :\t%f\r\n", cnd->inner_max) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Inner lobe area (below surface)   :\t%d\r\n", cnd->inner_npix) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Inner lobe area (below, km^2)     :\t%e\r\n", cnd->inner_npix * cnd->pixsize / 1.E6) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Inner lobe area (total) (km^2)    :\t%e\r\n", cnd->inner_npix_all * cnd->pixsize / 1.E6) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Inner lobe volume                 :\t%e\r\n", cnd->inner_vol) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	
	outstr.Format ("Inner lobe volume (km^3)           :\t%e\r\n", cnd->inner_vol * cnd->pixsize / 1.E9) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Pixels below surrounding surface  :\t%d\r\n\r\n\r\n", cnd->inner_npix_below) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	}

	// outer lobe measurements 
	if (analphase ==5) 
	{
	outstr.Format ("Outer lobe avg thickness          :\t%f\r\n", cnd->outer_avg) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Outer lobe med thickness          :\t%f\r\n", cnd->outer_median) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Outer lobe max thickness          :\t%f\r\n", cnd->outer_max) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Outer lobe area (below surface)   :\t%d\r\n", cnd->outer_npix) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Outer lobe area (below, km^2)     :\t%e\r\n", cnd->outer_npix * cnd->pixsize / 1.E6) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Outer lobe area (total) (km^2)    :\t%e\r\n", cnd->outer_npix_all * cnd->pixsize / 1.E6) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Outer lobe volume                 :\t%e\r\n", cnd->outer_vol) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	
	outstr.Format ("Outer lobe volume (km^3)           :\t%e\r\n", cnd->outer_vol * cnd->pixsize / 1.E9) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Pixels below surrounding surface  :\t%d\r\n\r\n\r\n", cnd->outer_npix_below) ;
	cfil.Write (outstr, outstr.GetLength()) ;

	}



	

	cfil.Close () ;


	// call the fcn to write the tabulated file
	if (analphase > 1) WriteTabulatedFile () ;
	return  ;
}


LRESULT CNewestView::LeftZoom (WPARAM wp, LPARAM lp)
{
	
	
	int xloc, yloc ;
	xloc = (wp & 0xFFFF0000) >> 16 ;
	yloc = (wp & 0x0000FFFF) ;

	CPoint cp (xloc, yloc) ;
	OnLButtonUp (200, cp) ;
	return (0) ;
}

LRESULT CNewestView::RightZoom (WPARAM wp, LPARAM lp)
{
	
	
	int xloc, yloc ;
	xloc = (wp & 0xFFFF0000) >> 16 ;
	yloc = (wp & 0x0000FFFF) ;

	CPoint cp (xloc, yloc) ;
	OnRButtonDown (200, cp) ;
	return (0) ;
}

void CNewestView::OnSetFocus(CWnd* pOldWnd) 
{
	CScrollView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	
}

void CNewestView::OnDefcraterctr() 
{
	// TODO: Add your command handler code here
	char line [420], title [100] ;
	int  lineval, sampval ;
	float lat, lon ;

	DefCraterCur = 1 ;
	DefCrater = 1 ;
	DefCraterMask = 0 ;

	CNewestDoc *cnd = (CNewestDoc *) GetDocument () ;

	
	CCraterID_Dlg cid ;
	cid.m_CraterID = cnd->cratername ;
	int status = cid.DoModal () ;
	if (status == IDCANCEL) return ;
	cratername = cid.m_CraterID ;
	
	cnd->cratername = cratername ;

	// Define output file names 
	CFileSelectDlg cfsd ;
	cfsd.m_AnalFile = outdir + cratername + _T("_Results.txt") ;
	cfsd.m_FeatFile = outdir + cratername + _T("_Features.txt") ;
	cfsd.m_SurfFile = outdir + cratername + _T("_SurfStats.txt") ;
	int len = cnd->m_strTabFile.GetLength() ;
	if (len == 0) {
		cfsd.m_TabFile = outdir + _T("CraterTable.txt") ;
	}
	else cfsd.m_TabFile  = cnd->m_strTabFile ; 

	status = cfsd.DoModal () ;
	if (status == IDCANCEL) return ;
	cnd->m_strAnalFile = cfsd.m_AnalFile ;
	cnd->m_strFeatFile = cfsd.m_FeatFile ;
	cnd->m_strSurfFile = cfsd.m_SurfFile ;
	cnd->m_strTabFile  = cfsd.m_TabFile ;
	cnd->GetPath (cnd->m_strSurfFile, &outdir) ;
	cnd->m_strProfFile = cfsd.m_SurfFile ;
	cnd->m_strProfFile.Replace ("SurfStats", "Prof") ;
	m_bDefFiles = 1 ;
	
	CFile outfile (cnd->m_strTabFile, CFile::modeWrite | 
		CFile::modeNoTruncate | CFile::modeCreate ) ;
	m_TabFilePosition = outfile.GetLength () ;

	// read in the points which have already been hit if the file is created
		
	outfile.Close () ;
	
	
	
	/*
	ifstream ifil (cnd->m_strTabFile, ios::in) ;
	int icount=0 ;
	while (!ifil.eof()) {

		
		ifil.getline (line, 420, '\n') ;
		if (strlen (line > 2)) 
		{
			if (icount > 0) {
				sscanf (line, "%s %f %f", title, lat, lon) ;
				cnd->HitCraters[cnd->m_nNumHitCraters].y = (grid_ll [1] - lat) / (grid_ll[3]) ;
				cnd->HitCraters[cnd->m_nNumHitCraters].x = (lon - grid_ll [0]) / (grid_ll[2]) ;
				cnd->m_nNumHitCraters++ ;				
			}
		}
				
		icount++ ;
	}
	*/
	MessageBox (_T("Hit with left button on Zoom Window crater center"), _T("Information")) ;


}

void CNewestView::OnNewcrater() 
{
	// TODO: Add your command handler code here
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	DefineMode = 0 ;
	cmenu = pFrame->GetMenu ()  ;

	int status = MessageBox ("This will clear all information related to previous crater", NULL, MB_OKCANCEL) ;
	if (status == IDCANCEL) return ;
	m_nValMin = -1.E6 ;

	m_nValMax = 1.E6 ;
	
	DefUnaffCur = 0 ;
	DefUnaff = 0 ;
	DefInnPrime = 0 ;
	DefInnPrimeCur = 0 ;
	Unaff_pts = 0 ;
	DefRimCur = 0 ;
	DefRim = 0 ;
	DefPrimeSec = 0 ;
	DefPrimeSecCur = 0 ;
	DefSec = 0 ;
	DefSecCur = 0 ;
	Rim_pts = 0 ;
	ShowCrater = 0 ;
	DefCrater = 0 ;
	DefCraterCur = 0 ;
	DefLobesCur = 0 ;
	DefCraterMask = 0 ;
	cifdem->DefMask () ;
	dib->AddRegion (cifdem->CPM, cifdem->samps) ;
	
	CNewestDoc * cnd = GetDocument() ;
	cnd->Init() ;
	Invalidate (TRUE) ;
	czm->SetUnaffPts (NULL, NULL, 0) ;
	czm->SetRimPts (NULL, 0) ;
	czm->SetInnPrimePts (NULL, 0) ;
	czm->SetPrimeSecPts (NULL, 0) ;
	czm->SetSecPts (NULL, 0) ;
	czm->SetCraterPts (NULL, NULL, NULL, 0) ;
	czm->Invalidate (TRUE) ;

	m_bDefFiles = FALSE ;
	
	// uncheck all menu items
	cmenu->CheckMenuItem (IDC_DEFCRATERCTR, MF_BYCOMMAND | MF_UNCHECKED) ;
	cmenu->CheckMenuItem (IDC_DEF_RIM, MF_BYCOMMAND | MF_UNCHECKED) ;
	cmenu->CheckMenuItem (ID_DEF_INNERPRIMARY, MF_BYCOMMAND | MF_UNCHECKED) ;
	cmenu->CheckMenuItem (ID_DEFINEPRIMARYSECONDARYBOUNDARY, MF_BYCOMMAND | MF_UNCHECKED) ;
	cmenu->CheckMenuItem (ID_DEF_SECONDARY, MF_BYCOMMAND | MF_UNCHECKED) ;
	cmenu->CheckMenuItem (ID_DEF_UNAFFECT, MF_BYCOMMAND | MF_UNCHECKED) ;
	cmenu->CheckMenuItem (IDC_DEFLOBES, MF_BYCOMMAND | MF_UNCHECKED) ;
}


int CNewestView::MakeProfile(POINT *cpoints, int npts)
{

	// first time through get the number of points that 
	// are required for the profile
	int    i, idist, xloc, yloc ;
	float	avetotal=0. ;
	double xdist, ydist, dist, xinc, yinc, xrad, yrad, radius, totalRadius, azimuth ;
	long totdist = 0 ;
	float *rimprof, *rimprof_corr, maxval = -1.E12, minval = 1.E12;
	CStatic *plotwin ;
	CPoint *rimprof_coords;
	CString outstr ;

	totalRadius = 0. ;

	// get the Document for holding rimprof array
	CNewestDoc *cnd = (CNewestDoc *) GetDocument () ;
	CFile cfil ;

	TRY {
			cfil.Open (cnd->m_strProfFile, CFile::modeWrite |
			CFile::modeCreate ) ;
		}
		CATCH (CFileException, e) 		{
		}
		END_CATCH 

	

	for (i=0; i<npts-1; i++)
	{
		 xdist = cpoints[i+1].x - cpoints[i].x  ;
		 ydist = cpoints[i+1].y - cpoints[i].y ;
		 dist = sqrt (xdist * xdist + ydist * ydist) ;
		 totdist += (int) (dist+1.) ;
	}

	
	rimprof = new float [totdist+30] ;
	
	rimprof_corr = new float [totdist+30] ;
	rimprof_coords = new CPoint [totdist+30] ; 
	totdist=0 ;
	
	float *azimRad = new float [360] ;
	float *azimElev = new float [360] ;
	float *azimCElev= new float [360] ;
	int *nptsAzim = new int [360] ;
	int azimBin ;
	for (i=0; i<360; i++) {
		azimRad[i] = 0. ;
		azimElev[i] = 0. ;
		azimCElev[i] = 0. ;
		nptsAzim[i] = 0 ;
	}
	for (i=0; i<npts-1; i++)
	{
		 xdist = cpoints[i+1].x - cpoints[i].x ;
		 ydist = cpoints[i+1].y - cpoints [i].y ;
		 dist = sqrt (xdist * xdist + ydist * ydist) ;
		 if (dist < 0.01) continue ; 
		 xinc = xdist / dist ;
		 yinc = ydist / dist ;
		 

		 for (idist=0; idist<int(dist); idist++) 
		 {
			 xloc = int (cpoints[i].x + float(idist) * xinc + .5) ;
			 yloc = int (cpoints[i].y + float(idist) * yinc + .5) ;
			 if (DefUnaff) {
			 rimprof_corr [totdist] = cifdem->GetVal_Corr (xloc, yloc) ;
			 if (rimprof_corr[totdist]>maxval) maxval = rimprof_corr [totdist] ;
			 if (rimprof_corr[totdist]<minval) minval = rimprof_corr [totdist] ;
			 avetotal += rimprof_corr [totdist] ;
			 }
			 rimprof_coords[totdist] = CPoint(xloc,yloc) ;
			 xrad = (xloc - cnd->centroid_x) * cnd->xsize_meters ;
			 yrad = (cnd->centroid_y - yloc) * cnd->ysize_meters ;
			 radius = sqrt (xrad * xrad + yrad * yrad) ;
			 // convert to degrees
			 azimuth = atan2 (xrad, yrad) * 57.29578  ;
			 if (azimuth < 0.) azimuth += 360. ;
			 azimBin = int(azimuth+0.5) ;
			 if (azimBin > 359) azimBin = 359 ;
			 azimRad[azimBin] += radius ;
			 nptsAzim[azimBin] += 1 ;
			 rimprof [totdist] = cifdem->GetVal (xloc, yloc) ;
			 azimElev[azimBin] += rimprof[totdist] ;
			 azimCElev[azimBin] += rimprof_corr[totdist] ;
			 totalRadius += radius ;
			
			 totdist++ ;
			 
		 }
	}
	for (i=0; i<360; i++) {
		if (nptsAzim[i] <= 0) continue ;
			azimRad[i] /= nptsAzim[i] ;
			azimElev[i] /= nptsAzim[i] ;
			azimCElev[i]/=nptsAzim[i] ;
	}
	int is, lowI, highI, ldist, hdist ;
	float fracLow, fracHigh, totDist ;
	bool fLow, fHigh ;
	for (i=0; i<360; i++) {
		if (nptsAzim[i] >0) continue ;
		for (is=1; is<360; is++) {
			lowI = i - is ;
			if (lowI < 0) lowI += 360 ;
			ldist = is ;
			if (nptsAzim[lowI] >0) break ;
			
		}
		for (is=1; is<360; is++) {
			highI = i + is ;
			if (highI > 359) highI -= 360 ;
			hdist = is ;
			if (nptsAzim[highI] >0) break ;
		}
		totDist = ldist + hdist ;
		fracLow = float (hdist) / totDist ;
		fracHigh = float (ldist) / totDist ;
		azimRad[i] = azimRad[lowI] * fracLow + azimRad[highI] * fracHigh ;
		azimElev[i] = azimElev[lowI] * fracLow + azimElev[highI] * fracHigh ;
		azimCElev[i] = azimCElev[lowI] * fracLow + azimCElev[highI] * fracHigh ;
	}
		
		 
	totalRadius /=  totdist ;
	
	//for (i=0; i<totdist; i++) {
	//	xdist = r

	cnd->AddRimProfile (rimprof_corr, totdist) ;
	if (totdist < .00001) avetotal=0. ;
	else avetotal /= totdist ;
	float diam = float (totdist) / 3.1415927 ;

	
	outstr.Format ("AZIMUTH\tRADIUS\tAveRad\tELEV\tCORR_ELEV\r\n") ;
	cfil.Write (outstr, outstr.GetLength() ) ;
	for (i=0;i<360; i++) {
		outstr.Format ("%d\t%f\t%f\t%f\t%f\r\n",i, azimRad[i], totalRadius,
				 azimElev[i], azimCElev[i]) ;
		cfil.Write (outstr, outstr.GetLength()) ;
	}

	cfil.Close() ;
	cnd->rimprof_avg = avetotal ;
	cnd->rimprof_max = maxval ;
	cnd->rimprof_min = minval ;
	cnd->radius_rim = totalRadius ;
	// this is essentially the same parameter as the crater diameter, can
	// report this as a check, hold off for now
	cnd->rim_diam = totalRadius * 2. ;

	// median rim value
	long nhist_bins, il,  *histo, cumtot=0, medval, index ; 
	nhist_bins = long (maxval - minval) + 1 ;
	if (nhist_bins == 1 || totdist < 2) medval = maxval ;
	else 
	{
		histo = new long [nhist_bins] ;
		for (il=0; il<nhist_bins; il++) histo[il]=0 ;

		for (i=0; i<totdist; i++)
		{
			index = int (rimprof_corr [i] - minval) ;
						
			histo [index]++ ;
					
				
		}
		

	
		for (il=0; il<nhist_bins && cumtot <= (totdist/2); il++) 
		{
			cumtot += histo [il] ;
		}

		medval = minval + il ;
		delete [] histo ;
	}


	profstring.Format ("%7f %7f %7f %6d %7f ",maxval, minval, avetotal, int(totdist), diam) ; 
	cnd->rimprof_med = medval ;

	delete [] rimprof ;
	delete [] rimprof_corr ;
	delete [] rimprof_coords ;
	delete [] nptsAzim ;
	delete [] azimRad ;
	delete [] azimElev ;
	delete [] azimCElev ;
	return (totdist) ;

}



void CNewestView::OnUpdateDefUnaffect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bDefFiles) pCmdUI->Enable (TRUE) ;
	else pCmdUI->Enable (FALSE) ;

	if (DefineMode) pCmdUI->Enable (FALSE) ;

}

void CNewestView::OnUpdateDefineprimarysecondaryboundary(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bDefFiles && DefUnaff) pCmdUI->Enable (TRUE) ;
	else pCmdUI->Enable (FALSE) ;

	if (DefineMode) pCmdUI->Enable (FALSE) ;

}

void CNewestView::OnUpdateDefSecondary(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bDefFiles && DefUnaff) pCmdUI->Enable (TRUE) ;
	else pCmdUI->Enable (FALSE) ;
	if (DefineMode) pCmdUI->Enable (FALSE) ;


	

}

void CNewestView::OnUpdateDefInnerprimary(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bDefFiles && DefUnaff) pCmdUI->Enable (TRUE) ;
	else pCmdUI->Enable (FALSE) ;
	if (DefineMode) pCmdUI->Enable (FALSE) ;

}

void CNewestView::OnUpdateDefRim(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bDefFiles && DefUnaff) pCmdUI->Enable (TRUE) ;
	else pCmdUI->Enable (FALSE) ;
	if (DefineMode) pCmdUI->Enable (FALSE) ;

	
}

void CNewestView::OnDeflobes() 
{
	// TODO: Add your command handler code here
	DefLobesCur = 1 ;
	MessageBox (_T("Define maximum lobe on zoom window"), _T("Information")) ;
	DefineMode = 1 ;
	
	
}

void CNewestView::OnUpdateDeflobes(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bDefFiles && DefUnaff) pCmdUI->Enable (TRUE) ;
	else pCmdUI->Enable (FALSE) ;
	if (DefineMode) pCmdUI->Enable (FALSE) ;

	
}

void CNewestView::OnShowHits() 
{
	// TODO: Add your command handler code here
	// Insert a check mark next to menu item 
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	cmenu = pFrame->GetMenu ()  ;
	UINT status = cmenu->CheckMenuItem (ID_SHOW_HITS, MF_BYCOMMAND | MF_CHECKED) ;
	
	// Check if the MenuItem has been checked or not,
	// if so UnShow the hits file
	// otherwise show it
	if (status == MF_UNCHECKED) 
	{
		dib->AddHitInfo (cifhit->rawdata, cifhit->samps) ;
		cmenu->CheckMenuItem (ID_SHOW_HITS, MF_BYCOMMAND | MF_CHECKED) ;
	}
	else 
	{
		dib->RemoveHitInfo (cifdem->CPM, cifdem->samps) ;
		cmenu->CheckMenuItem (ID_SHOW_HITS, MF_BYCOMMAND | MF_UNCHECKED) ;
	}
	//dib->AddHitInfo (cifhit->rawdata, cifdem->samps) ;
	
	czm->Invalidate (TRUE) ;
	Invalidate (FALSE) ;


	
	


}

void CNewestView::OnUpdateShowHits(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (HITloaded) pCmdUI->Enable (TRUE) ;
	else pCmdUI->Enable (FALSE) ;
	
}

void CNewestView::OnDefineHitfile() 
{
	// TODO: Add your command handler code here
	

	// TODO: Add your command handler code here
	
	char temppath [420], tempfile [420] ;
	OPENFILENAME m_ofn ;

	CNewestDoc *cnd = (CNewestDoc *) GetDocument () ;
	
	m_ofn.lpstrInitialDir = "C:\\HG" ;
	CFileDialog cfd (true, "*.hdr", "*.hdr", NULL, NULL, NULL) ;
	cfd.m_ofn.lpstrInitialDir = "C:\\HG" ;
	cfd.m_ofn.lpstrTitle = "Define Byte Hits File" ;
	cfd.m_ofn.lpstrFilter = ("Envi Header Files", "*.hdr") ;
	int status = cfd.DoModal() ;
	if (status == IDCANCEL) return ;
	// filename is now in cfd.m_szFileName ;

	// if extension is not .hdr then need to get file info
	TRACE ("File extension is %s\n", cfd.GetFileExt()) ;
	if (!strcmp (cfd.GetFileExt(), "hdr")) TRACE("file is hdr\n") ; 

	strcpy (tempfile, cfd.GetFileName()) ;
	strcpy (temppath, cfd.GetPathName()) ;
	if (cifhit) delete cifhit ;
	cifhit = new CImageFile  ;
	cifhit->ReadEnviHeader (temppath,tempfile) ;
	cifhit->SetCDocument (cnd) ;
	::SetCursor (::LoadCursor (NULL, IDC_WAIT) ) ;
	cifhit->GetData () ;
	//cifhit->DefMask () ;
	//for (int i=0; i<4; i++) {
		
	//	cnd->grid_ll [i] = cifhit->grid_ll [i] ;
	//}
	HITloaded = 1 ;

	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	cmenu = pFrame->GetMenu ()  ;
	status = cmenu->CheckMenuItem (ID_DEFINE_HITFILE, MF_BYCOMMAND | MF_CHECKED) ;
	

}

void CNewestView::OnDefAltshadefile() 
{
	// TODO: Add your command handler code here
	char temppath [420], tempfile [420] ;
	OPENFILENAME m_ofn ;
	m_ofn.lpstrInitialDir = "C:\\HG" ;
	CFileDialog cfd (true, "*.hdr", "*.hdr", NULL, NULL, NULL) ;
	cfd.m_ofn.lpstrInitialDir = "C:\\HG" ;
	cfd.m_ofn.lpstrTitle = "Define Alternate Shaded Relief File" ;
	int status = cfd.DoModal() ;
	if (status == IDCANCEL) return ;
	// filename is now in cfd.m_szFileName ;

	// if extension is not .hdr then need to get file info
	TRACE ("File extension is %s\n", cfd.GetFileExt()) ;
	if (!strcmp (cfd.GetFileExt(), "hdr")) TRACE("file is hdr\n") ; 

	//strcpy (tempfile, cfd.GetFileName()) ;
	strcpy (temppath, cfd.GetPathName()) ;
	strcpy (AltShadefilename, cfd.GetPathName ()) ;

	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	cmenu = pFrame->GetMenu ()  ;
	status = cmenu->CheckMenuItem (ID_DEF_ALTSHADEFILE, MF_BYCOMMAND | MF_CHECKED) ;
	
}

void CNewestView::OnShowAltShade() 
{
	// TODO: Add your command handler code here

		char temppath[240], tempfile [240] ;
	OPENFILENAME   m_ofn ;
	float scale=0., offset=0., min=127, max=127 ;
	CMArray ca ;
	
	int status ;
	
	if (!strcmp(AltShadefilename,"")) {
		MessageBox (TEXT ("Define Shaded Relief before displaying"),
			TEXT ("Information only"), MB_OK) ;
			return ;
	}

	CDC *cdc=GetDC () ;

	// set valid min and max for calculations
	ca.SetValid (m_nValMin, m_nValMax) ;



	
	if (cifalt) delete cifalt ;
	cifalt = new CImageFile  ;
	//cif->ReadEnviHeader (temppath,tempfile) ;
	cifalt->ReadEnviHeader (AltShadefilename) ;

	CDisplayscale_dialog cdd ;
	if (cif->dtype == 0)
		cdd.InitForByte () ;
	cdd.DoModal() ;
	cdd.ParseData() ;

	cifalt->GetData (cif->samps, cif->lines, cif->dtype, cdd.bandarr[0]) ;

	// get the values from the cdd class and decide how to display the data
	if (cdd.useUser) {
		if (cdd.useVal) {
			min = cdd.m_nMin [0] ;
			max = cdd.m_nMax [0] ;
		}
		else {
			int i, nbins ;
			long nvalid, val ;
			float lowval, highval,minperc, maxperc, binsize ;
			ca.minmax (cifalt->rawdata, long(cifalt->samps) * cifalt->lines, cifalt->dtype, &min, &max) ;
			if (cifalt->dtype <3) {
				nbins = int(max - min + 1) ;
				TRACE ("Nbins is %d\n", nbins); 
				long *histo = new long [nbins+1] ;
				nvalid = ca.histo (cifalt->rawdata, histo, cifalt->samps, cifalt->lines, cifalt->dtype, 1, min, 
					1., nbins, 1) ;
				minperc = cdd.m_nMin [0] * nvalid * .01f ;
				maxperc = cdd.m_nMax [0]* nvalid * .01f ;
				lowval = min ;
				highval = min ;
				for (i=0; i<nbins; i++) {
					val = histo [i] ;
					if (val < minperc) lowval = i ;
					if (val < maxperc) highval = i ;
				}
				lowval += min ;
				highval += min ;

				TRACE ("Total pixels %d   top level %d\n", nvalid, histo[255]) ;
				delete [] histo ;
			}
			if (cifalt->dtype ==3) {
				nbins = 10001  ;
				binsize = float((max -min) / 10000.) ;
				long *histo = new long [nbins] ;
				nvalid = ca.histo (cifalt->rawdata, histo, cifalt->samps, cifalt->lines, cifalt->dtype, 1, min, 
					binsize, nbins, 1) ;
				minperc = cdd.m_nMin [0] * nvalid * .01f ;
				maxperc = cdd.m_nMax [0]* nvalid * .01f ;
				lowval = min ;
				highval = min ;
				for (i=0; i<nbins; i++) {
					val = histo [i] ;
					if (val < minperc) lowval = i ;
					if (val < maxperc) highval = i ;
				}
				lowval = min + binsize * lowval ;
				highval = min + binsize * highval ;

				TRACE ("Total pixels %d   top level %d\n", nvalid, histo[nbins-1]) ;
				delete [] histo ;
			}
			min = lowval ;
			max = highval ; 
		}
		
	}
	else ca.minmax (cifalt->rawdata, long(cifalt->samps) * cifalt->lines, cifalt->dtype, &min, &max) ;
		
	if (bdata_alt) delete [] bdata_alt ;
	bdata_alt = new unsigned char [cifalt->samps * cifalt->lines] ;
	ca.bytescale (cifalt->rawdata, bdata_alt, long(cifalt->samps) * cifalt->lines, cifalt->dtype, min, max, &scale, &offset) ;


	// bdata is now the byte array for the DIB
	// we use the same DIB object but substitute in the bdata for the shade file bdata
	dib->SetAltShadeArray (bdata_alt, cifalt->samps, cifalt->lines) ;
	if (cifdem) dib->AddRegion (cifdem->CPM, cifdem->samps) ;

	czm->Invalidate (TRUE) ;
	
	Invalidate (TRUE) ;
	ShowAlt = TRUE ;

	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	cmenu = pFrame->GetMenu ()  ;
	cmenu->CheckMenuItem (ID_TOGGLE_ALT, MF_BYCOMMAND | MF_CHECKED) ;
	cmenu->CheckMenuItem (ID_SHOW_HITS, MF_BYCOMMAND | MF_UNCHECKED) ;
	

}

void CNewestView::OnUpdateDefAltshadefile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//if (cif) pCmdUI->Enable (TRUE) ;
	//else pCmdUI->Enable (FALSE) ;
	
}

void CNewestView::OnUpdateShowAltShade(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (strlen (AltShadefilename)  && dib) pCmdUI->Enable (TRUE) ;
	else pCmdUI->Enable (FALSE) ;
	
}

void CNewestView::OnUpdateToggleAlt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (cifalt && cif) pCmdUI->Enable (TRUE) ;
	else pCmdUI->Enable (FALSE) ;
}

void CNewestView::OnToggleAlt() 
{
	// TODO: Add your command handler code here
	// This routine will set the alt file if the shade file is
	// set, and vice versa
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	cmenu = pFrame->GetMenu ()  ;
	
	
	if (ShowAlt) {
		ShowAlt = FALSE ;
		dib->m_data_cur = dib->m_data_orig ;
		cmenu->CheckMenuItem (ID_TOGGLE_ALT, MF_BYCOMMAND | MF_UNCHECKED) ;
	}
	else {
		ShowAlt = TRUE ;
		dib->m_data_cur = dib->m_data_alt ;
		cmenu->CheckMenuItem (ID_TOGGLE_ALT, MF_BYCOMMAND | MF_CHECKED) ;
	
	
	
	}
	//dib->Reload () ;
	if (cifdem) dib->AddRegion (cifdem->CPM, cifdem->samps) ;
	UINT status = cmenu->CheckMenuItem (ID_SHOW_HITS, MF_BYCOMMAND | MF_UNCHECKED) ;
	

	Invalidate (TRUE) ;
	czm->Invalidate (TRUE) ;
}

void CNewestView::WriteTabulatedFile () 
{

	CNewestDoc *cnd = (CNewestDoc *) GetDocument () ;
	CString tempstr ;
	CFile outfile (cnd->m_strTabFile, CFile::modeWrite | 
		CFile::modeNoTruncate | CFile::modeCreate ) ;
	outfile.Seek (m_TabFilePosition, 0) ;

	if (m_TabFilePosition ==0) {
		tempstr.Format ("Name    Lat Long  Elev  Ctr_Diam   Ctr_Mx_Dpth  ") ;
		outfile.Write (tempstr, tempstr.GetLength()) ;
		tempstr.Format ("Ctr_Av_Dpth    Cav_Vol    Rim_Hgt   Rim_Vol   Ejct_Below ") ;
		outfile.Write (tempstr, tempstr.GetLength()) ;
		tempstr.Format (" IEL_Vol    IEL_Av_Thck   IEL_Area   OEL_Vol   OEL_Av_Th  OEL_Area  ") ;
		outfile.Write (tempstr, tempstr.GetLength()) ;
		tempstr.Format (" Av_Flr_Fill   Min_Flr_Fill\r\n") ;
		outfile.Write (tempstr, tempstr.GetLength()) ;
	}

//	tempstr.Format ("%s  %6.2f %7.2f %7.1f %7.1f ", cnd->cratername, cnd->center_lat, 
//		cnd->center_lon, cnd->center_elev, cnd->center_elev_corr) ;
	tempstr.Format ("%s  %6.2f %7.2f %7.1f ", cnd->cratername, cnd->center_lat, 
		cnd->center_lon, cnd->center_elev - cnd->center_elev_corr) ;
	outfile.Write (tempstr, tempstr.GetLength()) ;

	tempstr.Format ("%9.3f %9.1f %9.1f ", cnd->ctr_diam / 1.E3, 
		cnd->rimprof_avg - cnd->ctr_max_depth_all, 
		cnd->rimprof_avg - cnd->ctr_ave_depth_all) ; 
	outfile.Write (tempstr, tempstr.GetLength()) ;

	tempstr.Format ("%9.1f ", cnd->ctr_vol * cnd->pixsize / 1.E9) ;
	outfile.Write (tempstr, tempstr.GetLength()) ;

	tempstr.Format ("%9.1f %9.1f ", cnd->rimprof_avg, cnd->rim_vol * cnd->pixsize / 1.E9) ;
	outfile.Write (tempstr, tempstr.GetLength()) ;


	// get ejecta lobe percents below surface
	double den, percentbelow;
	if ((cnd->inner_npix_all + cnd->outer_npix_all) < 0.0001)
		percentbelow = 0. ;
	
	else 
		percentbelow = 100. *  (cnd->inner_npix_below + cnd->outer_npix_below) / 
			(cnd->inner_npix_all + cnd->outer_npix_all) ;
		

	tempstr.Format ("%9.2f ", percentbelow) ;
	outfile.Write (tempstr, tempstr.GetLength()) ;

	// ejecta lobes
	tempstr.Format ("%9.1f %9.1f %9.1f ", cnd->inner_vol * cnd->pixsize / 1.E9,
		cnd->inner_avg, 
		cnd->inner_npix_all * cnd->pixsize/1.E6) ;
	outfile.Write (tempstr, tempstr.GetLength()) ;

	tempstr.Format ("%9.1f %9.1f %9.1f ", cnd->outer_vol * cnd->pixsize / 1.E9,
		cnd->outer_avg, 
		cnd->outer_npix_all * cnd->pixsize/1.E6) ;
	outfile.Write (tempstr, tempstr.GetLength()) ;
	
	// floor fills - these are redundant but what the helll
	//tempstr.Format ("%9.1f %9.1f %9.1f %9.1f ", cnd->ctr_ave_depth_all, 
	//	cnd->ctr_max_depth_all, 200. - cnd->ctr_ave_depth_all, 
	//	200. - cnd->ctr_max_depth_all) ;
	
	
	tempstr.Format ("%9.1f %9.1f ", cnd->ctr_ave_depth_all, 
		cnd->ctr_max_depth_all) ;
	outfile.Write (tempstr, tempstr.GetLength()) ;
	//tempstr.Format ("%9.1f %9.1f\r\n", cnd->rimprof_avg - cnd->ctr_ave_depth_all,
	//	cnd->rimprof_avg - cnd->ctr_max_depth_all) ;
	//outfile.Write (tempstr, tempstr.GetLength()) ;


	outfile.Close () ;



}

void CNewestView::OnUpdateDefcraterctr(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	

	if (DefineMode) pCmdUI->Enable (FALSE) ;

	
}
