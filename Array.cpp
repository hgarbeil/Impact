// Array.cpp: implementation of the CMArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Newest.h"
#include "Array.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMArray::CMArray()
{

	bytesperpixel [0] = 1 ;
	bytesperpixel [1] = 2 ;
	bytesperpixel [2] = 4 ;
	bytesperpixel [3] = 4 ;
	valmin = -1.E6 ;
	valmax = 1.E6 ;

}

void CMArray::SetParams(int samps, int lines, int dt) {
	ns = samps ;
	nl = lines ;
	dtype = dt ;
}

CMArray::~CMArray()
{
	//if (cumhist) delete [] cumhist ;

}


int CMArray::bytescale (unsigned char *indat, unsigned char *outdat, long np, int dtype, float min, float max, 
					   float *scale, float *offset) 
{
	
	short int *sptr ;
	int       i, *iptr ;
	float	  *fptr ;
	float fval ;


	bpp = bytesperpixel [dtype] ;

	// to go from file val to DN val, subtract offset  and multiply by scale
	*scale = float (255. / (max - min))  ;
	*offset = min ;
	

	switch (dtype) {
	case 0 :
			for ( i=0; i<np; i++) {
				fval = (float) *(indat + i) ;
				fval = *scale * (fval - *(offset)) ;
				fval = (fval < 0.) ? 0.f : fval ;
				fval = (fval > 255.) ? 255.f : fval ;
				*(outdat + i) = (unsigned char) int(fval) ;
			}
			break ;
	case  1 :
				sptr = (short int *) &indat [0] ;
			for ( i=0; i<np; i++) {
				
				fval = (float) *(sptr + i) ;
				fval = *scale * (fval - *(offset)) ;
				fval = (fval < 0.) ? 0.f : fval ;
				fval = (fval > 255.) ? 255.f : fval ;
				*(outdat + i) = (unsigned char) int(fval) ;
			}
			break ;
	case 2 :
				iptr = (int *) &indat [0] ;
			for ( i=0; i<np; i++) {
				
				fval = (float) *(iptr + i) ;
				fval = *scale * (fval - *(offset)) ;
				fval = (fval < 0.) ? 0.f : fval ;
				fval = (fval > 255.) ? 255.f : fval ;
				*(outdat + i) = (unsigned char) int(fval) ;
			}
			break ;
	case 3 :
				fptr = (float *) &indat [0] ;
			for ( i=0; i<np; i++) {
				
				fval = *(fptr + i) ;
				fval = *scale * (fval - *(offset)) ;
				fval = (fval < 0.) ? 0.f : fval ;
				fval = (fval > 255.) ? 255.f : fval ;
				*(outdat + i) = (unsigned char) int(fval) ;
			}
			break ;



	}

return (1) ;
}



int CMArray::minmax (unsigned char *indat, long np, int dtype, float *min, float *max) 
{

	
	short int *sptr ;
	int       i, *iptr ;
	float	  *fptr ;
	float fval ;
	float mnval, mxval ;



	bpp = bytesperpixel [dtype] ;
	mnval = 1.E9 ;
	mxval =-1.E9 ;
	// to go from file val to DN val, subtract offset  and multiply by scale

	

	switch (dtype) {
	case 0 :
			for ( i=0; i<np; i++) {
				fval = (float) *(indat + i) ;
				if (fval < valmin || fval > valmax) continue ;
				if (fval > mxval) mxval = fval ;
				if (fval < mnval) mnval = fval ;

			}
			break ;
	case  1 :
				sptr = (short int *) &indat [0] ;
			for ( i=0; i<np; i++) {
				
				fval = (float) *(sptr + i) ;
				if (fval < valmin || fval > valmax) continue ;
				if (fval > mxval) mxval = fval ;
				if (fval < mnval) mnval = fval ;

				
			}
			break ;
	case 2 :
				iptr = (int *) &indat [0] ;
			for ( i=0; i<np; i++) {
				
				fval = (float) *(iptr + i) ;
				if (fval < valmin || fval > valmax) continue ;
				if (fval > mxval) mxval = fval ;
				if (fval < mnval) mnval = fval ;

				
			}
			break ;
	case 3 :
				fptr = (float *) &indat [0] ;
			for ( i=0; i<np; i++) {
				
				fval = *(fptr + i) ;
				if (fval > -.0001 && fval < .0001) continue ;
				if (fval < valmin || fval > valmax) continue ;
				if (fval > mxval) mxval = fval ;
				if (fval < mnval) mnval = fval ;

			
			}
			break ;



	}


	*min = mnval ;
	*max = mxval ;

	return (1) ;
}


long CMArray::histo     (unsigned char *indat,  long *cumhist, int ns, int nl, int dtype, int sampinc, float min,
					float binsize, int nbins, int cumflag)
{

	short int	*sptr ;
	int			i, j, *iptr, ival, bin ;
	long		nvalid = 0 ;
	float		*fptr, fval ;


	for (i=0; i<nbins; i++) cumhist [i]=0 ;
	switch (dtype) {
	case 0 :
		for (i=0; i<nl; i+=sampinc) {
			for (j=0; j<ns; j+=sampinc) {
				ival = int(*(indat + i* ns + j)) ;
				if (ival < valmin || ival > valmax) continue ;
				bin = int(float((ival - min))/binsize) ;
				if (bin < 0 || bin > nbins -1 ) continue ;
				cumhist [bin] +=1 ; 
				nvalid++ ;
			}
		}
		break ;
	case 1 :
		sptr = (short *) &indat [0] ;
		for (i=0; i<nl; i+=sampinc) {
			for (j=0; j<ns; j+=sampinc) {
				ival = int(*(sptr + i* ns + j)) ;
				if (ival < valmin || ival > valmax) continue ;
				bin = int(float((ival - min))/binsize) ;
				if (bin < 0 || bin > nbins -1 ) continue ;
				cumhist [bin] +=1 ;
				nvalid++ ;
			}
		}
		break ;
	case 2 :
		iptr = (int *) &indat [0] ;
		for (i=0; i<nl; i+=sampinc) {
			for (j=0; j<ns; j+=sampinc) {
				ival = int(*(iptr + i* ns + j)) ;
				if (ival < valmin || ival > valmax) continue ;
				bin = int(float((ival - min))/binsize) ;
				if (bin < 0 || bin > nbins -1 ) continue ;
				cumhist [bin] +=1 ;
				nvalid++ ;
			}
		}
		break ;
	case 3 :
		fptr = (float *) &indat [0] ;
		for (i=0; i<nl; i+=sampinc) {
			for (j=0; j<ns; j+=sampinc) {
				fval = float(*(fptr + i* ns + j)) ;
				if (fval < valmin || fval > valmax) continue ;
				bin = int(float((fval - min))/binsize) ;
				if (bin < 0 || bin > nbins -1 ) continue ;
				cumhist [bin] +=1 ;
				nvalid++ ;
			}
		}
		break ;
	}


	if (cumflag)
	for (i=1; i<nbins; i++) 
		cumhist [i] += cumhist [i-1] ; 


	return (nvalid) ;
}

int CMArray::SetValid(float min, float max)
{
	valmin = min ;
	valmax = max ;
	return (1) ;
}
