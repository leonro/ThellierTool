// ChildFrm.cpp : Implementierung der Klasse CChildFrame
//

#include "stdafx.h"
#include "ThellierTool.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

// eingefügt von leon (19.12.03)
int CChildFrame::m_nDefCmdShow = SW_SHOWMAXIMIZED;
int CChildFrame::m_nDefCmdShowOld = SW_SHOWMAXIMIZED;
// Variablen für Fenstergröße
int CChildFrame::m_v0_x = 570;
int CChildFrame::m_v0_y = 50;
int CChildFrame::m_v1_x = 300;
int CChildFrame::m_v1_y = 355;
int CChildFrame::m_v0_x_old = 570;
int CChildFrame::m_v0_y_old = 50;
int CChildFrame::m_v1_x_old = 300;
int CChildFrame::m_v1_y_old = 355;

static TCHAR BASED_CODE szSec[] = _T("Settings");
static TCHAR BASED_CODE szShowCmd[] = _T("ShowCmd");
static TCHAR BASED_CODE szSplit0x[] = _T("FrameSplit0x");
static TCHAR BASED_CODE szSplit0y[] = _T("FrameSplit0y");
static TCHAR BASED_CODE szSplit1x[] = _T("FrameSplit1x");
static TCHAR BASED_CODE szSplit1y[] = _T("FrameSplit1y");


BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame Konstruktion/Destruktion

CChildFrame::CChildFrame()
{
	// ZU ERLEDIGEN: Hier Code zur Member-Initialisierung einfügen
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{

	// create a splitter with 1 row, 2 columns
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	// add the first splitter pane - the default view in column 0
	if (!m_wndSplitter.CreateView(0, 0,
		pContext->m_pNewViewClass, CSize(m_v0_x, m_v0_y), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(CResultForm), CSize(m_v1_x, m_v1_y), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}

	// activate the input view
	SetActiveView((CView*)m_wndSplitter.GetPane(0,0));

	return TRUE;

}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;

}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame Diagnose

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame Nachrichten-Handler


// eingefügt von leon (19.12.03)
void CChildFrame::Initialize()
{
	// Fenster maximiert oder normal
	m_nDefCmdShow = AfxGetApp()->GetProfileInt(szSec, szShowCmd, m_nDefCmdShow);
	m_nDefCmdShowOld = m_nDefCmdShow;
	// Grösse der Splitter
	m_v0_x = AfxGetApp()->GetProfileInt(szSec, szSplit0x, m_v0_x);
	m_v0_x_old = m_v0_x;
	m_v0_y = AfxGetApp()->GetProfileInt(szSec, szSplit0y, m_v0_y);
	m_v0_y_old = m_v0_y;
	m_v1_x = AfxGetApp()->GetProfileInt(szSec, szSplit1x, m_v1_x);
	m_v1_x_old = m_v1_x;
	m_v1_y = AfxGetApp()->GetProfileInt(szSec, szSplit1y, m_v1_y);
	m_v1_y_old = m_v1_y;

}

void CChildFrame::Terminate()
{
	if (m_nDefCmdShow != m_nDefCmdShowOld)
	{
		AfxGetApp()->WriteProfileInt(szSec, szShowCmd, m_nDefCmdShow);
		m_nDefCmdShowOld = m_nDefCmdShow;
	}
	// Grösse der Splitter
	if (m_v0_x != m_v0_x_old)
	{
		AfxGetApp()->WriteProfileInt(szSec, szSplit0x, m_v0_x);
		m_v0_x_old = m_v0_x;
	}
	if (m_v0_y != m_v0_y_old)
	{
		AfxGetApp()->WriteProfileInt(szSec, szSplit0y, m_v0_y);
		m_v0_y_old = m_v0_y;
	}
	if (m_v1_x != m_v1_x_old)
	{
		AfxGetApp()->WriteProfileInt(szSec, szSplit1x, m_v1_x);
		m_v1_x_old = m_v1_x;
	}
	if (m_v1_y != m_v1_y_old)
	{
		AfxGetApp()->WriteProfileInt(szSec, szSplit1y, m_v1_y);
		m_v1_y_old = m_v1_y;
	}
}

void CChildFrame::ActivateFrame(int nCmdShow) 
{
	if (nCmdShow == -1)
		nCmdShow = m_nDefCmdShow;   // verwenden unserer Defaulteinstellung
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

void CChildFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIChildWnd::OnSize(nType, cx, cy);
	
	if (!IsWindowVisible())
		return;

	int wx;
	int minwx;
	m_wndSplitter.GetColumnInfo(0, wx, minwx);
	m_v0_x = wx;
	
	switch (nType)
	{
	case SIZE_MAXIMIZED:
		m_nDefCmdShow = SW_SHOWMAXIMIZED;
		break;
	case SIZE_RESTORED:
		m_nDefCmdShow = SW_SHOWNORMAL;
		break;
	}	
}


void CChildFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CMDIChildWnd::OnShowWindow(bShow, nStatus);
	
	int wx;
	int minwx;
	m_wndSplitter.GetColumnInfo(0, wx, minwx);
	m_v0_x = wx;	
}

