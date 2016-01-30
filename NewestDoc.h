// NewestDoc.h : interface of the CNewestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWESTDOC_H__6CEE748D_1DA8_4FE1_B446_FF88E368A168__INCLUDED_)
#define AFX_NEWESTDOC_H__6CEE748D_1DA8_4FE1_B446_FF88E368A168__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNewestDoc : public CDocument
{
protected: // create from serialization only
	CNewestDoc();
	DECLARE_DYNCREATE(CNewestDoc)

// Attributes
public:
	// usually generated by the CNewestView::MakeProfile fcn
	// then set by the AddRimProfile fcn
	float		*rimprof_corr ;
	long	    rimprof_npts ;


	// copied from CCraterStats
	int   geomflag, Centerflag, Rimflag, RimInnerflag, Innerflag, Outerflag, SFitflag ;
	POINT center ;
	float center_lat, center_lon, center_elev, center_elev_corr ;

	SIZE  range_to_max, range_to_min ;
	float range_max_z, range_min_z ;
	CString cratername ;
	float  head_to_max, head_to_min ;
	float elev_at_max, elev_at_min, ysize_meters, xsize_meters ;
	float grid_ll [4], pixsize, pixdim_avg, surf_ave_elev ;
	

	// rim characteristics
	int    Rim_pts, Inn_Prime_Pts, Prime_Sec_Pts, Sec_Pts ;
	int	   nsamps, nlines, centroid_x, centroid_y ;
	float  rim_max, rim_avg, rim_min, rim_diam, rim_median, radius_rim ;
	long   rim_npix, rim_npix_below ;
	float  rimprof_max, rimprof_min, rimprof_avg, rimprof_med ;
	POINT  *RimPtLoc, *InnPrime, *PrimeSec, *Sec ;

	// crater characteristics 
	float ctr_ave_depth, ctr_area, ctr_median_depth, ctr_ave_depth_all, ctr_max_depth_all ; 
	long  ctr_npix,  ctr_npix_above ;
	float ctr_diam, ctr_vol, ctr_max_depth ;

	float inner_max, inner_min, inner_avg, inner_diam ;
	long  inner_npix, inner_npix_below, inner_npix_all ;
	float inner_vol, inner_median ;

	float outer_max, outer_min, outer_avg, outer_diam ; 
	long  outer_npix, outer_npix_below, outer_npix_all ;
	float outer_vol, outer_median ;

	// Surface fitting results
	double coefs [6], coefs_stddev [6], tiepts_resids_rms, tiepts_r2 ;
	double tiepts_mean, tiepts_stdev ;
	int    *tiepts_x, *tiepts_y, nTiepts ; 
	double  *tiepts_z, *tiepts_resids ;


// Operations
public:
	void GetGeom () ;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	long m_nNumHitCraters;
	POINT *HitCraters;
	long Ctrprof_pts;
	void AddCtrProfile (POINT *, long npts);
	BOOL Ctrprof_show;
	
	POINT *Ctrprof;
	double rim_vol;
	void SetRimVertices (POINT *,  int);
	void SetInnPrimeVertices (POINT *, int) ;
	void SetPrimeSecVertices (POINT *, int) ;
	void SetSecVertices (POINT *, int) ;
	void WriteFeatFile (int Analphase);
	void GetPath (CString filename, CString *);
	
	void GetLatLon (int x, int y, float *lon, float *lat)  ;

	CString m_strSurfFile;
	CString m_strFeatFile;
	CString m_strAnalFile;
	CString m_strTabFile ;
	CString m_strProfFile ;
	
	void SetSurfaceTieptsStats (float mean, float stdev);
	// for unaffected surface definition
	void SetSurfaceCoefs (double *coefarr, double *stdarr, double r2);
	void SetSurfaceTiepts (int *x, int *y, double *z, double *resids, int npts) ;

	// initialize for new and first crater
	void Init ();

	long AddRimProfile (float *rimpts, long npts);
	virtual ~CNewestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNewestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWESTDOC_H__6CEE748D_1DA8_4FE1_B446_FF88E368A168__INCLUDED_)