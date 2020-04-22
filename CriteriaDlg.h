#if !defined(AFX_CRITERIADLG_H__052DA475_501C_4CB8_9EA4_D6C8FF84EC53__INCLUDED_)
#define AFX_CRITERIADLG_H__052DA475_501C_4CB8_9EA4_D6C8FF84EC53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CriteriaDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCriteriaDlg 

class CCriteriaDlg : public CDialog
{
// Konstruktion
public:
	static void Initialize(); // leon
	static void Terminate(); // leon
	void UpdateCriteria(); // leon
	void UpdateCriteriaLocal(); // leon (nach Load)
	CThellierToolDoc* m_pDoc;
	CCriteriaDlg(CThellierToolDoc* pDoc, CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CCriteriaDlg)
	enum { IDD = IDD_CRITERIA_DIALOG };
	int		m_crit_A_n;
	int		m_crit_A_q;
	double	m_crit_A_f;
	double	m_crit_A_std;
	int		m_crit_A_ckerror;
	int		m_crit_A_mad;
	int		m_crit_A_ckdiff;
	int		m_crit_A_acerror;
	int		m_crit_A_rdiff;
	int		m_crit_B_acerror;
	int		m_crit_B_ckdiff;
	int		m_crit_B_ckerror;
	double	m_crit_B_f;
	int		m_crit_B_mad;
	int		m_crit_B_n;
	int		m_crit_B_q;
	int		m_crit_B_rdiff;
	double	m_crit_B_std;
	int		m_crit_B_zdiff;
	int		m_crit_A_zdiff;
	int		m_maximizingpar;
	BOOL	m_autock_enable;
	int		m_crit_arai_norm;
	int		m_crit_A_alpha;
	int		m_crit_B_alpha;
	int		m_crit_A_drat;
	int		m_crit_B_drat;
	int		m_crit_A_tstar;
	int		m_crit_B_tstar;
	CString	m_cripath;
	int		m_crit_A_mad_na;
	int		m_crit_B_mad_na;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CCriteriaDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	static int A_n;
	static int A_n_old;
	static double A_std;
	static double A_std_old;
	static double A_f;
	static double A_f_old;
	static int A_q;
	static int A_q_old;
	static int A_mad;
	static int A_mad_old;
	static int A_mad_na;
	static int A_mad_na_old;
	static int A_ckerror;
	static int A_ckerror_old;
	static int A_ckdiff;
	static int A_ckdiff_old;
	static int A_drat;
	static int A_drat_old;
	static int A_alpha;
	static int A_alpha_old;
	static int A_acerror;
	static int A_acerror_old;
	static int A_rdiff;
	static int A_rdiff_old;
	static int A_tstar;
	static int A_tstar_old;
	static int B_n;
	static int B_n_old;
	static double B_std;
	static double B_std_old;
	static double B_f;
	static double B_f_old;
	static int B_q;
	static int B_q_old;
	static int B_mad;
	static int B_mad_old;
	static int B_mad_na;
	static int B_mad_na_old;
	static int B_ckerror;
	static int B_ckerror_old;
	static int B_ckdiff;
	static int B_ckdiff_old;
	static int B_drat;
	static int B_drat_old;
	static int B_alpha;
	static int B_alphB_old;
	static int B_acerror;
	static int B_acerror_old;
	static int B_rdiff;
	static int B_rdiff_old;
	static int B_tstar;
	static int B_tstar_old;
	static int maximizingpar;
	static int maximizingpar_old;
	static BOOL autock_enable;
	static BOOL autock_enable_old;
	static int arai_norm;
	static int arai_norm_old;
	static CString criteria_path;
	static CString criteria_path_old;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CCriteriaDlg)
	afx_msg void OnApplyButton();
	afx_msg void OnCriloadButton();
	afx_msg void OnCrisaveButton();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCridefaultButton();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_CRITERIADLG_H__052DA475_501C_4CB8_9EA4_D6C8FF84EC53__INCLUDED_
