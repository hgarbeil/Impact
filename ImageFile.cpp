// ImageFile.cpp: implementation of the CImageFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Newest.h"
#include "ImageFile.h"
#include <iostream>
#include <fstream> 
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageFile::CImageFile()
{
		lines = 0 ;
		samps = 0 ;
		nbands = 1 ;
		dtype = 0 ;
		bform = 0 ;
		data = NULL ;
		rawdata = NULL ;
		maskarr = NULL ;
		bpp [0] = 1 ;
		bpp [1] = 2 ;
		bpp [2] = 3 ;
		bpp [3] = 4 ;
		CPM = NULL ;
		
}

CImageFile::CImageFile(int ns, int nl, int dt, int nb, int bf)
{
		lines = nl ;
		samps = ns ;
		nbands = nb ;
		dtype = dt ;
		bform = bf ;
		data = NULL ;
		rawdata = NULL ;
		maskarr = NULL ;
		bpp [0] = 1 ;
		bpp [1] = 2 ;
		bpp [2] = 3 ;
		bpp [3] = 4 ;
		CPM = NULL ;
		

}

void CImageFile::SetParams(int ns, int nl, int dt, int nb, int bf)
{
		lines = nl ;
		samps = ns ;
		nbands = nb ;
		dtype = dt ;
		bform = bf ;
		
}


CImageFile::~CImageFile()
{

		if (data) delete [] data ;
		if (rawdata) delete [] rawdata ;
		if (maskarr) delete [] maskarr ;
		if (CPM) delete [] CPM ;
}

int CImageFile::ReadEnviHeader(char *pathname, char *flname)
{

	
	
	cfo.ReadEnviHeader (pathname) ;
	lines = cfo.lines ;
	samps = cfo.samps ;
	dtype = cfo.dtype ;
	nbands = cfo.bands ;
	bform = cfo.bform ;
	strcpy (filename, cfo.filename) ;

	for (int i=0; i<4; i++) grid_ll [i] = cfo.grid_ll [i] ;


	return (0) ;
}

int CImageFile::ReadEnviHeader(char *pathname)
{

	
	
	cfo.ReadEnviHeader (pathname) ;
	lines = cfo.lines ;
	samps = cfo.samps ;
	dtype = cfo.dtype ;
	nbands = cfo.bands ;
	bform = cfo.bform ;
	strcpy (filename, cfo.filename) ;

	for (int i=0; i<4; i++) 
		grid_ll [i] = cfo.grid_ll [i] ;

	/*
	ifstream ifil (flname, ios::in) ;
	newtoken = strstr(pathname,".hdr") ;

	
	strncpy (filename, pathname, newtoken-pathname) ; 
	strcpy (filename + (newtoken-pathname), "") ;
	

	while (!ifil.eof()){

		ifil.getline (linedat, 440, '\n') ;
		if (strlen (linedat) < 2 && ifil.eof()) break ;
		token = strtok (linedat, "=") ;
			// find the issues of concern
		
		if (!strncmp (token, "samp", 4)) {
			token = strtok (NULL, "=") ;
			samps = atoi (token) ;	
		}
		
		if (!strncmp (token, "line", 4)) {
			token = strtok (NULL, "=") ;
			lines = atoi (token) ;	
		}

		if (!strncmp (token, "bands", 5)) {
			token = strtok (NULL, "=") ;
			nbands = atoi (token) ;	
		}
	
		//TRACE ("%s\n", linedat) ;
	}
	ifil.close() ;
	*/


	return (0) ;
}

int CImageFile::ReadDDR(char *filename)
{
	char linedat [440] ;
	ifstream ifil (filename, ios::in) ;
	
	while (!ifil.eof()){

		ifil.getline (linedat,440) ;
	
		TRACE ("%s\n", linedat) ;
	}


	return (0) ;
}

int CImageFile::GetData () 
{
	int  bandnum = 0 ;
	long nbytes_read ;
	bytesperpixel = bpp [dtype] ;
	bytesperband = long(samps) * lines * bytesperpixel ;
	//bytesperband = 100000 ;
	if (rawdata) delete rawdata ;
	rawdata = new unsigned char [bytesperband] ;

	CFile cf (filename, CFile::modeRead) ;
	nbytes_read = cf.Read (rawdata, samps * lines * bytesperpixel) ;
	cf.Close () ;
		
	TRACE ("Number of bytes read are %d\n", nbytes_read) ;
	
	return (1) ;
}


void CImageFile::DefMask () 
{
	long is ;
	if (maskarr)  delete [] maskarr ;
	maskarr = new unsigned char [samps * lines] ;

	for (is=0; is<samps * lines; is++) maskarr [is] = 0 ;

	if (CPM) delete [] CPM ;
	CPM = new Crater_pixmask [samps * lines] ;
	for (is=0; is<samps * lines; is++) {
		CPM[is].crater = 0 ;
		CPM[is].rim = 0 ;
		CPM[is].primary = 0 ;
		CPM[is].secondary = 0 ;
	}
	return  ;
}


int CImageFile::GetData(int ns, int nl, int dt, int bandnum)
{
	int nbytes_read ;
	bytesperpixel = bpp [dt] ;
	bytesperband = long(ns) * nl * bytesperpixel ;
	if (rawdata) delete rawdata ;
	rawdata = new unsigned char [ns * nl * bytesperpixel] ;

	CFile cf (filename, CFile::modeRead) ;
	cf.Seek(long(ns) * nl * bandnum * bytesperpixel, 0) ;
	nbytes_read = cf.Read (rawdata, ns * nl * bytesperpixel) ;
	cf.Close () ;
		
	TRACE ("Number of bytes read are %d\n", nbytes_read) ;
	
	return (1) ;
}


int CImageFile::GetData_3(int ns, int nl, int dt, int nb, int *bandarr)
{
	int nbytes_read ;
	//long bytesperband ;
	bytesperpixel = bpp [dt] ;
	
	// nb should always be 3 
	CFile cf (filename, CFile::modeRead) ;
	data = new unsigned char [ns * nl * nb] ;

	bytesperband = long(ns) * nl * bytesperpixel ;
	
	for (int ib=0; ib<nb; ib++) {
		cf.Seek (bytesperband * *(bandarr + ib), 0) ;
		nbytes_read = cf.Read (data + ib * bytesperband, bytesperband) ;
	}
	cf.Close () ;
	
	TRACE ("Number of bytes read are %d\n", nbytes_read) ;
	return (1) ;
}

int CImageFile::GetFile_and_Params(char *searchdir)
{
	int				status ;
	char			tempfile[420], temppath[420] ;
	OPENFILENAME	m_ofn ;


	m_ofn.lpstrInitialDir = searchdir ;
	
	static char BASED_CODE szFilter[] = "Header Files (*.hdr)|*.hdr||All Files (*.*)|*.*||";
	CFileDialog cfd (true, NULL, NULL, NULL, szFilter, NULL) ;
	cfd.m_ofn.lpstrInitialDir = searchdir ;
	status = cfd.DoModal() ;
	if (status == IDCANCEL) {
		MessageOut ("User canceled file selection ") ;
		return (0) ;
	}
		
	strcpy (tempfile, cfd.GetFileName() ) ;
	strcpy (temppath, cfd.GetPathName() ) ;
	if (strcmp (cfd.GetFileExt(), "hdr")) {
		MessageOut ("A *.hdr file  is required, create one please") ;
		return (0) ;
	}

	ReadEnviHeader (temppath, tempfile) ;

	

	return (1) ;
}

void CImageFile::MessageOut(char *stringout)
{

	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd ;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar ;
	if (pStatus) {
		CString cstr = stringout ;
		pStatus->SetPaneText (0, cstr, true) ;
	}

}


int CImageFile::GetOutputFile(char *searchdir)
{
	int				status ;
	char			 temppath[420],  *newtoken ; ;
//	OPENFILENAME	m_ofn ;



	
	static char BASED_CODE szFilter[] = "Header Files (*.hdr)|*.hdr||All Files (*.*)|*.*||";
	CFileDialog cfd (false, NULL, NULL, NULL, szFilter, NULL) ;
	cfd.m_ofn.lpstrInitialDir = searchdir ;
	status = cfd.DoModal() ;
	if (status == IDCANCEL) {
		MessageOut ("User canceled file selection ") ;
		return (0) ;
	}

	strcpy (temppath, cfd.GetPathName()) ;
	
	 
	
	
	newtoken = strstr(temppath,".hdr") ;

	
	strncpy (filename, temppath, newtoken-temppath) ; 
	strcpy (filename + (newtoken-temppath), "") ;
	
	/*	
	strcpy (tempfile, cfd.GetFileName() ) ;
	strcpy (temppath, cfd.GetPathName() ) ;
	if (strcmp (cfd.GetFileExt(), "hdr")) {
		MessageOut ("A *.hdr file  is required, create one please") ;
		return (0) ;
	}
	*/
	//ReadEnviHeader (temppath, tempfile) ;

	return (0) ;
}

int CImageFile::AllocData (int nb) {

	if (rawdata) delete [] rawdata ;

	bytesperband = samps * lines * bpp [dtype]  ;
	rawdata = new unsigned char [bytesperband] ;
	if (rawdata == NULL) return (0) ;
	return (1) ;
}
	

int CImageFile::WriteHeaderFile()
{
	char hdrfile [420] ;
	strcpy (hdrfile, filename) ;
	strcat (hdrfile, ".hdr") ;

	cfo.WriteHdrFile (hdrfile, samps, lines, nbands, dtype, bform) ;
	return (1) ;

}

int CImageFile::WriteData()
{
	

	CFile cf (filename, CFile::modeCreate | CFile::modeWrite) ;
	cf.Write (rawdata, samps * lines * bpp[dtype]) ;
	cf.Close () ;
		
	//TRACE ("Number of bytes written are %d\n", nbytes_write) ;
	
	return (1) ;
}

float CImageFile::GetVal (int x, int y) 
{
	unsigned char *rdata ;
	short *sptr ;
	int   *iptr ;
	float *fptr ;

	float fval ;
	bytesperpixel = bpp [dtype] ;
	
	rdata = rawdata + bytesperpixel * y * samps + bytesperpixel * x ;
	switch (dtype) {
	case 0 :
		fval = (float) *(rdata) ;
		break ;
	case 1 :
		sptr =  ((short *) (rdata)) ;
		fval = float (*sptr) ;
		break ;
	case 2 :
		iptr = ((int *) (rdata)) ;
		fval = float (*iptr) ;
		break ;
	case 3 :
		fptr =  ((float*) (rdata)) ;
		fval = *fptr ;
		break ;
	}
	return fval ;
}

void CImageFile::LoadSurfCoefs (float *scoefs) 
{
	for (int i=0; i<6; i++) 
		coefs [i] = scoefs [i] ;

}
void CImageFile::LoadSurfCoefs (double *scoefs) 
{
	for (int i=0; i<6; i++) 
		coefs [i] = (float) scoefs [i] ;

}


float CImageFile::GetVal_Corr (int x, int y) 
{
	unsigned char *rdata ;
	short *sptr ;
	int   *iptr ;
	float *fptr, corrval ;

	float fval ;
	bytesperpixel = bpp [dtype] ;

	float xval = x ;
	float yval = y ;
	corrval = coefs [0] + coefs [1] * xval + coefs [2] * yval + coefs [3] *
		xval * yval + coefs [4] * xval * xval + coefs [5] * yval * yval ;
	
	rdata = rawdata + bytesperpixel * y * samps + bytesperpixel * x ;
	switch (dtype) {
	case 0 :
		fval = (float) *(rdata) ;
		break ;
	case 1 :
		sptr =  ((short *) (rdata)) ;
		fval = float (*sptr) ;
		break ;
	case 2 :
		iptr = ((int *) (rdata)) ;
		fval = float (*iptr) ;
		break ;
	case 3 :
		fptr =  ((float*) (rdata)) ;
		fval = *fptr ;
		break ;
	}
	return (fval-corrval)  ;
}





 float CImageFile::CalcCraterVolume(POINT *rimpts, int npts)
{

	int		i, j ;
	long	npixel=0, npixel_in=0 ;
	float	zcorr, medval ;
	double	total=0., minval = 1.E9, maxval = -1.E9, minval_all= 1.E9, total_all=0. ;
	double  maxval_all = -1.E9 ;
	
	CRgn    crgn_rim ;
	crgn_rim.CreatePolygonRgn (rimpts, npts, ALTERNATE) ;
	// variables for calculating the centroid region
	long	xlocTot, ylocTot ;
	long	il, *histo, cumtot, nhist_bins, index ;
	long	npix = long(samps) * lines ;
	for (long is=0; is<npix; is++) CPM [is].crater = 0 ;

	xlocTot = 0 ;
	ylocTot = 0 ;
	for (i=0; i<lines; i++)
		for (j=0; j<samps; j++) 
		{

			if (crgn_rim.PtInRegion(j, i)) {
				npixel++ ;
				xlocTot += j ;
				ylocTot += i ;
			//	zval = GetVal (j, i) ;
				zcorr = GetVal_Corr (j, i) ;
				total_all += zcorr ;
				if (zcorr<minval_all) minval_all = zcorr ;
				if (zcorr>maxval_all) maxval_all = zcorr ;
				
				if (zcorr < 0.) {
					if (zcorr < minval) minval = zcorr ;
					if (zcorr > maxval) maxval = zcorr ;
					npixel_in++ ;
					total += zcorr ;
					maskarr [i * samps + j] |= 1 ;
					CPM[i * samps + j].crater = 1 ;
				}
				
			}
		}

		// get the centroid x and y location
		xlocTot /= npixel ;
		ylocTot /= npixel ;



		// now make a histogram to get the median
		nhist_bins = maxval_all - minval_all + 1 ;
		if (nhist_bins == 1 || npixel_in == 0) medval = maxval ;
		else {
			histo = new long [nhist_bins] ;
			for (il=0; il<nhist_bins; il++) histo[il]=0 ;

			for (i=0; i<lines; i++)
				for (j=0; j<samps; j++) 
				{

				if (crgn_rim.PtInRegion(j, i)) {
					zcorr = GetVal_Corr (j, i) ;
					
					index = int (zcorr - minval_all) ;
						histo [index]++ ;
				}	
				
				}
		

		cumtot = 0 ;
		for (il=0; il<nhist_bins && cumtot <= (npixel /2); il++) 
		{
			cumtot += histo [il] ;
		}

		medval = minval_all + il ;
		delete [] histo ;
		}	
						

		// volume based on pixels below only
		cnd->ctr_vol = total ;
		// depths are relative to reference surface
		// pmm wants them reported relative to avg rim height
		cnd->ctr_ave_depth = total / npixel_in ;
		cnd->ctr_ave_depth_all = total_all / npixel ;
		cnd->ctr_max_depth_all = minval_all ;

		// npixel is the total number of pixels within the rim outline
		// npixel_in is the number of pixels below reference surface
		// area based upon all pixels, but volume based on all pixels
		cnd->ctr_npix = npixel_in ;
		cnd->ctr_npix_above = npixel- npixel_in ;
		cnd->ctr_max_depth = minval ;

		// area based on all pixels
		cnd->ctr_area = npixel ;
		cnd->centroid_x = (int)xlocTot ;
		cnd->centroid_y = (int)ylocTot ;

		
		// diameter is based on the total number of pixels
		cnd->ctr_diam = 2. * sqrt(npixel * cnd->pixsize/ 3.14159265) ;
		cnd->ctr_median_depth = medval ;
		
		
		DeleteObject (&crgn_rim) ;
		return (float(total)) ; 
}
				

float CImageFile::CalcRimVolume(POINT *inn_prime, int npts)
{

	int		i, j, npix = 0, npix_in = 0 ;
	float	zcorr, maxval = -1E9, minval = 1.E9, medval ;
	double	total=0.  ;
	CRgn crgn_rim ;
	crgn_rim.CreatePolygonRgn (inn_prime, npts, ALTERNATE) ;

	// we use all points within the boundary not worrying about whether 
	// it was marked as a crater point since we are making a distinction
	// between whether the pixel is above surrounding surface or not.
	
	for (long is=0; is<long (samps* lines); is++) CPM [is].rim = 0 ;
	long	il, *histo, cumtot, nhist_bins, index ;

	for (i=0; i<lines; i++)
		for (j=0; j<samps; j++) 
		{

			if (crgn_rim.PtInRegion(j, i)) {
				npix++ ;
				//	zval = GetVal (j, i) ;
				zcorr = GetVal_Corr (j, i) ;
				
				if (zcorr > 0.) {
					if (zcorr > maxval) maxval = zcorr ;
					if (zcorr < minval) minval = zcorr ;
					npix_in++ ;
					total += zcorr ;
					maskarr [i * samps + j] |= 2 ;
					CPM [i * samps + j].rim = 1 ;
				}
				
			}
		}

		nhist_bins = maxval - minval + 1 ;
		if (nhist_bins == 1 || npix_in == 0) medval = maxval ;
		else {
			histo = new long [nhist_bins] ;
			for (il=0; il<nhist_bins; il++) histo[il]=0 ;

			for (i=0; i<lines; i++)
				for (j=0; j<samps; j++) 
				{

				if (crgn_rim.PtInRegion(j, i)) {
					zcorr = GetVal_Corr (j, i) ;
					if (zcorr >0.) {
						index = int (zcorr - minval) ;
						histo [index]++ ;
					}
				}
				}
		

		cumtot = 0 ;
		for (il=0; il<nhist_bins && cumtot <= (npix_in /2); il++) 
		{
			cumtot += histo [il] ;
		}

		medval = minval + il ;
		delete [] histo ;
		}	

		
		
		
		
		cnd->rim_vol = total ;
		cnd->rim_avg = total / npix_in ;
		cnd->rim_median = medval ;
		cnd->rim_npix = npix_in ;
		cnd->rim_npix_below = npix - npix_in ;
		cnd->rim_max = maxval ;
		cnd->rim_min = minval ;
		cnd->rim_diam = 2. * sqrt(npix  / 3.14159265) ;


		DeleteObject (crgn_rim) ;
		
		return (float(total)) ; 
}


float CImageFile::CalcPrimaryVolume(POINT *prime_sec, int npts)
{

	int		i, j ;
	long    npix_below=0, npix_above=0;
	float	zcorr, maxval = -1E9, minval=1.E9, medval ;
	double	total=0.  ;
	CRgn crgn_prime ;
	crgn_prime.CreatePolygonRgn (prime_sec, npts, ALTERNATE) ;

	
	for (long is=0; is<long(samps)* lines; is++) CPM [is].primary = 0 ;
	long	il, *histo, cumtot, nhist_bins, index, index_histo ;

	for (i=0; i<lines; i++)
		for (j=0; j<samps; j++) 
		{
			index = i * samps + j ;
			if (crgn_prime.PtInRegion(j, i)) {
				if (CPM[index].rim || CPM[index].crater) continue ;
				//	zval = GetVal (j, i) ;
				zcorr = GetVal_Corr (j, i) ;
				if (zcorr < 0.) {
					npix_below++ ;
				}
				if (zcorr > 0.) {
					npix_above ++ ;
					if (zcorr>maxval ) maxval = zcorr ;
					if (zcorr <minval) minval = zcorr ;
					total += zcorr ;
					maskarr [i * samps + j] |= 2 ;
					CPM [index].primary = 1 ;
				}
				
			}
		}

		nhist_bins = maxval - minval + 1 ;
		if (nhist_bins == 1 || npix_above == 0) medval = maxval ;
		else {
			histo = new long [nhist_bins] ;
			for (il=0; il<nhist_bins; il++) histo[il]=0 ;

			for (i=0; i<lines; i++)
				for (j=0; j<samps; j++) 
				{
				index = i * samps + j ;
				if (crgn_prime.PtInRegion(j, i)) {
					if (CPM[index].rim || CPM[index].crater) continue ;
					zcorr = GetVal_Corr (j, i) ;
					
					if (zcorr >0. && CPM [index].rim ==0) {
						index_histo = int (zcorr - minval) ;
						histo [index_histo]++ ;
					}
				}
				}
		

		cumtot = 0 ;
		for (il=0; il<nhist_bins && cumtot <= (npix_above /2); il++) 
		{
			cumtot += histo [il] ;
		}

		medval = minval + il ;
		delete [] histo ;
		}	
		
		primary_volume = total ;

		cnd->inner_avg = total / npix_above ;
		cnd->inner_median = medval ;
		cnd->inner_vol = total ;
		cnd->inner_max = maxval ;
		cnd->inner_min = minval ;
		cnd->inner_npix = npix_above ;
		cnd->inner_npix_below = npix_below ;
		cnd->inner_npix_all = npix_above + npix_below ;
		DeleteObject (crgn_prime) ;
		
		return (float(total)) ; 
}
		

float CImageFile::CalcSecondaryVolume(POINT *sec, int npts)
{

	int		i, j ;
	long    npix_above=0, npix_below =0;
	float	zcorr, maxval = -1E9, minval = 1.E9, medval ;
	double	total=0.  ;
	CRgn crgn_sec ;
	crgn_sec.CreatePolygonRgn (sec, npts, ALTERNATE) ;

	
	for (long is=0; is<long (samps) * lines; is++) CPM [is].secondary = 0 ;
	long	il, *histo, cumtot, nhist_bins, index, index_histo ;

	for (i=0; i<lines; i++)
		for (j=0; j<samps; j++) 
		{
			index = i * samps + j ;
			if (crgn_sec.PtInRegion(j, i)) {
				if (CPM[index].rim || CPM[index].crater || CPM[index].primary) continue ;
			//	zval = GetVal (j, i) ;
				zcorr = GetVal_Corr (j, i) ;
				if (zcorr < 0. ) npix_below++ ;
				if (zcorr > 0. ) {
					npix_above++ ;
					total += zcorr ;
					if (zcorr > maxval) maxval = zcorr ;
					if (zcorr < minval) minval = zcorr ;
					maskarr [i * samps + j] |= 2 ;
					CPM [index].secondary = 1 ;
				}
				
			}
		}

		nhist_bins = maxval - minval + 1 ;
		if (nhist_bins == 1 || npix_above == 0) medval = maxval ;
		else {
			histo = new long [nhist_bins] ;
			for (il=0; il<nhist_bins; il++) histo[il]=0 ;
			
			for (i=0; i<lines; i++)
				for (j=0; j<samps; j++) 
				{
				index = i * samps + j ;
				if (crgn_sec.PtInRegion(j, i)) {
					if (CPM[index].rim || CPM[index].crater || CPM[index].primary) continue ;
					zcorr = GetVal_Corr (j, i) ;
					if (zcorr >0.) {
						index_histo = int (zcorr - minval) ;
						histo [index_histo]++ ;
					}
				}
				}
		

		cumtot = 0 ;
		for (il=0; il<nhist_bins && cumtot <= (npix_above /2); il++) 
		{
			cumtot += histo [il] ;
		}

		medval = minval + il ;
		delete [] histo ;
		}	

		secondary_volume = total ;
		cnd->outer_avg = total / npix_above ;
		cnd->outer_vol = total ;
		cnd->outer_max = maxval ;
		cnd->outer_min = minval ;
		cnd->outer_median = medval ;
		cnd->outer_npix = npix_above ;
		cnd->outer_npix_below = npix_below ;
		cnd->outer_npix_all = npix_above + npix_below ;
		DeleteObject (crgn_sec) ;
		
		return (float(total)) ; 
}


void CImageFile::GetLatLon (int x, int y, float *lon, float *lat) 
{
	*lon = grid_ll [0] + x * grid_ll [2] ;
	*lat = grid_ll [1] - y * grid_ll [3] ;

	return ;

}

void CImageFile::SetCDocument(CNewestDoc *cptr)
{
	cnd = cptr ;

}
