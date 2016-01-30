// DIB.cpp: implementation of the DIB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Newest.h"
#include "DIB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DIB::DIB()
{	
	bi = NULL ;
	lpbih = NULL ;
	m_data = NULL ;
	m_data_orig = NULL ;
	m_data_alt = NULL ;


}



DIB::~DIB()
{ 
	if (m_data) delete [] m_data ;
	if (bi) delete bi ;
	if (m_data_orig) delete [] m_data_orig ;
	if (m_data_alt) delete [] m_data_alt ;
}

DIB::DIB(int nsamps, int nlines, BYTE *data)
{
	int pad ;
	long i,j ;
	ns = nsamps ;
	nl = nlines ;

	pad = (ns % 4) ;
	if (pad  > 0) ns += 4-pad ;
//	if (m_data) delete [] m_data ;
//	if (m_data_orig) delete [] m_data_orig ;
	m_data = new unsigned char [long(ns) * nl * 3] ;

	m_data_alt = NULL ;
	m_data_orig = new unsigned char [long(ns) * nl * 3] ;
	m_data_cur = m_data_orig ;
	for (i=0; i<nl; i++){
		for (j=0; j<nsamps; j++)
		{
			*(m_data+i*ns*3+j*3)=*(data+i*nsamps+j) ;
			*(m_data+i*ns*3+j*3+1)=*(data+i*nsamps+j) ;
			*(m_data+i*ns*3+j*3+2)=*(data+i*nsamps+j) ;
	
		}
	}
	
	long npix = ns * nl ;
	for (i=0; i<npix * 3; i++) m_data_orig [i] = m_data [i] ;
		
	bi = (LPBITMAPINFO) new unsigned char [sizeof(BITMAPINFO)] ;
	lpbih = (LPBITMAPINFOHEADER) bi ;
	lpbih->biSize = sizeof (BITMAPINFOHEADER) ;
	lpbih->biWidth = ns;
	lpbih->biHeight = nl ;
	lpbih->biPlanes = 1 ;
	lpbih->biBitCount = 24 ;
	lpbih->biCompression = BI_RGB ;
	lpbih->biSizeImage = 0 ;
	lpbih->biClrUsed = 0 ;
	lpbih->biClrImportant = 0 ;

}

DIB::DIB(int nsamps, int nlines, int nbands, BYTE *data)
{
	int ib, pad ;
	long i,j, npix_band ;
	ns = nsamps ;
	nl = nlines ;

	npix_band = long(nsamps) * nlines ;
	

	pad = (ns % 4) ;
	if (pad  > 0) ns += 4-pad ;
	m_data = new unsigned char [long(ns) * nl * 3] ;
	m_data_orig = new unsigned char [long(ns) * nl * 3] ;
	m_data_cur = m_data_orig ;
	m_data_alt = NULL ;

	for (ib=0; ib<3; ib++)
	for (i=0; i<nl; i++){
		for (j=0; j<nsamps; j++)
		{
			*(m_data+i*ns*3+j*3+ib)=*(data + npix_band * (2 - ib) + i * nsamps + j ) ;
			
	
		}
	}
	
	long npix = ns * nl ;
	for (i=0; i<npix * 3; i++) m_data_orig [i] = m_data [i] ;
		
	bi = (LPBITMAPINFO) new unsigned char [sizeof(BITMAPINFO)] ;
	lpbih = (LPBITMAPINFOHEADER) bi ;
	lpbih->biSize = sizeof (BITMAPINFOHEADER) ;
	lpbih->biWidth = ns;
	lpbih->biHeight = nl ;
	lpbih->biPlanes = 1 ;
	lpbih->biBitCount = 24 ;
	lpbih->biCompression = BI_RGB ;
	lpbih->biSizeImage = 0 ;
	lpbih->biClrUsed = 0 ;
	lpbih->biClrImportant = 0 ;

}

void DIB::AddRegion (cpm *CPM, int nsamps_data) 
{
	long i ;
	long npix_band = long (nsamps_data) * nl, index_dib, index_dem ;

	for (i=0; i<npix_band * 3; i++) m_data [i] = m_data_cur [i] ;

	for (i=0; i< nl; i++) 
	{
		for (int j=0; j< nsamps_data; j++)
		{	
			index_dib = i * ns * 3 + j * 3 ;
			index_dem = i * nsamps_data + j ;
		
			if (CPM[index_dem].crater) {
				*(m_data + index_dib) = 255 ;
				*(m_data + index_dib+2) = 255 ;
			}
			if (CPM[index_dem].rim) {
				*(m_data + index_dib) = 255 ;
				
			}
			if (CPM[index_dem].primary) {
				*(m_data + index_dib) = 255 ;
				*(m_data + index_dib+1) = 255 ;
			}
			if (CPM[index_dem].secondary) {
				
				*(m_data + index_dib+1) = 255 ;
			}

		}

	}

	return ;
}


void DIB::AddHitInfo (BYTE *inhits, int nsamps_data)  
{

	long npix_band = long (nsamps_data) * nl, index_dib, index_dem ;

	//for (long i=0; i<npix_band * 3; i++) m_data [i] = m_data_orig [i] ;

	for (int i=0; i< nl; i++) 
	{
		for (int j=0; j< nsamps_data; j++)
		{	
			index_dib = i * ns * 3 + j * 3 ;
			index_dem = i * nsamps_data + j ;
			
			if (!*(inhits + i * nsamps_data + j) ) 
			{
				*(m_data+index_dib+2) = 255 ;
			}



		}

	}

	return ;
}

void DIB::RemoveHitInfo (cpm *CPM, int nsamps_data)  
{

	long npix_band = long (nsamps_data) * nl ;

	for (long i=0; i<npix_band * 3; i++) m_data [i] = m_data_cur [i] ;

	AddRegion (CPM, nsamps_data) ;

/*
	for (i=0; i< nl; i++) 
	{
		for (int j=0; j< nsamps_data; j++)
		{	
			index_dib = i * ns * 3 + j * 3 ;
			index_dem = i * nsamps_data + j ;
		
			if (CPM[index_dem].crater) {
				*(m_data + index_dib) = 255 ;
				*(m_data + index_dib+2) = 255 ;
			}
			if (CPM[index_dem].rim) {
				*(m_data + index_dib) = 255 ;
				
			}
			if (CPM[index_dem].primary) {
				*(m_data + index_dib) = 255 ;
				*(m_data + index_dib+1) = 255 ;
			}
			if (CPM[index_dem].secondary) {
				
				*(m_data + index_dib+1) = 255 ;
			}

		}

	
	}
	
*/
	return ;
}

void DIB::SetAltShadeArray (BYTE *data, int nsamps, int nl) 
{

	int pad, i, j ;

	pad = (ns % 4) ;
	if (pad  > 0) ns += 4-pad ;
	
	if (m_data_alt) delete [] m_data_alt ;
	
	m_data_alt = new unsigned char [long(ns) * nl * 3] ;
	m_data_cur = m_data_alt ;
	for (i=0; i<nl; i++){
		for (j=0; j<nsamps; j++)
		{
			*(m_data_alt+i*ns*3+j*3)=*(data+i*nsamps+j) ;
			*(m_data_alt+i*ns*3+j*3+1)=*(data+i*nsamps+j) ;
			*(m_data_alt+i*ns*3+j*3+2)=*(data+i*nsamps+j) ;
	
		}
	}

	

}

void DIB::Reload () 
{
}