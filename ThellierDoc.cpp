// ThellierDoc.cpp : Implementierung der Klasse CThellierDoc
//

#include "stdafx.h"
#include "Thellier.h"

#include "ThellierDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThellierDoc

IMPLEMENT_DYNCREATE(CThellierDoc, CDocument)

BEGIN_MESSAGE_MAP(CThellierDoc, CDocument)
	//{{AFX_MSG_MAP(CThellierDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThellierDoc Konstruktion/Destruktion

CThellierDoc::CThellierDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CThellierDoc::~CThellierDoc()
{
}

BOOL CThellierDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CThellierDoc Serialisierung

void CThellierDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Hier Code zum Speichern einfügen
	}
	else
	{
		CString line;
		int pos;
		int k = 1;
	
		while(ar.ReadString(line) != NULL)
		{
			pos = line.Find("\t",0);
			if (pos <= 0)
				pos = line.Find(" ",0);
			samplethellier[k] = line.Left(pos);
			line.Replace(samplethellier[k],"");
			sscanf ( line, "%e%e%e%e", &temp[k], &mag[k], &dec[k], &inc[k]);
			k++;
			thellier_datalength = k;
		}

	}
}

/////////////////////////////////////////////////////////////////////////////
// CThellierDoc Diagnose

#ifdef _DEBUG
void CThellierDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CThellierDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThellierDoc Befehle

BOOL CThellierDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	temp_min = 20;
	m_temp_max = 600;
	m_lfield = 35;
	return TRUE;
}
