// ResultForm.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ThellierTool.h"
#include "ResultForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Initialisirung der statischen Variablen (leon)
CString CResultForm::savefilename = "*.thl";

/////////////////////////////////////////////////////////////////////////////
// CResultForm

IMPLEMENT_DYNCREATE(CResultForm, CFormView)

CResultForm::CResultForm()
	: CFormView(CResultForm::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CResultForm)
	m_labfield = 0.0f;
	m_samplename = _T("");
	m_mainview = -1;
	m_coordinates = -1;
	m_accheck = FALSE;
	m_ckcorr = FALSE;
	m_zonly = FALSE;
	m_auto = -1;
	m_mintemp = 0;
	m_maxtemp = 0;
	m_N = 0;
	m_slope = 0.0;
	m_stdslope = 0.0;
	m_sd = 0.0;
	m_palint = 0.0;
	m_q = 0.0;
	m_w = 0.0;
	m_g = 0.0;
	m_f = 0.0;
	m_class = _T("");
	m_type = _T("");
	m_trm = 0.0;
	m_nrmt = 0.0;
	m_mad = 0.0;
	m_inc = 0.0;
	m_dec = 0.0;
	m_ckdiff = 0.0;
	m_ckerror = 0.0;
	m_acerror = 0.0;
	m_trerror = 0.0;
	m_use_autock = FALSE;
	m_drat = 0.0;
	m_alpha = 0.0;
	m_tstar = 0.0;
	m_dec_na = 0.0;
	m_inc_na = 0.0;
	m_mad_na = 0.0;
	m_altcheckmethod = _T("");
	//}}AFX_DATA_INIT
}

CResultForm::~CResultForm()
{
}

void CResultForm::OnFinalRelease()
{
	// Nachdem die letzte Referenz auf ein Automatisierungsobjekt freigegeben wurde,
	// wird OnFinalRelease aufgerufen. Die Basisklasse löscht das Objekt
	// automatisch. Fügen Sie zusätzlichen Bereinigungscode für Ihr Objekt
	// hinzu, bevor Sie die Basisklasse aufrufen.

	CFormView::OnFinalRelease();
}

void CResultForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultForm)
	DDX_Control(pDX, IDC_MDTAIL_LIST, m_taillist);
	DDX_Control(pDX, IDC_RAWDATA_LIST, m_rawdatalist);
	DDX_Text(pDX, IDC_LABFIELD_EDIT, m_labfield);
	DDX_Text(pDX, IDC_SAMPLENAME_EDIT, m_samplename);
	DDX_Radio(pDX, IDC_THELLIERPLOT_RADIO, m_mainview);
	DDX_Radio(pDX, IDC_CORECO_RADIO, m_coordinates);
	DDX_Check(pDX, IDC_AC_CHECK, m_accheck);
	DDX_Check(pDX, IDC_CORR_CHECK, m_ckcorr);
	DDX_Check(pDX, IDC_ZONLY_CHECK, m_zonly);
	DDX_Radio(pDX, IDC_AUTO_RADIO, m_auto);
	DDX_Text(pDX, IDC_TMIN_EDIT, m_mintemp);
	DDX_Text(pDX, IDC_TMAX_EDIT, m_maxtemp);
	DDX_Text(pDX, IDC_N_EDIT, m_N);
	DDX_Text(pDX, IDC_SLOPE_EDIT, m_slope);
	DDX_Text(pDX, IDC_STDSLOPE_EDIT, m_stdslope);
	DDX_Text(pDX, IDC_SD_EDIT, m_sd);
	DDX_Text(pDX, IDC_PALINT_EDIT, m_palint);
	DDX_Text(pDX, IDC_Q_EDIT, m_q);
	DDX_Text(pDX, IDC_W_EDIT, m_w);
	DDX_Text(pDX, IDC_G_EDIT, m_g);
	DDX_Text(pDX, IDC_F_EDIT, m_f);
	DDX_Text(pDX, IDC_CLASS_EDIT, m_class);
	DDX_Text(pDX, IDC_TYPE_EDIT, m_type);
	DDX_Text(pDX, IDC_TRM_EDIT, m_trm);
	DDX_Text(pDX, IDC_NRMT_EDIT, m_nrmt);
	DDX_Text(pDX, IDC_MAD_EDIT, m_mad);
	DDX_Text(pDX, IDC_INC_EDIT, m_inc);
	DDX_Text(pDX, IDC_DEC_EDIT, m_dec);
	DDX_Text(pDX, IDC_CKDIFF_EDIT, m_ckdiff);
	DDX_Text(pDX, IDC_CKERROR_EDIT, m_ckerror);
	DDX_Text(pDX, IDC_ACCHECK_EDIT, m_acerror);
	DDX_Text(pDX, IDC_TRERROR_EDIT, m_trerror);
	DDX_Check(pDX, IDC_AUTOCK_CHECK, m_use_autock);
	DDX_Text(pDX, IDC_DRAT_EDIT, m_drat);
	DDX_Text(pDX, IDC_ALPHA_EDIT, m_alpha);
	DDX_Text(pDX, IDC_TSTAR_EDIT, m_tstar);
	DDX_Text(pDX, IDC_DEC_NA_EDIT, m_dec_na);
	DDX_Text(pDX, IDC_INC_NA_EDIT, m_inc_na);
	DDX_Text(pDX, IDC_MAD_NA_EDIT, m_mad_na);
	DDX_Text(pDX, IDC_ALTCHECKMETHOD_EDIT, m_altcheckmethod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResultForm, CFormView)
	//{{AFX_MSG_MAP(CResultForm)
	ON_BN_CLICKED(IDC_CORECO_RADIO, OnCorecoRadio)
	ON_BN_CLICKED(IDC_GEOCO_RADIO, OnGeocoRadio)
	ON_BN_CLICKED(IDC_BEDCO_RADIO, OnBedcoRadio)
	ON_BN_CLICKED(IDC_THELLIERPLOT_RADIO, OnThellierplotRadio)
	ON_BN_CLICKED(IDC_ZIJPLOT_RADIO, OnZijplotRadio)
	ON_BN_CLICKED(IDC_DECAYPLOT_RADIO, OnDecayplotRadio)
	ON_BN_CLICKED(IDC_MDPLOT_RADIO, OnMdplotRadio)
	ON_BN_CLICKED(IDC_ALLPLOTS_RADIO, OnAllplotsRadio)
	ON_BN_CLICKED(IDC_AC_CHECK, OnAcCheck)
	ON_BN_CLICKED(IDC_CORR_CHECK, OnCorrCheck)
	ON_BN_CLICKED(IDC_ZONLY_CHECK, OnZonlyCheck)
	ON_BN_CLICKED(IDC_AUTO_RADIO, OnAutoRadio)
	ON_BN_CLICKED(IDC_MANUELL_RADIO, OnManuellRadio)
	ON_BN_CLICKED(IDC_APPLY_BUTTON, OnApplyButton)
	ON_BN_CLICKED(IDC_SAVERESULTS_BUTTON, OnSaveresultsButton)
	ON_BN_CLICKED(IDC_NOTEPAD_BUTTON, OnNotepadButton)
	ON_BN_CLICKED(IDC_AUTOCK_CHECK, OnAutockCheck)
	ON_BN_CLICKED(IDC_TEST_BUTTON, OnTestButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CResultForm, CFormView)
	//{{AFX_DISPATCH_MAP(CResultForm)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Hinweis: Wir stellen Unterstützung für IID_IResultForm zur Verfügung, um typsicheres Binden
//  von VBA zu ermöglichen. Diese IID muss mit der GUID übereinstimmen, die in der
//  Disp-Schnittstelle in der .ODL-Datei angegeben ist.

// {9BCCB409-4142-44E7-954A-6BA621126818}
static const IID IID_IResultForm =
{ 0x9bccb409, 0x4142, 0x44e7, { 0x95, 0x4a, 0x6b, 0xa6, 0x21, 0x12, 0x68, 0x18 } };

BEGIN_INTERFACE_MAP(CResultForm, CFormView)
	INTERFACE_PART(CResultForm, IID_IResultForm, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CResultForm

#ifdef _DEBUG
void CResultForm::AssertValid() const
{
	CFormView::AssertValid();
}

void CResultForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CResultForm 

void CResultForm::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Fenstereinstellungen
	GetDlgItem(IDC_TMIN_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMAX_EDIT)->EnableWindow(FALSE);

	// Alteration Analyse ausblenden und deaktivieren
	GetDlgItem(IDC_TEST_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_TEST_BUTTON)->ShowWindow(FALSE);

	UpdateData(TRUE);

	// ViewOptions einlesen
	m_mainview = pDoc->vopt.mainview;
	m_coordinates = pDoc->vopt.coordinates;
	m_auto = pDoc->vopt.automatic;
	m_accheck = pDoc->vopt.accheck;
	m_ckcorr = pDoc->vopt.ckcorr;
	m_zonly = pDoc->vopt.zonly;

	m_labfield = pDoc->fielddata.labfield;
	m_samplename = pDoc->fielddata.name;

	// Alteration check method auslesen
	CString checktype = pDoc->fielddata.checktype;
	if (checktype.IsEmpty())
		checktype = "no alteration check";
	m_altcheckmethod = checktype;

//	UpdateData (FALSE);
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnCorecoRadio() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	pDoc->vopt.coordinates = m_coordinates;
	pDoc->UpdateAllViews(NULL);	
}

void CResultForm::OnGeocoRadio() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	pDoc->vopt.coordinates = m_coordinates;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnBedcoRadio() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	pDoc->vopt.coordinates = m_coordinates;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnThellierplotRadio() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	pDoc->vopt.mainview = m_mainview;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnZijplotRadio() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	pDoc->vopt.mainview = m_mainview;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnDecayplotRadio() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	pDoc->vopt.mainview = m_mainview;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnMdplotRadio() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	pDoc->vopt.mainview = m_mainview;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnAllplotsRadio() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	pDoc->vopt.mainview = m_mainview;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	double mag, dec, inc, x, y, z;
	int tr, step, temp;  
	double angle, t_star, d_inc, d_TR;
	CString ListLine;

	// Übergabe von View updates
	m_ckcorr = pDoc->vopt.ckcorr;

	// Berücksichtigung der automatischen CK Korrektur
	if (pDoc->criteria.m_autock_enable && pDoc->results.m_type == "MT4")
		GetDlgItem(IDC_AUTOCK_CHECK)->ShowWindow(TRUE);
	else
		GetDlgItem(IDC_AUTOCK_CHECK)->ShowWindow(FALSE);

	// Übergabe der Ergebnisse
	m_N = pDoc->results.m_numberofpoints;
	m_slope = pDoc->results.m_slope;
	m_stdslope = pDoc->results.m_stdslope;
	m_nrmt = pDoc->results.m_nrmt;
	m_trm = pDoc->results.m_trm;
	m_palint = pDoc->results.m_paleoint;
	m_sd = pDoc->results.m_stddev;
	m_f = pDoc->results.m_f;
	m_g = pDoc->results.m_g;
	m_q = pDoc->results.m_q;
	m_w = pDoc->results.m_w;
	m_mintemp = pDoc->results.m_mintemp;
	m_maxtemp = pDoc->results.m_maxtemp;
	m_inc = pDoc->results.m_inc;
	m_dec = pDoc->results.m_dec;
	m_mad = pDoc->results.m_mad;
	m_class = pDoc->results.m_class;
	m_type = pDoc->results.m_type;
	m_ckdiff = pDoc->results.m_ckdiff;
	m_ckerror = pDoc->results.m_ckerror;
	m_acerror = pDoc->results.m_ACerror;
	m_trerror = pDoc->results.m_rTRerror;
	m_drat = pDoc->results.m_drat;
	m_alpha = pDoc->results.m_alpha;
	m_tstar = pDoc->results.m_tstar;
	m_inc_na = pDoc->results.m_inc_na;
	m_dec_na = pDoc->results.m_dec_na;
	m_mad_na = pDoc->results.m_mad_na;

	CString checktype = pDoc->fielddata.checktype;
	if (checktype.IsEmpty())
		checktype = "no alteration check";
	m_altcheckmethod = checktype;

	// ************************************************************
	// Hervorhebung von Ergebnissen die die Kriterien überschreiten
	// ************************************************************

	Invalidate();
	if (m_palint != 0)
	{
		CBrush RedBrush, YellowBrush;
		RedBrush.CreateSolidBrush (RGB(255,0,0));
		YellowBrush.CreateSolidBrush (RGB(255,255,0));
		CBrush* pRedBrush;
		CBrush* pYellowBrush;
		CPaintDC dc (this);
		// N
		if (m_N < pDoc->criteria.m_crit_B_n)
		{
			CRect test;
			GetDlgItem(IDC_N_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_N < pDoc->criteria.m_crit_A_n && m_N >= pDoc->criteria.m_crit_B_n)
		{
			CRect test;
			GetDlgItem(IDC_N_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		//Std versus Slope
		if (m_stdslope > pDoc->criteria.m_crit_B_std)
		{
			CRect test;
			GetDlgItem(IDC_STDSLOPE_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_stdslope > pDoc->criteria.m_crit_A_std && m_stdslope <= pDoc->criteria.m_crit_B_std)
		{
			CRect test;
			GetDlgItem(IDC_STDSLOPE_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		// F
		if (m_f < pDoc->criteria.m_crit_B_f)
		{
			CRect test;
			GetDlgItem(IDC_F_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_f < pDoc->criteria.m_crit_A_f && m_f >= pDoc->criteria.m_crit_B_f)
		{
			CRect test;
			GetDlgItem(IDC_F_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		// Q
		if (m_q < pDoc->criteria.m_crit_B_q)
		{
			CRect test;
			GetDlgItem(IDC_Q_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_q < pDoc->criteria.m_crit_A_q && m_q >= pDoc->criteria.m_crit_B_q)
		{
			CRect test;
			GetDlgItem(IDC_Q_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}	
		// MAD
		if (m_mad > pDoc->criteria.m_crit_B_mad)
		{
			CRect test;
			GetDlgItem(IDC_MAD_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_mad > pDoc->criteria.m_crit_A_mad && m_mad <= pDoc->criteria.m_crit_B_mad)
		{
			CRect test;
			GetDlgItem(IDC_MAD_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}	
		// MAD (not anchored)
		if (m_mad_na > pDoc->criteria.m_crit_B_mad_na)
		{
			CRect test;
			GetDlgItem(IDC_MAD_NA_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_mad_na > pDoc->criteria.m_crit_A_mad_na && m_mad <= pDoc->criteria.m_crit_B_mad_na)
		{
			CRect test;
			GetDlgItem(IDC_MAD_NA_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}	
		// Alpha
		if (m_alpha > pDoc->criteria.m_crit_B_alpha)
		{
			CRect test;
			GetDlgItem(IDC_ALPHA_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_alpha > pDoc->criteria.m_crit_A_alpha && m_alpha <= pDoc->criteria.m_crit_B_alpha)
		{
			CRect test;
			GetDlgItem(IDC_ALPHA_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}	
		// CK error
		if (m_ckerror > pDoc->criteria.m_crit_B_ckerror)
		{
			CRect test;
			GetDlgItem(IDC_CKERROR_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_ckerror > pDoc->criteria.m_crit_A_ckerror && m_ckerror <= pDoc->criteria.m_crit_B_ckerror)
		{
			CRect test;
			GetDlgItem(IDC_CKERROR_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		// CK diff
		if (m_ckdiff > pDoc->criteria.m_crit_B_ckdiff)
		{
			CRect test;
			GetDlgItem(IDC_CKDIFF_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_ckdiff > pDoc->criteria.m_crit_A_ckdiff && m_ckdiff <= pDoc->criteria.m_crit_B_ckdiff)
		{
			CRect test;
			GetDlgItem(IDC_CKDIFF_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		// Drat
		if (m_drat > pDoc->criteria.m_crit_B_drat)
		{
			CRect test;
			GetDlgItem(IDC_DRAT_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_drat > pDoc->criteria.m_crit_A_drat && m_drat <= pDoc->criteria.m_crit_B_drat)
		{
			CRect test;
			GetDlgItem(IDC_DRAT_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		// AC Error
		if (m_acerror > pDoc->criteria.m_crit_B_acerror)
		{
			CRect test;
			GetDlgItem(IDC_ACCHECK_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_acerror > pDoc->criteria.m_crit_A_acerror && m_acerror <= pDoc->criteria.m_crit_B_acerror)
		{
			CRect test;
			GetDlgItem(IDC_ACCHECK_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		// TR Error
		if (m_trerror > pDoc->criteria.m_crit_B_rdiff)
		{
			CRect test;
			GetDlgItem(IDC_TRERROR_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_trerror > pDoc->criteria.m_crit_A_rdiff && m_trerror <= pDoc->criteria.m_crit_B_rdiff)
		{
			CRect test;
			GetDlgItem(IDC_TRERROR_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		// T-Star
		if (m_tstar > pDoc->criteria.m_crit_B_tstar)
		{
			CRect test;
			GetDlgItem(IDC_TSTAR_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pRedBrush = dc.SelectObject(&RedBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}
		if (m_tstar > pDoc->criteria.m_crit_A_tstar && m_tstar <= pDoc->criteria.m_crit_B_tstar)
		{
			CRect test;
			GetDlgItem(IDC_TSTAR_EDIT)->GetWindowRect(test);
			ScreenToClient(test);
			pYellowBrush = dc.SelectObject(&YellowBrush);
			dc.Rectangle(test.left,test.bottom,test.right,test.bottom+4);
		}

	}

/*	CFont THfont, PTfont, TRfont;
	LOGFONT logfont1 ={50,0,0,0,0,0,0,0,0,0,0,0,0,"arial"};
	LOGFONT logfont2 ={50,0,0,0,0,0,0,0,0,0,0,0,0,"arial"};
	logfont1.lfHeight = 50;

	THfont.CreatePointFontIndirect (&logfont1, NULL);
//	PTfont = SelectObject(&THfont);
*/
	m_rawdatalist.ResetContent();
	for (int i = 0; i < pDoc->AllDataList.GetSize(); i++)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )pDoc->AllDataList.GetAt(i);
		tr = daten1->m_tr;
		temp = daten1->m_temp;
		mag = daten1->m_mag;
		x = daten1->m_x;
		y = daten1->m_y;
		z = daten1->m_z;
		pDoc->XYZtoDecInc(&dec,&inc,x,y,z);
//		m_rawdatalist.SetFont(&THfont);
		ListLine.Format("%d%7d%10.2f%10.2f%10.2f", tr, temp, mag, dec, inc);
		m_rawdatalist.AddString(ListLine);
	}

	m_taillist.ResetContent();
	for (i = 0; i < pDoc->TRResList.GetSize(); i++)
	{
		CThellierResStruct* daten2 = ( CThellierResStruct* )pDoc->TRResList.GetAt(i);
		step = daten2->m_temp;
		angle = daten2->m_x;
		d_inc = daten2->m_y;
		t_star = daten2->m_z;
		d_TR = daten2->m_mag;
		ListLine.Format("%d°C%8.1f°%9.1f°%9.1f%9.1f", step, angle, d_inc, t_star, d_TR);
		m_taillist.AddString(ListLine);
	}
/*
// Test
	int temp;
	int tr;
//	pDoc->VectorSub(&pDoc->AllDataList);

	for (int i = 0; i < pDoc->CKDataList.GetSize(); i++)
	{
		CThellierResStruct* daten = ( CThellierResStruct* )pDoc->CKDataList.GetAt(i);
		tr = daten->m_tr;
		step = daten->m_temp;
		temp = daten->m_sptemp;
		mag = daten->m_x;
		dec = daten->m_y;
		inc = daten->m_z;
		ListLine.Format("%d\t%.2f\t%d\t%.2f\t%.2f\t%.2f", tr, step, temp, mag, dec, inc);
		m_rawdatalist.AddString(ListLine);
	}
*/	
	UpdateData (FALSE);
	
}

void CResultForm::OnAcCheck() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	pDoc->vopt.accheck = m_accheck;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnCorrCheck() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	pDoc->vopt.ckcorr = m_ckcorr;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnZonlyCheck() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	pDoc->vopt.zonly = m_zonly;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnAutoRadio() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	GetDlgItem(IDC_TMIN_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMAX_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOCK_CHECK)->EnableWindow(TRUE);
	pDoc->vopt.automatic = m_auto;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnManuellRadio() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	GetDlgItem(IDC_TMIN_EDIT)->EnableWindow(TRUE);
	GetDlgItem(IDC_TMAX_EDIT)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOCK_CHECK)->EnableWindow(FALSE);
	pDoc->vopt.automatic = m_auto;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnApplyButton() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData (TRUE);
	if (m_mintemp > m_maxtemp)
	{
		MessageBox( "Check your temperature range !");
		return;
	}

	pDoc->fielddata.labfield = m_labfield;
	pDoc->results.m_mintemp = m_mintemp;
	pDoc->results.m_maxtemp = m_maxtemp;
	pDoc->UpdateAllViews(NULL);	
}

void CResultForm::OnSaveresultsButton() 
{
	CString saveline;
	saveline.Empty();

	CFileDialog dlg(TRUE, "thl",savefilename);
	if (dlg.DoModal() == IDOK)
	{
		CString directorypath = dlg.GetPathName();
		savefilename = dlg.GetFileName();
		FILE *savefile;
		if ((savefile = fopen(directorypath, "r")) == NULL)
		{
			savefile = fopen(directorypath, "w");
			fprintf (savefile, "Name\tLabfield\tPaleoint\tStddev\tTmin\tTmax\tN\tslope\tStd/slope\tf\tg\tq\tw\tTRM\tNRMt\tInc anchored\tDec anchored\tMad anchored\tInc free\tDec free\tMad free\tAlpha\tCoordinates\tType\tClass\tCK-error\tCK-diff\tDrat\td(t*)\td(TR)\td(AC)\n");
			fclose (savefile);
		}
		else
		{
			char firstline [199];
			int linelength = 199;
			savefile = fopen(directorypath, "r");
			fgets (firstline, linelength, savefile);
			CString testline = firstline;
			if (testline.Find("Paleoint",0) <= 0)
			{
				MessageBox( "This is not a Thellier-Data-File !!");
				return;
			};
			fclose(savefile);
		}

		savefile = fopen(directorypath, "a+");

		CString coordinates;
		switch (m_coordinates)
		{
		case 0: coordinates = "CC";
				break;
		case 1: coordinates = "IS";
				break;
		case 2: coordinates = "BC";
				break;
		}
		saveline.Format("%s\t%.1f\t%.2f\t%.2f\t%d\t%d\t%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%s\t%s\t%s\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f", m_samplename, m_labfield, m_palint, m_sd, m_mintemp, m_maxtemp, m_N, m_slope, m_stdslope, m_f, m_g, m_q, m_w, m_trm, m_nrmt, m_inc, m_dec, m_mad, m_inc_na, m_dec_na, m_mad_na, m_alpha, coordinates, m_type, m_class, m_ckerror, m_ckdiff, m_drat, m_tstar, m_trerror, m_acerror);
		fprintf (savefile, "%s\n", saveline);
		fclose (savefile);
	};
	
}

void CResultForm::OnNotepadButton() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	UpdateData(TRUE);
	CString program = "notepad.exe";
	CString pathdata = pDoc->vopt.pathdata;
	CString editdata = program + ' ' + pathdata;
	WinExec(editdata, SW_SHOW);
}

void CResultForm::OnAutockCheck() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData(TRUE);
	pDoc->vopt.use_autock = m_use_autock;
	pDoc->UpdateAllViews(NULL);
}

void CResultForm::OnTestButton() 
{
	// Test Funktion
	// im Moment Spline 

	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	UpdateData(TRUE);
	pDoc->CkErrorSpline(&pDoc->CkErrorList, 0.99e31, 0.99e31);
	m_trerror = pDoc->CkErrorSplinet(&pDoc->CkErrorList, pDoc->ckspline_y2, pDoc->ckspline_length, 150)*100/pDoc->results.m_trm;
	m_acerror = pDoc->CkErrorSplinet(&pDoc->CkErrorList, pDoc->ckspline_y2, pDoc->ckspline_length, 200)*100/pDoc->results.m_trm;;
}
