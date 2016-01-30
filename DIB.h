// DIB.h: interface for the DIB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__D34411B1_B232_4FA0_9ED1_BFCAE960CB9D__INCLUDED_)
#define AFX_DIB_H__D34411B1_B232_4FA0_9ED1_BFCAE960CB9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageFile.h"

class DIB  
{
public:
	BYTE *m_data, *m_data_orig, *m_data_cur, *m_data_alt ;
	DIB (int ns, int nl, BYTE *data);
	DIB (int ns, int nl, int nb, BYTE *data);
	
	DIB();
	virtual ~DIB();
	HPALETTE			m_hPalette ;
	LPBITMAPINFO		bi ;
	LPBITMAPINFOHEADER lpbih ;

	void AddRegion (cpm *, int ns) ;
	void RemoveHitInfo (cpm *, int ns) ;
	void AddHitInfo (BYTE *inhits, int nsamps) ;
	void Reload () ;

	void SetAltShadeArray (BYTE *bdata_arr, int ns, int nl) ;
	// dimensions 
	int				nl ;
	int				ns ;


};

#endif // !defined(AFX_DIB_H__D34411B1_B232_4FA0_9ED1_BFCAE960CB9D__INCLUDED_)
