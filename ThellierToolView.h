// ThellierToolView.h : Schnittstelle der Klasse CThellierToolView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THELLIERTOOLVIEW_H__0DDD1084_1514_4398_96B6_83BD0A26AE0F__INCLUDED_)
#define AFX_THELLIERTOOLVIEW_H__0DDD1084_1514_4398_96B6_83BD0A26AE0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CThellierToolView : public CScrollView
{
protected: // Nur aus Serialisierung erzeugen
	CThellierToolView();
	DECLARE_DYNCREATE(CThellierToolView)

// Attribute
public:
	CThellierToolDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CThellierToolView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // das erste mal nach der Konstruktion aufgerufen
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
public:
	void AllPlots(CDC *pDC, int scfa);
	void MDPlot(CDC *pDC, int x_pos, int y_pos, int viewmode, int scfa, CThellierResList *datalist, CThellierResList *secondlist, CThellierResList *thirdlist);
	void DecayPlot(CDC *pDC, int x_pos, int y_pos, int viewmode, int scfa, CThellierResList *datalist, CThellierResList *secondlist);
	void ZijPlot(CDC *pDC, int x_pos, int y_pos, int viewmode, int scfa, CThellierResList *datalist, CThellierResList *secondlist);
	void ThellierPlot(CDC *pDC, int x_pos, int y_pos, int viewmode, int scfa, CThellierResList *datalist, CThellierResList *secondlist, CThellierResList *thirdlist, CThellierResList *fourthlist);
	virtual ~CThellierToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CThellierToolView)
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnEditCopy();
	afx_msg void OnFileSavegraph();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in ThellierToolView.cpp
inline CThellierToolDoc* CThellierToolView::GetDocument()
   { return (CThellierToolDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_THELLIERTOOLVIEW_H__0DDD1084_1514_4398_96B6_83BD0A26AE0F__INCLUDED_)
