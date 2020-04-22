// ThellierToolView.cpp : Implementierung der Klasse CThellierToolView
//

#include "stdafx.h"
#include "ThellierTool.h"

#include "ThellierToolDoc.h"
#include "ThellierToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThellierToolView

IMPLEMENT_DYNCREATE(CThellierToolView, CScrollView)

BEGIN_MESSAGE_MAP(CThellierToolView, CScrollView)
	//{{AFX_MSG_MAP(CThellierToolView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_SAVEGRAPH, OnFileSavegraph)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThellierToolView Konstruktion/Destruktion

CThellierToolView::CThellierToolView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CThellierToolView::~CThellierToolView()
{
}

BOOL CThellierToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CThellierToolView Zeichnen

void CThellierToolView::OnDraw(CDC* pDC)
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDC->SetMapMode(MM_TEXT);
	pDC->SetTextAlign(TA_BASELINE | TA_CENTER);
	pDC->SetBkMode(TRANSPARENT);

	// Initialisierung der Schriften
	CFont textfont, *oldfont;
	LOGFONT logfont ={100,0,0,0,0,0,0,0,0,0,0,0,0,"arial"};

	CSize digitSize = pDC->GetTextExtent("0");
	int scalefactor = digitSize.cx/7;

	if(pDC->m_hAttribDC != NULL)
	{
		textfont.CreatePointFontIndirect (&logfont, pDC);
		oldfont = pDC->SelectObject(&textfont);
		CSize digitSize = pDC->GetTextExtent("0");
		scalefactor = digitSize.cx/7;
	}
	else
	{
		logfont.lfHeight = 16;
		textfont.CreateFontIndirect(&logfont);
		oldfont = pDC->SelectObject(&textfont);
		scalefactor = 1;
	}




	int mainview;
	mainview = pDoc->vopt.mainview;

	if (pDoc != 0 && pDoc->ThellierData.GetSize() != 0)
	{
		// (1) Koordinatentransformation und Messtyp-Bestimmung
		pDoc->CoorTrans(&pDoc->ThellierData);
		// (2) Vektorsubtraktion und Berechnung von Minimal bzw. Maximalwerten
		pDoc->VectorSub(&pDoc->AllDataList);
		// (3) Analyse der TR steps
		pDoc->TRCheckAnalysis(&pDoc->THDataList, &pDoc->TRDataList, &pDoc->PTDataList);
		// (4) Check Korrektur durchführen und Ergebnisse in eigene Liste speichern
		pDoc->CheckCorrection( &pDoc->PTDataList, &pDoc->CKDataList);
		// (5) Falls check Korrektur erwünscht: korrigierte Daten in Hauptliste übernehmen und AC Analyse durchführen
		if (pDoc->vopt.ckcorr)
		{
			pDoc->CKCorrToPTData( &pDoc->PTCkCorrDataList,  &pDoc->CKRemainingDataList);
			pDoc->ACCheckAnalysis(&pDoc->ACDataList, &pDoc->PTDataList, &pDoc->CkErrorList);
		}
		else
		{
			pDoc->ACCheckAnalysis(&pDoc->ACDataList, &pDoc->PTDataList, &pDoc->CkErrorList);
		}
		// (6) Berechnung der Paleointensität		
				// Zuerst suche nach class A Ergebnissen
		pDoc->ThellierCalc(&pDoc->THDataList, &pDoc->PTDataList, &pDoc->CkErrorList, &pDoc->TRResList, &pDoc->ACResList, 0);
				// wenn nicht erfolgreich, suche nach class B Ergebnissen
		if (pDoc->results.m_paleoint == 0)
			pDoc->ThellierCalc(&pDoc->THDataList, &pDoc->PTDataList, &pDoc->CkErrorList, &pDoc->TRResList, &pDoc->ACResList, 1);
		// (6b) optional: Berechnung der Korrigierten Paleonintensität
		if (pDoc->results.m_type == "MT4" && pDoc->vopt.use_autock && pDoc->vopt.automatic == 0)
		{
//			UpdateData(TRUE);
//			pDoc->vopt.ckcorr = TRUE;
			if (pDoc->results.m_paleoint == 0)  // Falls noch kein Ergebniss
			{
				pDoc->vopt.ckcorr = TRUE;
				pDoc->CKCorrToPTData( &pDoc->PTCkCorrDataList,  &pDoc->CKRemainingDataList);
				pDoc->ACCheckAnalysis(&pDoc->ACDataList, &pDoc->PTDataList, &pDoc->CkErrorList);
				pDoc->ThellierCalc(&pDoc->THDataList, &pDoc->PTDataList, &pDoc->CkErrorList, &pDoc->TRResList, &pDoc->ACResList, 0);
				if (pDoc->results.m_paleoint == 0)
					pDoc->ThellierCalc(&pDoc->THDataList, &pDoc->PTDataList, &pDoc->CkErrorList, &pDoc->TRResList, &pDoc->ACResList, 1);
			}
			else
			{
				pDoc->vopt.ckcorr = TRUE;
				double wmax_without_corr;
				if (pDoc->criteria.m_maximizingpar == 0)
					wmax_without_corr = pDoc->results.m_w;
				else
					wmax_without_corr = pDoc->results.m_q;
				pDoc->CKCorrToPTData( &pDoc->PTCkCorrDataList,  &pDoc->CKRemainingDataList);
				pDoc->ACCheckAnalysis(&pDoc->ACDataList, &pDoc->PTDataList, &pDoc->CkErrorList);
				pDoc->ThellierCalc(&pDoc->THDataList, &pDoc->PTDataList, &pDoc->CkErrorList, &pDoc->TRResList, &pDoc->ACResList, 0);
				if (pDoc->results.m_paleoint == 0)
					pDoc->ThellierCalc(&pDoc->THDataList, &pDoc->PTDataList, &pDoc->CkErrorList, &pDoc->TRResList, &pDoc->ACResList, 1);
				double wmax_with_corr;
				if (pDoc->criteria.m_maximizingpar == 0)
					wmax_with_corr = pDoc->results.m_w;
				else
					wmax_with_corr = pDoc->results.m_q;
				if (wmax_with_corr < wmax_without_corr) // Falls Ergebnis nicht besser als ohne Korrektur
				{
					pDoc->vopt.ckcorr = FALSE;
					pDoc->CoorTrans(&pDoc->ThellierData);
					pDoc->VectorSub(&pDoc->AllDataList);
					pDoc->TRCheckAnalysis(&pDoc->THDataList, &pDoc->TRDataList, &pDoc->PTDataList);
					pDoc->CheckCorrection( &pDoc->PTDataList, &pDoc->CKDataList);
					pDoc->ACCheckAnalysis(&pDoc->ACDataList, &pDoc->PTDataList, &pDoc->CkErrorList);
					pDoc->ThellierCalc(&pDoc->THDataList, &pDoc->PTDataList, &pDoc->CkErrorList, &pDoc->TRResList, &pDoc->ACResList, 0);
					if (pDoc->results.m_paleoint == 0)
						pDoc->ThellierCalc(&pDoc->THDataList, &pDoc->PTDataList, &pDoc->CkErrorList, &pDoc->TRResList, &pDoc->ACResList, 1);
				}
			}
		}

		// (7) Normierung der TR daten auf true NRM
		pDoc->NormTRRes(&pDoc->TRResList, pDoc->results.m_nrmt);

		// (8) Bestimmung der Auswerteklasse
		switch (pDoc->CriteriaCheck())
		{
		case 0:	if (!pDoc->vopt.ckcorr)
					pDoc->results.m_class = "A";
				else
					pDoc->results.m_class = "A*";
				break;
		case 1:	if (!pDoc->vopt.ckcorr)
					pDoc->results.m_class = "B";
				else
					pDoc->results.m_class = "B*";
				break;
		case 2:	if (pDoc->results.m_paleoint == 0)
					pDoc->results.m_class.Empty();
				else
				{
					if (!pDoc->vopt.ckcorr)
						pDoc->results.m_class = "C";
					else
						pDoc->results.m_class = "C*";
				}
				break;
		};

		switch (mainview)
		{
		case 0: if (pDoc->vopt.m_arai_norm == 0)
					ThellierPlot (pDC, 400, 300, 0, scalefactor, &pDoc->THDataList, &pDoc->PTDataList, &pDoc->CKDataList, &pDoc->ACResList);
				else
					ThellierPlot (pDC, 300, 300, 0, scalefactor, &pDoc->THDataList, &pDoc->PTDataList, &pDoc->CKDataList, &pDoc->ACResList);
				break;
		case 1: ZijPlot (pDC, 400, 400, 0, scalefactor, &pDoc->THDataList, &pDoc->TRDataList);
				break;
		case 2: DecayPlot (pDC, 400, 300, 0, scalefactor, &pDoc->THDataList, &pDoc->TRDataList);
				break;
		case 3: if (pDoc->vopt.ckcorr)
					MDPlot (pDC, 400, 300, 0, scalefactor, &pDoc->PTDataList, &pDoc->ACResList, &pDoc->TRResList);
				else
					MDPlot (pDC, 400, 300, 0, scalefactor, &pDoc->PTDataList, &pDoc->CkErrorList, &pDoc->TRResList);
				break;
		case 4: AllPlots (pDC, scalefactor);
				break;
		};

	}

 
	pDoc->UpdateAllViews(this);  // Erneuert alle Ansichten ausser CThellierTool3View !! -> Führt zu Problemen mit PrintPreview

}

void CThellierToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// ZU ERLEDIGEN: Gesamte Größe dieser Ansicht berechnen
	sizeTotal.cx = sizeTotal.cy = 1000;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CThellierToolView Drucken

BOOL CThellierToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CThellierToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CThellierToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

/////////////////////////////////////////////////////////////////////////////
// OLE-Server-Unterstützung

// Der folgende Befehls-Handler stellt die Standardtastatur als
//  Benutzerschnittstelle zum Abbruch der direkten Bearbeitungssitzung zur Verfügung. Hier
//  verursacht der Container (nicht der Server) die Deaktivierung.
void CThellierToolView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CThellierToolView Diagnose

#ifdef _DEBUG
void CThellierToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CThellierToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CThellierToolDoc* CThellierToolView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CThellierToolDoc)));
	return (CThellierToolDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThellierToolView Nachrichten-Handler

void CThellierToolView::ThellierPlot(CDC *pDC, int x_pos, int y_pos, int viewmode, int scfa, CThellierResList *datalist, CThellierResList *secondlist, CThellierResList *thirdlist, CThellierResList *fourthlist)
{
	// *************************************************************
	//					    	Thellier plot
	// *************************************************************

	CRect rect;
	GetClientRect(&rect);

	int position1, position2;
	if (viewmode == 0)
	{
		position1 = rect.Width()/2*scfa;
		position2 = rect.Height()/2*scfa;
	}
	else
	{
		position1 = 200*scfa;
		position2 = 200*scfa;
	}

	// Achsenlänge
	int x_l = x_pos*scfa;
	int y_l = y_pos*scfa;
	CSize axesth (x_l, y_l);

	// Null Punkt
	CPoint zeropointth (position1-axesth.cx/2, position2+axesth.cy/2);
	//rechter Rand
	CPoint rigthpointth (position1+axesth.cx/2, position2+axesth.cy/2);
	// oberer Rand
	CPoint uppointth (position1-axesth.cx/2, position2-axesth.cy/2);
	// Radius der Punkte
	int p_r = axesth.cx/100;
	// Dreieck
	int tr = axesth.cx/80;
	// Text Abstand
	int ta = axesth.cy/50;
	int ta_up = ta*3;	

		// Koordinatensystem
	pDC->MoveTo(rigthpointth);
	pDC->LineTo(zeropointth);
	pDC->LineTo(uppointth);

	pDC->MoveTo(rigthpointth);
	pDC->LineTo(rigthpointth.x,zeropointth.y+p_r);
	pDC->MoveTo(zeropointth.x+axesth.cx/2,zeropointth.y);
	pDC->LineTo(zeropointth.x+axesth.cx/2,zeropointth.y+p_r/2);
	pDC->MoveTo(zeropointth);
	pDC->LineTo(zeropointth.x,zeropointth.y+p_r);
	pDC->MoveTo(zeropointth);
	pDC->LineTo(zeropointth.x-p_r,zeropointth.y);
	pDC->MoveTo(zeropointth.x,zeropointth.y-axesth.cy/2);
	pDC->LineTo(zeropointth.x-p_r/2,zeropointth.y-axesth.cy/2);
	pDC->MoveTo(uppointth);
	pDC->LineTo(zeropointth.x-p_r,uppointth.y);

	int tempTH, tempPT, tempCK, tempCKstart;
	double magTH, magPT, magCK;
	CString actualtemp; // zum auslesen des Temperaturschritts
	int deci, sign; //Decimale und Vorzeichen des Tempschritts

	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	double maxmagTH = pDoc->minmax.maxmagTH;
	double maxmagPT = pDoc->minmax.maxmagPT;

	// Abfrage der größeren Achse für Art des Arai plots
	if (pDoc->vopt.m_arai_norm == 1)
	{
		double maxmagALL;
		if (maxmagTH >= maxmagPT)
			maxmagALL = maxmagTH;
		else
			maxmagALL = maxmagPT;
		maxmagTH = maxmagALL;
		maxmagPT = maxmagALL;
	}


	for (int i = 0; i < datalist->GetSize(); i++)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist->GetAt(i);
		tempTH = daten1->m_temp;
		magTH = daten1->m_mag;
		for (int j = 0; j < secondlist->GetSize(); j++)
		{
			CThellierResStruct* daten2 = ( CThellierResStruct* )secondlist->GetAt(j);
			tempPT = daten2->m_temp;
			magPT = daten2->m_mag;
			if (tempTH == tempPT)
			{
				CRect Datapointsize((zeropointth.x+p_r)+(magPT*axesth.cx/maxmagPT),(zeropointth.y-p_r)-(magTH*axesth.cy/maxmagTH),(zeropointth.x-p_r)+(magPT*axesth.cx/maxmagPT),(zeropointth.y+p_r)-(magTH*axesth.cy/maxmagTH));
				pDC->Ellipse (&Datapointsize);
				if (i == 1 || i == 4 || i == 7 || i == 10 || i == 13 || i == 16 || i == 19)
				{
					actualtemp = ecvt(tempPT,3,&deci,&sign);
					actualtemp.Insert(deci,"°C");
					if(tempPT < 100 && tempPT > 10)
						actualtemp.Delete(4);
					pDC->TextOut((zeropointth.x+ta)+(magPT*axesth.cx/maxmagPT),(zeropointth.y-ta_up)-(magTH*axesth.cy/maxmagTH),actualtemp);
				}
			}
		} // Ende der pTRM Werte
		for (j = 0; j < thirdlist->GetSize(); j++)
		{
			CThellierResStruct* daten3 = ( CThellierResStruct* )thirdlist->GetAt(j);
			tempCKstart = daten3->m_temp;
			tempCK = daten3->m_sptemp;
			magCK = daten3->m_mag;
			if (tempTH == tempCK && thirdlist->GetSize() != 0)
			{
				int linksunten_x = (zeropointth.x-tr)+(magCK*axesth.cx/maxmagPT);
				int rechtsunten_x = (zeropointth.x+tr)+(magCK*axesth.cx/maxmagPT);
				int unten_y = (zeropointth.y+p_r)-(magTH*axesth.cy/maxmagTH);
				int oben_x = zeropointth.x+(magCK*axesth.cx/maxmagPT);
				int oben_y = (zeropointth.y-p_r)-(magTH*axesth.cy/maxmagTH);
				pDC->MoveTo (linksunten_x,unten_y);
				pDC->LineTo (rechtsunten_x,unten_y);
				pDC->LineTo (oben_x,oben_y);
				pDC->LineTo (linksunten_x,unten_y);
				for (int k = 0; k < secondlist->GetSize(); k++)
				{
					CThellierResStruct* daten2 = ( CThellierResStruct* )secondlist->GetAt(k);
					tempPT = daten2->m_temp;
					magPT = daten2->m_mag;
					if (tempCKstart == tempPT)
					{
						int line_y;
						int line_x = zeropointth.x+(magPT*axesth.cx/maxmagPT);
						for (int l = 0; l < datalist->GetSize(); l++)
						{
							CThellierResStruct* daten4 = ( CThellierResStruct* )datalist->GetAt(l);
							int tempTHnew = daten4->m_temp;
							double magTHnew = daten4->m_mag;
							if (tempTHnew == tempPT)
							{
								line_y = zeropointth.y-(magTHnew*axesth.cy/maxmagTH);
								pDC->MoveTo (line_x,line_y);
								pDC->LineTo (oben_x,line_y);
								pDC->LineTo (oben_x,unten_y);
							}
						}
					}
				}
			}
		} // Ende der CK Werte
		for (j = 0; j < fourthlist->GetSize(); j++)
		{
			CThellierResStruct* daten5 = ( CThellierResStruct* )fourthlist->GetAt(j);
			int tempACstart = daten5->m_temp;
			int tempAC = daten5->m_sptemp;
			double magAC = daten5->m_z;
			double magPT_AC2 = daten5->m_y;
			double magPT_AC = daten5->m_x;
			if (tempTH == tempAC && fourthlist->GetSize() != 0 && pDoc->vopt.accheck)
			{
				// neu (Modell, 23.09.03)
				int linksunten_x = (zeropointth.x-p_r)+((magAC)*axesth.cx/maxmagPT);
				int rechtsunten_x = (zeropointth.x+p_r)+((magAC)*axesth.cx/maxmagPT);
				int unten_y = (zeropointth.y+p_r)-(magTH*axesth.cy/maxmagTH);
				int oben_x = zeropointth.x+((magAC)*axesth.cx/maxmagPT);
				int oben_y = (zeropointth.y-p_r)-(magTH*axesth.cy/maxmagTH);
				/* alter code von David
				int linksunten_x = (zeropointth.x-p_r)+((magPT_AC-magAC)*axesth.cx/maxmagPT);
				int rechtsunten_x = (zeropointth.x+p_r)+((magPT_AC-magAC)*axesth.cx/maxmagPT);
				int unten_y = (zeropointth.y+p_r)-(magTH*axesth.cy/maxmagTH);
				int oben_x = zeropointth.x+((magPT_AC-magAC)*axesth.cx/maxmagPT);
				int oben_y = (zeropointth.y-p_r)-(magTH*axesth.cy/maxmagTH);
				*/ 	
				CBrush HorBrush;
				HorBrush.CreateSolidBrush (RGB(255,0,0));
				CBrush* pOriginalBrush;
				pOriginalBrush = pDC->SelectObject(&HorBrush);

				CRect TempACdatapointsize(linksunten_x,unten_y,rechtsunten_x,oben_y);
				pDC->Rectangle(&TempACdatapointsize);
				pDC->SelectObject(pOriginalBrush);
			
				for (int k = 0; k < secondlist->GetSize(); k++)
				{
					CThellierResStruct* daten2 = ( CThellierResStruct* )secondlist->GetAt(k);
					tempPT = daten2->m_temp;
					magPT = daten2->m_mag;
					if (tempACstart == tempPT)
					{
						int line_y;
						int line_x = zeropointth.x+(magPT*axesth.cx/maxmagPT);
						for (int l = 0; l < datalist->GetSize(); l++)
						{
							CThellierResStruct* daten4 = ( CThellierResStruct* )datalist->GetAt(l);
							int tempTHnew = daten4->m_temp;
							double magTHnew = daten4->m_mag;
							if (tempTHnew == tempPT)
							{
								line_y = zeropointth.y-(magTHnew*axesth.cy/maxmagTH);
								pDC->MoveTo (line_x,line_y);
								pDC->LineTo (line_x,unten_y-p_r);
								pDC->LineTo (oben_x,unten_y-p_r);
							}
						}
					}
				}
			} 
		}// AC if zu
	}

	// *************** Fit - Gerade für Thellier plot *********************

		double maxPT, minPT;
		double y_ende, y_anfang;

		minPT = pDoc->results.x_1;
		maxPT = pDoc->results.x_2;

		y_ende = pDoc->results.y_gerade - (maxPT - pDoc->results.x_gerade)*sqrt(pDoc->results.m_slope*pDoc->results.m_slope);
		y_anfang = pDoc->results.y_gerade - (minPT - pDoc->results.x_gerade)*sqrt(pDoc->results.m_slope*pDoc->results.m_slope);


		CPen PaleoPen;
		CPen LinePen;
		LinePen.CreatePen (PS_SOLID,1,RGB(0,0,0));
		PaleoPen.CreatePen (PS_DASH,2,RGB(0,0,0));


		CPen* qOriginalPen;
		qOriginalPen = pDC->SelectObject(&PaleoPen);

		if (y_anfang > 0)
		{
			pDC->MoveTo(zeropointth.x+(minPT*axesth.cx/maxmagPT),zeropointth.y-(y_anfang*axesth.cy/maxmagTH));
			pDC->LineTo(zeropointth.x+(maxPT*axesth.cx/maxmagPT),zeropointth.y-(y_ende*axesth.cy/maxmagTH));
		}
		CPen* pOriginalPen;
		pOriginalPen = pDC->SelectObject(&LinePen);

	
	// *************  Beschriftung der Achsen *****************
		
	CString smaxmagPT, smaxmagTH;
	smaxmagPT = ecvt(maxmagPT,5,&deci,&sign);
	if (deci <= 0)
	{
		smaxmagPT.Insert(deci,"0.");
		for (int n = 0; n < -deci; n++)
			smaxmagPT.Insert(2,'0');
	}
	else
		smaxmagPT.Insert(deci,".");
	smaxmagTH = ecvt(maxmagTH,5,&deci,&sign);
	if (deci <= 0)
	{
		smaxmagTH.Insert(deci,"0.");
		for (int n = 0; n < -deci; n++)
			smaxmagTH.Insert(2,'0');
	}
	else
		smaxmagTH.Insert(deci,".");
	// y-Achse
	pDC->TextOut(zeropointth.x-0.05*axesth.cx, zeropointth.y-0.98*axesth.cy, "1.0");		
	pDC->TextOut(zeropointth.x-0.05*axesth.cx, zeropointth.y-0.48*axesth.cy, "0.5");		
	pDC->TextOut(zeropointth.x-0.05*axesth.cx, zeropointth.y+0.02*axesth.cy, "0.0");		
	pDC->TextOut(zeropointth.x+0.1*axesth.cx,zeropointth.y-1.1*axesth.cy,"NRM (* "+smaxmagTH+" mA/m)");	
	// x-Achse
	pDC->TextOut(zeropointth.x, zeropointth.y+0.07*axesth.cy, "0.0");		
	pDC->TextOut(zeropointth.x+0.5*axesth.cx, zeropointth.y+0.07*axesth.cy, "0.5");		
	pDC->TextOut(zeropointth.x+axesth.cx, zeropointth.y+0.07*axesth.cy, "1.0");
	pDC->TextOut(zeropointth.x+axesth.cx*0.5,zeropointth.y+0.13*axesth.cy,"pTRM (* "+smaxmagPT+" mA/m)");

	// *************  Ausgabe des Probennames + Palint *****************

	CString palint, name;
	name = pDoc->fielddata.name;
	int length = name.GetLength();
	CString chara = "	";
	if (name.GetAt(length-1) == chara)
		name.Delete(length-1);
	palint.Format("%.2f \xb1 %.2f \xb5T ",pDoc->results.m_paleoint,pDoc->results.m_stddev);
	pDC->TextOut(rigthpointth.x-0.15*axesth.cy, uppointth.y, name);		
	pDC->TextOut(rigthpointth.x-0.15*axesth.cy, uppointth.y+0.07*axesth.cy, palint);		


}

void CThellierToolView::ZijPlot(CDC *pDC, int x_pos, int y_pos, int viewmode, int scfa, CThellierResList *datalist, CThellierResList *secondlist)
{
	// *************************************************************
	//					    	Zij plot
	// *************************************************************

	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	CPen AxisPen;
	CPen HPen;
	CPen VPen;
	CPen DirPen;
	CBrush HorBrush;
	CBrush OrgBrush;
	AxisPen.CreatePen (PS_SOLID,1,RGB(0,0,0));
	HPen.CreatePen (PS_SOLID,1,RGB(255,0,0));
	VPen.CreatePen (PS_SOLID,1,RGB(0,0,255));
	DirPen.CreatePen (PS_DASH,1,RGB(0,255,0));
	HorBrush.CreateSolidBrush (RGB(255,0,0));
	OrgBrush.CreateSolidBrush (RGB(255,255,255));
	CBrush* pOriginalBrush;
	CPen* pOriginalPen;
	pOriginalPen = pDC->SelectObject(&AxisPen);

	// ******************
	// Position des Plots
	// ******************

	CRect rect;
	GetClientRect(&rect);

	int position1, position2;
	if (viewmode == 0)
	{
		position1 = rect.Width()/2*scfa;
		position2 = rect.Height()/2*scfa;
	}
	else
	{
		position1 = 550*scfa;
		position2 = 200*scfa;
	}

	int x_l = x_pos*scfa;
	int y_l = y_pos*scfa;
	CSize axesth (x_l, y_l);
	int p_r = axesth.cx/80;
	int a_r = axesth.cx/80;


	// Berechnung der absoluten Max.-werte für die Darstellung
	// Deklination:
	// x auf der x Achse
	// y auf der y Achse (positive Wert nach unten)
	// => North enstpricht rechts, West entspricht oben
	// Inklination:
	// z auf der y Achse (positive Werte nach unten)??


	// Bestimmung der maximalen x - Achsen Werte
	double max_left = pDoc->minmax.minx;
	double max_right = pDoc->minmax.maxx;
	if (pDoc->minmax.maxh > max_right)
		max_right = pDoc->minmax.maxh; 
	if (pDoc->minmax.minh < max_left)
		max_left = pDoc->minmax.minh; 

	// Bestimmung der maximalen y - Achsen Werte
	double max_down = pDoc->minmax.maxy;
	double max_up = pDoc->minmax.miny;
	if (pDoc->minmax.minz < max_up)
		max_up = pDoc->minmax.minz; 
	if (pDoc->minmax.maxz > max_down)
		max_down = pDoc->minmax.maxz;

	// Coordinatensystem - Ranbedingungen
	if (max_left > 0)
		max_left = 0.0f;
	if (max_right < 0)
		max_right = 0.0f;
	if (max_down < 0)
		max_down = 0.0f;
	if (max_up > 0)
		max_up = 0.0f;

	// Bestimmung der längsten Achse
	double max_tmp1, max_tmp2, max_all, max_all_sum;
	if (max_down > -max_up)
		max_tmp1 = max_down;
	else
		max_tmp1 = -max_up;
	if (-max_left > max_right)
		max_tmp2 = -max_left;
	else
		max_tmp2 = max_right;
	if (max_tmp1 > max_tmp2)
		max_all = max_tmp1;
	else
		max_all = max_tmp2;
	if ((-max_left + max_right) > (max_down - max_up))
		max_all_sum = -max_left + max_right;
	else
		max_all_sum = -max_up + max_down;

	// Position des Nullpunktes
	int zero_x = position1 - axesth.cx/2 + (-max_left * axesth.cx / (max_all_sum));
	int zero_y = position2 + axesth.cy/2 - (max_down * axesth.cy / (max_all_sum));

	CPoint zeropoint (zero_x, zero_y);
	// unterer rechter Rand
	CPoint rightdownpoint (position1+axesth.cx/2, position2+axesth.cy/2);
	// oberer linker Rand
	CPoint leftuppoint (position1-axesth.cx/2, position2-axesth.cy/2);
	// oberer rechter Rand
	CPoint rightuppoint (position1+axesth.cx/2, position2-axesth.cy/2);

	// Koordinatensystem
	pDC->MoveTo(zeropoint);
	pDC->LineTo(zeropoint.x, zeropoint.y + max_up/max_all_sum*axesth.cy);
	pDC->MoveTo(zeropoint);
	pDC->LineTo(zeropoint.x, zeropoint.y + max_down/max_all_sum*axesth.cy);
	pDC->MoveTo(zeropoint);
	pDC->LineTo(zeropoint.x + max_left/max_all_sum*axesth.cx, zeropoint.y);
	pDC->MoveTo(zeropoint);
	pDC->LineTo(zeropoint.x + max_right/max_all_sum*axesth.cx, zeropoint.y);

	// Erweiterung des Koordinatensystems und Beschriftung
	int x_x_letter = zeropoint.x + 3*a_r + max_right/max_all_sum*axesth.cx;
	int y_x_letter = zeropoint.y + 0.8*a_r;
	int x_y_letter = zeropoint.x;
	int y_y_letter = zeropoint.y - 1.5*a_r + max_up/max_all_sum*axesth.cy;
	CString x_letter, y_letter;
	if (pDoc->vopt.coordinates == 0)
	{
		x_letter = "X,H";
		y_letter = "-Y,-Z";
	}
	else
	{
		x_letter = "N";
		y_letter = "Up,W";
	}
	
	if (-max_left < 0.05*max_right)
	{
		pDC->MoveTo(zeropoint);
		pDC->LineTo(zeropoint.x - 5*a_r, zeropoint.y);
	}
	if (max_right < -0.05*max_left)
	{
		pDC->MoveTo(zeropoint);
		pDC->LineTo(zeropoint.x + 5*a_r, zeropoint.y);
		x_x_letter += 5*a_r; 

	}
	if (-max_up < 0.05*max_down)
	{
		pDC->MoveTo(zeropoint);
		pDC->LineTo(zeropoint.x, zeropoint.y - 5*a_r);
		y_y_letter -= 5*a_r;
	}
	if (max_down < -0.05*max_up)
	{
		pDC->MoveTo(zeropoint);
		pDC->LineTo(zeropoint.x, zeropoint.y + 5*a_r);
	}
	pDC->TextOut(x_x_letter, y_x_letter, x_letter, x_letter.GetLength());
	pDC->TextOut(x_y_letter, y_y_letter, y_letter, y_letter.GetLength());

	// Zeichnen der H-Kurve
	pOriginalPen = pDC->SelectObject(&HPen);
	pOriginalBrush = pDC->SelectObject(&HorBrush);

	for (int i=0; i < datalist->GetSize(); i++)
	{
		CThellierResStruct* daten = ( CThellierResStruct* )datalist->GetAt(i);
		// Linien zeichnen
		if (i > 0)
			pDC->LineTo(zeropoint.x+(daten->m_x*axesth.cx/max_all_sum),zeropoint.y+(daten->m_y*axesth.cy/max_all_sum));
		// Punkte zeichnen
		int rigthdown_x = (zeropoint.x+p_r) + (daten->m_x*axesth.cx/max_all_sum);
		int rigthdown_y = (zeropoint.y-p_r) + (daten->m_y*axesth.cy/max_all_sum);
		int leftdown_x = (zeropoint.x-p_r) + (daten->m_x*axesth.cx/max_all_sum);
		int leftdown_y = (zeropoint.y+p_r) + (daten->m_y*axesth.cy/max_all_sum);
		CRect datapointsize(rigthdown_x,rigthdown_y,leftdown_x,leftdown_y);
		pDC->Ellipse (&datapointsize);
		// Zeiger zurücksetzten
		pDC->MoveTo(zeropoint.x+(daten->m_x*axesth.cx/max_all_sum),zeropoint.y+(daten->m_y*axesth.cy/max_all_sum));
	}

	// Zeichnen der V-Kurve
	pOriginalPen = pDC->SelectObject(&VPen);
	pOriginalBrush = pDC->SelectObject(&OrgBrush);

	// Mittleres x und vorzeichen von x_mean berechnen (für ZIJ-Plot, leon, 3.01.04)
	double x_mean = 0.0;
	double x_sign;
	for (i=0; i < datalist->GetSize(); i++)
	{
		CThellierResStruct* daten = ( CThellierResStruct* )datalist->GetAt(i);
		x_mean += daten->m_x/(datalist->GetSize()-1);
	}
	x_sign = x_mean/fabs(x_mean);

	for (i=0; i < datalist->GetSize(); i++)
	{
		CThellierResStruct* daten = ( CThellierResStruct* )datalist->GetAt(i);
		// Linien zeichnen
		// - Vorzeichen von x-Wert berücksichtigen (siehe oben)
		//		- (x + -> rechte Plot-Hälfte, Inc + -> unten rechts, Inc - -> oben rechts)
		//		- (x - -> linke Plot-Hälfte, Inc + -> links unten, Inc - -> links oben)
//		double m_h = daten->m_x/fabs(daten->m_x)*sqrt(pow(daten->m_x,2) + pow(daten->m_y,2));
		double m_h = x_sign*sqrt(pow(daten->m_x,2) + pow(daten->m_y,2));
		if (i > 0)
			pDC->LineTo(zeropoint.x+(m_h*axesth.cx/max_all_sum),zeropoint.y+(daten->m_z*axesth.cy/max_all_sum));
		// Punkte zeichnen
		int rigthdown_x = (zeropoint.x+p_r) + (m_h*axesth.cx/max_all_sum);
		int rigthdown_y = (zeropoint.y-p_r) + (daten->m_z*axesth.cy/max_all_sum);
		int leftdown_x = (zeropoint.x-p_r) + (m_h*axesth.cx/max_all_sum);
		int leftdown_y = (zeropoint.y+p_r) + (daten->m_z*axesth.cy/max_all_sum);
		CRect datapointsize(rigthdown_x,rigthdown_y,leftdown_x,leftdown_y);
		pDC->Ellipse (&datapointsize);
		// Temperaturbeschriftung
		if (i == 1 || i == 4 || i == 7 || i == 10 || i == 13 || i == 16 || i == 19)
		{
			int deci, sign;
			CString actualtemp = ecvt(daten->m_temp,3,&deci,&sign);
			actualtemp.Insert(deci,"°C");
			if(daten->m_temp < 100 && daten->m_temp > 10)
			actualtemp.Delete(4);
			pDC->TextOut((zeropoint.x+2*p_r)+(m_h*axesth.cx/max_all_sum),(zeropoint.y-2*p_r)+(daten->m_z*axesth.cy/max_all_sum),actualtemp);
		}
		// Zeiger zurücksetzten
		pDC->MoveTo(zeropoint.x+(m_h*axesth.cx/max_all_sum),zeropoint.y+(daten->m_z*axesth.cy/max_all_sum));
	}

	// *********************
	// Scales auf den Achsen
	// *********************

	pOriginalPen = pDC->SelectObject(&AxisPen);

	double scaleex;
	double stepvalue, x_pos_stepvalue, y_pos_stepvalue, x_neg_stepvalue, y_neg_stepvalue;
	double i_tmp;

	if (max_all > 10) // richtigen Bereich für scales bestimmen
	{
		for (i = 10; i < 100000; i = i*10)
		{
			if (max_all/i <= 10 && max_all/i > 1)
			{
				scaleex = i;
				stepvalue = max_all/i;
				x_neg_stepvalue = -max_left/i;
				y_neg_stepvalue = -max_up/i;
				x_pos_stepvalue = max_right/i;
				y_pos_stepvalue = max_down/i;
			}
		};
	}
	else
	{
		for (i = 10; i < 10000000; i = i*10)
		{
			i_tmp = 10.0/i;
			if (max_all/i_tmp <= 10 && max_all/i_tmp > 1)
			{
				scaleex = i_tmp;
				stepvalue = max_all/i_tmp;
				x_neg_stepvalue = -max_left/i_tmp;
				y_neg_stepvalue = -max_up/i_tmp;
				x_pos_stepvalue = max_right/i_tmp;
				y_pos_stepvalue = max_down/i_tmp;
			}
		};
	}


	int scale_stepwidth = 0;
	if (-max_left >= max_right && -max_left >= max_down && -max_left >= -max_up)
		scale_stepwidth = (zeropoint.x-leftuppoint.x)/stepvalue;
	else
		if (max_right > -max_up && max_right > max_down)
			scale_stepwidth = (rightuppoint.x-zeropoint.x)/stepvalue;
		else
			if (-max_up >= max_down)
				scale_stepwidth = (zeropoint.y-leftuppoint.y)/stepvalue;
			else
				scale_stepwidth = (rightdownpoint.y-zeropoint.y)/stepvalue;

	// Variablen für die Beschriftung
	CString magnetization;	
	char step [11];
	int deci, sign;

	for (i = 1; i < x_pos_stepvalue; i++)
	{
		pDC->MoveTo(zeropoint.x+i*scale_stepwidth, zeropoint.y - a_r);
		pDC->LineTo(zeropoint.x+i*scale_stepwidth, zeropoint.y + a_r);
		if (x_neg_stepvalue <= x_pos_stepvalue)
		{
			if (x_pos_stepvalue < 4)
			{
				magnetization = ecvt(i*scaleex, 10, &deci,&sign);
				if (deci <= 0)
				{
					magnetization.Insert(deci,"0.");
					for (int n = 0; n < -deci; n++)
						magnetization.Insert(2,'0');
					magnetization = magnetization.Left(-deci+3);
				}
				else
					magnetization = magnetization.Left(deci);
				//itoa (i*scaleex, step, 10);
				//magnetization = step;
				pDC->TextOut(zeropoint.x+i*scale_stepwidth, zeropoint.y + 5*p_r, magnetization, magnetization.GetLength());
			}
			else
				if (x_pos_stepvalue < 7)
				{
					if (i/2.0 == 1 || i/2.0 == 2 || i/2.0 == 3)
					{
						magnetization = ecvt(i*scaleex, 10, &deci,&sign);
						if (deci <= 0)
						{
							magnetization.Insert(deci,"0.");
							for (int n = 0; n < -deci; n++)
								magnetization.Insert(2,'0');
							magnetization = magnetization.Left(-deci+3);
						}
						else
							magnetization = magnetization.Left(deci);
						//itoa (i*scaleex, step, 10);
						//magnetization = step;
						pDC->TextOut(zeropoint.x+i*scale_stepwidth, zeropoint.y + 5*p_r, magnetization, magnetization.GetLength());
					}
				}
				else
				{
					if (i == 5 )
					{
						magnetization = ecvt(i*scaleex,10, &deci,&sign);
						if (deci <= 0)
						{
							magnetization.Insert(deci,"0.");
							for (int n = 0; n < -deci; n++)
								magnetization.Insert(2,'0');
							magnetization = magnetization.Left(-deci+3);
						}
						else
							magnetization = magnetization.Left(deci);
						//itoa (i*scaleex, step, 10);
						//magnetization = step;
						pDC->TextOut(zeropoint.x+i*scale_stepwidth, zeropoint.y + 5*p_r, magnetization, magnetization.GetLength());
					}
				}
		}
	};

	for (i = 1; i < y_pos_stepvalue; i++)
	{
		pDC->MoveTo(zeropoint.x - a_r, zeropoint.y+i*scale_stepwidth);
		pDC->LineTo(zeropoint.x + a_r, zeropoint.y+i*scale_stepwidth);
	};
	for (i = 1; i < x_neg_stepvalue; i++)
	{
		pDC->MoveTo(zeropoint.x-i*scale_stepwidth, zeropoint.y - a_r);
		pDC->LineTo(zeropoint.x-i*scale_stepwidth, zeropoint.y + a_r);
		if (x_neg_stepvalue > x_pos_stepvalue)
		{
			if (x_pos_stepvalue < 4)
			{
				magnetization = ecvt(i*scaleex,10, &deci,&sign);
				if (deci <= 0)
				{
					magnetization.Insert(deci,"0.");
					for (int n = 0; n < -deci; n++)
						magnetization.Insert(2,'0');
					magnetization = magnetization.Left(-deci+3);
				}
				else
					magnetization = magnetization.Left(deci);
				//itoa (i*scaleex, step, 10);
				//magnetization = step;
				magnetization.Insert(0,'-');
				pDC->TextOut(zeropoint.x-i*scale_stepwidth, zeropoint.y + 5*p_r, magnetization, magnetization.GetLength());
			}
			else
				if (x_pos_stepvalue < 7)
				{
					if (i/2.0 == 1 || i/2.0 == 2 || i/2.0 == 3)
					{
						magnetization = ecvt(i*scaleex,10, &deci,&sign);
						if (deci <= 0)
						{
							magnetization.Insert(deci,"0.");
							for (int n = 0; n < -deci; n++)
								magnetization.Insert(2,'0');
							magnetization = magnetization.Left(-deci+3);
						}
						else
							magnetization = magnetization.Left(deci);
						//itoa (i*scaleex, step, 10);
						//magnetization = step;
						magnetization.Insert(0,'-');
						pDC->TextOut(zeropoint.x-i*scale_stepwidth, zeropoint.y + 5*p_r, magnetization, magnetization.GetLength());
					}
				}
				else
				{
					if (i == 5 )
					{
						magnetization = ecvt(i*scaleex,10, &deci,&sign);
						if (deci <= 0)
						{
							magnetization.Insert(deci,"0.");
							for (int n = 0; n < -deci; n++)
								magnetization.Insert(2,'0');
							magnetization = magnetization.Left(-deci+3);
						}
						else
							magnetization = magnetization.Left(deci);
						//itoa (i*scaleex, step, 10);
						//magnetization = step;
						magnetization.Insert(0,'-');
						pDC->TextOut(zeropoint.x-i*scale_stepwidth, zeropoint.y + 5*p_r, magnetization, magnetization.GetLength());
					}
				}
		}
	};
	for (i = 1; i < y_neg_stepvalue; i++)
	{
		pDC->MoveTo(zeropoint.x - a_r, zeropoint.y-i*scale_stepwidth);
		pDC->LineTo(zeropoint.x + a_r, zeropoint.y-i*scale_stepwidth);
	};

	// *******************************************
	// Mittlere Richtung (Berechnung und zeichnen)
	// *******************************************

	pOriginalPen = pDC->SelectObject(&DirPen);
	if (pDoc->results.m_paleoint > 0)
	{
			double pi = 3.141592654;
			double pis = pi/180;
			double H = pDoc->minmax.maxmagTH * cos(pis*pDoc->results.m_inc);
			double x_md = H * cos(pis*pDoc->results.m_dec);
			double y_md = H * sin(pis*pDoc->results.m_dec);
			double z_md = pDoc->minmax.maxmagTH * sin(pis*pDoc->results.m_inc);
			double h_md = x_md/fabs(x_md) * sqrt(pow(x_md,2) + pow(y_md,2));
			if (!pDoc->vopt.zonly)
			{
				pDC->MoveTo(zeropoint.x,zeropoint.y);
				pDC->LineTo(zeropoint.x+(x_md*axesth.cx/max_all_sum),zeropoint.y+(y_md*axesth.cy/max_all_sum));
			};
			pDC->MoveTo(zeropoint.x,zeropoint.y);
			pDC->LineTo(zeropoint.x+(h_md*axesth.cx/max_all_sum),zeropoint.y+(z_md*axesth.cy/max_all_sum));
	};
	// Stift zurücksetzten
	pOriginalPen = pDC->SelectObject(&AxisPen);

}

void CThellierToolView::DecayPlot(CDC *pDC, int x_pos, int y_pos, int viewmode, int scfa, CThellierResList *datalist, CThellierResList *secondlist)
{
	// ********************************************
	// Decay - Plot *******************************
	// ********************************************

	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rect;
	GetClientRect(rect);

	CPen AxisPen;
	AxisPen.CreatePen (PS_SOLID,1,RGB(0,0,0));
	CPen* pOriginalPen;
	pOriginalPen = pDC->SelectObject(&AxisPen);
	CBrush HorBrush;
	HorBrush.CreateSolidBrush (RGB(0,0,0));


	int position1, position2;

	if (viewmode == 0)
	{
		position1 = rect.Width()/2*scfa;
		position2 = rect.Height()/2*scfa;
	}
	else
	{
		position1 = 200*scfa;
		position2 = 550*scfa;
	}

	// Achsenlänge
	int x_l = x_pos*scfa;
	int y_l = y_pos*scfa;
	CSize axesth (x_l, y_l);

	// Null Punkt
	CPoint zeropointth (position1-axesth.cx/2, position2+axesth.cy/2);
	//rechter Rand
	CPoint rigthpointth (position1+axesth.cx/2, position2+axesth.cy/2);
	// oberer Rand
	CPoint uppointth (position1-axesth.cx/2, position2-axesth.cy/2);
	// Radius der Punkte
	int p_r = axesth.cx/100;

		// Koordinatensystem
	pDC->MoveTo(rigthpointth);
	pDC->LineTo(zeropointth);
	pDC->LineTo(uppointth);

	int maxTH = pDoc->minmax.maxstep;
	double maxmagTH = pDoc->minmax.maxmagTH;
	int tempTH, tempTR;
	double magTH, magTR;

	for (int i = 0; i < datalist->GetSize(); i++)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist->GetAt(i);
		tempTH = daten1->m_temp;
		magTH = daten1->m_mag;
		if (i > 0)
			pDC->LineTo(zeropointth.x+(tempTH*axesth.cx/maxTH),zeropointth.y-(magTH*axesth.cy/maxmagTH));
		pDC->MoveTo(zeropointth.x+(tempTH*axesth.cx/maxTH),zeropointth.y-(magTH*axesth.cy/maxmagTH));
		CRect Tempdatapointsize((zeropointth.x+p_r)+(tempTH*axesth.cx/maxTH),(zeropointth.y-p_r)-(magTH*axesth.cy/maxmagTH),(zeropointth.x-p_r)+(tempTH*axesth.cx/maxTH),(zeropointth.y+p_r)-(magTH*axesth.cy/maxmagTH));
		pDC->Ellipse (&Tempdatapointsize);
		pDC->MoveTo(zeropointth.x+(tempTH*axesth.cx/maxTH),zeropointth.y-(magTH*axesth.cy/maxmagTH));
	}

	for (int j = 0; j < secondlist->GetSize(); j++)
	{
		CThellierResStruct* daten2 = ( CThellierResStruct* )secondlist->GetAt(j);
		tempTR = daten2->m_temp;
		magTR = daten2->m_mag;
		CBrush* pOriginalBrush;
		pOriginalBrush = pDC->SelectObject(&HorBrush);

		CRect TempTRdatapointsize((zeropointth.x+p_r)+(tempTR*axesth.cx/maxTH),(zeropointth.y-p_r)-(magTR*axesth.cy/maxmagTH),(zeropointth.x-p_r)+(tempTR*axesth.cx/maxTH),(zeropointth.y+p_r)-(magTR*axesth.cy/maxmagTH));
		pDC->Rectangle(&TempTRdatapointsize);
		pDC->SelectObject(pOriginalBrush);
	}


	//Scales auf der x-Achse
	pDC->TextOut(zeropointth.x+axesth.cx*0.5,zeropointth.y+axesth.cy*0.14,"Temp. [°C]");

	int n_temphund = maxTH/100;
	int stepdistance = 100*axesth.cx/maxTH;
	char step [4];
	for (int n = 1; n < n_temphund+1; n++ )
	{
		int newstep = stepdistance*n;
		pDC->MoveTo(zeropointth.x+(stepdistance*n),zeropointth.y);
		pDC->LineTo(zeropointth.x+(stepdistance*n),zeropointth.y+p_r);
		itoa (n*100, step, 10);
		pDC->TextOut (zeropointth.x+newstep,zeropointth.y+5*p_r,step);
	}
	//Scales auf der y-Achse
	CString smaxmagTH;
	int deci, sign;
	smaxmagTH = ecvt(maxmagTH,5,&deci,&sign);
	if (deci <= 0)
	{
		smaxmagTH.Insert(deci,"0.");
		for (int n = 0; n < -deci; n++)
			smaxmagTH.Insert(2,'0');
	}
	else
		smaxmagTH.Insert(deci,".");
	pDC->MoveTo(zeropointth);
	pDC->LineTo(zeropointth.x-p_r,zeropointth.y);
	pDC->MoveTo(zeropointth.x,zeropointth.y-axesth.cy/2);
	pDC->LineTo(zeropointth.x-p_r/2,zeropointth.y-axesth.cy/2);
	pDC->MoveTo(uppointth);
	pDC->LineTo(zeropointth.x-p_r,uppointth.y);
	pDC->TextOut(zeropointth.x-0.05*axesth.cx, zeropointth.y-0.98*axesth.cy, "1.0");		
	pDC->TextOut(zeropointth.x-0.05*axesth.cx, zeropointth.y-0.48*axesth.cy, "0.5");		
	pDC->TextOut(zeropointth.x-0.05*axesth.cx, zeropointth.y+0.02*axesth.cy, "0.0");		
	pDC->TextOut(zeropointth.x+0.1*axesth.cx,zeropointth.y-1.1*axesth.cy,"NRM (* "+smaxmagTH+" mA/m)");	

}

void CThellierToolView::MDPlot(CDC *pDC, int x_pos, int y_pos, int viewmode, int scfa, CThellierResList *datalist, CThellierResList *secondlist, CThellierResList *thirdlist)
{

	// *************************************************************
	//					Checkdiff and MD tail plot
	// *************************************************************

	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rect;
	GetClientRect(rect);

	int position1, position2;
	if (viewmode == 0)
	{
		position1 = rect.Width()/2*scfa;
		position2 = rect.Height()/2*scfa;
	}
	else
	{
		position1 = 550*scfa;
		position2 = 550*scfa;
	}

	// Achsenlänge
	int x_l = x_pos*scfa;
	int y_l = y_pos*scfa;
	CSize axesall (x_l, y_l);
	// Individual Plots
	CSize axesth (0.45*x_l,0.45*y_l);

	CPen LinePen;
	CBrush AngDiffBrush;
	CBrush NormalBrush;
	AngDiffBrush.CreateSolidBrush (RGB(255,0,0));
	LinePen.CreatePen (PS_SOLID,1,RGB(0,0,0));
	NormalBrush.CreateSolidBrush (RGB(255,255,255));

	CBrush* qOriginalBrush;
	CPen* pOriginalPen;

	CString Diff;
	CString AngDiff;
	Diff.Empty();
	AngDiff.Empty();
	int i;
	int p_r = axesth.cx/100;

	// Bestimmung der maximaltemp
	int maxTH = pDoc->minmax.maxstep;

	// Pi
	double pi = 3.141592654;
	double pis = pi/180;

	// Variablen zur Achsenbeschriftung
	int n_temphund;
	int stepdistance;
	char step [4];
	int n;
	int fivepercentsteps;
	int maxrdiff;

	// ********************************************
	// Differnce pTRM-dir and Labfield-dir ********
	// ********************************************

	CPoint zeropointp1 (position1-axesall.cx/2, position2);
	//rechter Rand
	CPoint rigthpointp1 (position1-0.05*axesall.cx, position2);
	// oberer Rand
	CPoint uppointp1 (position1-axesall.cx/2, position2-0.45*axesall.cy);
	// oberer rechter Rand
	CPoint uprightpointp1 (position1-0.05*axesall.cx, position2-0.45*axesall.cy);

	pDC->MoveTo(rigthpointp1);
	pDC->LineTo(zeropointp1);
	pDC->LineTo(uppointp1);
	pDC->LineTo(uprightpointp1);
	pDC->LineTo(rigthpointp1);
	
	for (i = 1; i < datalist->GetSize(); i++)
	{
		CThellierResStruct* daten = ( CThellierResStruct* )datalist->GetAt(i);
		int tempPT = daten->m_temp;
		double xPT = daten->m_x;
		double yPT = daten->m_y;
		double zPT = daten->m_z;
		double dirPT = fabs(atan(zPT/sqrt(xPT*xPT + yPT*yPT))*180/pi);
		CRect rectanglesize_difffield((zeropointp1.x+2*p_r)+(tempPT*axesth.cx/maxTH),(zeropointp1.y),(zeropointp1.x-2*p_r)+(tempPT*axesth.cx/maxTH),(zeropointp1.y-(90-dirPT)*axesth.cy/90));
		qOriginalBrush = pDC->SelectObject(&NormalBrush);
		pDC->Rectangle (&rectanglesize_difffield);
	}

	// Achsenbeschriftung (Initialisierungen)
		qOriginalBrush = pDC->SelectObject(&NormalBrush);
		pOriginalPen = pDC->SelectObject(&LinePen);

		n_temphund = 90/30;
		stepdistance = 30*axesth.cy/90;

		// Beschriftung der y-Achse
		for (n = 1; n < n_temphund+1; n++ )
		{
			int newstep = stepdistance*n;
			pDC->MoveTo(zeropointp1.x,zeropointp1.y-(stepdistance*n));
			pDC->LineTo(zeropointp1.x+3*p_r,zeropointp1.y-(stepdistance*n));
			itoa (n*30, step, 10);
			pDC->TextOut (zeropointp1.x-0.06*axesth.cx,zeropointp1.y-newstep+0.03*axesth.cy,step);
		}
		pDC->SetTextAlign(TA_LEFT);
		pDC->TextOut(uppointp1.x+5*p_r,uppointp1.y+5*p_r,"Ang. diff Labfield <-> pTRM [°]"); // (positiv for decrease of intensity)
		pDC->SetTextAlign(TA_BASELINE | TA_CENTER);

		// Beschriftung der x-Achse
		n_temphund = maxTH/100;
		stepdistance = 100*axesth.cx/maxTH;

		for (n = 1; n < n_temphund+1; n++ )
		{
			int newstep = stepdistance*n;
			pDC->MoveTo(zeropointp1.x+(stepdistance*n),zeropointp1.y);
			pDC->LineTo(zeropointp1.x+(stepdistance*n),zeropointp1.y-3*p_r);
			pDC->MoveTo(uppointp1.x+newstep,uppointp1.y);
			pDC->LineTo(uppointp1.x+newstep,uppointp1.y+3*p_r);
			if (thirdlist->GetSize() == 0)
			{
				itoa (n*100, step, 10);
				pDC->TextOut (zeropointp1.x+newstep,zeropointp1.y+0.1*axesth.cy,step);
			}
		}
		if (thirdlist->GetSize() == 0)
			pDC->TextOut(zeropointp1.x+axesth.cx*0.5,zeropointp1.y+axesth.cy*0.2,"Temp. [°C]");

	
	// ********************************************
	// Differnce of Checks and pTRMs **************
	// ********************************************

	if (secondlist->GetSize() != 0)
	{

		CPoint zeropointp2 (position1+0.05*axesall.cx, position2-(0.45*axesall.cy)/2);
		//rechter Rand
		CPoint rigthpointp2 (position1+axesall.cx/2, position2-(0.45*axesall.cy)/2);
		// oberer Rand
		CPoint uppointp2 (position1+0.05*axesall.cx, position2-0.45*axesall.cy);
		// unterer Rand
		CPoint downpointp2 (position1+0.05*axesall.cx, position2);
		// oberer rechter Rand
		CPoint uprightpointp2 (position1+axesall.cx/2, position2-0.45*axesall.cy);
		// unterer rechter Rand
		CPoint downrightpointp2 (position1+axesall.cx/2, position2);


		pDC->MoveTo(rigthpointp2);
		pDC->LineTo(zeropointp2);
		pDC->LineTo(uppointp2);
		pDC->LineTo(downpointp2);
		pDC->LineTo(downrightpointp2);
		pDC->LineTo(uprightpointp2);
		pDC->LineTo(uppointp2);

		double CK_error;
		double maxckdiff;

		for (i = 0; i < secondlist->GetSize(); i++)
		{
			CThellierResStruct* daten = ( CThellierResStruct* )secondlist->GetAt(i);
			int tempCK = daten->m_sptemp;
			if (pDoc->results.m_trm > 0)
			{
				CK_error = daten->m_mag*100/pDoc->results.m_trm; // normiert auf TRM (falls möglich)
				if (pDoc->vopt.ckcorr)
					fivepercentsteps = ceil((pDoc->minmax.maxdiffAC*100/pDoc->results.m_trm)/5);
				else
					fivepercentsteps = ceil((pDoc->minmax.maxdiffCK*100/pDoc->results.m_trm)/5);
				maxckdiff = fivepercentsteps*5;
			}
			else
			{
				CK_error = daten->m_mag*100/pDoc->minmax.maxmagTH; // ansonsten auf maximale NRM
				if (pDoc->vopt.ckcorr)
					fivepercentsteps = ceil((pDoc->minmax.maxdiffAC*100/pDoc->minmax.maxmagTH)/5);
				else
					fivepercentsteps = ceil((pDoc->minmax.maxdiffCK*100/pDoc->minmax.maxmagTH)/5);
				maxckdiff = fivepercentsteps*5;
			}
			if (maxckdiff != 0)
			{
				CRect rectanglesize_difffield((zeropointp2.x+2*p_r)+(tempCK*axesth.cx/maxTH),(zeropointp2.y),(zeropointp2.x-2*p_r)+(tempCK*axesth.cx/maxTH),(zeropointp2.y-CK_error*axesth.cy/2/maxckdiff));
				qOriginalBrush = pDC->SelectObject(&NormalBrush);
				pDC->Rectangle (&rectanglesize_difffield);
			}
		}
		
/*		// Spline zeichnen
		pDoc->CkErrorSpline(&pDoc->CkErrorList, 3, 1.99e30);
		if (pDoc->results.m_trm > 0 && !pDoc->vopt.ckcorr)
		{
			pDC->MoveTo(zeropointp2);
			for (i = 0; i < 550; i=i+20)
			{
				pDC->LineTo ((zeropointp2.x)+(i*axesth.cx/maxTH),(zeropointp2.y - pDoc->CkErrorSplinet(&pDoc->CkErrorList, pDoc->ckspline_y2, pDoc->ckspline_length, i)*100/pDoc->results.m_trm*axesth.cy/2/maxckdiff));
			}
		}
*/
		// Achsenbeschriftung (Initialisierungen)
		qOriginalBrush = pDC->SelectObject(&NormalBrush);
		pOriginalPen = pDC->SelectObject(&LinePen);

		int stepper; // Schrittweite y-Achse für Plot
		if (maxckdiff < 30)
			stepper = 5;
		else
			stepper = 10;


		n_temphund = maxckdiff/stepper;
		if (maxckdiff == 0)
			stepdistance = 5*axesth.cy/2/5;
		else
			stepdistance = stepper*axesth.cy/2/maxckdiff;

		// Beschriftung der y-Achse
		for (n = 1; n < n_temphund+1; n++ )
		{
			int newstep = stepdistance*n;
			pDC->MoveTo(zeropointp2.x,zeropointp2.y-(stepdistance*n));
			pDC->LineTo(zeropointp2.x+3*p_r,zeropointp2.y-(stepdistance*n));
			itoa (n*stepper, step, 10);
			pDC->TextOut (zeropointp2.x-0.06*axesth.cx,zeropointp2.y-newstep+0.03*axesth.cy/2,step);
		}
		pDC->SetTextAlign(TA_LEFT);
		if (pDoc->vopt.ckcorr)
			pDC->TextOut(uppointp2.x+5*p_r,uppointp2.y+5*p_r,"delta AC [%]"); // (positiv for decrease of intensity)
		else
			pDC->TextOut(uppointp2.x+5*p_r,uppointp2.y+5*p_r,"delta Ck [%]"); // (positiv for decrease of intensity)
		pDC->SetTextAlign(TA_BASELINE | TA_CENTER);

		// Beschriftung der x-Achse
		n_temphund = maxTH/100;
		stepdistance = 100*axesth.cx/maxTH;

		for (n = 1; n < n_temphund+1; n++ )
		{
			int newstep = stepdistance*n;
			pDC->MoveTo(zeropointp2.x+(stepdistance*n),zeropointp2.y-3*p_r);
			pDC->LineTo(zeropointp2.x+(stepdistance*n),zeropointp2.y+3*p_r);
			pDC->MoveTo(downpointp2.x+newstep,downpointp2.y);
			pDC->LineTo(downpointp2.x+newstep,downpointp2.y-3*p_r);
			pDC->MoveTo(uppointp2.x+newstep,uppointp2.y);
			pDC->LineTo(uppointp2.x+newstep,uppointp2.y+3*p_r);
			if (thirdlist->GetSize() == 0)
			{
				itoa (n*100, step, 10);
				pDC->TextOut (downpointp2.x+newstep,downpointp2.y+0.1*axesth.cy,step);
			}
		}
		if (thirdlist->GetSize() == 0)
			pDC->TextOut(downpointp2.x+axesth.cx*0.5,downpointp2.y+axesth.cy*0.2,"Temp. [°C]");

	}	
	// ********************************************
	// Differnce of TH and TR - Plot: Intensity ***
	// ********************************************

	if (thirdlist->GetSize() != 0)
	{
		double magTRdiff;
		double zTRdiff;
		double hTRdiff;
		int tempTR;

		CPoint zeropointp3 (position1+0.05*axesall.cx, position2+axesall.cy*(0.55/2));
		//rechter Rand
		CPoint rigthpointp3 (position1+axesall.cx/2, position2+axesall.cy*(0.55/2));
		// oberer Rand
		CPoint uppointp3 (position1+0.05*axesall.cx, position2+0.05*axesall.cy);
		// unterer Rand
		CPoint downpointp3 (position1+0.05*axesall.cx, position2+axesall.cy/2);
		// oberer rechter Rand
		CPoint uprightpointp3 (position1+axesall.cx/2, position2+0.05*axesall.cy);
		// unterer rechter Rand
		CPoint downrightpointp3 (position1+axesall.cx/2, position2+axesall.cy/2);

		pDC->MoveTo(rigthpointp3);
		pDC->LineTo(zeropointp3);
		pDC->LineTo(uppointp3);
		pDC->LineTo(downpointp3);
		pDC->LineTo(downrightpointp3);
		pDC->LineTo(uprightpointp3);
		pDC->LineTo(uppointp3);

		fivepercentsteps = ceil(pDoc->minmax.maxrdiffTR/5);
		maxrdiff = fivepercentsteps*5;

		for (i = 0; i < thirdlist->GetSize(); i++)
		{
			CThellierResStruct* daten = ( CThellierResStruct* )thirdlist->GetAt(i);
			tempTR = daten->m_temp;
			magTRdiff = daten->m_mag;
			if (maxrdiff != 0)
			{
				CRect rectanglesize_difffield((zeropointp3.x+2*p_r)+(tempTR*axesth.cx/maxTH),(zeropointp3.y),(zeropointp3.x-2*p_r)+(tempTR*axesth.cx/maxTH),(zeropointp3.y-magTRdiff*axesth.cy/2/maxrdiff));
				qOriginalBrush = pDC->SelectObject(&NormalBrush);
				pDC->Rectangle (&rectanglesize_difffield);
			}
		}

		// Achsenbeschriftung (Initialisierungen)
		qOriginalBrush = pDC->SelectObject(&NormalBrush);
		pOriginalPen = pDC->SelectObject(&LinePen);

		int stepper; // Schrittweite y-Achse für Plot
		if (maxrdiff < 30)
			stepper = 5;
		else
			stepper = 10;

		n_temphund = maxrdiff/stepper;
		if (maxrdiff == 0)
			stepdistance = 5*axesth.cy/2/5;
		else
			stepdistance = stepper*axesth.cy/2/maxrdiff;

		// Beschriftung der y-Achse
		for (n = 1; n < n_temphund+1; n++ )
		{
			int newstep = stepdistance*n;
			pDC->MoveTo(zeropointp3.x,zeropointp3.y-(stepdistance*n));
			pDC->LineTo(zeropointp3.x+3*p_r,zeropointp3.y-(stepdistance*n));
			itoa (n*stepper, step, 10);
			pDC->TextOut (zeropointp3.x-0.06*axesth.cx,zeropointp3.y-newstep+0.03*axesth.cy/2,step);
		}
		pDC->SetTextAlign(TA_LEFT);
		pDC->TextOut(uppointp3.x+5*p_r,uppointp3.y+5*p_r,"delta TR [%]"); // (positiv for decrease of intensity)
		pDC->SetTextAlign(TA_BASELINE | TA_CENTER);

		// Beschriftung der x-Achse
		n_temphund = maxTH/100;
		stepdistance = 100*axesth.cx/maxTH;

		for (n = 1; n < n_temphund+1; n++ )
		{
			int newstep = stepdistance*n;
			pDC->MoveTo(zeropointp3.x+(stepdistance*n),zeropointp3.y-3*p_r);
			pDC->LineTo(zeropointp3.x+(stepdistance*n),zeropointp3.y+3*p_r);
			pDC->MoveTo(downpointp3.x+newstep,downpointp3.y);
			pDC->LineTo(downpointp3.x+newstep,downpointp3.y-3*p_r);
			pDC->MoveTo(uppointp3.x+newstep,uppointp3.y);
			pDC->LineTo(uppointp3.x+newstep,uppointp3.y+3*p_r);
			itoa (n*100, step, 10);
			pDC->TextOut (downpointp3.x+newstep,downpointp3.y+0.1*axesth.cy,step);
		}
		pDC->TextOut(downpointp3.x+axesth.cx*0.5,downpointp3.y+axesth.cy*0.2,"Temp. [°C]");
		
	// *********************************************
	// Differnce of TH and TR - Plot: Z and H comp *
	// *********************************************


		CPoint zeropointth (position1-axesall.cx/2, position2+axesall.cy*(0.55/2));
		//rechter Rand
		CPoint rigthpointth (position1-0.05*axesall.cx, position2+axesall.cy*(0.55/2));
		// oberer Rand
		CPoint uppointth (position1-axesall.cx/2, position2+0.05*axesall.cy);
		// unterer Rand
		CPoint downpoint (position1-axesall.cx/2, position2+axesall.cy/2);
		// oberer rechter Rand
		CPoint uprightpoint (position1-0.05*axesall.cx, position2+0.05*axesall.cy);
		// unterer rechter Rand
		CPoint downrightpoint (position1-0.05*axesall.cx, position2+axesall.cy/2);

		pDC->MoveTo(rigthpointth);
		pDC->LineTo(zeropointth);
		pDC->LineTo(uppointth);
		pDC->LineTo(downpoint);
		pDC->LineTo(downrightpoint);
		pDC->LineTo(uprightpoint);
		pDC->LineTo(uppointth);

		fivepercentsteps = ceil(pDoc->minmax.maxzdiffTR/5);
		int maxdiff = fivepercentsteps*5;

		for (i = 0; i < thirdlist->GetSize(); i++)
		{
			CThellierResStruct* daten = ( CThellierResStruct* )thirdlist->GetAt(i);
			tempTR = daten->m_temp;
			zTRdiff = daten->m_z;
			hTRdiff = daten->m_y;
			if (maxdiff != 0)
			{
				CRect rectanglesize_diffmag((zeropointth.x+2*p_r)+(tempTR*axesth.cx/maxTH),(zeropointth.y),(zeropointth.x-2)+(tempTR*axesth.cx/maxTH),(zeropointth.y-zTRdiff*axesth.cy/2/maxdiff));
				//CRect rectanglesize_angdiff((zeropointth.x-4*p_r)+(tempTR*axesth.cx/maxTH),(zeropointth.y),(zeropointth.x)+(tempTR*axesth.cx/maxTH),(zeropointth.y-hTRdiff*axesth.cy/2/maxdiff));
				qOriginalBrush = pDC->SelectObject(&NormalBrush);
				pDC->Rectangle (&rectanglesize_diffmag);
				qOriginalBrush = pDC->SelectObject(&AngDiffBrush);
				//pDC->Rectangle (&rectanglesize_angdiff);
			}
		}

		// Achsenbeschriftung (Initialisierungen)
		qOriginalBrush = pDC->SelectObject(&NormalBrush);
		pOriginalPen = pDC->SelectObject(&LinePen);

		n_temphund = maxdiff/5;
		if (maxdiff == 0)
			stepdistance = 5*axesth.cy/2/5;
		else
			stepdistance = 5*axesth.cy/2/maxdiff;

		// Beschriftung der y-Achse
		for (n = 1; n < n_temphund+1; n++ )
		{
			int newstep = stepdistance*n;
			pDC->MoveTo(zeropointth.x,zeropointth.y-(stepdistance*n));
			pDC->LineTo(zeropointth.x+3*p_r,zeropointth.y-(stepdistance*n));
			itoa (n*5, step, 10);
			pDC->TextOut (zeropointth.x-0.06*axesth.cx,zeropointth.y-newstep+0.03*axesth.cy/2,step);
		}
		pDC->SetTextAlign(TA_LEFT);
		pDC->TextOut(uppointth.x+5*p_r,uppointth.y+5*p_r,"delta t* [%]"); 
		pDC->SetTextAlign(TA_BASELINE | TA_CENTER);

		// Beschriftung der x-Achse
		n_temphund = maxTH/100;
		stepdistance = 100*axesth.cx/maxTH;

		for (n = 1; n < n_temphund+1; n++ )
		{
			int newstep = stepdistance*n;
			pDC->MoveTo(zeropointth.x+(stepdistance*n),zeropointth.y-3*p_r);
			pDC->LineTo(zeropointth.x+(stepdistance*n),zeropointth.y+3*p_r);
			pDC->MoveTo(downpoint.x+newstep,downpoint.y);
			pDC->LineTo(downpoint.x+newstep,downpoint.y-3*p_r);
			pDC->MoveTo(uppointth.x+newstep,uppointth.y);
			pDC->LineTo(uppointth.x+newstep,uppointth.y+3*p_r);
			itoa (n*100, step, 10);
			pDC->TextOut (downpoint.x+newstep,downpoint.y+0.1*axesth.cy,step);
		}
		pDC->TextOut(downpoint.x+axesth.cx*0.5,downpoint.y+axesth.cy*0.2,"Temp. [°C]");
	};

}

void CThellierToolView::AllPlots(CDC *pDC, int scfa)
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Initialisierung von kleineren Schriften 
	CFont textfont, *oldfont;
	LOGFONT logfont ={50,0,0,0,0,0,0,0,0,0,0,0,0,"arial"};
	logfont.lfHeight = 50;
	textfont.CreatePointFontIndirect (&logfont, pDC);
	oldfont = pDC->SelectObject(&textfont);

	if (pDoc->vopt.m_arai_norm == 0)
		ThellierPlot (pDC, 300, 200, 1, scfa, &pDoc->THDataList, &pDoc->PTDataList, &pDoc->CKDataList, &pDoc->ACResList);
	else
		ThellierPlot (pDC, 200, 200, 1, scfa, &pDoc->THDataList, &pDoc->PTDataList, &pDoc->CKDataList, &pDoc->ACResList);
	ZijPlot (pDC, 250, 250, 1, scfa, &pDoc->THDataList, &pDoc->TRDataList);
	DecayPlot (pDC, 300, 200, 1, scfa, &pDoc->THDataList, &pDoc->TRDataList);
	if (pDoc->vopt.ckcorr)
		MDPlot (pDC, 300, 200, 1, scfa, &pDoc->PTDataList, &pDoc->ACResList, &pDoc->TRResList);
	else
		MDPlot (pDC, 300, 200, 1, scfa, &pDoc->PTDataList, &pDoc->CkErrorList, &pDoc->TRResList);
}

void CThellierToolView::OnEditCopy() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	CMetaFileDC * m_pMetaDC = new CMetaFileDC();
	m_pMetaDC->CreateEnhanced(GetDC(),NULL,NULL,"ThellierPlot\0Copy\0\0");
//	m_pMetaDC->SetMapMode(MM_TEXT);
	OnDraw(m_pMetaDC);

	HENHMETAFILE hMF = m_pMetaDC->CloseEnhanced();

	//copy to clipboard
	OpenClipboard();
	EmptyClipboard();
	::SetClipboardData(CF_ENHMETAFILE,hMF);
	CloseClipboard();
	//DeleteMetaFile(hMF);
	delete m_pMetaDC;

	
}

void CThellierToolView::OnFileSavegraph() 
{
	CThellierToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	char strFilter[] = { "Enhanced Metafile (*.emf)|*.emf||" };
	CFileDialog SaveDlg(FALSE, ".emf",NULL,OFN_OVERWRITEPROMPT,strFilter);

	if (SaveDlg.DoModal() == IDOK)
	{
		CString savefilepath = SaveDlg.GetPathName();

		CMetaFileDC * m_pMetaDC = new CMetaFileDC();
		m_pMetaDC->CreateEnhanced(GetDC(),savefilepath,NULL,"ThellierPlot");
		m_pMetaDC->SetMapMode(MM_TEXT);
		OnDraw(m_pMetaDC);

		HENHMETAFILE hEMF = m_pMetaDC->CloseEnhanced();

		DeleteEnhMetaFile(hEMF);
		delete m_pMetaDC;

	}	
	
}
