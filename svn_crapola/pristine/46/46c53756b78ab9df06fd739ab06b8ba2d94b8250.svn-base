// ImageFile.h: interface for the CImageFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEFILE_H__3AE27010_60D9_11D5_BAB5_005056986301__INCLUDED_)
#define AFX_IMAGEFILE_H__3AE27010_60D9_11D5_BAB5_005056986301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "FileOperations.h"
#include "CraterStats.h"
#include "NewestDoc.h"

typedef struct cpm  {
		unsigned int crater  : 1 ;
		unsigned int rim : 1 ;
		unsigned int primary : 1 ;
		unsigned int secondary : 1 ;
	} Crater_pixmask ;

class CImageFile  
{
public:
	void SetCDocument (CNewestDoc *cptr);
	float CalcCraterVolume (POINT *, int npts);
	float CalcRimVolume (POINT *, int npts) ;
	float CalcPrimaryVolume (POINT *, int npts) ;
	float CalcSecondaryVolume (POINT *, int npts) ;
	int WriteHeaderFile ();
	int GetOutputFile (char *startdir);
	void SetParams (int ns, int nl, int dt, int nb, int bf);
	void LoadSurfCoefs (float *scoefs) ;
	void LoadSurfCoefs (double *scoefs) ;
	void DefMask () ;
	CImageFile (int ns, int nl, int dtype, int nb, int bf);
	void MessageOut (char *);
	int GetFile_and_Params (char *);
	long bytesperband;
	int GetData (int ns, int nl, int dtype, int bandnum);
	int GetData ();
	float GetVal (int x, int y) ;
	float GetVal_Corr (int x, int y) ;
	void GetLatLon (int x, int y, float *lon, float *lat) ;
	int GetData_3 (int ns, int nl, int dtype, int nbands, int *bandarr);

	int FindCrater (POINT *, int) ;
	int WriteData () ;
	int AllocData (int nb) ;
	int nbands;
	int ReadDDR (char *filename);
	int ReadEnviHeader(char *pathname, char *filename);
	int ReadEnviHeader(char *pathname);

	CImageFile();
	virtual ~CImageFile();

	char	filename [420] ;
	unsigned char *maskarr ;
	int		lines ;
	int		samps ;
	int		dtype ; // 0 - byte ; 1 - short int ; 2 - i*4 ; 3 - float ; 4 - complex
	int		bform ; // 0 - bsq ; 1 - bil ; 2 - bip
	int     bpp [4] ;
	int     bytesperpixel ;
	unsigned char *data ;
	unsigned char *rawdata ;
	float   coefs [6] ;
	double  grid_ll [4] ;

	Crater_pixmask *CPM ;
	CNewestDoc	*cnd ;

	// impact crater stuff
	float crater_volume, rim_volume, primary_volume, secondary_volume ;

	CFileOperations cfo ;
};

#endif // !defined(AFX_IMAGEFILE_H__3AE27010_60D9_11D5_BAB5_005056986301__INCLUDED_)
