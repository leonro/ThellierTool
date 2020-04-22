// ThellierView.h : Schnittstelle der Klasse CThellierView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THELLIERVIEW_H__213E807B_E20E_11D3_A435_0050043044BE__INCLUDED_)
#define AFX_THELLIERVIEW_H__213E807B_E20E_11D3_A435_0050043044BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CThellierView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CThellierView();
	DECLARE_DYNCREATE(CThellierView)

// Attribute
public:
	CThellierDoc* GetDocument();

	// Loading files
	CString samplethellier [99];
	CString line;
	float temp [99];
	float mag [99];
	float dec [99];
	float inc [99];
	int thellier_datalength;
	// Calculation
	double xTH[99];
	double yTH[99];
	double zTH[99];

	double magTH[99];
	double tempTH[99];
	double magPT[99];
	double tempPT[99];
	double magCK[99];
	double tempCK[99];
	double tempCKstart[99];
	double maxmagPT;
	double maxmagTH;

	int pTRM_steps;
	int TH_steps;

	// Bildschirmausgabe
	double x_gerade;
	double y_gerade;
	double CK_error[99];
	double max_CK_error;
	double paleofield;
	double slope;
	int number_of_points;
	double stderror_vs_slope;
	double stddev;
	double f, g, Q;
	double w;
	// Menü-Variablen
	int m_komp;
	double m_field;
	int temp_range_min;
	int temp_range_max;

	// zum Testen

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CThellierView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
public:
	void Linear(int t_start, int t_end);
	void Calculation();
	virtual ~CThellierView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CThellierView)
	afx_msg void OnVektorFkomp();
	afx_msg void OnVektorZkomp();
	afx_msg void OnOptionenRange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in ThellierView.cpp
inline CThellierDoc* CThellierView::GetDocument()
   { return (CThellierDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_THELLIERVIEW_H__213E807B_E20E_11D3_A435_0050043044BE__INCLUDED_)
