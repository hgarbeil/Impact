// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Newest.h"
#include "FileOperations.h"
#include "Dialog_BandSelect.h"
#include "TopoParams_dlg.h"
#include "TopoArray.h"



#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_GEN_HDR, OnGenHdr)
	ON_COMMAND(ID_SHADE, OnShade)
	ON_COMMAND(ID_STATISTICS_SUMMARY, OnStatisticsSummary)
	ON_COMMAND(IDC_SLOPEMAP, OnSlopemap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	cif = NULL ;
	cifout = NULL ;
	
}	

CMainFrame::~CMainFrame()
{
	if (cif) delete cif ;
	if (cifout) delete cifout ;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	*/

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~FWS_ADDTOTITLE ;
	cs.lpszName = _T("IMPACT CRATER PROGRAM") ;
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnGenHdr() 
{
 
 	// TODO: Add your command handler code here
 	// This will create the header file for an image
 
 	char fname [420] ;
 	CFileDialog cfd (NULL, NULL, NULL, NULL) ;
 	cfd.DoModal() ;
 
 	CFileParams_Dialog cfpd ;
 	strcpy (fname, cfd.GetPathName()) ;
 	cfpd.SetDefaults (fname, "BYTE", "BSQ") ;
  	cfpd.DoModal() ;
 

	CFileOperations cfo ;
	strcpy (fname, cfpd.m_Filename) ;
	
	// append .hdr to file to create
	strcat (fname, ".hdr") ;
	cfo.WriteHdrFile (fname, cfpd.m_samps, cfpd.m_lines, cfpd.m_nbands, cfpd.dt, cfpd.bform) ; 

	int hg=1 ;		

	
}

void CMainFrame::OnShade() 
{
	// TODO: Add your command handler code here
	int status, bandnum=0  ;
	char tempfile [420], temppath [420] ;
	OPENFILENAME m_ofn ;
	
	if (cif) delete cif ;
	cif = new CImageFile ; ;
	status = cif->GetFile_and_Params("H:\\harold\\stereo_aster\\peru\\stereo") ;
	if (!status) return ;
	if (cif->nbands > 1) {
		CDialog_BandSelect cdbs ;
		cdbs.SetBandsTotal (cif->nbands) ;
		cdbs.DoModal () ;
		bandnum = cdbs.m_nBandnum ;
	}

	// get shaded relief parameters 
	CTopoParams_dlg ctp_dlg ;
	status = ctp_dlg.DoModal () ;
	if (status == IDCANCEL) {
		delete cif ;
		return ;
	}


	

	if (cifout) delete cifout ;
	// set output file parameters
	cifout = new CImageFile (cif->samps, cif->lines, 0, 1, 0) ; 
	status = cifout->GetOutputFile ("H:\\harold\\stereo_aster\\peru\\stereo") ;
	CWaitCursor cwf ;
	MessageOut ("Getting input data") ;
	cif->GetData (cif->samps, cif->lines, cif->dtype, bandnum) ;
	
	MessageOut ("Allocating output data") ;
	status = cifout->AllocData (1) ;

	CTopoArray cta ;
	cta.SetParams (cif->samps, cif->lines, cif->dtype) ;
	MessageOut ("Generating shaded relief image ") ;
	cta.Calcshade (cif->rawdata, cifout->rawdata, ctp_dlg.m_nSunElev, ctp_dlg.m_nSunAz, 
		ctp_dlg.m_nPixDim, ctp_dlg.m_nMinVal) ;
	MessageOut ("Writing to file ") ;
	cifout->WriteData () ;
	cifout->WriteHeaderFile () ;

	MessageOut ("Shaded relief complete") ;
	



	//cif->ReadEnviHeader (temppath,tempfile) ;


}

void CMainFrame::OnStatisticsSummary() 
{
	// TODO: Add your command handler code here
	cplotwin = new CPlotWin ;
	CRect rect ;
	rect.SetRect (100, 100, 355, 355) ;
	cplotwin->Create (NULL, "Summary Statistics : Histogram", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		rect) ;
	cplotwin->MDIActivate () ;
	
}

void CMainFrame::MessageOut(char *outstring)
{




//	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	//m_wndStatusBar ;
//	if (pStatus) {
		CString cstr = outstring ;
		m_wndStatusBar.SetPaneText (0, cstr, true) ;
//	}


}

void CMainFrame::OnSlopemap() 
{
	// TODO: Add your command handler code here
	int status, bandnum=0  ;
	char tempfile [420], temppath [420] ;
	OPENFILENAME m_ofn ;
	
	if (cif) delete cif ;
	cif = new CImageFile ; ;
	status = cif->GetFile_and_Params("H:\\harold\\stereo_aster\\peru\\stereo") ;
	if (!status) return ;
	if (cif->nbands > 1) {
		CDialog_BandSelect cdbs ;
		cdbs.SetBandsTotal (cif->nbands) ;
		cdbs.DoModal () ;
		bandnum = cdbs.m_nBandnum ;
	}

	// get shaded relief parameters 
	CTopoParams_dlg ctp_dlg ;
	status = ctp_dlg.DoModal () ;
	if (status == IDCANCEL) {
		delete cif ;
		return ;
	}


	

	if (cifout) delete cifout ;
	// set output file parameters
	cifout = new CImageFile (cif->samps, cif->lines, 3, 1, 0) ; 
	status = cifout->GetOutputFile ("H:\\harold\\stereo_aster\\peru\\stereo") ;
	CWaitCursor cwf ;
	MessageOut ("Getting input data") ;
	cif->GetData (cif->samps, cif->lines, cif->dtype, bandnum) ;
	
	MessageOut ("Allocating output data") ;
	status = cifout->AllocData (1) ;

	CTopoArray cta ;
	cta.SetParams (cif->samps, cif->lines, cif->dtype) ;
	MessageOut ("Generating shaded relief image ") ;
	cta.Calcslope (cif->rawdata, (float *) cifout->rawdata, ctp_dlg.m_nPixDim) ;
	MessageOut ("Writing to file ") ;
	cifout->WriteData () ;
	cifout->WriteHeaderFile () ;

	MessageOut ("Slope Map Generated") ;
	
	
}

void CMainFrame::ShowResFormView()
{
	// This routine is typically called after the other views are set to the 
	// main frame. This view is used to display the results of the analysis

	CMDIChildWnd *pActiveChild = MDIGetActive () ;
	CDocument *pDocument = pActiveChild->GetActiveDocument () ;
	

	// create and load up the results template
	CDocTemplate *pTemplate=((CNewestApp*)AfxGetApp())->pDocResTemplate ;
	ASSERT_VALID(pTemplate) ;
	CFrameWnd *pFrame = pTemplate->CreateNewFrame (pDocument, pActiveChild) ;
	pTemplate->InitialUpdateFrame (pFrame, pDocument) ;

	
	// activate the image view so that most of the menu is active....
	MDIActivate (pActiveChild) ;

}



void CMainFrame::ShowProfileFormView()
{
	// This routine is typically called after the other views are set to the 
	// main frame. This view is used to display the results of the analysis

	CMDIChildWnd *pActiveChild = MDIGetActive () ;
	CDocument *pDocument = pActiveChild->GetActiveDocument () ;
	

	// create and load up the results template
	CDocTemplate *pTemplate=((CNewestApp*)AfxGetApp())->pDocProfTemplate ;
	ASSERT_VALID(pTemplate) ;
	CFrameWnd *pFrame = pTemplate->CreateNewFrame (pDocument, pActiveChild) ;
	pTemplate->InitialUpdateFrame (pFrame, pDocument) ;

	
	// activate the image view so that most of the menu is active....
	MDIActivate (pActiveChild) ;

}

void CMainFrame::SetDemPtr(CImageFile)
{

}
