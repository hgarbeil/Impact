// FileOperations.cpp: implementation of the CFileOperations class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Newest.h"
#include "FileOperations.h"
#include <fstream>
#include <iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std ;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileOperations::CFileOperations()
{
	envi2me_dt [0] = 0 ;
	envi2me_dt [1] = 0 ;
	envi2me_dt [2] = 1 ;
	envi2me_dt [3] = 2 ;
	envi2me_dt [4] = 3 ;
	envi2me_dt [5] = 3 ;
	envi2me_dt [6] = 4 ;
	me2envi_dt [0] = 0 ;
	me2envi_dt [1] = 2 ;
	me2envi_dt [2] = 3 ;
	me2envi_dt [3] = 4 ;
	me2envi_dt [4] = 6 ;

	for (int i=0; i<4; i++) grid_ll [i] = 0. ;
}

CFileOperations::~CFileOperations()
{

}

int CFileOperations::WriteHdrFile(char *filename, int ns, int nl, int nb, int dt, int bform)
{

	// the filename is not appended with the .hdr suffix.
	// therefore, the program should check to make sure it has been passed with a .hdr
	// suffix



	char buf [240], *token ;
	int  len, len1 ;

	token = strstr (filename, ".hdr") ;
	len = strlen (filename) ;
	len1 = strlen (token) ;
	if (len1 <4) return (-1) ;
	ofstream ofil (filename, ios::out) ;
	if (ofil.bad() )
		return (-1) ;
	ofil << "ENVI" << endl ;
	ofil << "description = {" << endl ;
	ofil << "   File Imported into ENVI.}" << endl ;


	sprintf (buf, "samples = %5d", ns) ;
	ofil << buf << endl ;

	sprintf (buf, "lines = %d", nl) ;
	ofil << buf << endl ;

	sprintf (buf, "bands = %d", nb) ;
	ofil << buf << endl ;

	dt = me2envi_dt [dt] ;
	sprintf (buf, "data type = %1d", dt) ;
	ofil << buf << endl ;

	switch (bform) {
	case '0' :
			strcpy (buf, "interleave = bsq") ;
			ofil << buf << endl ;
			break ;
	case '1' :
			strcpy (buf, "interleave = bil") ;
			ofil << buf << endl ;
			break ;
	case '2' :
			strcpy (buf, "interleave = bip") ;
			ofil << buf << endl ;
			break ;
	}


	return (0) ;
}


int CFileOperations::ReadEnviHeader(char *pathname) 
{

	int  dt ;
	char linedat [440], *token, *newtoken ;
	CFileStatus cfs ;
	
	

	CFile cfil (pathname, CFile::modeRead) ;
	cfil.GetStatus (cfs) ;
	if (cfil == NULL) {
		sprintf (linedat,"Problem opening %s", pathname) ;
		MessageBox (NULL, linedat, TEXT("ERROR"), MB_OK) ;
		return (-1) ;
	}
	cfil.Close () ;
	
	ifstream ifil (pathname, ios::in) ;
	newtoken = strstr(pathname,".hdr") ;
	strncpy (filename, pathname, newtoken-pathname) ; 
	strcpy (filename + (newtoken-pathname), "") ;
	

	while (!ifil.eof()){

		ifil.getline (linedat, 440, '\n') ;
		if (strlen (linedat) < 2 && ifil.eof()) break ;
		token = strtok (linedat, "=") ;
			// find the issues of concern
		
		if (!strncmp (token, "samp", 4)) {
			token = strtok (NULL, "=") ;
			samps = atoi (token) ;	
		}
		
		if (!strncmp (token, "line", 4)) {
			token = strtok (NULL, "=") ;
			lines = atoi (token) ;	
		}

		if (!strncmp (token, "bands", 5)) {
			token = strtok (NULL, "=") ;
			bands = atoi (token) ;	
		}

		if (!strncmp (token, "data", 4)) {
			token = strtok (NULL, "=") ;
			dt = atoi (token) ;	
			dtype = envi2me_dt [dt] ;
		}
		if (!strncmp (token, "inte", 4)) {
			token = strtok (NULL, "=") ;
			if (!strncmp(token, "bsq",3)) bform = 0 ;
			if (!strncmp(token, "bil",3)) bform = 1 ;
			if (!strncmp(token, "bip",3)) bform = 2 ;
		}

		if (!strncmp (token, "map", 3)) {
			token = strtok (NULL, ",") ;
			token = strtok (NULL, ",") ;
			token = strtok (NULL, ",") ;
			token = strtok (NULL, ",") ;
			// get lat, lon, space_x, space_y
			grid_ll [0] = atof (token) ;
			token = strtok (NULL, ",") ;
			grid_ll [1] =  atof (token) ;
			token = strtok (NULL, ",") ;
			grid_ll [2] =  atof (token) ;
			token = strtok (NULL, ",") ;
			grid_ll [3] =  atof (token) ;
		}
			
			

			
		
			
		
	
		//TRACE ("%s\n", linedat) ;
	}
	ifil.close() ;



	return (0) ;
}


