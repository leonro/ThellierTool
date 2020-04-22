// SrvrItem.h : Schnittstelle der Klasse CThellierToolSrvrItem
//

#if !defined(AFX_SRVRITEM_H__AAF0AF93_E8F6_4B07_A1EF_68648C7D0EA1__INCLUDED_)
#define AFX_SRVRITEM_H__AAF0AF93_E8F6_4B07_A1EF_68648C7D0EA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CThellierToolSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CThellierToolSrvrItem)

// Konstruktoren
public:
	CThellierToolSrvrItem(CThellierToolDoc* pContainerDoc);

// Attribute
	CThellierToolDoc* GetDocument() const
		{ return (CThellierToolDoc*)COleServerItem::GetDocument(); }

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CThellierToolSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementierung
public:
	~CThellierToolSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // überladen für Dokument-E/A
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_SRVRITEM_H__AAF0AF93_E8F6_4B07_A1EF_68648C7D0EA1__INCLUDED_)
