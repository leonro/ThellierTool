// SrvrItem.cpp : Implementierung der Klasse CThellierToolSrvrItem
//

#include "stdafx.h"
#include "ThellierTool.h"

#include "ThellierToolDoc.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThellierToolSrvrItem Implementierung

IMPLEMENT_DYNAMIC(CThellierToolSrvrItem, COleServerItem)

CThellierToolSrvrItem::CThellierToolSrvrItem(CThellierToolDoc* pContainerDoc)
	: COleServerItem(pContainerDoc, TRUE)
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen
	//  (z.B. Hinzufügen von zusätzlichen Zwischenablageformaten zur Datenquelle des Elements)
}

CThellierToolSrvrItem::~CThellierToolSrvrItem()
{
	// ZU ERLEDIGEN: Hier Bereinigungscode hinzufügen
}

void CThellierToolSrvrItem::Serialize(CArchive& ar)
{
	// CThellierToolSrvrItem::Serialize wird automatisch aufgerufen, wenn
	//  das Element in die Zwischenablage kopiert wird. Dies kann automatisch 
	//  über die OLE-Rückruffunktion OnGetClipboardData geschehen. Ein Standardwert für
	//  das eingebundene Element dient einfach zur Delegierung der Serialisierungsfunktion des 
	//  Dokuments. Wenn Sie Verweise unterstützen, möchten Sie vielleicht nur einen Teil des
	//  Dokuments serialisieren.

	if (!IsLinkedItem())
	{
		CThellierToolDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->Serialize(ar);
	}
}

BOOL CThellierToolSrvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// Die meisten Anwendungen (wie auch diese) unterstützen als einzigen Aspekt das Zeichnen
	//  des Elementinhalts. Wollen Sie andere Aspekte unterstützen, wie z.B.
	//  DVASPECT_THUMBNAIL (durch Überladen von OnDrawEx), so sollte diese
	//  Implementierung von OnGetExtent dahingehend modifiziert werden, dass sie
	//  zusätzliche Aspekte verarbeiten kann.

	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// CThellierToolSrvrItem::OnGetExtent wird aufgerufen, um das Extent in 
	//  HIMETRIC-Einheiten des gesamten Elements zu ermitteln. Die Standardimplementierung
	//  liefert hier einfach eine fest programmierte Einheitenanzahl zurück.

	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// ZU ERLEDIGEN: Ersetzen Sie diese willkürlich gewählte Größe

	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC Einheiten

	return TRUE;
}

BOOL CThellierToolSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	// Entfernen Sie dies, wenn Sie rSize verwenden
	UNREFERENCED_PARAMETER(rSize);

	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// ZU ERLEDIGEN: Setzen Sie Mapping-Modus und Extent
	//  (Das Extent stimmt üblicherweise mit der von OnGetExtent zurückgelieferten Größe überein)
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

	// ZU ERLEDIGEN: Hier Code zum Zeichnen einfügen. Füllen Sie wahlweise das HIMETRIC-Extent aus.
	//  Alle Zeichenoperationen finden innerhalb des Metadatei-Gerätekontexts (pDC) statt.

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CThellierToolSrvrItem Diagnose

#ifdef _DEBUG
void CThellierToolSrvrItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void CThellierToolSrvrItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
