// TopoParams_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Newest.h"
#include "TopoParams_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTopoParams_dlg dialog


CTopoParams_dlg::CTopoParams_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTopoParams_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTopoParams_dlg)
	m_nMinVal = -10000.0f;
	m_nPixDim = 15.f;
	m_nSunAz = 90.0f;
	m_nSunElev = 38.0f;
	m_nMaxVal = 10000.0f;
	//}}AFX_DATA_INIT
}


void CTopoParams_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTopoParams_dlg)
	DDX_Text(pDX, IDC_MINVAL, m_nMinVal);
	DDV_MinMaxFloat(pDX, m_nMinVal, -1.e+009f, 1.e+009f);
	DDX_Text(pDX, IDC_PIXDIM, m_nPixDim);
	DDV_MinMaxFloat(pDX, m_nPixDim, 1.e-010f, 1.e+009f);
	DDX_Text(pDX, IDC_SUNAZ, m_nSunAz);
	DDV_MinMaxFloat(pDX, m_nSunAz, -1.e-005f, 360.f);
	DDX_Text(pDX, IDC_SUNELEV, m_nSunElev);
	DDV_MinMaxFloat(pDX, m_nSunElev, 0.f, 90.f);
	DDX_Text(pDX, IDC_MAXVAL, m_nMaxVal);
	DDV_MinMaxFloat(pDX, m_nMaxVal, -1.e+009f, 1.e+009f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTopoParams_dlg, CDialog)
	//{{AFX_MSG_MAP(CTopoParams_dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTopoParams_dlg message handlers
