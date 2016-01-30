// Fitres_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Newest.h"
#include "Fitres_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFitres_dlg dialog


CFitres_dlg::CFitres_dlg(CWnd* pParent /*=NULL*/)
: CDialog(CFitres_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFitres_dlg)
	m_FitResults = _T("");
	//}}AFX_DATA_INIT
	
}

CFitres_dlg::CFitres_dlg (CView *pView) 
{
	
	//{{AFX_DATA_INIT(CFitres_dlg)
	m_FitResults = _T("");
	//}}AFX_DATA_INIT
	
	m_pView = pView ;
}

void CFitres_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFitres_dlg)
	DDX_Text(pDX, IDC_FITRESULTS, m_FitResults);
	DDV_MaxChars(pDX, m_FitResults, 50000);
	//}}AFX_DATA_MAP
	
}


BEGIN_MESSAGE_MAP(CFitres_dlg, CDialog)
	//{{AFX_MSG_MAP(CFitres_dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFitres_dlg message handlers

BOOL CFitres_dlg::Create()
{
	return CDialog::Create (CFitres_dlg::IDD,m_pView) ;
	//CDialog::Create(IDD_FITRES_DLG) ;
	

}

CFitres_dlg::~CFitres_dlg()
{
	DestroyWindow () ;

}
