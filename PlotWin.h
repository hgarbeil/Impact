#if !defined(AFX_PLOTWIN_H__E9B95E32_7161_11D5_BABE_005056986301__INCLUDED_)
#define AFX_PLOTWIN_H__E9B95E32_7161_11D5_BABE_005056986301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlotWin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlotWin frame

class CPlotWin : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPlotWin)
protected:
	          // protected constructor used by dynamic creation

// Attributes
public:
	CPlotWin();
	virtual ~CPlotWin();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlotWin)
	//}}AFX_VIRTUAL

// Implementation
protected:
	

	// Generated message map functions
	//{{AFX_MSG(CPlotWin)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLOTWIN_H__E9B95E32_7161_11D5_BABE_005056986301__INCLUDED_)
