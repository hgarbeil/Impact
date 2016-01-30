// Array.h: interface for the CArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARRAY_H__98662824_658C_11D5_BAB7_005056986301__INCLUDED_)
#define AFX_ARRAY_H__98662824_658C_11D5_BAB7_005056986301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMArray  
{
public:
	int SetValid (float min, float max);
	CMArray();
	virtual ~CMArray();

	void SetParams (int ns, int nl, int dt) ;
	int dtype ;
	int bpp ;
	int ns ;
	int nl ;
	int bytesperpixel [5] ;
	long npix ;
	unsigned char *indat ;
	short int	  *sdat ;
	int			  *idat ;
	float		  *fdat, valmin, valmax ;

	int bytescale (unsigned char *indat, unsigned char *outdat, long np, int dtype, float min, float max,
					float *scale, float *offset) ;
	//int minmax    (unsigned char *indat, unsigned char *outdat, int ns, int nl, int dtype, int sampinc, float *min, float *max) ; 

	long histo     (unsigned char *indat,  long *cumhist, int ns, int nl, int dtype, int sampinc, float min,
					float binsize, int nbins, int cumflag) ;
	int minmax (unsigned char *indat, long np, int dtype, float *min, float *max) ;

};

#endif // !defined(AFX_ARRAY_H__98662824_658C_11D5_BAB7_005056986301__INCLUDED_)
