// MainFrm.h : Schnittstelle der Klasse CMainFrame
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__A691BD9A_32BF_4960_B47E_8902625172CF__INCLUDED_)
#define AFX_MAINFRM_H__A691BD9A_32BF_4960_B47E_8902625172CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWnd
{
	//DECLARE_DYNAMIC(CMainFrame)
	DECLARE_DYNCREATE(CMainFrame) //leon (19.12.03)
public:
	CMainFrame();

// Attribute
public:

// Operationen
public:
	void InitialShowWindow(UINT nCmdShow);

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // Eingebundene Elemente der Steuerleiste
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MAINFRM_H__A691BD9A_32BF_4960_B47E_8902625172CF__INCLUDED_)
