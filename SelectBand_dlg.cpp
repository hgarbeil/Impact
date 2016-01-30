// SelectBand_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Newest.h"
#include "SelectBand_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectBand_dlg dialog


CSelectBand_dlg::CSelectBand_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectBand_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectBand_dlg)
	m_nBand = 0;
	//}}AFX_DATA_INIT
}


void CSelectBand_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectBand_dlg)
	DDX_Text(pDX, IDC_Bandselect, m_nBand);
	DDV_MinMaxInt(pDX, m_nBand, 0, 16384);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectBand_dlg, CDialog)
	//{{AFX_MSG_MAP(CSelectBand_dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectBand_dlg message handlers
