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
	// ZU ERLEDIGEN: Hier Code f�r One-Time-Konstruktion einf�gen
	//  (z.B. Hinzuf�gen von zus�tzlichen Zwischenablageformaten zur Datenquelle des Elements)
}

CThellierToolSrvrItem::~CThellierToolSrvrItem()
{
	// ZU ERLEDIGEN: Hier Bereinigungscode hinzuf�gen
}

void CThellierToolSrvrItem::Serialize(CArchive& ar)
{
	// CThellierToolSrvrItem::Serialize wird automatisch aufgerufen, wenn
	//  das Element in die Zwischenablage kopiert wird. Dies kann automatisch 
	//  �ber die OLE-R�ckruffunktion OnGetClipboardData geschehen. Ein Standardwert f�r
	//  das eingebundene Element dient einfach zur Delegierung der Serialisierungsfunktion des 
	//  Dokuments. Wenn Sie Verweise unterst�tzen, m�chten Sie vielleicht nur einen Teil des
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
	// Die meisten Anwendungen (wie auch diese) unterst�tzen als einzigen Aspekt das Zeichnen
	//  des Elementinhalts. Wollen Sie andere Aspekte unterst�tzen, wie z.B.
	//  DVASPECT_THUMBNAIL (durch �berladen von OnDrawEx), so sollte diese
	//  Implementierung von OnGetExtent dahingehend modifiziert werden, dass sie
	//  zus�tzliche Aspekte verarbeiten kann.

	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// CThellierToolSrvrItem::OnGetExtent wird aufgerufen, um das Extent in 
	//  HIMETRIC-Einheiten des gesamten Elements zu ermitteln. Die Standardimplementierung
	//  liefert hier einfach eine fest programmierte Einheitenanzahl zur�ck.

	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// ZU ERLEDIGEN: Ersetzen Sie diese willk�rlich gew�hlte Gr��e

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
	//  (Das Extent stimmt �blicherweise mit der von OnGetExtent zur�ckgelieferten Gr��e �berein)
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

	// ZU ERLEDIGEN: Hier Code zum Zeichnen einf�gen. F�llen Sie wahlweise das HIMETRIC-Extent aus.
	//  Alle Zeichenoperationen finden innerhalb des Metadatei-Ger�tekontexts (pDC) statt.

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
