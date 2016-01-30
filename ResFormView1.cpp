// ResFormView1.cpp : implementation file
//

#include "stdafx.h"
#include "newest.h"
#include "ResFormView1.h"
#include "NewestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResFormView

IMPLEMENT_DYNCREATE(CResFormView, CFormView)

CResFormView::CResFormView()
	: CFormView(CResFormView::IDD)
{
	//{{AFX_DATA_INIT(CResFormView)
	m_strLocationString = _T("");
	m_strSurftext = _T("");
	m_strCratRim = _T("");
	m_strInner = _T("");
	m_strOuter = _T("");
	m_strXmax = _T("");
	m_strXmin = _T("");
	m_strYmax = _T("");
	m_strYmin = _T("");
	//}}AFX_DATA_INIT
}

CResFormView::~CResFormView()
{

	int hg = 1 ;
}

void CResFormView::CleanUp ()
{
	m_strLocationString = _T("");
	m_strSurftext = _T("");
	m_strCratRim = _T("");
	m_strInner = _T("");
	m_strOuter = _T("");
	Invalidate (TRUE) ;
}

void CResFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResFormView)
	DDX_Control(pDX, IDC_RIMPROF, m_statRimProf);
	DDX_Text(pDX, IDC_LOCATION, m_strLocationString);
	DDX_Text(pDX, IDC_SURFTEXT, m_strSurftext);
	DDX_Text(pDX, IDC_CratRimText, m_strCratRim);
	DDX_Text(pDX, IDC_InnerLobe, m_strInner);
	DDX_Text(pDX, IDC_Outer, m_strOuter);
	DDX_Text(pDX, IDC_XMAX, m_strXmax);
	DDX_Text(pDX, IDC_XMIN, m_strXmin);
	DDX_Text(pDX, IDC_YMAX, m_strYmax);
	DDX_Text(pDX, IDC_YMIN, m_strYmin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResFormView, CFormView)
	//{{AFX_MSG_MAP(CResFormView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResFormView diagnostics

#ifdef _DEBUG
void CResFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CResFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResFormView message handlers

void CResFormView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CResFormView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	//Invalidate (FALSE) ;
	SetWindowText (_T("BLIPPY") );
	CString tempstring ;

	CNewestDoc *cnd = (CNewestDoc *) GetDocument () ;
	CDC *cdc = m_statRimProf.GetDC () ;
	if (cnd->rimprof_npts) MakeProfile () ;
	UpdateData (FALSE) ;

	if (lHint == 17) CleanUp () ;

	if (cnd->Centerflag) {
		m_strLocationString.Format ("Crater : \t%s\r\nX : %5d    \t\tY : %5d\r\nLon : %8.4f   \tLat : %7.4f\r\n",
			cnd->cratername, cnd->center.x, cnd->center.y, cnd->center_lon, 
			cnd->center_lat) ;
		tempstring.Format ("Pixel Dimension (m) : \t%9.1f\r\nPixel Area  (m2) : \t%9.0f\r\n", 
			cnd->pixdim_avg, cnd->pixsize) ;
		m_strLocationString += tempstring ;
	}

	if (cnd->SFitflag) {
		m_strSurftext.Format ("UNAFFECTED SURFACE FITTING\r\nNumber of Tiepoints : \t\t%5d\r\n",
			cnd->nTiepts) ;
		tempstring.Format ("Tiepts Resids Std Deviation : \t%9.1f\r\nTiepts R2 :  \t\t\t%5.2f \r\n",
			cnd->tiepts_stdev, cnd->tiepts_r2)   ;
		m_strSurftext += tempstring ;
	}

	if (cnd->Rimflag ) {
		m_strCratRim.Format ("CRATER STATISTICS\r\nApprox. Diam (km) : \t\t%9.1f\r\nMax Depth : \t\t\t%9.1f\r\nAvg Depth :\t\t\t%9.1f\r\nMed Depth : \t\t\t%9.1f\r\n",
			cnd->ctr_diam / 1.E3, -cnd->ctr_max_depth_all, -cnd->ctr_ave_depth_all, -cnd->ctr_median_depth) ;
		
		tempstring.Format ("Total Area (km2): \t\t%9.1f\r\nVol (only pxls below) (km3):\t%9.1f\r\n", 
			cnd->ctr_area * cnd->pixsize / 1.E6, cnd->ctr_vol * cnd->pixsize / 1.E9) ;
		m_strCratRim += tempstring ;


		tempstring.Format ("\r\nRIM PROFILE STATISTICS\r\nMax Height (m):  \t\t%9.1f\r\n",
			cnd->rimprof_max) ;

		m_strCratRim += tempstring ;
		tempstring.Format ("Avg Height : \t\t\t%9.1f\r\nMed Height : \t\t\t%9.1f\r\nAvg Height to Crater Max Depth :  %9.1f\r\nAvg Height to Crater Avg Depth :  %9.1f\r\n", 
			cnd->rimprof_avg, cnd->rimprof_med, cnd->rimprof_avg - cnd->ctr_max_depth_all, cnd->rimprof_avg - cnd->ctr_ave_depth_all) ;
		m_strCratRim += tempstring ;
	}

	if (cnd->RimInnerflag) {
		tempstring.Format ("\r\nRIM VOLUME STATISTICS\r\nArea (km2):   \t\t\t%9.1f\r\nVolume (km3):  \t\t\t%9.1f\r\n",
			cnd->rim_npix * cnd->pixsize / 1.E6, cnd->rim_vol * cnd->pixsize / 1.E9) ;
		m_strCratRim += tempstring ;
		
	}


	if (cnd->Innerflag) {
		m_strInner.Format ("INNER LOBE STATISTICS\r\nMax Thickness : \t%9.1f\r\n",
			cnd->inner_max) ;
		tempstring.Format ("Avg Thickness  : \t%9.1f\r\nMed Thickness : \t%9.1f\r\n",
			cnd->inner_avg, cnd->inner_median) ;
		m_strInner += tempstring ;
		tempstring.Format ("Area (km2) :\t\t%9.1f\r\nVolume (km3) :\t\t%9.1f\r\n", cnd->inner_npix_all * cnd->pixsize / 1.E6,
			cnd->inner_vol * cnd->pixsize / 1.E9) ;
		m_strInner += tempstring ;
	}
	if (cnd->Outerflag ) {
		m_strOuter.Format ("OUTER LOBE STATISTICS\r\nMax Thickness : \t%9.1f\r\n",
			cnd->outer_max) ;
		tempstring.Format ("Avg Thickness  : \t%9.1f\r\nMed Thickness  : \t%9.1f\r\n",
			cnd->outer_avg, cnd->outer_median) ;
		m_strOuter += tempstring ;
		tempstring.Format ("Area (km2) :\t\t%9.1f\r\nVolume (km3) :\t\t%9.1f\r\n", cnd->outer_npix_all * cnd->pixsize / 1.E6,
			cnd->outer_vol * cnd->pixsize / 1.E9) ;
		m_strOuter += tempstring ;
	}



	Invalidate (FALSE) ;
}

void CResFormView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	CNewestDoc *cnd = (CNewestDoc *) GetDocument () ;
	if (cnd->rimprof_npts) MakeProfile () ;
	UpdateData (FALSE) ;


	

}



void CResFormView::MakeProfile()
{
	int i, npts, totdist ;
	float *rimprof_corr ;

	CNewestDoc *cnd = (CNewestDoc *) GetDocument () ;
	rimprof_corr = cnd->rimprof_corr ;
	totdist = cnd->rimprof_npts ;
	CDC *cdc = m_statRimProf.GetDC () ;
	

	int     idist, xloc, yloc ;
	
	//double	xdist, ydist, dist, xinc, yinc ;
	
	float	maxval = -1.E12, minval = 1.E12;
	
	
	
	for (i=0; i<totdist; i++) {
		if (rimprof_corr[i]>maxval) maxval = rimprof_corr [i] ;
		if (rimprof_corr[i]<minval) minval = rimprof_corr [i] ;
	}




	// would like to use the ResFormView to plot this now

	// now want to plot this in the Results window 
	CRect cr ;
	int width, height ;
	
	m_statRimProf.GetClientRect (cr) ;
	width = cr.Width () ;
	height = cr.Height () ;
	float xploc, yploc, yrange ;
	
	xploc = 0 ;
	
	yrange = maxval - minval ;

	cdc->FillSolidRect (0, 0, width, height, 0xFFFFFF) ;
	for (i=0; i<totdist; i++) {
		
		yploc = height - (rimprof_corr [i] - minval)  / yrange * height;
		xploc = float (i) / totdist * width ;
		if (i== 0)cdc->MoveTo (xploc, yploc) ;
		cdc->LineTo (xploc, yploc) ;
	
	}

	m_strXmax.Format ("%5d", int(totdist)) ;
	m_strXmin= _T("0") ;
	m_strYmin.Format ("%6d", int(minval)) ;
	m_strYmax.Format ("%6d", int(maxval)) ;

	

}

BOOL CResFormView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style &= ~FWS_ADDTOTITLE ;
	cs.lpszName = _T("CRATER ANALYSIS RESULT WINDOW") ;
	return CFormView::PreCreateWindow(cs);
	
}


