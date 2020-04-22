#if !defined(AFX_RANGEDLG1_H__FDD03DB7_E6E6_11D3_A435_0050043044BE__INCLUDED_)
#define AFX_RANGEDLG1_H__FDD03DB7_E6E6_11D3_A435_0050043044BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RangeDlg1.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CRangeDlg 

class CRangeDlg : public CDialog
{
// Konstruktion
public:
	CThellierDoc* m_pDoc;
	CRangeDlg(CThellierDoc* pDocu, CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CRangeDlg)
	enum { IDD = IDD_RANGE_DIALOG };
	int		m_tempmin;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CRangeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CRangeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_RANGEDLG1_H__FDD03DB7_E6E6_11D3_A435_0050043044BE__INCLUDED_
