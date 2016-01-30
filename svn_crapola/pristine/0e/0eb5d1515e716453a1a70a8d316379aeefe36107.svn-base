// FileSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "newest.h"
#include "FileSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSelectDlg dialog


CFileSelectDlg::CFileSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileSelectDlg)
	m_AnalFile = _T("");
	m_FeatFile = _T("");
	m_SurfFile = _T("");
	m_TabFile =  _T("");
	//}}AFX_DATA_INIT
}


void CFileSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSelectDlg)
	DDX_Text(pDX, IDC_ANALYSISFILE, m_AnalFile);
	DDX_Text(pDX, IDC_FEATUREFILE, m_FeatFile);
	DDX_Text(pDX, IDC_SURFACEFILE, m_SurfFile);
	DDX_Text(pDX, IDC_TABFILE, m_TabFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CFileSelectDlg)
	ON_BN_CLICKED(IDC_BUTTON_STATSELECT, OnButtonStatselect)
	ON_BN_CLICKED(IDC_BUTTON_FEATURESELECT, OnButtonFeatureselect)
	ON_BN_CLICKED(IDC_BUTTON_ANALYSISSELECT, OnButtonAnalysisselect)
	ON_BN_CLICKED(IDC_BROWSE_TABFILE, OnBrowseTabfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSelectDlg message handlers

void CFileSelectDlg::OnButtonStatselect() 
{
	// TODO: Add your control notification handler code here
	OPENFILENAME lpofn ;
	lpofn.lpstrInitialDir =(m_SurfFile) ;
	CFileDialog cfd (FALSE, _T("*.txt"), m_SurfFile) ;
	int status = cfd.DoModal () ;
	if (status == IDCANCEL) return ;
	else m_SurfFile = cfd.GetPathName () ;
	UpdateData (FALSE) ;
}

void CFileSelectDlg::OnButtonFeatureselect() 
{
	// TODO: Add your control notification handler code here
	OPENFILENAME lpofn ;
	lpofn.lpstrInitialDir =(m_FeatFile) ;
	CFileDialog cfd (FALSE, _T("*.txt"), m_FeatFile) ;
	int status = cfd.DoModal () ;
	if (status == IDCANCEL) return ;
	else m_FeatFile = cfd.GetPathName () ;
	UpdateData (FALSE) ;
}

void CFileSelectDlg::OnButtonAnalysisselect() 
{
	// TODO: Add your control notification handler code here
	OPENFILENAME lpofn ;
	lpofn.lpstrInitialDir =(m_AnalFile) ;
	CFileDialog cfd (FALSE, _T("*.txt"), m_AnalFile) ;
	int status = cfd.DoModal () ;
	if (status == IDCANCEL) return ;
	else m_AnalFile = cfd.GetPathName () ;

	UpdateData (FALSE) ;
	
}

void CFileSelectDlg::OnBrowseTabfile() 
{
	// TODO: Add your control notification handler code here
	OPENFILENAME lpofn ;
	lpofn.lpstrInitialDir =(m_TabFile) ;
	CFileDialog cfd (FALSE, _T("*.txt"), m_TabFile) ;
	int status = cfd.DoModal () ;
	if (status == IDCANCEL) return ;
	else m_TabFile = cfd.GetPathName () ;
	UpdateData (FALSE) ;
	
}
