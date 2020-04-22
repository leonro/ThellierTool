// RangeForm.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Thellier.h"
#include "ThellierDoc.h"
#include "ThellierView.h"
#include "RangeForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CRangeForm 


CRangeForm::CRangeForm(CThellierDoc* pDocu, CWnd* pParent /*=NULL*/)
	: CDialog(CRangeForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRangeForm)
	m_tempmin = 0;
	m_field = NULL;
	//}}AFX_DATA_INIT
	m_pDoc = pDocu;
}


void CRangeForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRangeForm)
	DDX_Text(pDX, IDC_TEMPMIN_EDIT, m_tempmin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRangeForm, CDialog)
	//{{AFX_MSG_MAP(CRangeForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CRangeForm 

BOOL CRangeForm::OnInitDialog() 
{
	
	if (m_pDoc	!= NULL)
		m_tempmin = m_pDoc->temp[1];

	CDialog::OnInitDialog();

		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
