// ThellierView.cpp : Implementierung der Klasse CThellierView
//

#include "stdafx.h"
#include "Thellier.h"

#include "ThellierDoc.h"
#include "ThellierView.h"
#include "RangeDlg1.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThellierView

IMPLEMENT_DYNCREATE(CThellierView, CView)

BEGIN_MESSAGE_MAP(CThellierView, CView)
	//{{AFX_MSG_MAP(CThellierView)
	ON_COMMAND(ID_VEKTOR_FKOMP, OnVektorFkomp)
	ON_COMMAND(ID_VEKTOR_ZKOMP, OnVektorZkomp)
	ON_COMMAND(ID_OPTIONEN_RANGE, OnOptionenRange)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThellierView Konstruktion/Destruktion

CThellierView::CThellierView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CThellierView::~CThellierView()
{
}

BOOL CThellierView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CThellierView Zeichnen

void CThellierView::OnDraw(CDC* pDC)
{
	CThellierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen

	int deci, sign;


	Calculation();

	CString test;
	test = ecvt(tempPT[2],8,&deci,&sign);
	test.Insert(deci,".");

	pDC->TextOut(380,275,test);	


	// ********* Darstellungsdaten **********
	// Thellierplot
	// Null Punkt
	int x_n = 50;
	int y_n = 350;
	//rechter Rand
	int x_r = 450;
	// oberer Rand
	int y_o = 50;
	// Achsenlänge
	int x_l = 400;
	int y_l = 300;
	// Radius der Punkte
	int p_r = 4;
	// Dreieck
	int tr = p_r +1;


//	char step [20];
//	itoa (pTRM_steps, step, 10);

	pDC->MoveTo(x_n,y_n);
	pDC->LineTo(x_r,y_n);
	pDC->MoveTo(x_n,y_n);
	pDC->LineTo(x_n,y_o);

	int i,k,j,l;

	for (k=1; k<thellier_datalength; k++)
	{
		for (i=1; i<pTRM_steps; i++)
		{
			if (temp[k] == tempPT[i])
			{
				CRect Datapointsize((x_n+p_r)+(magPT[i]*x_l/maxmagPT),(y_n-p_r)-(mag[k]*y_l/maxmagTH),(x_n-p_r)+(magPT[i]*x_l/maxmagPT),(y_n+p_r)-(mag[k]*y_l/maxmagTH));
				pDC->Ellipse (&Datapointsize);
			};
			if (temp[k] == tempCK[i])
			{
				if (magCK[i] != 0)
				{
				int linksunten_x = (x_n-tr)+(magCK[i]*x_l/maxmagPT);
				int rechtsunten_x = (x_n+tr)+(magCK[i]*x_l/maxmagPT);
				int unten_y = (y_n+p_r)-(mag[k]*y_l/maxmagTH);
				int oben_x = x_n+(magCK[i]*x_l/maxmagPT);
				int oben_y = (y_n-p_r)-(mag[k]*y_l/maxmagTH);
				pDC->MoveTo (linksunten_x,unten_y);
				pDC->LineTo (rechtsunten_x,unten_y);
				pDC->LineTo (oben_x,oben_y);
				pDC->LineTo (linksunten_x,unten_y);
				for (j = 1; j < pTRM_steps; j++)
					if (tempCKstart[i] == tempPT[j] || (tempCKstart[i]-0.11) == tempPT[j])
					{
						int line_y;
						int line_x = x_n+(magPT[j]*x_l/maxmagPT);
						for (l = 1; l < thellier_datalength; l++)
							if (temp[l] == tempPT[j])
								line_y = y_n-(mag[l]*y_l/maxmagTH);
						pDC->MoveTo (line_x,line_y);
						pDC->LineTo (oben_x,line_y);
						pDC->LineTo (oben_x,unten_y);
					}
				}

			}

		}
	};
	
	// ZIJ - Plot

	int ho_xl = 550;
	int ho_xr = 800;
	int ve_yd = 350;
	int ve_yu = 100;
	int axis_length = 250;

	double max_left = 0.0;
	double max_up = 0.0;
	double min_rigth = 0.0;
	double min_down = 0.0;
	double hTH[99];
	double x_ax;
	double y_ax;

	for (i=1; i<TH_steps; i++)
		hTH[i] = sqrt(pow(xTH[i],2) + pow(yTH[i],2));

		// Suche nach max und min

	for (i=1; i<TH_steps; i++)
	{
		if (max_up < zTH[i])
			max_up = zTH[i];
		if (min_down > zTH[i])
			min_down = zTH[i];
	};
	for (i=1; i<TH_steps; i++)
	{
		if (max_up < xTH[i])
			max_up = xTH[i];
		if (min_down > xTH[i])
			min_down = xTH[i];
	};
	for (i=1; i<TH_steps; i++)
	{
		if (max_left < yTH[i])
			max_left = yTH[i];
		if (min_rigth > yTH[i])
			min_rigth = yTH[i];
	};
	for (i=1; i<TH_steps; i++)
	{
		if (max_left < hTH[i])
			max_left = hTH[i];
		if (min_rigth > hTH[i])
			min_rigth = hTH[i];
	}
		// x achse

	x_ax = max_left - min_rigth;
	if (max_left > x_ax)
		x_ax = max_left;
	if (-min_rigth > x_ax)
		x_ax = -min_rigth;

	int x_null = ho_xl+((x_ax - max_left)*axis_length/x_ax);

	y_ax = max_up - min_down;
	if (max_up > y_ax)
		y_ax = max_up;
	if (-min_down > y_ax)
		y_ax = -min_down;

	int y_null = ve_yd-((y_ax - max_up)*axis_length/y_ax);

	pDC->MoveTo(x_null, ve_yd);
	pDC->LineTo(x_null, ve_yu);
	pDC->MoveTo(ho_xr,y_null);
	pDC->LineTo(ho_xl,y_null);

	CPen LinePen;
	CBrush HorBrush;
	HorBrush.CreateSolidBrush (RGB(0,0,0));
	LinePen.CreatePen (PS_SOLID,1,RGB(0,0,0));


	CBrush* pOriginalBrush;
	pOriginalBrush = pDC->SelectObject(&HorBrush);
	CPen* pOriginalPen;
	pOriginalPen = pDC->SelectObject(&LinePen);


	CRect ZijpointsizeH((x_null+p_r)+(yTH[1]*axis_length/x_ax),(y_null-p_r)-(xTH[1]*axis_length/y_ax),(x_null-p_r)+(yTH[1]*axis_length/x_ax),(y_null+p_r)-(xTH[1]*axis_length/y_ax));
	pDC->Ellipse (&ZijpointsizeH);

	pDC->SelectObject(pOriginalBrush);

	CRect ZijpointsizeV((x_null+p_r)+(hTH[1]*axis_length/x_ax),(y_null-p_r)-(zTH[1]*axis_length/y_ax),(x_null-p_r)+(hTH[1]*axis_length/x_ax),(y_null+p_r)-(zTH[1]*axis_length/y_ax));
	pDC->Ellipse (&ZijpointsizeV);

	for (i=2; i < TH_steps; i++)
	{
		CBrush* pOriginalBrush;
		pOriginalBrush = pDC->SelectObject(&HorBrush);

		CRect ZijpointsizeH((x_null+p_r)+(yTH[i]*axis_length/x_ax),(y_null-p_r)-(xTH[i]*axis_length/y_ax),(x_null-p_r)+(yTH[i]*axis_length/x_ax),(y_null+p_r)-(xTH[i]*axis_length/y_ax));
		pDC->Ellipse (&ZijpointsizeH);

		pDC->SelectObject(pOriginalBrush);

		pDC->MoveTo(x_null+(yTH[i-1]*axis_length/x_ax),y_null-(xTH[i-1]*axis_length/y_ax));
		pDC->LineTo(x_null+(yTH[i]*axis_length/x_ax),y_null-(xTH[i]*axis_length/y_ax));
		CRect ZijpointsizeV((x_null+p_r)+(hTH[i]*axis_length/x_ax),(y_null-p_r)-(zTH[i]*axis_length/y_ax),(x_null-p_r)+(hTH[i]*axis_length/x_ax),(y_null+p_r)-(zTH[i]*axis_length/y_ax));
		pDC->Ellipse (&ZijpointsizeV);
		pDC->MoveTo(x_null+(hTH[i-1]*axis_length/x_ax),y_null-(zTH[i-1]*axis_length/y_ax));
		pDC->LineTo(x_null+(hTH[i]*axis_length/x_ax),y_null-(zTH[i]*axis_length/y_ax));

	};


	CString test2;
	test2 = ecvt(min_down,8,&deci,&sign);
	test2.Insert(deci,".");
	pDC->TextOut(750,275,test2);	

	// Fit - Geraden in Plots

	double maxPT;
	double y_ende, y_anfang, x_anfang;

	for (i=1;i<pTRM_steps; i++)
		if (tempPT[i] <= temp_range_max)
			maxPT = magPT[i];

	y_ende = y_gerade - (maxPT - x_gerade)*slope;
	y_anfang = y_gerade + (y_gerade - y_ende);
	x_anfang = maxPT + (y_ende - y_anfang)/slope;


	CPen PaleoPen;
	PaleoPen.CreatePen (PS_DASH,1,RGB(0,0,0));


	CPen* qOriginalPen;
	qOriginalPen = pDC->SelectObject(&PaleoPen);

	pDC->MoveTo(x_n+(x_anfang*x_l/maxmagPT),y_n-(y_anfang*y_l/maxmagTH));
	pDC->LineTo(x_n+(maxPT*x_l/maxmagPT),y_n-(y_ende*y_l/maxmagTH));


	
	// Beschriftung und Daten

	CString smaxmagPT, smaxmagTH;
	smaxmagPT = ecvt(maxmagPT,4,&deci,&sign);
	smaxmagPT.Insert(deci,".");
	smaxmagTH = ecvt(maxmagTH,4,&deci,&sign);
	smaxmagTH.Insert(deci,".");


	pDC->TextOut(210,30,samplethellier[2]);	
	pDC->TextOut(x_n+x_l*0.45,y_n+15,"pTRM (* "+smaxmagPT+" mA/m)");	
	pDC->TextOut(x_n-35,y_n-y_l/2,"NRM");	

	CString sslope, sstderror_vs_slope, sstddev, sf, sg, sQ;
	CString smax_CK_error, sw, spaleofield;
	spaleofield = ecvt(paleofield,3,&deci,&sign);
	spaleofield.Insert(deci,".");
	sslope = ecvt(slope,4,&deci,&sign);
	sslope.Insert(deci,".");
	sstderror_vs_slope = ecvt(stderror_vs_slope,4,&deci,&sign);
	sstderror_vs_slope.Insert(deci,".");
	sstddev = ecvt(stddev,3,&deci,&sign);
	sstddev.Insert(deci,".");
	sf = ecvt(f,2,&deci,&sign);
	sf.Insert(deci,".");
	sg = ecvt(g,2,&deci,&sign);
	sg.Insert(deci,".");
	sQ = ecvt(Q,3,&deci,&sign);
	sQ.Insert(deci,".");
	smax_CK_error = ecvt(max_CK_error,4,&deci,&sign);
	smax_CK_error.Insert(deci,".");
	sw = ecvt(w,3,&deci,&sign);
	sw.Insert(deci,".");
	pDC->TextOut(100,410,"Paleofield:  "+spaleofield+" uT");	
	pDC->TextOut(100,430,"std-dev:  "+sstddev+" uT");	
	pDC->TextOut(100,450,"slope:  "+sslope);	
	pDC->TextOut(100,470,"std vs. slope:  "+sstderror_vs_slope);	
	pDC->TextOut(250,410,"f:  "+sf);	
	pDC->TextOut(250,430,"g:  "+sg);	
	pDC->TextOut(250,450,"q:  "+sQ);	
	pDC->TextOut(350,410,"Max. CK-error(%):  "+smax_CK_error);	
	pDC->TextOut(350,430,"w:  "+sw);	


}

/////////////////////////////////////////////////////////////////////////////
// CThellierView Drucken

BOOL CThellierView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CThellierView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CThellierView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

/////////////////////////////////////////////////////////////////////////////
// CThellierView Diagnose

#ifdef _DEBUG
void CThellierView::AssertValid() const
{
	CView::AssertValid();
}

void CThellierView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CThellierDoc* CThellierView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CThellierDoc)));
	return (CThellierDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThellierView Nachrichten-Handler

void CThellierView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// Pointer zu Doc
	CThellierDoc* pDoc = GetDocument();

	thellier_datalength = pDoc->thellier_datalength;

	for (int i = 1; i < thellier_datalength; i++)
	{
		samplethellier [i] = pDoc->samplethellier[i];
		temp [i] = pDoc->temp[i];
		mag [i] = pDoc->mag [i];
		dec [i] = pDoc->dec[i];
		inc [i]= pDoc->inc[i];
	}
	line = pDoc->line;

	m_komp = 1;
	
}

void CThellierView::Calculation()
{
	// Berechnung von x,y,z

	double pi = 3.141592654;
	double pis = pi/180;

	double x[99];
	double y[99];
	double z[99];

	int i,j,k;

	for (k = 1; k < thellier_datalength; k++)
	{
		double H = mag[k] * cos(pis*inc[k]);
		x[k] = H * cos(pis*dec[k]);
		y[k] = H * sin(pis*dec[k]);
		z[k] = mag[k] * sin(pis*inc[k]);
	}


	// Initialisierung von magCK

	for (i = 1; i < 99; i++)
		magCK[i] = 0.0;

	// Vektorsubstarktion für pTRMs und CKs

	int o = 1;  // Zählvariable für TH-Messungen
	int p = 2;	// Zählvariable für pTRM-Messungen
	int q = 1;	// Zählvariable für CK-Messungen

	double xPT[99];
	double yPT[99];
	double zPT[99];
	double xCK[99];
	double yCK[99];
	double zCK[99];

	// TH-Messung
	maxmagTH = 0.0;

	// pTRM - Messung
	maxmagPT = 0.0;

	// CK - Messung
	double tempmax = 0.0;
	int pos_temp;



	// Abtrennung der TH-Messungen
	for (k=1; k < thellier_datalength; k++)
		for (i=1; i < thellier_datalength; i++)
		{
			if (temp[k] == 0)
				temp[k] = 20.0;
			double t_vs_t1 = temp[i] - floor (temp[k]);
			double t_vs_t2 = temp[i]/temp[k];
			if(t_vs_t1 == 0 && t_vs_t2 == 1)
			{
				tempTH[o] = temp[k];
				magTH[o] = mag[k];
				xTH[o] = x[k];
				yTH[o] = y[k];
				zTH[o] = z[k];
				if (maxmagTH < magTH[o])
					maxmagTH = magTH[o];
				o++;
				TH_steps = o;
			}
		}
			

	// PT bei Raumtemperatur
	magPT[1] = 0.0;
	tempPT[1] = tempTH[1];


	float starttemp = temp[1];
	int CK_steps;
	int n;

	// Vektorsubtraktion TH - pTRM - CK Messung

	for (k = 1; k < TH_steps; k++)
		for (i = 1; i < thellier_datalength; i++)
		{
			float tmptemp1 = floor(temp[i]*100 - 10.9) / 100;
			float tmptemp2 = floor(temp[i]*100 - 11.9) / 100;

			if (tempTH[k] == tmptemp1)
			{
				xPT[p] = xTH[k] - x[i];
				yPT[p] = yTH[k] - y[i];
				zPT[p] = zTH[k] - z[i];
				tempPT[p] = tempTH[k];
				if (m_komp == 1)
					magPT[p] = sqrt(xPT[p]*xPT[p] + yPT[p]*yPT[p] + zPT[p]*zPT[p]);
				else
					magPT[p] = sqrt(zPT[p]*zPT[p]);
				if (maxmagPT < magPT[p])
					maxmagPT = magPT[p];
				p++;
				pTRM_steps = p;
			};
			if (tempTH[k] == tmptemp2)
			{
				for (j = 1; j < i; j++)
					for (n = 1; n < TH_steps; n++)
					if (tempmax < temp[j] && temp[j] == tempTH[n])
					{
						tempmax = temp[j];
						pos_temp = j;
					};
				xCK[q] = x[pos_temp] - x[i];
				yCK[q] = y[pos_temp] - y[i];
				zCK[q] = z[pos_temp] - z[i];
				tempCK[q] = tempTH[k];
				tempCKstart[q] = tempmax;
				if (m_komp == 1)
					magCK[q] = sqrt(xCK[q]*xCK[q] + yCK[q]*yCK[q] + zCK[q]*zCK[q]);
				else
					magCK[q] = sqrt(zCK[q]*zCK[q]);
				q++;
				CK_steps = q;
			};
		};


	// Fehler bei den Checks
	for (k = 1; k < CK_steps; k++)
		for (i = 1; i< pTRM_steps; i++)
			if (tempCK[k] == tempPT[i])
				CK_error[k] = 100* (abs(magCK[k] - magPT[i])/magTH[1]);


	// Maximaler Check-Fehler

	max_CK_error = 0.0;
	int n_end;

	for (n = 1; n < CK_steps; n++)
		if (tempCK[n] > temp_range_max || tempCKstart[n] > temp_range_max)
		{
			n_end = n;
			break;
		}
		else
			n_end = CK_steps;
	
	for (n = 1; n < n_end; n++)
		if (max_CK_error < CK_error[n])
			max_CK_error = CK_error[n];

	Linear(temp_range_min, temp_range_max);
}


void CThellierView::Linear(int t_start, int t_end)
{


	int o,p;

	int o_start, o_end;
	int p_start, p_end;


	// Verbesseren: PT und TH in eine Zählung !!!!!!

	// ********  start und endwert Bestimmung
	// TH
	for (o = 1; o < TH_steps; o++)
		if (tempTH[o] > t_end)
		{
			o_end = o;
			break;
		}
		else
			o_end = TH_steps;

	for (o = 1; o < TH_steps; o++)
		if (tempTH[o] == t_start)
		{
			o_start = o;
			break;
		}
		else
			if (tempTH[o] > t_start)
			{
				if (o==1)
					o_start = 1;
				else
					o_start = o;
				break;
			}
	//pTRM
	for (p = 1; p < pTRM_steps; p++)
		if (tempPT[p] > t_end)
		{
			p_end = p;
			break;
		}
		else
			p_end = pTRM_steps;

	for (p = 1; p < pTRM_steps; p++)
		if (tempPT[p] == t_start)
		{
			p_start = p;
			break;
		}
		else
			if (tempPT[p] > t_start)
			{
				if (p==1)
					p_start = 1;
				else
					p_start = p;
				break;
			}


	double summe_magPT = 0.0;
	double summe_magTH = 0.0;
	double summe_norm_magPT = 0.0;
	double summe_norm_magTH = 0.0;
	double mittelwert_magPT;
	double mittelwert_magTH;
	double mittelwert_norm_magPT;
	double mittelwert_norm_magTH;

	double x_xav[99], x_xav2[99], y_yav[99], y_yav2[99];
	double x_xav_norm[99], x_xav2_norm[99], y_yav_norm[99], y_yav2_norm[99];
	int l = 1;
	int m = 1;
	int paleowindow;
	double summe_x_xav2 = 0.0;
	double summe_y_yav2 = 0.0;
	double summe_xav_yav = 0.0;
	double summe_x_xav2_norm = 0.0;
	double summe_y_yav2_norm = 0.0;
	double summe_xav_yav_norm = 0.0;
	double stderror;
	int i;
	double min_norm_magTH = 2.0;
	double max_norm_magTH = 0.0;

	for (o = o_start; o < o_end; o++)
	{
		summe_magTH += magTH[o];
		summe_norm_magTH += magTH[o]/magTH[1];
		if (min_norm_magTH > magTH[o]/magTH[1])
			min_norm_magTH = magTH[o]/magTH[1];
		if (max_norm_magTH < magTH[o]/magTH[1])
			max_norm_magTH = magTH[o]/magTH[1];
	}

	for (p = p_start; p < p_end; p++)
	{
		summe_magPT += magPT[p];
		summe_norm_magPT += magPT[p]/magPT[2];
	}

	mittelwert_magTH = summe_magTH/(o_end-o_start);

	mittelwert_magPT = summe_magPT/(p_end-p_start);

	mittelwert_norm_magTH = summe_norm_magTH/(o_end-o_start);

	mittelwert_norm_magPT = summe_norm_magPT/(p_end-p_start);

	for (p = p_start; p < p_end; p++)
	{
		x_xav[l] = magPT[p] - mittelwert_magPT;
		x_xav_norm[l] = magPT[p]/magPT[2] - mittelwert_norm_magPT;
		x_xav2[l] = pow(x_xav[l], 2);
		x_xav2_norm[l] = pow(x_xav_norm[l], 2);
		summe_x_xav2  += x_xav2[l];
		summe_x_xav2_norm += x_xav2_norm[l];
		l++;
		paleowindow = l;
	}
	for (o = o_start; o < o_end; o++)
	{
		y_yav[m] = magTH[o] - mittelwert_magTH;
		y_yav_norm[l] = magTH[o]/magTH[1] - mittelwert_norm_magTH;
		y_yav2[m] = pow(y_yav[m], 2);
		y_yav2_norm[l] = pow(y_yav_norm[l], 2);
		summe_y_yav2  += y_yav2[m];
		summe_y_yav2_norm += y_yav2_norm[l];
		m++;
		paleowindow = m;
	}
	for (i = 1; i < paleowindow; i++)
	{
		summe_xav_yav += sqrt(x_xav2[i]) * sqrt(y_yav2[i]); //// * 
		summe_xav_yav_norm += (x_xav_norm[i] * y_yav_norm[i]);
	}

	slope = sqrt(summe_y_yav2/summe_x_xav2);

	y_gerade = mittelwert_magTH;
	x_gerade = mittelwert_magPT;

	number_of_points = paleowindow - 1;

	stderror = sqrt(((2*summe_y_yav2) - (2*slope*summe_xav_yav))/((number_of_points-2)*summe_x_xav2));
 
	stderror_vs_slope = stderror/slope;

	// Normierte Fehlerrechnung
	double M, C, Mp, delYt;
	double tot_norm_magTH = 0.0;
	double Cp[99], Y[99], delY2[99];
	double summe_delY2 = 0.0;

	M = -sqrt(summe_y_yav2_norm/summe_x_xav2_norm);
	C = mittelwert_norm_magTH - (M * mittelwert_norm_magPT);
	Mp = - 1/M;

	for (o = 1; o < TH_steps; o++)
	{
		if (tot_norm_magTH < magTH[o]/magTH[1])
			tot_norm_magTH = magTH[o]/magTH[1];
	}

	delYt = (max_norm_magTH - min_norm_magTH);

	f = (max_norm_magTH - min_norm_magTH)/tot_norm_magTH;

	for (o = o_start; o < o_end; o++)
		Cp[o] = magTH[o]/magTH[1] - (Mp * magPT[o]/magPT[2]);

	for (o = o_start; o < o_end; o++)
		Y[o] = (Cp[o]*M - C*Mp)/ (M - Mp);

	for (o = o_start; o < o_end-1; o++)
	{
		delY2[o] = (Y[o] - Y[o+1])*(Y[o] - Y[o+1]);
		summe_delY2 += delY2[o];
	}

	g = 1 - ((1/delYt) * summe_delY2 / delYt);

	Q = sqrt(slope*slope) * f * g / stderror;

	w = f * g /(sqrt(number_of_points-2) * stderror_vs_slope);

	paleofield = m_field * slope;

	stddev = m_field * stderror_vs_slope;

}

void CThellierView::OnVektorFkomp() 
{
	m_komp = 1;
	UpdateData( FALSE );
	Invalidate();
}

void CThellierView::OnVektorZkomp() 
{
	m_komp = 2;
	UpdateData( FALSE );
	Invalidate();	
}

void CThellierView::OnOptionenRange() 
{
	CRangeDlg dlg ( GetDocument() );
	dlg.DoModal();

//	temp_range_min = 300;
	temp_range_max = 525;
	m_field = 35;
	UpdateData( FALSE );
	Invalidate();
	
}
