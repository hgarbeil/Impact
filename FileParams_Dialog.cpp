// FileParams_Dialog.cpp : implementation file
//

#include "stdafx.h"
#include "Newest.h"
#include "FileParams_Dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileParams_Dialog dialog


 CFileParams_Dialog::CFileParams_Dialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFileParams_Dialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileParams_Dialog)
	m_BFORM = _T("");
	m_nbands = 0;
	m_dtype = _T("");
	m_Filename = _T("");
	m_samps = 0;
	m_lines = 0;
	//}}AFX_DATA_INIT
}


void CFileParams_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileParams_Dialog)
	DDX_CBString(pDX, IDC_BFORM, m_BFORM);
	DDV_MaxChars(pDX, m_BFORM, 12);
	DDX_Text(pDX, IDC_BANDS, m_nbands);
	DDV_MinMaxInt(pDX, m_nbands, 0, 8192);
	DDX_CBString(pDX, IDC_DTYPE, m_dtype);
	DDV_MaxChars(pDX, m_dtype, 12);
	DDX_Text(pDX, IDC_FILENAME, m_Filename);
	DDV_MaxChars(pDX, m_Filename, 440);
	DDX_Text(pDX, IDC_SAMPS, m_samps);
	DDV_MinMaxInt(pDX, m_samps, 0, 16384);
	DDX_Text(pDX, IDC_LINES, m_lines);
	DDV_MinMaxInt(pDX, m_lines, 0, 8192);
	//}}AFX_DATA_MAP

	if (!strcmp("BSQ", m_BFORM)) bform = 0 ;
	if (!strcmp("BIL", m_BFORM)) bform = 1 ;
	if (!strcmp("BIP", m_BFORM)) bform = 2 ;

	if (!strcmp("BYTE", m_dtype)) dt = 0 ;
	if (!strcmp("SHORT INT", m_dtype)) dt = 1 ;
	if (!strcmp("INT", m_dtype)) dt = 2 ;
	if (!strcmp("FLOAT", m_dtype)) dt = 3 ;
	if (!strcmp("COMPLEX", m_dtype)) dt = 4 ;


}


BEGIN_MESSAGE_MAP(CFileParams_Dialog, CDialog)
	//{{AFX_MSG_MAP(CFileParams_Dialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileParams_Dialog message handlers

int CFileParams_Dialog::SetDefaults(char *filename, char *dt, char *bf)
{
	m_Filename = filename ;
	m_dtype = dt ;
	m_BFORM = bf ; 

	return (1) ;
}

//DEL int CFileParams_Dialog::WriteHdrFile(int ns, int nl, int nb, int dt, int bform)
//DEL {
//DEL 
//DEL }
