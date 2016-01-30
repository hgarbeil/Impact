// TopoArray.cpp: implementation of the CTopoArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Newest.h"
#include "TopoArray.h"
#include  <iostream>
#include "constants.h"
#include "math.h"
#ifdef _DEBUG

#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTopoArray::CTopoArray()
{
	maskmin = -60000. ;
}

CTopoArray::~CTopoArray()
{

}

void CTopoArray::Calcshade(unsigned char *indat, BYTE *outdat, float sunelev, float sunaz, float pixdim, float maskval)
{


	unsigned char 	*outptr ;
	unsigned char 	*iptr ;
	int 		i, j, js, npts_top, npts_bot, npts_lft, npts_rht ;
	float		fval, lftsum, rhtsum, topsum, botsum ;
	double 		dx, dy, a[3], b[3], alpha ;

	// calculate the unit vector depicting the sun direction

	// send to the correct function depending upon input data type
	if (dtype == 1) Calcshade ((short *)indat, outdat, sunelev, sunaz, pixdim, maskval) ;
	if (dtype == 2) Calcshade ((int *)indat, outdat, sunelev, sunaz, pixdim, maskval) ;
	if (dtype == 3) Calcshade ((float *)indat, outdat, sunelev, sunaz, pixdim, maskval) ;

	if (dtype >0) return  ;
	std::cout << "Azimuth is   " << sunaz << std::endl ;
	cout << "Elevation is " << sunelev << endl ;
	sunaz *= float(DEG2RAD) ;
	sunelev *= float(DEG2RAD) ;
	b [0] = sin (sunaz) * cos (sunelev) ;
	b [1] = cos (sunaz) * cos (sunelev) ;
	b [2] = sin (sunelev) ;

	// initialize the first line to zero
	for (j=0; j<ns; j++)
		*(outdat + j) = 0 ;

	for (i=1; i<nl-1; i++)
	{
		outptr = outdat + i * ns ;
		for (j=0; j<ns; j++)
			*(outptr+j) = 0 ;
		for (j=1; j<ns-1; j++)
		{
			// get the top three pixels	
			npts_top = 0 ;
			topsum = 0. ;
			iptr = indat + (i-1) * ns + j - 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js) ;
				if (fval > maskval) 
				{
					topsum += fval ;
					npts_top++ ;
				}
			}
			if (npts_top) topsum /= npts_top ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}
			// get the bot three pixels	
			npts_bot = 0 ;
			botsum = 0. ;
			iptr = indat + (i+1) * ns + j - 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js) ;
				if (fval > maskval) 
				{
					botsum += fval ;
					npts_bot++ ;
				}
			}
			if (npts_bot) botsum /= npts_bot ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}
			// get the left three pixels	
			npts_lft = 0 ;
			lftsum = 0. ;
			iptr = indat + (i-1) * ns + j - 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js*ns) ;
				if (fval > maskval) 
				{
					lftsum += fval ;
					npts_lft++ ;
				}
			}
			if (npts_lft) lftsum /= npts_lft ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}
			// get the right three pixels	
			npts_rht = 0 ;
			rhtsum = 0. ;
			iptr = indat + (i-1) * ns + j + 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js*ns) ;
				if (fval > maskval) 
				{
					rhtsum += fval ;
					npts_rht++ ;
				}
			}
			if (npts_rht) rhtsum /= npts_rht ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}

			// if we get to this point all direct derivs
			// can be calculated
			dx = (lftsum - rhtsum) / (2. * pixdim) ;
			dy = (botsum - topsum) / (2. * pixdim) ;

			a [0] = dx / sqrt(dx * dx + dy * dy + 1.) ;
			a [1] = dy / sqrt(dx * dx + dy * dy + 1.) ;
			a [2] = 1. / sqrt(dx * dx + dy * dy + 1.) ;

			alpha = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] ;
			alpha *=255. ;
			alpha =(alpha<0.) ? 0. : alpha ;
			alpha =(alpha>255.) ? 255. : alpha ;
			*(outptr + j) = (unsigned char) alpha ;
		}
	}

}


void CTopoArray::Calcshade(short int *indat, BYTE *outdat, float sunelev, float sunaz, float pixdim, float maskval)
{


	unsigned char 	*outptr ;
	short int	 	*iptr ;
	int 		i, j, js, npts_top, npts_bot, npts_lft, npts_rht ;
	float		fval, lftsum, rhtsum, topsum, botsum ;
	double 		dx, dy, a[3], b[3], alpha ;

	// calculate the unit vector depicting the sun direction
	cout << "Azimuth is   " << sunaz << endl ;
	cout << "Elevation is " << sunelev << endl ;
	sunaz *= float(DEG2RAD) ;
	sunelev *= float(DEG2RAD) ;
	b [0] = sin (sunaz) * cos (sunelev) ;
	b [1] = cos (sunaz) * cos (sunelev) ;
	b [2] = sin (sunelev) ;

	// initialize the first line to zero
	for (j=0; j<ns; j++)
		*(outdat + j) = 0 ;

	for (i=1; i<nl-1; i++)
	{
		outptr = outdat + i * ns ;
		for (j=0; j<ns; j++)
			*(outptr+j) = 0 ;
		for (j=1; j<ns-1; j++)
		{
			// get the top three pixels	
			npts_top = 0 ;
			topsum = 0. ;
			iptr = indat + (i-1) * ns + j - 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js) ;
				if (fval > maskval) 
				{
					topsum += fval ;
					npts_top++ ;
				}
			}
			if (npts_top) topsum /= npts_top ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}
			// get the bot three pixels	
			npts_bot = 0 ;
			botsum = 0. ;
			iptr = indat + (i+1) * ns + j - 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js) ;
				if (fval > maskval) 
				{
					botsum += fval ;
					npts_bot++ ;
				}
			}
			if (npts_bot) botsum /= npts_bot ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}
			// get the left three pixels	
			npts_lft = 0 ;
			lftsum = 0. ;
			iptr = indat + (i-1) * ns + j - 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js*ns) ;
				if (fval > maskval) 
				{
					lftsum += fval ;
					npts_lft++ ;
				}
			}
			if (npts_lft) lftsum /= npts_lft ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}
			// get the right three pixels	
			npts_rht = 0 ;
			rhtsum = 0. ;
			iptr = indat + (i-1) * ns + j + 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js*ns) ;
				if (fval > maskval) 
				{
					rhtsum += fval ;
					npts_rht++ ;
				}
			}
			if (npts_rht) rhtsum /= npts_rht ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}

			// if we get to this point all direct derivs
			// can be calculated
			dx = (lftsum - rhtsum) / (2. * pixdim) ;
			dy = (botsum - topsum) / (2. * pixdim) ;

			a [0] = dx / sqrt(dx * dx + dy * dy + 1.) ;
			a [1] = dy / sqrt(dx * dx + dy * dy + 1.) ;
			a [2] = 1. / sqrt(dx * dx + dy * dy + 1.) ;

			alpha = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] ;
			alpha *=255. ;
			alpha =(alpha<0.) ? 0. : alpha ;
			alpha =(alpha>255.) ? 255. : alpha ;
			*(outptr + j) = (unsigned char) alpha ;
		}
	}

}
void CTopoArray::Calcshade(int *indat, BYTE *outdat, float sunelev, float sunaz, float pixdim, float maskval)
{


	unsigned char 	*outptr ;
	int	 	*iptr ;
	int 		i, j, js, npts_top, npts_bot, npts_lft, npts_rht ;
	float		fval, lftsum, rhtsum, topsum, botsum ;
	double 		dx, dy, a[3], b[3], alpha ;

	// calculate the unit vector depicting the sun direction
	cout << "Azimuth is   " << sunaz << endl ;
	cout << "Elevation is " << sunelev << endl ;
	sunaz *= float(DEG2RAD) ;
	sunelev *= float(DEG2RAD) ;
	b [0] = sin (sunaz) * cos (sunelev) ;
	b [1] = cos (sunaz) * cos (sunelev) ;
	b [2] = sin (sunelev) ;

	// initialize the first line to zero
	for (j=0; j<ns; j++)
		*(outdat + j) = 0 ;

	for (i=1; i<nl-1; i++)
	{
		outptr = outdat + i * ns ;
		for (j=0; j<ns; j++)
			*(outptr+j) = 0 ;
		for (j=1; j<ns-1; j++)
		{
			// get the top three pixels	
			npts_top = 0 ;
			topsum = 0. ;
			iptr = indat + (i-1) * ns + j - 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js) ;
				if (fval > maskval) 
				{
					topsum += fval ;
					npts_top++ ;
				}
			}
			if (npts_top) topsum /= npts_top ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}
			// get the bot three pixels	
			npts_bot = 0 ;
			botsum = 0. ;
			iptr = indat + (i+1) * ns + j - 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js) ;
				if (fval > maskval) 
				{
					botsum += fval ;
					npts_bot++ ;
				}
			}
			if (npts_bot) botsum /= npts_bot ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}
			// get the left three pixels	
			npts_lft = 0 ;
			lftsum = 0. ;
			iptr = indat + (i-1) * ns + j - 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js*ns) ;
				if (fval > maskval) 
				{
					lftsum += fval ;
					npts_lft++ ;
				}
			}
			if (npts_lft) lftsum /= npts_lft ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}
			// get the right three pixels	
			npts_rht = 0 ;
			rhtsum = 0. ;
			iptr = indat + (i-1) * ns + j + 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js*ns) ;
				if (fval > maskval) 
				{
					rhtsum += fval ;
					npts_rht++ ;
				}
			}
			if (npts_rht) rhtsum /= npts_rht ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}

			// if we get to this point all direct derivs
			// can be calculated
			dx = (lftsum - rhtsum) / (2. * pixdim) ;
			dy = (botsum - topsum) / (2. * pixdim) ;

			a [0] = dx / sqrt(dx * dx + dy * dy + 1.) ;
			a [1] = dy / sqrt(dx * dx + dy * dy + 1.) ;
			a [2] = 1. / sqrt(dx * dx + dy * dy + 1.) ;

			alpha = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] ;
			alpha *=255. ;
			alpha =(alpha<0.) ? 0. : alpha ;
			alpha =(alpha>255.) ? 255. : alpha ;
			*(outptr + j) = (unsigned char) alpha ;
		}
	}

}
void CTopoArray::Calcshade(float *indat, BYTE *outdat, float sunelev, float sunaz, float pixdim, float maskval)
{


	unsigned char 	*outptr ;
	float		 	*iptr ;
	int 		i, j, js, npts_top, npts_bot, npts_lft, npts_rht ;
	float		fval, lftsum, rhtsum, topsum, botsum ;
	double 		dx, dy, a[3], b[3], alpha ;

	// calculate the unit vector depicting the sun direction
	cout << "Azimuth is   " << sunaz << endl ;
	cout << "Elevation is " << sunelev << endl ;
	sunaz *= float(DEG2RAD) ;
	sunelev *= float(DEG2RAD) ;
	b [0] = sin (sunaz) * cos (sunelev) ;
	b [1] = cos (sunaz) * cos (sunelev) ;
	b [2] = sin (sunelev) ;

	// initialize the first line to zero
	for (j=0; j<ns; j++)
		*(outdat + j) = 0 ;

	for (i=1; i<nl-1; i++)
	{
		outptr = outdat + i * ns ;
		for (j=0; j<ns; j++)
			*(outptr+j) = 0 ;
		for (j=1; j<ns-1; j++)
		{
			// get the top three pixels	
			npts_top = 0 ;
			topsum = 0. ;
			iptr = indat + (i-1) * ns + j - 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js) ;
				if (fval > maskval) 
				{
					topsum += fval ;
					npts_top++ ;
				}
			}
			if (npts_top) topsum /= npts_top ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}
			// get the bot three pixels	
			npts_bot = 0 ;
			botsum = 0. ;
			iptr = indat + (i+1) * ns + j - 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js) ;
				if (fval > maskval) 
				{
					botsum += fval ;
					npts_bot++ ;
				}
			}
			if (npts_bot) botsum /= npts_bot ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}
			// get the left three pixels	
			npts_lft = 0 ;
			lftsum = 0. ;
			iptr = indat + (i-1) * ns + j - 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js*ns) ;
				if (fval > maskval) 
				{
					lftsum += fval ;
					npts_lft++ ;
				}
			}
			if (npts_lft) lftsum /= npts_lft ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}
			// get the right three pixels	
			npts_rht = 0 ;
			rhtsum = 0. ;
			iptr = indat + (i-1) * ns + j + 1 ;
			for (js=0; js<3; js++)
			{
				fval = (float) *(iptr+js*ns) ;
				if (fval > maskval) 
				{
					rhtsum += fval ;
					npts_rht++ ;
				}
			}
			if (npts_rht) rhtsum /= npts_rht ;
			else 
			{
				*(outptr +j) = 0 ;
				continue ;
			}

			// if we get to this point all direct derivs
			// can be calculated
			dx = (lftsum - rhtsum) / (2. * pixdim) ;
			dy = (botsum - topsum) / (2. * pixdim) ;

			a [0] = dx / sqrt(dx * dx + dy * dy + 1.) ;
			a [1] = dy / sqrt(dx * dx + dy * dy + 1.) ;
			a [2] = 1. / sqrt(dx * dx + dy * dy + 1.) ;

			alpha = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] ;
			alpha *=255. ;
			alpha =(alpha<0.) ? 0. : alpha ;
			alpha =(alpha>255.) ? 255. : alpha ;
			*(outptr + j) = (unsigned char) alpha ;
		}
	}

}


void CTopoArray::Calcslope (unsigned char *indat, float *outdat, float pixdim) 
{
	
	int 	i, j, il, npts_top, npts_bot, npts_lft, npts_rht ;
	unsigned char *kdatptr, *inptr ;
	float   *outptr ;
	double  fval0, fval1, vertslope, horizslope, sum, tval ;
	double  bval, lval, rval, slope ;

	if (dtype==1) Calcslope ((short int *) indat, outdat, pixdim) ;
	if (dtype==2) Calcslope ((int *) indat, outdat, pixdim) ;
	if (dtype==3) Calcslope ((float *) indat, outdat, pixdim) ;

	if (dtype >0) return ;
	for (il=0; il<nl; il++) 
	{
		inptr = indat + il * ns ;
	
	for (i=1; i<ns-1; i++)
	{
		// get the sum of the top three pixels
		kdatptr = inptr + i - ns - 1 ;
		outptr = outdat + i ;
		npts_top = 0 ;
		sum = 0. ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j) ;
			if (fval0 > maskmin)
			{
				npts_top++ ;
				sum += fval0 ;
			}
		}
		if (npts_top)
			tval = sum / npts_top ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}
		// now get the average bottom value
		npts_bot = 0 ;
		sum = 0. ;
		kdatptr = indat + i + ns - 1 ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j) ;
			if (fval0 > maskmin)
			{
				npts_bot++ ;
				sum += fval0 ;
			}
		}
		if (npts_bot)
			bval = sum / npts_bot ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}

		// now get the average left value
		npts_lft = 0 ;
		sum = 0. ;
		kdatptr = indat + i - ns - 1 ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j * ns) ;
			if (fval0 > maskmin)
			{
				npts_lft++ ;
				sum += fval0 ;
			}
		}
		if (npts_lft)
			lval = sum / npts_bot ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}

		// now get the average rightt value
		npts_rht = 0 ;
		sum = 0. ;
		kdatptr = indat + i - ns + 1 ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j * ns) ;
			if (fval0 > maskmin)
			{
				npts_rht++ ;
				sum += fval0 ;
			}
		}
		if (npts_rht)
			rval = sum / npts_rht ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}

		// if we get to this point there is a valid point
		// for each of the directions
		// now do the slope calcs 
		vertslope = (tval - bval)/(pixdim * 2.) ;
		horizslope = (lval - rval) /(pixdim * 2.) ; 
		slope = pow(vertslope,2.) + pow(horizslope,2.) ;
		slope = sqrt(slope) ;
		// the slope is now percent slope
		// convert to degree slope 
		slope = atan (slope) ;
		slope = slope * RAD2DEG ;
		*outptr = slope ;
		
	}
	}

}



void CTopoArray::Calcslope (short int *indat, float *outdat, float pixdim) 
{
	
	int 	i, j, il, npts_top, npts_bot, npts_lft, npts_rht ;
	short int *kdatptr, *inptr ;
	float   *outptr ;
	double  fval0, fval1, vertslope, horizslope, sum, tval ;
	double  bval, lval, rval, slope ;

	for (il=0; il<nl; il++) 
	{
		inptr = indat + il * ns ;
	
	for (i=1; i<ns-1; i++)
	{
		// get the sum of the top three pixels
		kdatptr = inptr + i - ns - 1 ;
		outptr = outdat + i ;
		npts_top = 0 ;
		sum = 0. ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j) ;
			if (fval0 > maskmin)
			{
				npts_top++ ;
				sum += fval0 ;
			}
		}
		if (npts_top)
			tval = sum / npts_top ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}
		// now get the average bottom value
		npts_bot = 0 ;
		sum = 0. ;
		kdatptr = indat + i + ns - 1 ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j) ;
			if (fval0 > maskmin)
			{
				npts_bot++ ;
				sum += fval0 ;
			}
		}
		if (npts_bot)
			bval = sum / npts_bot ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}

		// now get the average left value
		npts_lft = 0 ;
		sum = 0. ;
		kdatptr = indat + i - ns - 1 ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j * ns) ;
			if (fval0 > maskmin)
			{
				npts_lft++ ;
				sum += fval0 ;
			}
		}
		if (npts_lft)
			lval = sum / npts_bot ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}

		// now get the average rightt value
		npts_rht = 0 ;
		sum = 0. ;
		kdatptr = indat + i - ns + 1 ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j * ns) ;
			if (fval0 > maskmin)
			{
				npts_rht++ ;
				sum += fval0 ;
			}
		}
		if (npts_rht)
			rval = sum / npts_rht ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}

		// if we get to this point there is a valid point
		// for each of the directions
		// now do the slope calcs 
		vertslope = (tval - bval)/(pixdim * 2.) ;
		horizslope = (lval - rval) /(pixdim * 2.) ; 
		slope = pow(vertslope,2.) + pow(horizslope,2.) ;
		slope = sqrt(slope) ;
		// the slope is now percent slope
		// convert to degree slope 
		slope = atan (slope) ;
		slope = slope * RAD2DEG ;
		*outptr = slope ;
		
	}
	}

}



void CTopoArray::Calcslope (int *indat, float *outdat, float pixdim) 
{
	
	int 	i, j, il, npts_top, npts_bot, npts_lft, npts_rht ;
	int		*kdatptr, *inptr ;
	float   *outptr ;
	double  fval0, fval1, vertslope, horizslope, sum, tval ;
	double  bval, lval, rval, slope ;

	for (il=0; il<nl; il++) 
	{
		inptr = indat + il * ns ;
	
	for (i=1; i<ns-1; i++)
	{
		// get the sum of the top three pixels
		kdatptr = inptr + i - ns - 1 ;
		outptr = outdat + i ;
		npts_top = 0 ;
		sum = 0. ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j) ;
			if (fval0 > maskmin)
			{
				npts_top++ ;
				sum += fval0 ;
			}
		}
		if (npts_top)
			tval = sum / npts_top ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}
		// now get the average bottom value
		npts_bot = 0 ;
		sum = 0. ;
		kdatptr = indat + i + ns - 1 ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j) ;
			if (fval0 > maskmin)
			{
				npts_bot++ ;
				sum += fval0 ;
			}
		}
		if (npts_bot)
			bval = sum / npts_bot ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}

		// now get the average left value
		npts_lft = 0 ;
		sum = 0. ;
		kdatptr = indat + i - ns - 1 ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j * ns) ;
			if (fval0 > maskmin)
			{
				npts_lft++ ;
				sum += fval0 ;
			}
		}
		if (npts_lft)
			lval = sum / npts_bot ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}

		// now get the average rightt value
		npts_rht = 0 ;
		sum = 0. ;
		kdatptr = indat + i - ns + 1 ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j * ns) ;
			if (fval0 > maskmin)
			{
				npts_rht++ ;
				sum += fval0 ;
			}
		}
		if (npts_rht)
			rval = sum / npts_rht ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}

		// if we get to this point there is a valid point
		// for each of the directions
		// now do the slope calcs 
		vertslope = (tval - bval)/(pixdim * 2.) ;
		horizslope = (lval - rval) /(pixdim * 2.) ; 
		slope = pow(vertslope,2.) + pow(horizslope,2.) ;
		slope = sqrt(slope) ;
		// the slope is now percent slope
		// convert to degree slope 
		slope = atan (slope) ;
		slope = slope * RAD2DEG ;
		*outptr = slope ;
		
	}
	}

}




void CTopoArray::Calcslope (float *indat, float *outdat, float pixdim) 
{
	
	int 	i, j,  npts_top, npts_bot, npts_lft, npts_rht ;
	long	il, npix ;
	float	*kdatptr, *inptr ;
	float   *outptr ;
	double  fval0, fval1, vertslope, horizslope, sum, tval ;
	double  bval, lval, rval, slope ;

	npix = long (ns) * nl ;
	for (il=0; il<npix; il++) *(outdat+il) = 0. ;

	for (il=1; il<nl-2; il++) 
	{
		inptr = indat + il * ns ;
	
	for (i=1; i<ns-2; i++)
	{
		// get the sum of the top three pixels
		kdatptr = inptr + i - ns - 1 ;
		outptr = outdat + il * ns + i ;
		npts_top = 0 ;
		sum = 0. ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j) ;
			if (fval0 > maskmin)
			{
				npts_top++ ;
				sum += fval0 ;
			}
		}
		if (npts_top)
			tval = sum / npts_top ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}
		// now get the average bottom value
		npts_bot = 0 ;
		sum = 0. ;
		kdatptr = inptr + i + ns - 1 ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j) ;
			if (fval0 > maskmin)
			{
				npts_bot++ ;
				sum += fval0 ;
			}
		}
		if (npts_bot)
			bval = sum / npts_bot ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}

		// now get the average left value
		npts_lft = 0 ;
		sum = 0. ;
		kdatptr = inptr + i - ns - 1 ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j * ns) ;
			if (fval0 > maskmin)
			{
				npts_lft++ ;
				sum += fval0 ;
			}
		}
		if (npts_lft)
			lval = sum / npts_bot ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}

		// now get the average rightt value
		npts_rht = 0 ;
		sum = 0. ;
		kdatptr = inptr + i - ns + 1 ;
		for (j=0; j<3; j++) 
		{
			fval0 = (double) *(kdatptr + j * ns) ;
			if (fval0 > maskmin)
			{
				npts_rht++ ;
				sum += fval0 ;
			}
		}
		if (npts_rht)
			rval = sum / npts_rht ;
		else 
		{ 
			*outptr = 0. ;
			continue ;
		}

		// if we get to this point there is a valid point
		// for each of the directions
		// now do the slope calcs 
		vertslope = (tval - bval)/(pixdim * 2.) ;
		horizslope = (lval - rval) /(pixdim * 2.) ; 
		slope = pow(vertslope,2.) + pow(horizslope,2.) ;
		slope = sqrt(slope) ;
		// the slope is now percent slope
		// convert to degree slope 
		slope = atan (slope) ;
		slope = slope * RAD2DEG ;
 		*outptr = slope ;
		
	}
	}

}



