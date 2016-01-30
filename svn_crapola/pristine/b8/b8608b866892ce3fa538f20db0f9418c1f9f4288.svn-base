// Results_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "newest.h"
#include "Results_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResults_dlg dialog


CResults_dlg::CResults_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResults_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResults_dlg)
	m_xmax = _T("");
	m_xmin = _T("");
	m_ymax = _T("");
	m_ymin = _T("");
	m_RimText = _T("");
	m_cratervol = _T("");
	m_Primvol = _T("");
	m_Rimvol = _T("");
	m_Secvol = _T("");
	m_outfilename = _T("Results.txt");
	//}}AFX_DATA_INIT
	outfilename = "Results.txt" ;
	m_outfilename = _T("Results.txt");
}

CResults_dlg::CResults_dlg(CView *pView)
{
	m_pView = pView ;
	outfilename = "Results.txt" ;

}

BOOL CResults_dlg::Create()
{
	return CDialog::Create (CResults_dlg::IDD, m_pView) ;
	//CDialog::Create(IDD_FITRES_DLG) ;
	



}

void CResults_dlg::update () 
{
	UpdateData (FALSE) ;
	
}

void CResults_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResults_dlg)
	DDX_Control(pDX, IDC_RIM_PROF, m_RimProfile);
	DDX_Text(pDX, IDC_XMAX, m_xmax);
	DDX_Text(pDX, IDC_XMIN, m_xmin);
	DDX_Text(pDX, IDC_YMAX, m_ymax);
	DDX_Text(pDX, IDC_YMIN, m_ymin);
	DDX_Text(pDX, IDC_RIMTEXT, m_RimText);
	DDX_Text(pDX, IDC_Cratervol, m_cratervol);
	DDX_Text(pDX, IDC_Primvol, m_Primvol);
	DDX_Text(pDX, IDC_Rimvol, m_Rimvol);
	DDX_Text(pDX, IDC_Secvol, m_Secvol);
	DDX_Text(pDX, IDC_EDIT_OUTFILE, m_outfilename);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CResults_dlg, CDialog)
	//{{AFX_MSG_MAP(CResults_dlg)
	ON_BN_CLICKED(IDC_BROWSE_OUTPUT, OnBrowseOutput)
	ON_BN_CLICKED(IDWRITEFILE, OnWritefile)
	ON_BN_CLICKED(IDC_RIM_PROF, OnRimProf)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResults_dlg message handlers

void CResults_dlg::OnBrowseOutput() 
{
	// TODO: Add your control notification handler code here
	
	CFileDialog cfd (FALSE, TEXT("*.txt"), 	m_outfilename) ;
	int status = cfd.DoModal () ;
	if (status == IDCANCEL) return ;
	m_outfilename = cfd.GetPathName () ;
	UpdateData (FALSE) ;


}

void CResults_dlg::OnWritefile() 
{
	// TODO: Add your control notification handler code here
	m_pView->PostMessage (WM_WRITE_FILE, IDOK) ;
}


void CResults_dlg::OnRimProf() 
{
	// TODO: Add your control notification handler code here
	UpdateData (FALSE) ;
	
}
