// Thellier.h : Haupt-Header-Datei f�r die Anwendung THELLIER
//

#if !defined(AFX_THELLIER_H__213E8073_E20E_11D3_A435_0050043044BE__INCLUDED_)
#define AFX_THELLIER_H__213E8073_E20E_11D3_A435_0050043044BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CThellierApp:
// Siehe Thellier.cpp f�r die Implementierung dieser Klasse
//

class CThellierApp : public CWinApp
{
public:
	CThellierApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CThellierApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CThellierApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_THELLIER_H__213E8073_E20E_11D3_A435_0050043044BE__INCLUDED_)
