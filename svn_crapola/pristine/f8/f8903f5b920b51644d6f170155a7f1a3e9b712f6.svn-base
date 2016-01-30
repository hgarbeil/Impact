// Displayscale_dialog.cpp : implementation file
//

#include "stdafx.h"
#include "Newest.h"
#include "Displayscale_dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayscale_dialog dialog


CDisplayscale_dialog::CDisplayscale_dialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDisplayscale_dialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDisplayscale_dialog)
	m_nUsersel = 1 ;
	m_nVal = 0 ;
	useVal = 1 ;
	useUser = 1 ;
	m_bandstring = _T("0");
	m_nMaxString = _T("255");
	m_nMinString = _T("0");
	//}}AFX_DATA_INIT
}


void CDisplayscale_dialog::DoDataExchange(CDataExchange* pDX)
{

	
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisplayscale_dialog)
	DDX_Radio(pDX, IDC_USER_MNMX, m_nUsersel);
	DDX_Radio(pDX, IDC_VAL, m_nVal);
	DDX_Text(pDX, IDC_BANDS, m_bandstring);
	DDV_MaxChars(pDX, m_bandstring, 320);
	DDX_Text(pDX, IDC_MAXVAL, m_nMaxString);
	DDV_MaxChars(pDX, m_nMaxString, 240);
	DDX_Text(pDX, IDC_MINVAL, m_nMinString);
	DDV_MaxChars(pDX, m_nMinString, 240);
	//}}AFX_DATA_MAP

	if (m_nVal) useVal = 0 ;
	else useVal = 1 ;
	if (m_nUsersel) useUser = 0 ;
	else useUser = 1 ;
	/*
	
	*/
	//TRACE ("use User is %s\n", bandstr) ;
	
}


BEGIN_MESSAGE_MAP(CDisplayscale_dialog, CDialog)
	//{{AFX_MSG_MAP(CDisplayscale_dialog)
	ON_BN_CLICKED(IDC_RADIO9, OnPercent)
	ON_BN_CLICKED(IDC_VAL, OnVal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayscale_dialog message handlers

int CDisplayscale_dialog::InitForByte()
{
	char cbuf [240] ;
	m_nUsersel = 0 ;
	m_nVal = 0 ;
	m_nMin [0] = 0 ;
	m_nMax [0] = 255 ;
	nbands = 1 ;

	sprintf (cbuf, "%d", m_nMin [0]) ;
	m_nMinString = cbuf ;
	sprintf (cbuf, "%d", m_nMax [0]) ;
	m_nMaxString = "255" ;

	bandarr [0] = 0 ;
	m_bandstring = ("0") ;

	return (1) ;
}


void CDisplayscale_dialog::OnPercent() 
{
	// TODO: Add your control notification handler code here
	char cbuf []  = "96" ;
	m_nMin [0] = 4 ;
	m_nMax [0] = 96 ;

	SendDlgItemMessage (IDC_MAXVAL, WM_SETTEXT, 0, (LONG) (LPSTR) cbuf) ;
	strcpy (cbuf, "4") ;
	SendDlgItemMessage (IDC_MINVAL, WM_SETTEXT, 0, (LONG) (LPSTR) cbuf) ;
}

CDisplayscale_dialog::~CDisplayscale_dialog()
{
	

}

void CDisplayscale_dialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

int CDisplayscale_dialog::ParseData()
{
	char	bandstr [240], *token, *token1, *token2 ;
	strcpy (bandstr,  m_bandstring) ;
		bandarr [0] = strtol (bandstr, &token,10) ;
		m_nMin [0] = strtod (m_nMinString, &token1) ;
		m_nMax [0] = strtod (m_nMaxString, &token2) ;
	if (nbands > 1)  {
		if (token == NULL) bandarr [1] = bandarr [0] ;
		else 
		bandarr [1] = strtol (token, &token,10) ;
		if (token == NULL) bandarr [2] = bandarr [1] ;
		else 
		bandarr [2] = strtol (token, &token,10) ;


		if (token1 == NULL) m_nMin [1] = m_nMin [0] ;
		else 
			m_nMin [1] = strtod (token1, &token1) ;
		if (token1 == NULL) m_nMin[2] = m_nMin [1] ;
		else 
			m_nMin [2] = strtod (token1, &token1) ;

		if (token2 == NULL) m_nMax [1] = m_nMax [0] ;
		else 
			m_nMax [1] = strtod (token2, &token2) ;
		if (token2 == NULL) m_nMax[2] = m_nMax [1] ;
		else 
			m_nMax [2] = strtod (token2, &token2) ;
		
	}

	return (nbands) ;
}

int CDisplayscale_dialog::SetBands(int nb, int *bands)
{
	int  i ;
	char cbuf [240] ;
	nbands = nb ;
	for (i=0; i<nb; i++) {
		bandarr[i] = bands [i] ;
	}
	if (nb == 1) sprintf (cbuf , "%d", bandarr[i]) ;
	if (nb==3) sprintf (cbuf, "%d %d %d", bandarr[0], bandarr[1], bandarr[2]) ;

	m_bandstring = cbuf ;
	return (nb) ;
}


void CDisplayscale_dialog::OnVal() 
{
	// TODO: Add your control notification handler code here
		char cbuf []  = "255" ;
	m_nMin [0] = 0 ;
	m_nMax [0] = 255 ;

	SendDlgItemMessage (IDC_MAXVAL, WM_SETTEXT, 0, (LONG) (LPSTR) cbuf) ;
	strcpy (cbuf, "0") ;
	SendDlgItemMessage (IDC_MINVAL, WM_SETTEXT, 0, (LONG) (LPSTR) cbuf) ;
	
}
