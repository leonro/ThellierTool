// RangeDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Thellier.h"
#include "RangeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld RangeDlg 


RangeDlg::RangeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RangeDlg::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(RangeDlg)
	m_tempmax = 0;
	m_tempmin = 0;
	m_lfield = 0.0f;
	//}}AFX_DATA_INIT
}


void RangeDlg::OnFinalRelease()
{
	// Nachdem die letzte Referenz auf ein Automatisierungsobjekt freigegeben wurde,
	// wird OnFinalRelease aufgerufen. Die Basisklasse l�scht das Objekt
	// automatisch. F�gen Sie zus�tzlichen Bereinigungscode f�r Ihr Objekt
	// hinzu, bevor Sie die Basisklasse aufrufen.

	CDialog::OnFinalRelease();
}

void RangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RangeDlg)
	DDX_Text(pDX, IDC_TEMPMAX_EDIT, m_tempmax);
	DDX_Text(pDX, IDC_TEMPMIN_EDIT, m_tempmin);
	DDX_Text(pDX, IDC_LFIELD_EDIT, m_lfield);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RangeDlg, CDialog)
	//{{AFX_MSG_MAP(RangeDlg)
		// HINWEIS: Der Klassen-Assistent f�gt hier Zuordnungsmakros f�r Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(RangeDlg, CDialog)
	//{{AFX_DISPATCH_MAP(RangeDlg)
		// HINWEIS - Der Klassen-Assistent f�gt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Hinweis: Wir stellen Unterst�tzung f�r IID_IRangeDlg zur Verf�gung, um typsicheres Binden
//  von VBA zu erm�glichen. Diese IID muss mit der GUID �bereinstimmen, die in der
//  Disp-Schnittstelle in der .ODL-Datei angegeben ist.

// {FDD03DB1-E6E6-11D3-A435-0050043044BE}
static const IID IID_IRangeDlg =
{ 0xfdd03db1, 0xe6e6, 0x11d3, { 0xa4, 0x35, 0x0, 0x50, 0x4, 0x30, 0x44, 0xbe } };

BEGIN_INTERFACE_MAP(RangeDlg, CDialog)
	INTERFACE_PART(RangeDlg, IID_IRangeDlg, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten RangeDlg 
