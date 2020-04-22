// ChildFrm.h : Schnittstelle der Klasse CChildFrame
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__AA7D8AF9_68A6_4FE9_87AF_9B2FAA8CC37E__INCLUDED_)
#define AFX_CHILDFRM_H__AA7D8AF9_68A6_4FE9_87AF_9B2FAA8CC37E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attribute
protected:
	CSplitterWnd m_wndSplitter;
public:

// Operationen
public:
	static void Initialize(); // leon
	static void Terminate(); // leon

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	static int m_nDefCmdShow; // leon
	static int m_nDefCmdShowOld; // leon
	static int m_v0_x;
	static int m_v0_y;
	static int m_v1_x;
	static int m_v1_y;
	static int m_v0_x_old;
	static int m_v0_y_old;
	static int m_v1_x_old;
	static int m_v1_y_old;

	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_CHILDFRM_H__AA7D8AF9_68A6_4FE9_87AF_9B2FAA8CC37E__INCLUDED_)
