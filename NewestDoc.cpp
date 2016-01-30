// NewestDoc.cpp : implementation of the CNewestDoc class
//

#include "stdafx.h"
#include "Newest.h"

#include "NewestDoc.h"
#include <math.h>

#define PI 3.14159265
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewestDoc

IMPLEMENT_DYNCREATE(CNewestDoc, CDocument)

BEGIN_MESSAGE_MAP(CNewestDoc, CDocument)
	//{{AFX_MSG_MAP(CNewestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewestDoc construction/destruction

CNewestDoc::CNewestDoc()
{
	// TODO: add one-time construction code here
	// arrays which are dynamically allocated....
	rimprof_corr = NULL ;
	tiepts_resids = NULL ;
	tiepts_x = NULL ;
	tiepts_y = NULL ;
	tiepts_z = NULL ;

	xsize_meters = 1. ;
	ysize_meters = 1. ;
	pixdim_avg = 1. ;
	grid_ll [0] = 0. ;
	grid_ll [1] = 90. ;
	grid_ll [2] = .01 ;
	grid_ll [3] = .01 ;
	Init () ;
	Centerflag = 0 ;
	SFitflag = 0 ;
	Rimflag = 0 ;
	Innerflag = 0 ;

	// Coordinate arrays 
	InnPrime = NULL ;
	PrimeSec = NULL ;
	Sec = NULL ;
	RimPtLoc = NULL ;

	rimprof_npts = 0 ;
	Ctrprof_pts = 0 ;
	Ctrprof_show = 0 ;
	Ctrprof = NULL ;
	m_strTabFile = _T("") ;
	m_strProfFile = _T("") ;

	HitCraters = new POINT [30000] ;
	m_nNumHitCraters = 0 ;

	radius_rim = 0. ;
	Rimflag = 0 ;


	

}

CNewestDoc::~CNewestDoc()
{
	if (rimprof_corr) delete [] rimprof_corr ;
	if (tiepts_x) delete [] tiepts_x ;
	if (tiepts_y) delete [] tiepts_y ;
	if (tiepts_z) delete [] tiepts_z ;
	if (tiepts_resids) delete [] tiepts_resids ;
	if (InnPrime) delete [] InnPrime ;
	if (PrimeSec) delete [] PrimeSec ;
	if (RimPtLoc) delete [] RimPtLoc ;
	if (Ctrprof) delete [] Ctrprof ;
	
	if (Sec) delete [] Sec ;
	if (HitCraters) delete [] HitCraters ;
}

BOOL CNewestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNewestDoc serialization

void CNewestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CNewestDoc diagnostics

#ifdef _DEBUG
void CNewestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNewestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNewestDoc commands

long CNewestDoc::AddRimProfile(float *rimpts, long npts)
{
	// Recover memory if it had been allocated before
	if (rimprof_corr) delete rimprof_corr ;
	rimprof_corr= NULL ;
	if((rimprof_corr = new float [npts]) == NULL) return (-1) ;
	for (long i=0; i<npts; i++) rimprof_corr [i] = rimpts[i] ;
	rimprof_npts = npts ;
	return (npts) ;

}

void CNewestDoc::AddCtrProfile(POINT *centprof, long npts)
{
	// Recover memory if it had been allocated before

	if (Ctrprof) delete [] Ctrprof ;
	Ctrprof_pts = npts ;

	if (centprof) 
	{
		Ctrprof = new POINT [npts] ;
		for (long is=0; is<npts; is++) Ctrprof [is] = centprof[is] ;
	}


	Ctrprof_show = 1 ;


}



void CNewestDoc::GetGeom () 
{
	// given center lat and lon 
	// hardwire mars geometry for now


	// earlier version had eccentricity = .01291801
	// which squared gave a very small # for eccentricity
	//double eccentricity = 

	geomflag = 1 ;
	double eccsq = 0.01291801 ; 
	double radius = 3397000. ;

	double center_lat_rad = center_lat / 57.29577951 ;

	double denom2 = pow (1. - eccsq * pow(sin (center_lat_rad), 2),1.5) ;
	double denom2_x = pow (1. - eccsq * pow(sin (center_lat_rad), 2),0.5) ;

	ysize_meters = (PI / 180. )  * radius * (1. - eccsq) / denom2 ; 
	xsize_meters = (PI / 180) * radius * cos (center_lat_rad) / denom2_x ;
	xsize_meters *= grid_ll [2] ;
	ysize_meters *= grid_ll [3] ;
	pixsize = xsize_meters * ysize_meters ;
	pixdim_avg = (xsize_meters + ysize_meters) / 2. ;
	return ;

}


void CNewestDoc::Init()
{	
	center.x = 0 ;
	center.y = 0 ;
	center_lat = 0 ;
	center_lon= 0 ;
	cratername = "" ;
	ctr_area = 0 ;
	ctr_ave_depth = 0 ;
	ctr_ave_depth_all = 0. ;
	ctr_max_depth_all = 0. ;
	ctr_diam = 0 ;
	ctr_max_depth = 0 ;
	ctr_median_depth ;
	ctr_npix = 0 ;
	ctr_npix_above = 0 ;
	ctr_vol = 0 ;
	elev_at_max = 0 ;
	elev_at_min = 0 ;

	inner_avg = 0 ;
	inner_diam = 0 ;
	inner_max = 0 ; 
	inner_min = 0 ;
	inner_npix = 0 ;
	inner_npix_below = 0 ;
	inner_vol = 0. ;
	inner_median = 0. ;
	inner_npix_all = 0;

	
	outer_avg = 0 ;
	outer_diam = 0 ;
	outer_max = 0 ; 
	outer_min = 0 ;
	outer_npix = 0 ;
	outer_npix_below = 0 ;
	outer_vol =0 ;
	outer_npix_all = 0 ;

	range_max_z = 0 ;
	range_min_z = 0 ;

	rimprof_med = 0. ;
	rimprof_avg = 0. ;
	rimprof_max = 0. ;
	rimprof_npts = 0 ;
	Rimflag = 0 ;

	rim_avg=0 ;
	rim_diam = 0 ;
	rim_max = 0 ;
	rim_min = 0 ;
	rim_npix = 0 ;
	rim_npix_below = 0 ;
	rim_median = 0 ;
	rim_vol = 0. ;

	// Flags to determine what is put on the results window
	Centerflag = 0 ;
	SFitflag = 0 ;
	Rimflag = 0 ;
	RimInnerflag = 0 ;
	Innerflag = 0 ;
	Outerflag = 0 ;
	cratername = _T("Crater0") ;

	rimprof_npts = 0 ;
	Ctrprof_show = 0 ;
	Ctrprof_pts = 0 ;

	UpdateAllViews (NULL, 17) ;

}

void CNewestDoc::SetSurfaceCoefs(double *coefarr, double *stdarr, double r2)
{
	for (int i=0; i<6; i++)
	{
		coefs [i] = coefarr[i] ;
		coefs_stddev [i] = stdarr [i] ;
	}
	tiepts_r2 = r2 ;
	SFitflag = 1 ;
	return ;

}

void CNewestDoc::SetSurfaceTiepts (int *x, int *y, double *z, double *resids, int npts) 
{
	double total = 0. ;
	nTiepts = npts ;
	

	if (tiepts_x) delete [] tiepts_x ;
	if (tiepts_y) delete [] tiepts_y ;
	if (tiepts_z) delete [] tiepts_z ;
	if (tiepts_resids) delete [] tiepts_resids ;
	tiepts_x = new int [npts] ;
	tiepts_y = new int [npts] ;
	tiepts_z = new double [npts] ;
	tiepts_resids = new double [npts] ;


	for (int i =0; i<npts; i++) {
		tiepts_x [i] = x [i] ;
		tiepts_y [i] = y [i] ;
		tiepts_z [i] = z [i] ;
		tiepts_resids [i] = resids [i] ;
		total += (resids [i] * resids[i] ) ;
	}
	total /= npts ;
	tiepts_resids_rms = sqrt (total) ;
	return ;
}

void CNewestDoc::SetSurfaceTieptsStats(float mean, float stdev)
{	
	tiepts_mean = mean ;
	tiepts_stdev = stdev ;

}

void CNewestDoc::GetPath(CString filename, CString *outdir)
{

	int loc = filename.ReverseFind ('\\') ;
	if (loc <0) return ;
	*outdir = filename.Left (loc+1) ;
	return  ;
}

void CNewestDoc::WriteFeatFile(int analphase)
{
	
	int   i ;
	float xval=0., yval=0. ;

	CFile cfil ;
	// features which are defined by  user are the tiepoints and the vertices
	// of the different components of the impact crater.

	if (analphase==0) {
		TRY {
			cfil.Open (m_strFeatFile, CFile::modeWrite |
			CFile::modeCreate ) ;
		}
		CATCH (CFileException, e) 		
		{

		}
		END_CATCH 
	}
	else {
		cfil.Open (m_strFeatFile, CFile::modeWrite |
			CFile::modeNoTruncate | CFile::modeCreate ) ;
		cfil.SeekToEnd () ;
	}
	CString outstr, outstr1 ;
	//outstr1.Format ("%8f %8f %8f %8f ", cifdem->crater_volume, cifdem->rim_volume,
	//	cifdem->primary_volume, cifdem->secondary_volume) ;
	//outstr =  profstring + outstr1 + cres_dlg->m_Cratername+_T("\r\n") ;



	if (analphase==0)
	{
	outstr.Format ("Crater ID  :\t") ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr = cratername + "\r\n\r\n" ;
	cfil.Write (outstr, outstr.GetLength()) ;
	outstr.Format ("Crater center location (Lon  Lat) :\t%9f   %9f\r\n",center_lon, center_lat) ;
	cfil.Write (outstr, outstr.GetLength()) ;
	}

	if (analphase ==1) 
	{
	outstr.Format ("\r\nUnaffected surface tiepoint locations \r\n") ;
	cfil.Write (outstr, outstr.GetLength ()) ;
		for ( i =0; i<nTiepts; i++)
		{
			GetLatLon (tiepts_x[i], tiepts_y [i], &xval, &yval) ;
			outstr.Format ("%9f    %9f\r\n", xval, yval) ;
			cfil.Write (outstr, outstr.GetLength ()) ;
		}
	}

	if (analphase ==2) 
	{
	

	outstr.Format ("\r\nRim Vertices \r\n") ;
	cfil.Write (outstr, outstr.GetLength()) ;


	for (i=0; i<Rim_pts; i++)
	{
		GetLatLon (RimPtLoc [i].x, RimPtLoc[i].y, &xval, &yval) ;
		outstr.Format ("%9f   %9f\r\n", xval, yval) ;
		cfil.Write (outstr, outstr.GetLength()) ;
	}


	}


	if (analphase ==3) 
	{
	

	outstr.Format ("\r\nOuter Wall Vertices \r\n") ;
	cfil.Write (outstr, outstr.GetLength()) ;


	for (i=0; i<Inn_Prime_Pts; i++)
	{
		GetLatLon (InnPrime [i].x, InnPrime[i].y, &xval, &yval) ;
		outstr.Format ("%9f   %9f\r\n", xval, yval) ;
		cfil.Write (outstr, outstr.GetLength()) ;
	}


	}



	if (analphase ==4) 
	{
	

	outstr.Format ("\r\nInner  Lobe Vertices\r\n") ;
	cfil.Write (outstr, outstr.GetLength()) ;


	for (i=0; i<Prime_Sec_Pts; i++)
	{
		GetLatLon (PrimeSec [i].x, PrimeSec[i].y, &xval, &yval) ;
		outstr.Format ("%9f   %9f\r\n", xval, yval) ;
		cfil.Write (outstr, outstr.GetLength()) ;
	}


	}


	if (analphase ==5) 
	{
	

	outstr.Format ("\r\nOuter Lobe Vertices\r\n") ;
	cfil.Write (outstr, outstr.GetLength()) ;


	for (i=0; i<Sec_Pts; i++)
	{
		GetLatLon (Sec [i].x, Sec[i].y, &xval, &yval) ;
		outstr.Format ("%9f   %9f\r\n", xval, yval) ;
		cfil.Write (outstr, outstr.GetLength()) ;
	}


	}


	cfil.Close () ;

	return  ;

}

void CNewestDoc::SetRimVertices(POINT *rimloc, int npts)
{
	int i ;

	if (RimPtLoc) delete [] RimPtLoc ;
	RimPtLoc = new POINT [npts] ;
	Rim_pts = npts ;

	for (i=0;i<npts;i++) RimPtLoc [i] = rimloc [i] ;
	return ; 

}

void CNewestDoc::SetInnPrimeVertices(POINT *ip, int npts)
{
	int i ;

	if (InnPrime) delete [] InnPrime ;
	InnPrime = new POINT [npts] ;
	Inn_Prime_Pts = npts ;

	for (i=0;i<npts;i++) InnPrime [i] = ip [i] ;
	return ; 

}

void CNewestDoc::SetPrimeSecVertices(POINT *ip, int npts)
{
	int i ;

	if (PrimeSec) delete [] PrimeSec ;
	PrimeSec = new POINT [npts] ;
	Prime_Sec_Pts = npts ;

	for (i=0;i<npts;i++) PrimeSec [i] = ip [i] ;
	return ; 

}



void CNewestDoc::SetSecVertices(POINT *ip, int npts)
{
	int i ;

	if (Sec) delete [] Sec ;
	Sec = new POINT [npts] ;
	Sec_Pts = npts ;

	for (i=0;i<npts;i++) Sec [i] = ip [i] ;
	return ; 

}



void CNewestDoc::GetLatLon (int x, int y, float *lon, float *lat) 
{
	*lon = grid_ll [0] + x * grid_ll [2] ;
	*lat = grid_ll [1] - y * grid_ll [3] ;

	return ;

}
