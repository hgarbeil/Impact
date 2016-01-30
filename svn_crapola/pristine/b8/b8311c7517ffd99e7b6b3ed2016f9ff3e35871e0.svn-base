// RGB_Dialog.cpp : implementation file
//

#include "stdafx.h"
#include "Newest.h"
#include "RGB_Dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRGB_Dialog dialog


CRGB_Dialog::CRGB_Dialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRGB_Dialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRGB_Dialog)
	m_nGband = 1;
	m_nBband = 2;
	m_nRband = 0;
	//}}AFX_DATA_INIT

	
}


void CRGB_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRGB_Dialog)
	DDX_Text(pDX, IDC_GBAND, m_nGband);
	DDV_MinMaxInt(pDX, m_nGband, 0, 16384);
	DDX_Text(pDX, IDC_IDC_BBAND, m_nBband);
	DDV_MinMaxInt(pDX, m_nBband, 0, 16384);
	DDX_Text(pDX, IDC_RBAND, m_nRband);
	DDV_MinMaxInt(pDX, m_nRband, 0, 16384);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRGB_Dialog, CDialog)
	//{{AFX_MSG_MAP(CRGB_Dialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRGB_Dialog message handlers
