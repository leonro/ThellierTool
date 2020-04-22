#if !defined(AFX_RESULTFORM_H__02FB5CE1_5D0E_462F_B0D3_037EA990DAF4__INCLUDED_)
#define AFX_RESULTFORM_H__02FB5CE1_5D0E_462F_B0D3_037EA990DAF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultForm.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Formularansicht CResultForm 

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CResultForm : public CFormView
{
protected:
	CResultForm();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CResultForm)

// Formulardaten
public:
	//{{AFX_DATA(CResultForm)
	enum { IDD = IDD_RESULTFORM_FORM };
	CListBox	m_taillist;
	CListBox	m_rawdatalist;
	float	m_labfield;
	CString	m_samplename;
	int		m_mainview;
	int		m_coordinates;
	BOOL	m_accheck;
	BOOL	m_ckcorr;
	BOOL	m_zonly;
	int		m_auto;
	int		m_mintemp;
	int		m_maxtemp;
	int		m_N;
	double	m_slope;
	double	m_stdslope;
	double	m_sd;
	double	m_palint;
	double	m_q;
	double	m_w;
	double	m_g;
	double	m_f;
	CString	m_class;
	CString	m_type;
	double	m_trm;
	double	m_nrmt;
	double	m_mad;
	double	m_inc;
	double	m_dec;
	double	m_ckdiff;
	double	m_ckerror;
	double	m_acerror;
	double	m_trerror;
	BOOL	m_use_autock;
	double	m_drat;
	double	m_alpha;
	double	m_tstar;
	double	m_dec_na;
	double	m_inc_na;
	double	m_mad_na;
	CString	m_altcheckmethod;
	//}}AFX_DATA

// Attribute
public:
	CThellierToolDoc* GetDocument()
			{ return (CThellierToolDoc*)m_pDocument; }

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CResultForm)
	public:
	virtual void OnFinalRelease();
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CResultForm();
	static CString savefilename;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CResultForm)
	afx_msg void OnCorecoRadio();
	afx_msg void OnGeocoRadio();
	afx_msg void OnBedcoRadio();
	afx_msg void OnThellierplotRadio();
	afx_msg void OnZijplotRadio();
	afx_msg void OnDecayplotRadio();
	afx_msg void OnMdplotRadio();
	afx_msg void OnAllplotsRadio();
	afx_msg void OnAcCheck();
	afx_msg void OnCorrCheck();
	afx_msg void OnZonlyCheck();
	afx_msg void OnAutoRadio();
	afx_msg void OnManuellRadio();
	afx_msg void OnApplyButton();
	afx_msg void OnSaveresultsButton();
	afx_msg void OnNotepadButton();
	afx_msg void OnAutockCheck();
	afx_msg void OnTestButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generierte OLE-Dispatch-Zuordnungsfunktionen
	//{{AFX_DISPATCH(CResultForm)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_RESULTFORM_H__02FB5CE1_5D0E_462F_B0D3_037EA990DAF4__INCLUDED_
