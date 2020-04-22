// ThellierTool.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "ThellierTool.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "IpFrame.h"
#include "ThellierToolDoc.h"
#include "ThellierToolView.h"
#include "ResultForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThellierToolApp

BEGIN_MESSAGE_MAP(CThellierToolApp, CWinApp)
	//{{AFX_MSG_MAP(CThellierToolApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_CRITERIA, OnCriteria)
	//}}AFX_MSG_MAP
	// Dateibasierte Standard-Dokumentbefehle
//	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard-Druckbefehl "Seite einrichten"
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThellierToolApp Konstruktion

CThellierToolApp::CThellierToolApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CThellierToolApp-Objekt

CThellierToolApp theApp;

// Dieser Bezeichner wurde als statistisch eindeutig für Ihre Anwendung generiert.
// Sie können ihn ändern, wenn Sie einen bestimmten Bezeichnernamen bevorzugen.

// {64EC95E4-D441-11D5-A5A1-00105AD56AB0}
static const CLSID clsid =
{ 0x64ec95e4, 0xd441, 0x11d5, { 0xa5, 0xa1, 0x0, 0x10, 0x5a, 0xd5, 0x6a, 0xb0 } };

/////////////////////////////////////////////////////////////////////////////
// CThellierToolApp Initialisierung

BOOL CThellierToolApp::InitInstance()
{

/* auskommentiert, um Startauswahl zu verhindern (23.03.03, leon)

  {	// BLOCK: Registrierung der Dokumentvorlage
		// Registrieren der Dokumentvorlage.  Dokumentvorlagen dienen
		// als Verbindung zwischen Dokumenten, Rahmenfenstern und Ansichten.
		// Verbinden Sie dieses Formular mit einem anderen Dokument oder Rahmenfenster, indem Sie
		// das Dokument oder die Rahmenklasse im unten folgenden Konstruktor ändern.
		CMultiDocTemplate* pNewDocTemplate = new CMultiDocTemplate(
			IDR_RESULTFORM_TMPL,
			RUNTIME_CLASS(CThellierToolDoc),		// Dokumentklasse
			RUNTIME_CLASS(CMDIChildWnd),		// Rahmenklasse
			RUNTIME_CLASS(CResultForm));		// Ansichtklasse
		AddDocTemplate(pNewDocTemplate);
	}
*/

	// OLE-Bibliotheken initialisieren
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Größe Ihrer fertigen 
	//  ausführbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht benötigen, entfernen.

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	// Ändern des Registrierungsschlüssels, unter dem unsere Einstellungen gespeichert sind.
	// ZU ERLEDIGEN: Sie sollten dieser Zeichenfolge einen geeigneten Inhalt geben
	// wie z.B. den Namen Ihrer Firma oder Organisation.
	SetRegistryKey(_T("Munich Gang"));

//	LoadStdProfileSettings(8);  // Standard INI-Dateioptionen laden (einschließlich MRU)

	// Initialisierung der Frames
	CChildFrame::Initialize();

	// Dokumentvorlagen der Anwendung registrieren. Dokumentvorlagen
	//  dienen als Verbindung zwischen Dokumenten, Rahmenfenstern und Ansichten.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_THELLITYPE,
		RUNTIME_CLASS(CThellierToolDoc),
		RUNTIME_CLASS(CChildFrame), // Benutzerspezifischer MDI-Child-Rahmen
		RUNTIME_CLASS(CThellierToolView));
	pDocTemplate->SetServerInfo(
		IDR_THELLITYPE_SRVR_EMB, IDR_THELLITYPE_SRVR_IP,
		RUNTIME_CLASS(CInPlaceFrame));
	AddDocTemplate(pDocTemplate);

	// Verbinden des COleTemplateServer mit der Dokumentvorlage.
	//  Der COleTemplateServer legt auf Basis der Informationen in der
	//  Dokumentvorlage bei der Anforderung von OLE-Containern
	//  neue Dokumente an.
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);

	// Alle OLE-Server (-fabriken) als aktiv registrieren. Dies aktiviert die
	//  OLE-Bibliotheken, um Objekte von anderen Anwendungen zu erstellen.
	COleTemplateServer::RegisterAll();
		// Hinweis: MDI-Anwendungen registrieren alle Server-Objekte, ohne Rücksicht
		//  auf die Parameter /Embedding oder /Automation in der Befehlszeile.

	// Initialisierung der Kriterien
	CCriteriaDlg::Initialize();

	// Haupt-MDI-Rahmenfenster erzeugen
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	int nCmdShow = m_nCmdShow; // leon (19.12.03); für Fensteröffnung

	// Befehlszeile parsen, um zu prüfen auf Standard-Umgebungsbefehle DDE, Datei offen
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Anzeigen und Aktualisieren des Hauptfensters (eingefügt von leon)
	nCmdShow = !cmdInfo.m_bRunEmbedded ? m_nCmdShow : SW_HIDE;
	m_nCmdShow = SW_HIDE;

	if (!cmdInfo.m_bRunEmbedded)
	{
		m_pMainWnd->UpdateWindow();
	}

	// Öffnen per DragDrop aktivieren
	m_pMainWnd->DragAcceptFiles();

	// DDE-Execute-Open aktivieren
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	LoadStdProfileSettings(); //Lädt automatisch letzte geöffnete Datei

	// Testen, ob Ausführung als OLE-Server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Anwendung mit /Embedding oder /Automation gestartet. In diesem Fall
		//  kein Hauptfenster anzeigen.
		return TRUE;
	}

	// Wird eine Server-Anwendung im Standalone-Modus betrieben, ist es ratsam,
	//  die Systemregistrierung zu aktualisieren, falls diese beschädigt wurde.

// Auskommentiert um "failed zo update the system registry" Fehler zu unterbinden (Leon, 24.07.06)
//	m_server.UpdateRegistry(OAT_INPLACE_SERVER);
	COleObjectFactory::UpdateRegistryAll();

	// Falls Anwendung nicht mit /Embedding gestartet, dann Default-Hauptfenster anzeigen.

	// Verteilung der in der Befehlszeile angegebenen Befehle
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Das Hauptfenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
//	pMainFrame->ShowWindow(m_nCmdShow);
	m_nCmdShow = nCmdShow;
	((CMainFrame*)m_pMainWnd)->InitialShowWindow(nCmdShow); // leon (19.12.03): Hauptfenster wird jetzt an der zuletzt geöffneten position gezeigt (siehe MainFrm)
	pMainFrame->UpdateWindow();


	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialog für Info über Anwendung

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogdaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Überladungen für virtuelle Funktionen, die vom Anwendungs-Assistenten erzeugt wurden
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Anwendungsbefehl zum Ausführen des Dialogfelds
void CThellierToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CThellierToolApp-Nachrichtenbehandlungsroutinen


void CThellierToolApp::OnCriteria() 
{
	
}

int CThellierToolApp::ExitInstance() 
{
	// leon (19.12.03): Fenstervariablen und Kriterienpfad werden in .INI gespeichert
	CChildFrame::Terminate();
	CCriteriaDlg::Terminate();
	
	return CWinApp::ExitInstance();
}
