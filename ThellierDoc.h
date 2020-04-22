// ThellierDoc.h : Schnittstelle der Klasse CThellierDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THELLIERDOC_H__213E8079_E20E_11D3_A435_0050043044BE__INCLUDED_)
#define AFX_THELLIERDOC_H__213E8079_E20E_11D3_A435_0050043044BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CThellierDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CThellierDoc();
	DECLARE_DYNCREATE(CThellierDoc)

// Attribute
public:

	// Loading files
	CString samplethellier [99];
	CString line;
	float temp [99];
	float mag [99];
	float dec [99];
	float inc [99];
	int thellier_datalength;

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CThellierDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementierung
public:
	int m_lfield;
	int m_temp_max;
	int temp_min;
	virtual ~CThellierDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CThellierDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_THELLIERDOC_H__213E8079_E20E_11D3_A435_0050043044BE__INCLUDED_)
