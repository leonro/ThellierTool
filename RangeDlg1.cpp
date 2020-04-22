// RangeDlg1.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Thellier.h"
#include "ThellierDoc.h"
#include "RangeDlg1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CRangeDlg 


CRangeDlg::CRangeDlg(CThellierDoc* pDocu, CWnd* pParent /*=NULL*/)
	: CDialog(CRangeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRangeDlg)
	m_tempmin = 0;
	//}}AFX_DATA_INIT
	m_pDoc = pDocu;
}


void CRangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRangeDlg)
	DDX_Text(pDX, IDC_TEMPMIN_EDIT, m_tempmin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRangeDlg, CDialog)
	//{{AFX_MSG_MAP(CRangeDlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CRangeDlg 


BOOL CRangeDlg::OnInitDialog() 
{

	if (m_pDoc != NULL)
		m_tempmin = m_pDoc->temp_min;
	CDialog::OnInitDialog();
	
	UpdateData( FALSE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CRangeDlg::OnClose() 
{

	m_pDoc->temp_min = m_tempmin;

	UpdateData( FALSE );

	CDialog::OnClose();
}
