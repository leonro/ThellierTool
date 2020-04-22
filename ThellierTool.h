// ThellierTool.h : Haupt-Header-Datei für die Anwendung THELLIERTOOL
//

#if !defined(AFX_THELLIERTOOL_H__9BBCB262_4675_45C4_BD9A_0E5C18059CF6__INCLUDED_)
#define AFX_THELLIERTOOL_H__9BBCB262_4675_45C4_BD9A_0E5C18059CF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

#include "afxtempl.h"  // Vorlagen für typsicherheit (leon, 3.06.02)
#include "ThellierToolDoc.h" //Hauptfenster
#include "ResultForm.h"	// Editierbares Datenfenster (9.11.2001)
#include "CriteriaDlg.h"	// Kriterienfenster (22.03.2003)
#include <math.h>



/////////////////////////////////////////////////////////////////////////////
// CThellierToolApp:
// Siehe ThellierTool.cpp für die Implementierung dieser Klasse
//

class CThellierToolApp : public CWinApp
{
public:
	CThellierToolApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CThellierToolApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementierung
//	CCriteriaStruct criteria; // eingefügt von leon 
	COleTemplateServer m_server;
		// Server-Objekt für Dokumenterstellung
	//{{AFX_MSG(CThellierToolApp)
	afx_msg void OnAppAbout();
	afx_msg void OnCriteria();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_THELLIERTOOL_H__9BBCB262_4675_45C4_BD9A_0E5C18059CF6__INCLUDED_)
