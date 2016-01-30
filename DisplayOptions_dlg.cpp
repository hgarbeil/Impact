// DisplayOptions_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Newest.h"
#include "DisplayOptions_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayOptions_dlg dialog


CDisplayOptions_dlg::CDisplayOptions_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDisplayOptions_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDisplayOptions_dlg)
	m_nMax = 1.E6;
	m_nMin = -1.E6;
	//}}AFX_DATA_INIT
}


void CDisplayOptions_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisplayOptions_dlg)
	DDX_Text(pDX, IDC_VAL_MAX, m_nMax);
	DDV_MinMaxFloat(pDX, m_nMax, -1.e+009f, 1.e+009f);
	DDX_Text(pDX, IDC_VAL_MIN, m_nMin);
	DDV_MinMaxFloat(pDX, m_nMin, -1.e+009f, 1.e+009f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDisplayOptions_dlg, CDialog)
	//{{AFX_MSG_MAP(CDisplayOptions_dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayOptions_dlg message handlers
