// CraterStats.h: interface for the CCraterStats class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRATERSTATS_H__2C996F91_CFD5_41FB_8CC9_E929923CC767__INCLUDED_)
#define AFX_CRATERSTATS_H__2C996F91_CFD5_41FB_8CC9_E929923CC767__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCraterStats  
{
public:
	void Init ();
	CCraterStats();
	virtual ~CCraterStats();
	void GetGeom () ;

	// crater location and lobe parameters
	POINT center ;
	float center_lat, center_lon ;
//	POINT maxlobe, minlobe ;
	SIZE  range_to_max, range_to_min ;
	float range_max_z, range_min_z ;
	CString cratername ;
	float  head_to_max, head_to_min ;
	float elev_at_max, elev_at_min, ysize_meters, xsize_meters ;
	float grid_ll [4], pixsize ;

	// surrounding surface 
	float fitsurf_coefs [6], surf_ave_elev ;

	// rim characteristics
	float rim_max, rim_avg, rim_min, rim_diam ;
	long   rim_npix, rim_npix_below ;

	// crater characteristics 
	float ctr_ave_depth, ctr_area ; 
	long  ctr_npix,  ctr_npix_above ;
	float ctr_diam, ctr_vol, ctr_max_depth ;

	float inner_max, inner_min, inner_avg, inner_diam ;
	long  inner_npix, inner_npix_below ;
	float inner_vol ;

	float outer_max, outer_min, outer_avg, outer_diam ; 
	long   outer_npix, outer_npix_below ;
	float outer_vol ;
	
	
	


};

#endif // !defined(AFX_CRATERSTATS_H__2C996F91_CFD5_41FB_8CC9_E929923CC767__INCLUDED_)
