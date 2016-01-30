// CraterStats.cpp: implementation of the CCraterStats class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "newest.h"
#include "CraterStats.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define PI 3.14159265
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCraterStats::CCraterStats()
{
	xsize_meters = 1. ;
	ysize_meters = 1. ;
	grid_ll [0] = 0. ;
	grid_ll [1] = 90. ;
	grid_ll [2] = .01 ;
	grid_ll [3] = .01 ;

}

CCraterStats::~CCraterStats()
{

}

void CCraterStats::GetGeom () 
{
	// given center lat and lon 
	// hardwire mars geometry for now


	// earlier version had eccentricity = .01291801
	// which squared gave a very small # for eccentricity
	//double eccentricity = 
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
	return ;

}

void CCraterStats::Init()
{
	center.x = 0 ;
	center.y = 0 ;
	center_lat = 0 ;
	center_lon= 0 ;
	cratername = "" ;
	ctr_area = 0 ;
	ctr_ave_depth = 0 ;
	ctr_diam = 0 ;
	ctr_max_depth = 0 ;
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
	inner_vol ;
	
	outer_avg = 0 ;
	outer_diam = 0 ;
	outer_max = 0 ; 
	outer_min = 0 ;
	outer_npix = 0 ;
	outer_npix_below = 0 ;
	outer_vol =0 ;
	range_max_z = 0 ;
	range_min_z = 0 ;

	rim_avg=0 ;
	rim_diam = 0 ;
	rim_max = 0 ;
	rim_min = 0 ;
	rim_npix = 0 ;
	rim_npix_below = 0 ;

}
