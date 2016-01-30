// Dialog_BandSelect.cpp : implementation file
//

#include "stdafx.h"
#include "Newest.h"
#include "Dialog_BandSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_BandSelect dialog


CDialog_BandSelect::CDialog_BandSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_BandSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_BandSelect)
	m_nBandnum = 0;
	maxbands = 16384 ;
	//}}AFX_DATA_INIT
}



void CDialog_BandSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_BandSelect)
	DDX_Text(pDX, IDC_EDIT1, m_nBandnum);
	DDV_MinMaxInt(pDX, m_nBandnum, 0, maxbands);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_BandSelect, CDialog)
	//{{AFX_MSG_MAP(CDialog_BandSelect)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_BandSelect message handlers

int CDialog_BandSelect::SetBandsTotal(int nb)
{
	maxbands = nb ;
	return (1) ;

}
