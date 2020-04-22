#if !defined(AFX_RANGEFORM_H__FDD03DB6_E6E6_11D3_A435_0050043044BE__INCLUDED_)
#define AFX_RANGEFORM_H__FDD03DB6_E6E6_11D3_A435_0050043044BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RangeForm.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CRangeForm 

class CRangeForm : public CDialog
{
// Konstruktion
public:
	CThellierDoc* m_pDoc;
	CRangeForm(CThellierDoc* pDocu, CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CRangeForm)
	enum { IDD = IDD_FORMVIEW };
	int		m_tempmin;
	CThellierView*	m_field;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CRangeForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CRangeForm)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_RANGEFORM_H__FDD03DB6_E6E6_11D3_A435_0050043044BE__INCLUDED_
