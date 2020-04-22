// IpFrame.cpp : Implementierung der Klasse CInPlaceFrame
//

#include "stdafx.h"
#include "ThellierTool.h"

#include "IpFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame

IMPLEMENT_DYNCREATE(CInPlaceFrame, COleIPFrameWnd)

BEGIN_MESSAGE_MAP(CInPlaceFrame, COleIPFrameWnd)
	//{{AFX_MSG_MAP(CInPlaceFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame Konstruktion/Destruktion

CInPlaceFrame::CInPlaceFrame()
{
}

CInPlaceFrame::~CInPlaceFrame()
{
}

int CInPlaceFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleIPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// CResizeBar implementiert direkte Gr��en�nderungen.
	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Leiste f�r Gr��en�nderung konnte nicht erstellt werden\n");
		return -1;      // Fehler bei Erstellung
	}

	// Allgemein ist es von Vorteil, ein Drop-Ziel zu registrieren, das
	//  keinerlei Auswirkung auf Ihr Rahmenfenster hat. Dies verhindert bei Drops ("Abw�rfen")
	// ein "Durchfallen" zu einem Container, der Drag and Drop unterst�tzt.
	m_dropTarget.Register(this);

	return 0;
}

// OnCreateControlBars wird automatisch aufgerufen, um Steuerleisten im Fenster der
//  Container-Anwendung zu erstellen. pWndFrame ist das hierarchisch h�chste Rahmenfenster des
//  Containers und ist immer ungleich NULL. pWndDoc ist das Rahmenfenster auf Dokumentebene
//  und ist gleich NULL, wenn der Container eine SDI-Anwendung ist. Eine Server
//  Anwendung kann MFC-Steuerelementleisten in jedes Fenster platzieren.
BOOL CInPlaceFrame::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// Entfernen Sie dies, wenn Sie pWndDoc verwenden
	UNREFERENCED_PARAMETER(pWndDoc);

	// Dieses Fenster als Owner festlegen, damit Nachrichten an die richtige Anwendung gesendet werden
	m_wndToolBar.SetOwner(this);

	// Symbolleiste im Client-Fenster erzeugen
	if (!m_wndToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_THELLITYPE_SRVR_IP))
	{
		TRACE0("Symbolleiste konnte nicht erstellt werden\n");
		return FALSE;
	}

	// ZU ERLEDIGEN: L�schen Sie diese drei Zeilen, wenn Sie nicht wollen, dass die Symbolleiste
	//  andockbar ist.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->DockControlBar(&m_wndToolBar);

	return TRUE;
}

BOOL CInPlaceFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: �ndern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return COleIPFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame Diagnose

#ifdef _DEBUG
void CInPlaceFrame::AssertValid() const
{
	COleIPFrameWnd::AssertValid();
}

void CInPlaceFrame::Dump(CDumpContext& dc) const
{
	COleIPFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame Befehle