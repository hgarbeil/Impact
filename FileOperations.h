// FileOperations.h: interface for the CFileOperations class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOPERATIONS_H__0A5EE797_C8F6_4FFB_BA65_D11860999CE3__INCLUDED_)
#define AFX_FILEOPERATIONS_H__0A5EE797_C8F6_4FFB_BA65_D11860999CE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileOperations  
{
public:
	int WriteHdrFile(char *fname, int ns,int nl, int nb, int dt, int bform);
	int ReadEnviHeader (char *fname) ;
	CFileOperations();
	virtual ~CFileOperations();

	char filename [420] ;
	 
	int me2envi_dt [7] ;
	int envi2me_dt [7] ;
	double grid_ll [4] ;
	int samps ; 
	int lines ;
	int bands ;
	int dtype ;
	int bform ;

};

#endif // !defined(AFX_FILEOPERATIONS_H__0A5EE797_C8F6_4FFB_BA65_D11860999CE3__INCLUDED_)
