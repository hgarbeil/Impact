// TopoArray.h: interface for the CTopoArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOPOARRAY_H__941DFE22_6A48_11D5_BABA_005056986301__INCLUDED_)
#define AFX_TOPOARRAY_H__941DFE22_6A48_11D5_BABA_005056986301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Array.h"

class CTopoArray : public CMArray  
{
public:
	void Calcshade (unsigned char *indat, BYTE *outdat, float sunelev, float sunaz, float pixdim, float maskval);
	void Calcshade (short int *indat, BYTE *outdat, float sunelev, float sunaz, float pixdim, float maskval);
	void Calcshade (int *indat, BYTE *outdat, float sunelev, float sunaz, float pixdim, float maskval);
	void Calcshade (float *indat, BYTE *outdat, float sunelev, float sunaz, float pixdim, float maskval);
	void Calcslope (unsigned char *indat, float *outdat, float pixdim) ;
	void Calcslope (short int *indat, float *outdat, float pixdim) ;
	void Calcslope (int *indat, float *outdat, float pixdim) ;
	void Calcslope (float *indat, float *outdat, float pixdim) ;
	CTopoArray();
	virtual ~CTopoArray();

	float maskmin ;



};

#endif // !defined(AFX_TOPOARRAY_H__941DFE22_6A48_11D5_BABA_005056986301__INCLUDED_)
