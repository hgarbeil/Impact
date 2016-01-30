// ProfileForm.cpp : implementation file
//

#include "stdafx.h"
#include "newest.h"
#include "ProfileForm.h"

#include "math.h"

#ifndef DEG2RAD
#define DEG2RAD .0174532925
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfileForm

IMPLEMENT_DYNCREATE(CProfileForm, CFormView)

CProfileForm::CProfileForm()
	: CFormView(CProfileForm::IDD)
{
	//{{AFX_DATA_INIT(CProfileForm)
	m_fOrientation = 0.0f;
	m_fMinHeight = 0.0f;
	m_fMaxHeight = 0.0f;
	m_fProfLength = 0;
	m_nCentSamp = 0;
	m_nCentLine = 0;
	m_nAutoState = TRUE ;
	m_sYMax = _T("");
	m_sYMin = _T("");
	m_sXMax = _T("");
	m_sXMin = _T("");
	m_sYMid = _T("");
	//}}AFX_DATA_INIT
	m_nProfPts = NULL ;
	m_nNumProfPts = 0 ;
}

CProfileForm::~CProfileForm()
{
	if (m_nProfPts) delete [] m_nProfPts ;
}

void CProfileForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfileForm)
	DDX_Control(pDX, IDC_PROFWINDOW, m_cProfWindow);
	DDX_Text(pDX, IDC_ORIENTATION, m_fOrientation);
	DDV_MinMaxFloat(pDX, m_fOrientation, -360.f, 360.f);
	DDX_Text(pDX, IDC_MINHEIGHT, m_fMinHeight);
	DDX_Text(pDX, IDC_MAXHEIGHT, m_fMaxHeight);
	DDX_Text(pDX, IDC_LENGTH, m_fProfLength);
	DDV_MinMaxInt(pDX, m_fProfLength, 5, 100000);
	DDX_Text(pDX, IDC_CENTSAMP, m_nCentSamp);
	DDX_Text(pDX, IDC_CENTLINE, m_nCentLine);
	DDX_Check(pDX, IDC_AUTOSTATE, m_nAutoState);
	DDX_Text(pDX, IDC_YMAXLAB, m_sYMax);
	DDX_Text(pDX, IDC_YMINLAB, m_sYMin);
	DDX_Text(pDX, IDC_XMAXLAB, m_sXMax);
	DDX_Text(pDX, IDC_XMINLAB, m_sXMin);
	DDX_Text(pDX, IDC_YMID, m_sYMid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProfileForm, CFormView)
	//{{AFX_MSG_MAP(CProfileForm)
	ON_BN_CLICKED(IDC_BUTTON1, OnUpdateButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfileForm diagnostics

#ifdef _DEBUG
void CProfileForm::AssertValid() const
{
	CFormView::AssertValid();
}

void CProfileForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProfileForm message handlers

void CProfileForm::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
	CNewestDoc * cnd = (CNewestDoc *) GetDocument () ;
	if (cnd->Centerflag ) {
		m_nCentLine = cnd->center.y ;
		m_nCentSamp = cnd->center.x ;
		m_fProfLength = 100 ;
		m_fOrientation = 0. ;
	}

	
	UpdateData (FALSE) ;		
		
		

	
}

void CProfileForm::MakeCentProfile()
{
	int is, idist, ixloc, iyloc, ixstart, iystart, ixstop, iystop ;
	float xloc, yloc, xdist, ydist, dist, zval, zval_corr ;
	double ang_rad, xinc, yinc, minval=1.E9, maxval=-1.E9 ;

	int		height, width, prof_x, prof_y, minval_rem, maxval_rem ;
	float   yrange ;
	CRect cr ;
	CPen  surfPen ;
	
	CNewestDoc *cnd = (CNewestDoc *) GetDocument () ;
	UpdateData (TRUE) ;

	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	cifdem = pFrame->cifdemptr ;
	
	
	CDC *cdc = m_cProfWindow.GetDC () ;
	m_cProfWindow.GetClientRect (cr) ;
	height = cr.Height () ;
	width  = cr.Width () ;
	cdc->FillSolidRect (0, 0, width, height, 0xFFFFFF) ;
	ang_rad = m_fOrientation * DEG2RAD ;
	ixstart = int(m_nCentSamp + m_fProfLength / 2 * sin (ang_rad)) ;
	ixstop  = int(m_nCentSamp - m_fProfLength / 2 * sin (ang_rad)) ;
	iystart = int(m_nCentLine - m_fProfLength / 2 * cos (ang_rad)) ;
	iystop = int(m_nCentLine + m_fProfLength / 2 * cos (ang_rad)) ;

	
	xdist = ixstop - ixstart ;
	ydist = iystop - iystart ;
	
	dist = sqrt(xdist * xdist + ydist * ydist) ;
	xinc = xdist / dist ;
	yinc = ydist / dist ;
	

	idist = int (dist) ;

	m_nNumProfPts = idist ;
	if (m_nProfPts) delete [] m_nProfPts ;
	m_nProfPts = new POINT [idist+10] ;

	
	// scaling of the profile based either on data or the m_fMaxHeight and
	// m_fMinHeight
	if (m_nAutoState)
	{
		
		for (is=0;is <= idist; is++) {
		ixloc = int(ixstart + xinc * is) ;
		iyloc = int(iystart + yinc * is) ;

		if (ixloc >= 0 && ixloc < cnd->nsamps && iyloc < cnd->nlines && 
			iyloc >= 0){ 
			zval = cifdem->GetVal (ixloc, iyloc) ;
			if (zval < minval) minval = zval ;
			if (zval > maxval) maxval = zval ;
			}
		//if (cnd->SFitflag) zval_corr = zval - cifdem->GetVal_Corr (ixloc, iyloc) ;
		}

		minval_rem = int (minval) % 10 ;
		maxval_rem = int (maxval) % 10 ;
		m_fMinHeight = minval ;
		m_fMaxHeight = maxval ;

	}
		
	yrange = m_fMaxHeight - m_fMinHeight ; 
	if (yrange < 0.1) {
		m_fMaxHeight = m_fMinHeight + 1000. ;
		yrange = m_fMaxHeight - m_fMinHeight ; 
	}
		
	// Get the labels for the plot
	int ymx, ymn ;
	m_sXMin = _T("0") ;
	m_sXMax.Format ("%5d", idist) ;
	ymx = int (m_fMaxHeight);
	ymn = int (m_fMinHeight) ;
	m_sYMin.Format ("%5d",  ymn) ;
	m_sYMax.Format ("%5d",  ymx) ;
	int midval = int((m_fMinHeight + m_fMaxHeight)/2.) ;
	m_sYMid.Format ("%5d", midval) ;

	for (is=0;is <= idist; is++) {
		ixloc = int(ixstart + xinc * is) ;
		iyloc = int(iystart + yinc * is) ;

		
		m_nProfPts[is].x = ixloc ;
		m_nProfPts[is].y = iyloc ;
		
		if (ixloc >= 0 && ixloc < cnd->nsamps && iyloc < cnd->nlines && 
			iyloc >= 0)
		zval = cifdem->GetVal (ixloc, iyloc) ;
		else zval = m_fMinHeight ;
		//if (cnd->SFitflag) zval_corr = zval - cifdem->GetVal_Corr (ixloc, iyloc) ;

		prof_y = int (height - (zval - m_fMinHeight) / yrange * height) ;
		prof_x = int(float (is) / idist * width) ;

		// keep profile within the box
		if (prof_y < 0) prof_y = 0 ;
		if (prof_y > height) prof_y = height ;
		if (is==0) cdc->MoveTo (prof_x, prof_y) ;
		else cdc->LineTo (prof_x, prof_y) ;

		
		
	}
	surfPen.CreatePen (PS_SOLID, 1, RGB (255, 0, 255)) ;
	CPen *oldPen = cdc->SelectObject (&surfPen) ;
	if (cnd->SFitflag) 
	for (is=0;is <= idist; is++) {
		ixloc = int(ixstart + xinc * is) ;
		iyloc = int(iystart + yinc * is) ;

		//m_nProfPts[is].x = ixloc ;
		//nProfPts[is].y = iyloc ;
		
		//zval = cifdem->GetVal (ixloc, iyloc) -  cifdem->GetVal_Corr (ixloc, iyloc) ;
		if (ixloc >= 0 && ixloc < cnd->nsamps && iyloc < cnd->nlines && 
			iyloc >= 0)
		zval = cifdem->GetVal (ixloc, iyloc) -  cifdem->GetVal_Corr (ixloc, iyloc) ;
		else zval = m_fMinHeight ;
		
		prof_y = int (height - (zval - m_fMinHeight) / yrange * height) ;
		prof_x = int(float (is) / idist * width) ;

		// keep profile within the box
		if (prof_y < 0) prof_y = 0 ;
		if (prof_y > height) prof_y = height ;
		if (is==0) cdc->MoveTo (prof_x, prof_y) ;
		else cdc->LineTo (prof_x, prof_y) ;

		
		
	}

	surfPen.DeleteObject () ;
	
	// Draw a dashed line at the Ymidpoint 
	CPen midPen (PS_DASHDOTDOT, 1, RGB (255, 255, 0)) ;
	oldPen = cdc->SelectObject (&midPen) ;
	cdc->MoveTo (0, height * .5) ;
	cdc->LineTo (width, height * .5) ;
	cdc->SelectObject (&oldPen) ;
	midPen.DeleteObject () ;
	


	cnd->AddCtrProfile (m_nProfPts, idist) ;
	cnd->UpdateAllViews (this) ;
	m_cProfWindow.ReleaseDC (cdc) ;
	UpdateData (FALSE) ;
	

}

void CProfileForm::OnUpdateButton() 
{
	// TODO: Add your control notification handler code here
	MakeCentProfile () ;	
}

void CProfileForm::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CNewestDoc *cnd = (CNewestDoc *) GetDocument () ;
	if (m_nNumProfPts) 
	{
		MakeCentProfile () ;
		UpdateData (FALSE) ;
	}
	
}
