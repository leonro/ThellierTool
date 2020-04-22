// CriteriaDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ThellierTool.h"
#include "CriteriaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCriteriaDlg 

// Initialisirung der statischen Variablen (leon)
int CCriteriaDlg::A_n = 5;
int CCriteriaDlg::A_n_old = 5;
double CCriteriaDlg::A_std = 0.1;
double CCriteriaDlg::A_std_old = 0.1;
double CCriteriaDlg::A_f = 0.3;
double CCriteriaDlg::A_f_old = 0.3;
int CCriteriaDlg::A_q = 1;
int CCriteriaDlg::A_q_old = 1;
int CCriteriaDlg::A_mad = 6;
int CCriteriaDlg::A_mad_old = 6;
int CCriteriaDlg::A_mad_na = 999;
int CCriteriaDlg::A_mad_na_old = 999;
int CCriteriaDlg::A_ckerror = 5;
int CCriteriaDlg::A_ckerror_old = 5;
int CCriteriaDlg::A_ckdiff = 5;
int CCriteriaDlg::A_ckdiff_old = 5;
int CCriteriaDlg::A_drat = 999;
int CCriteriaDlg::A_drat_old = 999;
int CCriteriaDlg::A_alpha = 15;
int CCriteriaDlg::A_alpha_old = 15;
int CCriteriaDlg::A_acerror = 5;
int CCriteriaDlg::A_acerror_old = 5;
int CCriteriaDlg::A_rdiff = 10;
int CCriteriaDlg::A_rdiff_old = 10;
int CCriteriaDlg::A_tstar = 3;
int CCriteriaDlg::A_tstar_old = 5;
int CCriteriaDlg::B_n = 5;
int CCriteriaDlg::B_n_old = 5;
double CCriteriaDlg::B_std = 0.15;
double CCriteriaDlg::B_std_old = 0.15;
double CCriteriaDlg::B_f = 0.3;
double CCriteriaDlg::B_f_old = 0.3;
int CCriteriaDlg::B_q = 0;
int CCriteriaDlg::B_q_old = 0;
int CCriteriaDlg::B_mad = 15;
int CCriteriaDlg::B_mad_old = 15;
int CCriteriaDlg::B_mad_na = 999;
int CCriteriaDlg::B_mad_na_old = 999;
int CCriteriaDlg::B_ckerror = 7;
int CCriteriaDlg::B_ckerror_old = 7;
int CCriteriaDlg::B_ckdiff = 10;
int CCriteriaDlg::B_ckdiff_old = 10;
int CCriteriaDlg::B_drat = 999;
int CCriteriaDlg::B_drat_old = 999;
int CCriteriaDlg::B_alpha = 15;
int CCriteriaDlg::B_alphB_old = 15;
int CCriteriaDlg::B_acerror = 10;
int CCriteriaDlg::B_acerror_old = 10;
int CCriteriaDlg::B_rdiff = 15;
int CCriteriaDlg::B_rdiff_old = 15;
int CCriteriaDlg::B_tstar = 5;
int CCriteriaDlg::B_tstar_old = 7;
int CCriteriaDlg::maximizingpar = 0;
int CCriteriaDlg::maximizingpar_old = 0;
BOOL CCriteriaDlg::autock_enable = FALSE;
BOOL CCriteriaDlg::autock_enable_old = FALSE;
int CCriteriaDlg::arai_norm = 0;
int CCriteriaDlg::arai_norm_old = 0;

CString CCriteriaDlg::criteria_path = "DefaultCriteria";
CString CCriteriaDlg::criteria_path_old = "DefaultCriteria";

static TCHAR BASED_CODE szSec[] = _T("Settings");
static TCHAR BASED_CODE szPathCri[] = _T("PathCri");
static TCHAR BASED_CODE szNameCri[] = _T("DefaultCriteria");


CCriteriaDlg::CCriteriaDlg(CThellierToolDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CCriteriaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCriteriaDlg)
	m_crit_A_n = 0;
	m_crit_A_q = 0;
	m_crit_A_f = 0.0;
	m_crit_A_std = 0.0;
	m_crit_A_ckerror = 0;
	m_crit_A_mad = 0;
	m_crit_A_ckdiff = 0;
	m_crit_A_acerror = 0;
	m_crit_A_rdiff = 0;
	m_crit_B_acerror = 0;
	m_crit_B_ckdiff = 0;
	m_crit_B_ckerror = 0;
	m_crit_B_f = 0.0;
	m_crit_B_mad = 0;
	m_crit_B_n = 0;
	m_crit_B_q = 0;
	m_crit_B_rdiff = 0;
	m_crit_B_std = 0.0;
	m_crit_B_zdiff = 0;
	m_crit_A_zdiff = 0;
	m_maximizingpar = -1;
	m_autock_enable = FALSE;
	m_crit_arai_norm = -1;
	m_crit_A_alpha = 0;
	m_crit_B_alpha = 0;
	m_crit_A_drat = 0;
	m_crit_B_drat = 0;
	m_crit_A_tstar = 0;
	m_crit_B_tstar = 0;
	m_cripath = _T("");
	m_crit_A_mad_na = 0;
	m_crit_B_mad_na = 0;
	//}}AFX_DATA_INIT
	m_pDoc = pDoc;
}


void CCriteriaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCriteriaDlg)
	DDX_Text(pDX, IDC_N_CRIT_A_EDIT, m_crit_A_n);
	DDX_Text(pDX, IDC_Q_CRIT_A_EDIT, m_crit_A_q);
	DDX_Text(pDX, IDC_F_CRIT_A_EDIT, m_crit_A_f);
	DDX_Text(pDX, IDC_STD_CRIT_A_EDIT, m_crit_A_std);
	DDX_Text(pDX, IDC_CKERROR_CRIT_A_EDIT, m_crit_A_ckerror);
	DDX_Text(pDX, IDC_MAD_CRIT_A_EDIT, m_crit_A_mad);
	DDX_Text(pDX, IDC_CKDIFF_CRIT_A_EDIT, m_crit_A_ckdiff);
	DDX_Text(pDX, IDC_ACERROR_CRIT_A_EDIT, m_crit_A_acerror);
	DDX_Text(pDX, IDC_RDIFF_CRIT_A_EDIT, m_crit_A_rdiff);
	DDX_Text(pDX, IDC_ACERROR_CRIT_B_EDIT, m_crit_B_acerror);
	DDX_Text(pDX, IDC_CKDIFF_CRIT_B_EDIT, m_crit_B_ckdiff);
	DDX_Text(pDX, IDC_CKERROR_CRIT_B_EDIT, m_crit_B_ckerror);
	DDX_Text(pDX, IDC_F_CRIT_B_EDIT, m_crit_B_f);
	DDX_Text(pDX, IDC_MAD_CRIT_B_EDIT, m_crit_B_mad);
	DDX_Text(pDX, IDC_N_CRIT_B_EDIT, m_crit_B_n);
	DDX_Text(pDX, IDC_Q_CRIT_B_EDIT, m_crit_B_q);
	DDX_Text(pDX, IDC_RDIFF_CRIT_B_EDIT, m_crit_B_rdiff);
	DDX_Text(pDX, IDC_STD_CRIT_B_EDIT, m_crit_B_std);
	DDX_Text(pDX, IDC_ZDIFF_CRIT_B_EDIT, m_crit_B_zdiff);
	DDX_Text(pDX, IDC_ZDIFF_CRIT_A_EDIT, m_crit_A_zdiff);
	DDX_Radio(pDX, IDC_WEIGHT_W_RADIO, m_maximizingpar);
	DDX_Check(pDX, IDC_AUTOCK_YES_CHECK, m_autock_enable);
	DDX_Radio(pDX, IDC_SEPAXES_RADIO, m_crit_arai_norm);
	DDX_Text(pDX, IDC_ALPHA_CRIT_A_EDIT, m_crit_A_alpha);
	DDX_Text(pDX, IDC_ALPHA_CRIT_B_EDIT, m_crit_B_alpha);
	DDX_Text(pDX, IDC_DRAT_CRIT_A_EDIT, m_crit_A_drat);
	DDX_Text(pDX, IDC_DRAT_CRIT_B_EDIT, m_crit_B_drat);
	DDX_Text(pDX, IDC_HDIFF_CRIT_A_EDIT, m_crit_A_tstar);
	DDX_Text(pDX, IDC_HDIFF_CRIT_B_EDIT, m_crit_B_tstar);
	DDX_Text(pDX, IDC_CRIPATH_EDIT, m_cripath);
	DDX_Text(pDX, IDC_MAD_AN_CRIT_A_EDIT, m_crit_A_mad_na);
	DDX_Text(pDX, IDC_MAD_AN_CRIT_B_EDIT, m_crit_B_mad_na);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCriteriaDlg, CDialog)
	//{{AFX_MSG_MAP(CCriteriaDlg)
	ON_BN_CLICKED(IDC_APPLY_BUTTON, OnApplyButton)
	ON_BN_CLICKED(IDC_CRILOAD_BUTTON, OnCriloadButton)
	ON_BN_CLICKED(IDC_CRISAVE_BUTTON, OnCrisaveButton)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_CRIDEFAULT_BUTTON, OnCridefaultButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CCriteriaDlg 

void CCriteriaDlg::OnApplyButton() 
{
	UpdateData ( TRUE );
	// Class A Kriterien
	A_n = m_crit_A_n;
	A_std = m_crit_A_std;
	A_f = m_crit_A_f;
	A_q = m_crit_A_q;
	A_mad = m_crit_A_mad;
	A_mad_na = m_crit_A_mad_na;
	A_alpha = m_crit_A_alpha;
	A_ckerror = m_crit_A_ckerror;
	A_ckdiff = m_crit_A_ckdiff;
	A_drat = m_crit_A_drat;
	A_rdiff = m_crit_A_rdiff;
	A_tstar = m_crit_A_tstar;
	A_acerror = m_crit_A_acerror;
	// Class B Kriterien
	B_n = m_crit_B_n;
	B_std = m_crit_B_std;
	B_f = m_crit_B_f;
	B_q = m_crit_B_q;
	B_mad = m_crit_B_mad;
	B_mad_na = m_crit_B_mad_na;
	B_alpha = m_crit_B_alpha;
	B_ckerror = m_crit_B_ckerror;
	B_ckdiff = m_crit_B_ckdiff;
	B_drat = m_crit_B_drat;
	B_rdiff = m_crit_B_rdiff;
	B_tstar = m_crit_B_tstar;
	B_acerror = m_crit_B_acerror;
	// Parameter für automatische Berechnung
	maximizingpar = m_maximizingpar;
	autock_enable = m_autock_enable;
	// Parameter für General View options
	arai_norm = m_crit_arai_norm;

	UpdateCriteria();
	OnOK();		
}

// leon (19.12.03): folgende Funktionen (Initialize und Terminate) werden beim start bzw. beenden von ThellierTool ausgeführt
//					siehe thelliertool.cpp

void CCriteriaDlg::Initialize() 
{
	CString CriteriaPathDefault = "DefaultCriteria";
	CFile CriteriaFile;
	CString check;

	criteria_path = AfxGetApp()->GetProfileString(szSec, szPathCri, szNameCri);
	criteria_path_old = criteria_path;

	if (criteria_path != CriteriaPathDefault)
	{

		if (!CriteriaFile.Open(criteria_path, CFile::modeRead)) // | CFile::typeText))
		{
			criteria_path = "DefaultCriteria";
		}
		else
		{
			CArchive cr(&CriteriaFile, CArchive::load);
			cr >> check;
			cr >> A_n >> A_std >> A_f >> A_q >> A_mad >> A_mad_na >> A_alpha >> A_ckerror >> A_ckdiff >> A_drat >> A_rdiff >> A_tstar >> A_acerror;
			cr >> B_n >> B_std >> B_f >> B_q >> B_mad >> B_mad_na >> B_alpha >> B_ckerror >> B_ckdiff >> B_drat >> B_rdiff >> B_tstar >> B_acerror;
			cr >> maximizingpar >> autock_enable >> arai_norm;
			cr.Close();
			CriteriaFile.Close();
		}
	}
}

void CCriteriaDlg::Terminate() 
{
	if (criteria_path != criteria_path_old)
	{
		AfxGetApp()->WriteProfileString(szSec, szPathCri, criteria_path);
		criteria_path_old = criteria_path;
	}

}

void CCriteriaDlg::UpdateCriteria() 
{

	// Class A Kriterien
	m_pDoc->criteria.m_crit_A_n = A_n;
	m_pDoc->criteria.m_crit_A_std = A_std;
	m_pDoc->criteria.m_crit_A_f = A_f;
	m_pDoc->criteria.m_crit_A_q = A_q;
	m_pDoc->criteria.m_crit_A_mad = A_mad;
	m_pDoc->criteria.m_crit_A_mad_na = A_mad_na;
	m_pDoc->criteria.m_crit_A_alpha = A_alpha;
	m_pDoc->criteria.m_crit_A_ckerror = A_ckerror;
	m_pDoc->criteria.m_crit_A_ckdiff = A_ckdiff;
	m_pDoc->criteria.m_crit_A_drat = A_drat;
	m_pDoc->criteria.m_crit_A_rdiff = A_rdiff;
	m_pDoc->criteria.m_crit_A_tstar = A_tstar;
	m_pDoc->criteria.m_crit_A_acerror = A_acerror;
	// Class B Kriterien
	m_pDoc->criteria.m_crit_B_n = B_n;
	m_pDoc->criteria.m_crit_B_std = B_std;
	m_pDoc->criteria.m_crit_B_f = B_f;
	m_pDoc->criteria.m_crit_B_q = B_q;
	m_pDoc->criteria.m_crit_B_mad = B_mad;
	m_pDoc->criteria.m_crit_B_mad_na = B_mad_na;
	m_pDoc->criteria.m_crit_B_alpha = B_alpha;
	m_pDoc->criteria.m_crit_B_ckerror = B_ckerror;
	m_pDoc->criteria.m_crit_B_ckdiff = B_ckdiff;
	m_pDoc->criteria.m_crit_B_drat = B_drat;
	m_pDoc->criteria.m_crit_B_rdiff = B_rdiff;
	m_pDoc->criteria.m_crit_B_tstar = B_tstar;
	m_pDoc->criteria.m_crit_B_acerror = B_acerror;
	// Parameter für automatische Berechnung
	m_pDoc->criteria.m_maximizingpar = maximizingpar;
	m_pDoc->criteria.m_autock_enable = autock_enable;
	// Parameter für General View options
	m_pDoc->vopt.m_arai_norm = arai_norm;

	m_cripath = criteria_path;

}

void CCriteriaDlg::UpdateCriteriaLocal() 
{
	// Class A Kriterien
	m_crit_A_n = A_n;
	m_crit_A_std = A_std;
	m_crit_A_f = A_f;
	m_crit_A_q = A_q;
	m_crit_A_mad = A_mad;
	m_crit_A_mad_na = A_mad_na;
	m_crit_A_alpha = A_alpha;
	m_crit_A_ckerror = A_ckerror;
	m_crit_A_ckdiff = A_ckdiff;
	m_crit_A_drat = A_drat;
	m_crit_A_rdiff = A_rdiff;
	m_crit_A_tstar = A_tstar;
	m_crit_A_acerror = A_acerror;
	// Class B Kriterien
	m_crit_B_n = B_n;
	m_crit_B_std = B_std;
	m_crit_B_f = B_f;
	m_crit_B_q = B_q;
	m_crit_B_mad = B_mad;
	m_crit_B_mad_na = B_mad_na;
	m_crit_B_alpha = B_alpha;
	m_crit_B_ckerror = B_ckerror;
	m_crit_B_ckdiff = B_ckdiff;
	m_crit_B_drat = B_drat;
	m_crit_B_rdiff = B_rdiff;
	m_crit_B_tstar = B_tstar;
	m_crit_B_acerror = B_acerror;
	// Parameter für automatische Berechnung
	m_maximizingpar = maximizingpar;
	m_autock_enable = autock_enable;
	// Parameter für General View options
	m_crit_arai_norm = arai_norm;

	m_cripath = criteria_path;

	UpdateData(FALSE);

}

void CCriteriaDlg::OnCriloadButton() 
{
	CString CriteriaFilePath;
	CString CriteriaFileName;
	BOOL SelectPath = FALSE;
	CFile CriteriaFile;
	CString FileCheck = "Criteria";
	CString check;

	CFileDialog dlg(TRUE, "cri","*.cri");
	if (dlg.DoModal() == IDOK)
	{	
		CriteriaFilePath = dlg.GetPathName();
		SelectPath = TRUE;
	}

	if (SelectPath)
	{

		if (!CriteriaFile.Open(CriteriaFilePath, CFile::modeRead)) // | CFile::typeText))
		{
		}
		else
		{
			CriteriaFileName = CriteriaFile.GetFileTitle();
			CArchive cr(&CriteriaFile, CArchive::load);
			cr >> check;
			if (check != FileCheck)
			{
				cr.Close();
				CriteriaFile.Close();
				MessageBox("No Criteria File!");
			}
			else
			{
				cr >> A_n >> A_std >> A_f >> A_q >> A_mad >> A_mad_na >> A_alpha >> A_ckerror >> A_ckdiff >> A_drat >> A_rdiff >> A_tstar >> A_acerror;
				cr >> B_n >> B_std >> B_f >> B_q >> B_mad >> B_mad_na >> B_alpha >> B_ckerror >> B_ckdiff >> B_drat >> B_rdiff >> B_tstar >> B_acerror;
				cr >> maximizingpar >> autock_enable >> arai_norm;
				cr.Close();
				CriteriaFile.Close();
				criteria_path = CriteriaFilePath;
				UpdateCriteriaLocal();
			}
		}
	}

}

void CCriteriaDlg::OnCrisaveButton() 
{
	CString CriteriaFilePath;
	CString CriteriaFileName;
	BOOL SelectPath = FALSE;
	CString FileCheck = "Criteria";

	UpdateData(TRUE);


	CFileDialog dlg(FALSE, "cri","*.cri");
	if (dlg.DoModal() == IDOK)
	{	
		CriteriaFilePath = dlg.GetPathName();
		SelectPath = TRUE;
	}

	if (SelectPath)
	{
		CFile CriteriaFile (CriteriaFilePath, CFile::modeCreate | CFile::modeWrite);
		CriteriaFileName = CriteriaFile.GetFileTitle();
		CArchive cr(&CriteriaFile, CArchive::store);
		cr << FileCheck;
		cr << m_crit_A_n << m_crit_A_std << m_crit_A_f << m_crit_A_q << m_crit_A_mad << m_crit_A_mad_na << m_crit_A_alpha << m_crit_A_ckerror << m_crit_A_ckdiff << m_crit_A_drat << m_crit_A_rdiff << m_crit_A_tstar << m_crit_A_acerror;
		cr << m_crit_B_n << m_crit_B_std << m_crit_B_f << m_crit_B_q << m_crit_B_mad << m_crit_B_mad_na << m_crit_B_alpha << m_crit_B_ckerror << m_crit_B_ckdiff << m_crit_B_drat << m_crit_B_rdiff << m_crit_B_tstar << m_crit_B_acerror;
		cr << m_maximizingpar << m_autock_enable << m_crit_arai_norm;
		cr.Close();
		CriteriaFile.Close();
		criteria_path = CriteriaFilePath;
	}

}

void CCriteriaDlg::OnCridefaultButton() 
{
	A_n = 5;
	A_std = 0.1;
	A_f = 0.3;
	A_q = 1;
	A_mad = 6;
	A_mad_na = 999;
	A_ckerror = 5;
	A_ckdiff = 5;
	A_drat = 999;
	A_alpha = 15;
	A_acerror = 5;
	A_rdiff = 10;
	A_tstar = 3;
	B_n = 5;
	B_std = 0.15;
	B_f = 0.3;
	B_q = 0;
	B_mad = 15;
	B_mad_na = 999;
	B_ckerror = 7;
	B_ckdiff = 10;
	B_drat = 999;
	B_alpha = 15;
	B_acerror = 10;
	B_rdiff = 20;
	B_tstar = 5;
	maximizingpar = 0;
	autock_enable = FALSE;
	arai_norm = 0;

	criteria_path = "DefaultCriteria";
	
	UpdateCriteriaLocal();
	
}

int CCriteriaDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_cripath = criteria_path;
	
	return 0;
}


BOOL CCriteriaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Drittes Feld von repeated criteria ausblenden und deaktivieren
	GetDlgItem(IDC_ZDIFF_CRIT_A_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ZDIFF_CRIT_A_EDIT)->ShowWindow(FALSE);
	GetDlgItem(IDC_ZDIFF_CRIT_B_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ZDIFF_CRIT_B_EDIT)->ShowWindow(FALSE);
	// und zugehöriger Text ebenfalls
	GetDlgItem(IDC_ZDIFF_A_STATIC)->ShowWindow(FALSE);
	GetDlgItem(IDC_ZDIFF_B_STATIC)->ShowWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
