// CraterID_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "newest.h"
#include "CraterID_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCraterID_Dlg dialog


CCraterID_Dlg::CCraterID_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCraterID_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCraterID_Dlg)
	m_CraterID = _T("");
	//}}AFX_DATA_INIT
}


void CCraterID_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCraterID_Dlg)
	DDX_Text(pDX, IDC_CRATERID_EDIT, m_CraterID);
	DDV_MaxChars(pDX, m_CraterID, 400);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCraterID_Dlg, CDialog)
	//{{AFX_MSG_MAP(CCraterID_Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCraterID_Dlg message handlers
