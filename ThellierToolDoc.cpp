// ThellierToolDoc.cpp : Implementierung der Klasse CThellierToolDoc
//

#include "stdafx.h"
#include "ThellierTool.h"

#include "ThellierToolDoc.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Für Matrix Rechnungen der PCA Analyse
double CThellierToolDoc::pi = 3.1415926535897932384626433832795;
#define NP 10
#define NR_END 1
#define FREE_ARG char*
#define NRANSI
#include "stdlib.h"
#define ROTATE(a,i,j,k,l) g=a[i][j];h=a[k][l];a[i][j]=g-s*(h+g*tau);a[k][l]=h+s*(g-h*tau);


/////////////////////////////////////////////////////////////////////////////
// CThellierToolDoc

IMPLEMENT_DYNCREATE(CThellierToolDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CThellierToolDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CThellierToolDoc)
	ON_COMMAND(ID_CRITERIA, OnCriteria)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CThellierToolDoc, COleServerDoc)
	//{{AFX_DISPATCH_MAP(CThellierToolDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//      Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Hinweis: Wir stellen Unterstützung für IID_IThellierTool zur Verfügung, um typsicheres Binden 
//  von VBA zu unterstützen. Diese IID muss mit der GUID übereinstimmen, die bei der 
//  Disp-Schnittstelle in der .ODL-Datei angegeben ist.

// {82CA9F09-0760-4A60-B6F9-228F5277EBF9}
static const IID IID_IThellierTool =
{ 0x82ca9f09, 0x760, 0x4a60, { 0xb6, 0xf9, 0x22, 0x8f, 0x52, 0x77, 0xeb, 0xf9 } };

BEGIN_INTERFACE_MAP(CThellierToolDoc, COleServerDoc)
	INTERFACE_PART(CThellierToolDoc, IID_IThellierTool, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThellierToolDoc Konstruktion/Destruktion

CThellierToolDoc::CThellierToolDoc()
{
	// Verwenden Sie OLE-Compound-Dateien
	EnableCompoundFile();

	// Initialisierung der Views
	vopt.coordinates = 0;
	vopt.mainview = 0;
	vopt.automatic = 0;
	vopt.accheck = TRUE;
	vopt.ckcorr = FALSE;
	vopt.zonly = FALSE;
	vopt.use_autock = FALSE;
	vopt.pathdata.Empty();
	vopt.m_arai_norm = 0;

	// Initialiesierung der Feldaten
	fielddata.labfield = 35.0f;
	fielddata.bearing = 0.0f;
	fielddata.dip = 0.0f;
	fielddata.plunge = 0.0f;
	fielddata.strike = 0.0f;
	
	// Initialisierung der Ergebinsse
	results.m_numberofpoints = 0;
	results.m_slope = 0.0;
	results.m_stdslope = 0.0;
	results.m_trm = 0.0;
	results.m_nrmt = 0.0;
	results.m_f = 0.0;
	results.m_g = 0.0;
	results.m_q = 0.0;
	results.m_w = 0.0;
	results.m_paleoint = 0.0;
	results.m_stddev = 0.0;
	results.m_mintemp = 0;
	results.m_maxtemp = 0;
	results.m_inc = 0.0;
	results.m_dec = 0.0;
	results.m_mad = 0.0;
	results.m_inc_na = 0.0;
	results.m_dec_na = 0.0;
	results.m_mad_na = 0.0;
	results.m_alpha = 0.0;
	results.m_ckerror = 0.0;
	results.m_ckdiff = 0.0;
	results.m_ACerror = 0.0;
	results.m_rTRerror = 0.0;
	results.m_tstar = 0.0;
	results.m_drat = 0.0;
	results.m_length_of_fit = 1.0;

	//Initialiesierung der Kriterien (leon, 20.12.03)
	CCriteriaDlg m_CriDlg (this);
	m_CriDlg.UpdateCriteria();


	EnableAutomation();

	AfxOleLockApp();
}

CThellierToolDoc::~CThellierToolDoc()
{
	AfxOleUnlockApp();
}

BOOL CThellierToolDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	//return TRUE;
	return FALSE; // leon (12/03): Kein Fenster beim start öffnen
}

/////////////////////////////////////////////////////////////////////////////
// CThellierToolDoc Server-Implementierung

COleServerItem* CThellierToolDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem wird automatisch aufgerufen, um COleServerItem zu erhalten,
	//  das mit dem Dokument verknüpft ist. Die Funktion wird nur bei Bedarf aufgerufen.

	CThellierToolSrvrItem* pItem = new CThellierToolSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}



/////////////////////////////////////////////////////////////////////////////
// CThellierToolDoc Serialisierung

void CThellierToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Hier Code zum Speichern einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Hier Code zum Laden einfügen
	}
}

/////////////////////////////////////////////////////////////////////////////
// CThellierToolDoc Diagnose

#ifdef _DEBUG
void CThellierToolDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CThellierToolDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThellierToolDoc Befehle

// CThellierDataList Konstruktion und Destruktion
CThellierDataList::CThellierDataList()
{

}

CThellierDataList::~CThellierDataList()
{

}

// CThellierResList Konstruktion und Destruktion
CThellierResList::CThellierResList()
{

}

CThellierResList::~CThellierResList()
{

}

BOOL CThellierToolDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	// Definition des Datenpfades
	CString Thellierdata;
	CString pathdata;
	CString samplename;
	CString line;
	
	pathdata = lpszPathName;
	vopt.pathdata = pathdata; // Übergabe an View Options Klasse
	int laenge = pathdata.GetLength();

	Thellierdata = pathdata;

	CStdioFile ThellierFile;

	// Generierung der Listen zum Daten auslesen
	CStringList ThellierList;
	ThellierList.RemoveAll();
	samplename.Empty();

	// Einlesen der Palmag Daten
	if (!ThellierFile.Open(Thellierdata, CFile::modeRead | CFile::typeText))
	{
	}
	else
	{
		if (samplename.IsEmpty())
		{
			samplename = ThellierFile.GetFileTitle();
			samplename.Replace(".tdt","");
		}
		while(ThellierFile.ReadString(line) != NULL)
		{
			ThellierList.AddTail(line);
		}
		FileExtract(&ThellierList);
	}

	return TRUE;
}

void CThellierToolDoc::FileExtract(CStringList *datalist)
{
	CString Header1;
	CString Header2;
	CString LineAfterHeader;
	CString DataLine;
	CString name;
	CString true_name;
	float step, mag, dec, inc, labfield, bearing, plunge, strike, dip;

	POSITION pos = datalist->GetHeadPosition();
	Header1 = datalist->GetNext( pos );
	if (Header1.Left(12) == "Thellier-tdt")
	{
		Header2 = datalist->GetNext( pos );
		sscanf ( Header2, "%e%e%e%e%e", &labfield, &bearing, &plunge, &strike, &dip);
		fielddata.labfield = labfield;
		fielddata.bearing = bearing;
		fielddata.plunge = plunge;
		fielddata.dip = dip;
		fielddata.strike = strike;
		while( pos != NULL )
		{
			int n = 0;
			LineAfterHeader = datalist->GetNext( pos );
			n = LineAfterHeader.Find("	");
			if (n < 1 || n > 18)
				n = LineAfterHeader.Find(' ');
			name = LineAfterHeader.Left(n);
			DataLine = LineAfterHeader.Right(LineAfterHeader.GetLength()-n);
			if (name != "")
			{
				sscanf ( DataLine, "%e%e%e%e", &step, &mag, &dec, &inc);
				ThellierData.Add(new CThellierDataStruct (step, mag, inc, dec ));
				true_name = name;
			}
		}
	}
	else
	{
		int n = Header1.Find("	");
		if (n < 1 || n > 18)
			n = Header1.Find(' ');
		name = Header1.Left(n);
		DataLine = Header1.Right(Header1.GetLength()-n);
		sscanf ( DataLine, "%e%e%e%e", &step, &mag, &dec, &inc);
		ThellierData.Add(new CThellierDataStruct (step, mag, inc, dec));
		while( pos != NULL )
		{
			LineAfterHeader = datalist->GetNext( pos );
			n = LineAfterHeader.Find("	");
			if (n < 1 || n > 18)
			n = LineAfterHeader.Find(' ');
			name = LineAfterHeader.Left(n);
			DataLine = LineAfterHeader.Right(LineAfterHeader.GetLength()-n);
			if (name != "")
			{
				sscanf ( DataLine, "%e%e%e%e", &step, &mag, &dec, &inc);
				ThellierData.Add(new CThellierDataStruct (step, mag, inc, dec));
				true_name = name;
			}
		}
	}
	fielddata.name = true_name;
}

void CThellierToolDoc::CoorTrans(CThellierDataList *datalist)
{
	double x, y, z;
	double pis = pi/180;
	int maxtr = -1; // Für Typ

	float m_dip = fielddata.dip;
	float m_dirofdip = fielddata.strike;
	float m_bearing = fielddata.bearing;
	float m_plunge = fielddata.plunge;

	AllDataList.RemoveAll();

	// Kern, Geographische bzw, Bedding Korrektur
	for (int i = 0; i < datalist->GetSize(); i++)
	{
		CThellierDataStruct* daten = ( CThellierDataStruct* )datalist->GetAt(i);
		double H = daten->m_mag * cos(pis*daten->m_inc);
		double m_x = H * cos(pis*daten->m_dec);
		double m_y = H * sin(pis*daten->m_dec);
		double m_z = daten->m_mag * sin(pis*daten->m_inc);
		double xs = m_x*cos(pis*m_plunge)*cos(pis*m_bearing)-m_y*sin(pis*m_bearing)+m_z*sin(pis*m_plunge)*cos(pis*m_bearing);
		double ys = m_x*cos(pis*m_plunge)*sin(pis*m_bearing)+m_y*cos(pis*m_bearing)+m_z*sin(pis*m_plunge)*sin(pis*m_bearing);
		double zs = -m_x*sin(pis*m_plunge)+m_z*cos(pis*m_plunge);
		switch (vopt.coordinates)
		{
		case 0:		   // Kerkoordinaten
			x = m_x;
			y = m_y;
			z = m_z;
			break;
		case 1:		   // Geographische Korrektur
			x = xs;
			y = ys;
			z = zs;
			break;
		case 2:        // Bedding Korrektur
			//zs = zs;
			//double tmp_ys = xs;
			//xs = ys;
			//ys = tmp_ys;
			double cosDec = cos(pis*m_dirofdip);
			double cosInc = cos(pis*m_dip);
			double sinDec = sin(pis*m_dirofdip);
			double sinInc = sin(pis*m_dip);
			x = (cosDec * cosDec * cosInc + sinDec * sinDec) * xs +(cosDec * cosInc * sinDec - sinDec * cosDec) * ys +(cosDec * sinInc) * zs;
			y = (sinDec * cosInc * cosDec - sinDec * cosDec) * xs +(sinDec * sinDec * cosInc + cosDec * cosDec) * ys +(sinInc * sinDec) * zs;
			z = (-sinInc * cosDec) * xs +(-sinInc * sinDec) * ys + cosInc * zs;

		};
	int temp = floor(daten->m_step);
	double tr1 = fmod((daten->m_step)*1000,temp*1000);
	int tr;
	if (tr1 < 410) // für Tauxe Konvention (leon 22.12.03)
		tr = 4;
	if (tr1 < 310)
		tr = 3;
	if (tr1 < 210)
		tr = 2;

	if (tr1 < 141)
		tr = 4;
	if (tr1 < 131)
		tr = 3;
	if (tr1 < 121)
		tr = 2;
	if (tr1 < 111)
		tr = 1;
	if (tr1 < 99)
		tr = 0;
	if (maxtr < tr) // Für Messtyp MT3 (MD tail checks) und MT4 (AC)
		maxtr = tr;

	AllDataList.Add(new CThellierResStruct (tr, temp, temp, x, y, z, sqrt(x*x+y*y+z*z)));
	};

	// Bestimmung des Typs MT0 (keine checks), MT1 (standard) und MT2 (pTRM first)
	if (maxtr < 2)
		maxtr = 0;
	if (maxtr == 2)
	{
		CThellierDataStruct* data1 = ( CThellierDataStruct* )datalist->GetAt(1);
		CThellierDataStruct* data2 = ( CThellierDataStruct* )datalist->GetAt(2);
		if (data1->m_step - data2->m_step > 0)
			maxtr = 2;
		else
			maxtr = 1;
	}
	results.m_type.Format("MT%d",maxtr);

}

void CThellierToolDoc::VectorSub(CThellierResList *datalist)
{
	int tr1,temp1,tr2,temp2,temp1prev, tr3;
	double x1,y1,z1,x2,y2,z2;
	double diffmag;
	int measurementorder;
	// measurementorder = 1; in-field check after demag
	// measurementorder = 2; in-field check after TR
	// measurementorder = 3; zero-field check after pTRM acquisition

	temp1prev = -1000;

	THDataList.RemoveAll();
	PTDataList.RemoveAll();
	CKDataList.RemoveAll();
	TRDataList.RemoveAll();
	ACDataList.RemoveAll();

	for (int i = 0; i < datalist->GetSize(); i++)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist->GetAt(i);
		if (i > 0)
		{
			CThellierResStruct* daten3 = ( CThellierResStruct* )datalist->GetAt(i-1);
			tr3 = daten3->m_tr; // treatment before
		}
		tr1 = daten1->m_tr; // actual treatment
		temp1 = daten1->m_temp;
		x1 = daten1->m_x;
		y1 = daten1->m_y;
		z1 = daten1->m_z;
		// Reihenfolge der Messschritte
		if (tr1 == 2 && tr3 == 0)
		{
			measurementorder = 1;
			fielddata.checktype = "in-field alteration check";
		}
		if (tr1 == 2 && tr3 == 3)
		{
			measurementorder = 2;
			fielddata.checktype = "in-field alteration check after TR step";
		}
		if (tr1 == 2 && tr3 == 1)
		{
			measurementorder = 3;
			fielddata.checktype = "zero-field alteration check";
		}
		if (tr1 == 2 && tr3 == 2)
		{
			measurementorder = 4;
		}
		if (tr1 == 2 && tr3 == 4)
		{
			measurementorder = 5;
		}
		if (i == 0) // Startwert für PT Liste
			PTDataList.Add(new CThellierResStruct (1, temp1, temp1, 0.0, 0.0, 0.0, 0.0));
		if (tr1 == 0)
			THDataList.Add(new CThellierResStruct (tr1, temp1, temp1, daten1->m_x, daten1->m_y, daten1->m_z, sqrt(x1*x1+y1*y1+z1*z1)));
		else
		if (tr1 == 3)
			TRDataList.Add(new CThellierResStruct (tr1, temp1, temp1, daten1->m_x, daten1->m_y, daten1->m_z, sqrt(x1*x1+y1*y1+z1*z1)));
		else
		{
			for (int j = 0; j < datalist->GetSize(); j++)
			{
				CThellierResStruct* daten2 = ( CThellierResStruct* )datalist->GetAt(j);
				tr2 = daten2->m_tr; 
				temp2 = daten2->m_temp;
				x2 = daten2->m_x;
				y2 = daten2->m_y;
				z2 = daten2->m_z;
				if (!vopt.zonly)
					diffmag = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
				else
					diffmag = sqrt((z1-z2)*(z1-z2));
				if (tr1 == 1 && tr2 == 0 && temp1 == temp2)
					PTDataList.Add(new CThellierResStruct (tr1, temp2, temp2, x1-x2, y1-y2, z1-z2, diffmag));
				if (measurementorder == 1)
					if (tr1 == 2 && tr2 == 0 && temp1prev == temp2)
						CKDataList.Add(new CThellierResStruct (tr1, temp2, temp1, x1-x2, y1-y2, z1-z2, diffmag));
				if (measurementorder == 2)
					if (tr1 == 2 && tr2 == 3 && temp1prev == temp2)
						CKDataList.Add(new CThellierResStruct (tr1, temp2, temp1, x1-x2, y1-y2, z1-z2, diffmag));
				if (measurementorder == 3)
					if (tr1 == 2 && tr2 == 1 && temp1prev == temp2)
						CKDataList.Add(new CThellierResStruct (tr1, temp2, temp1, -(x1-x2), -(y1-y2), -(z1-z2), diffmag));
				if (measurementorder == 4 || measurementorder == 5)
					if (tr1 == 2 && tr2 == 0 && temp1prev == temp2)
						CKDataList.Add(new CThellierResStruct (tr1, temp2, temp1, x1-x2, y1-y2, z1-z2, diffmag));
//				Neuer Ansatz (wie im Modell) von Leon (23.09.03)
				if (tr1 == 4 && tr2 == 1 && temp1prev == temp2)
					ACDataList.Add(new CThellierResStruct (tr1, temp2, temp1, x2-x1, y2-y1, z2-z1, diffmag)); //sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1)))); // Immer voller Vektor
//				Alter Ansatz von David
//				if (tr1 == 4 && tr2 == 0 && temp1prev == temp2)
//					ACDataList.Add(new CThellierResStruct (tr1, temp2, temp1, x1-x2, y1-y2, z1-z2, sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))));
			}
		}
		if (tr1 == 0 || tr1 == 1) // Letzte Temperatur eines demag oder pTRM Schritts speichern: wichtig für Checks (in-field und zero-field)
			temp1prev = daten1->m_temp;
	}

	MaxMinValues(&THDataList, &PTDataList, &CKDataList);
}

void CThellierToolDoc::MaxMinValues(CThellierResList *datalist1,CThellierResList *datalist2,CThellierResList *datalist3)
{
	double minmagTH = 1000000.0;
	double maxmagTH = -1000000.0;
	int minstep = 1000000;
	int maxstep = -1000000;
	double minx = 1000000.0;
	double maxx = -1000000.0;
	double miny = 1000000.0;
	double maxy = -1000000.0;
	double minz = 1000000.0;
	double maxz = -1000000.0;
	double minh = 1000000.0;
	double maxh = -1000000.0;

	double maxmagPT = -1000000.0f;
	double maxmagTR = -1000000.0f;

	double m_h;
	int i;

	// TH Daten
	for (i = 0; i < datalist1->GetSize(); i++)
	{
		CThellierResStruct* daten = ( CThellierResStruct* )datalist1->GetAt(i);
		if (maxstep < daten->m_temp)
			maxstep = daten->m_temp;
		if (minstep > daten->m_temp)
			minstep = daten->m_temp;
		if (maxmagTH < daten->m_mag)
			maxmagTH = daten->m_mag;
		if (minmagTH > daten->m_mag)
			minmagTH = daten->m_mag;
		if (minx > daten->m_x)
			minx = daten->m_x;
		if (maxx < daten->m_x)
			maxx = daten->m_x;
		if (maxy < daten->m_y)
			maxy = daten->m_y;
		if (miny > daten->m_y)
			miny = daten->m_y;
		if (maxz < daten->m_z)
			maxz = daten->m_z;
		if (minz > daten->m_z)
			minz = daten->m_z;
		m_h = daten->m_x/fabs(daten->m_x)*sqrt(pow(daten->m_x,2) + pow(daten->m_y,2));
		if (maxh < m_h)
			maxh = m_h;
		if (minh > m_h)
			minh = m_h;
	}
	// pTRM Daten
	for (i = 0; i < datalist2->GetSize(); i++)
	{
		CThellierResStruct* daten = ( CThellierResStruct* )datalist2->GetAt(i);
		if (maxmagPT < daten->m_mag)
			maxmagPT = daten->m_mag;
	}

	// Übergabe an Klasse MinMax
	minmax.maxstep = maxstep;
	minmax.maxmagTH = maxmagTH;
	minmax.minstep = minstep;
	minmax.minmagTH = minmagTH;
	minmax.maxx = maxx;
	minmax.minx = minx;
	minmax.maxy = maxy;
	minmax.miny = miny;
	minmax.maxz = maxz;
	minmax.minz = minz;
	minmax.maxh = maxh;
	minmax.minh = minh;
	minmax.maxmagPT = maxmagPT;

}

void CThellierToolDoc::TRCheckAnalysis(CThellierResList *datalist1, CThellierResList *datalist2, CThellierResList *datalist3)
{

	// Differenzen zwischen ersten und wiederholtem Abmagnetisierschritt
	// normiert auf maximale NRM Messung
	// renormierung auf NRMt in Funktion NormTRRes();

	double Rdiff;  //absolute Differenz der Intensität
	double Hdiff;  //absolute Differenz der H-Komponente
	double Zdiff;  //absolute Differenz der Z-Komponente
	double inc_diff;
	double dHtan;

//	double pi = 3.141592654;
	int maxTH = minmax.maxstep;

	int tempTH, tempPT, tempTR;
	double xTH,yTH,zTH,xPT,yPT,zPT,xTR,yTR,zTR;
	double magTH,magPT,magTR;

	double maxhdiff = 0.0;
	double maxzdiff = 0.0;
	double maxrdiff = 0.0;
	double maxzhdiff = 0.0;
	double maxrzhdiff = 0.0;

	double inc_th, dec_th, dec_pt;
	double inc_tr, dec_tr;
	double inc_th_tr;

	int i,k;
	int j = 1;

	// Richtungsabhängige Rechnung des Tails
	double dZ, dH;

	// Initalisierung der ErgebnisListe
	TRResList.RemoveAll(); 

	for (i = 0; i < datalist1->GetSize(); i++)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist1->GetAt(i);
		tempTH = daten1->m_temp;
		xTH = daten1->m_x;
		yTH = daten1->m_y;
		zTH = daten1->m_z;
		magTH = daten1->m_mag;
		for (j = 0; j < datalist2->GetSize(); j++)
		{
			CThellierResStruct* daten2 = ( CThellierResStruct* )datalist2->GetAt(j);
			tempTR = daten2->m_temp;
			xTR = daten2->m_x;
			yTR = daten2->m_y;
			zTR = daten2->m_z;
			magTR = daten2->m_mag;
			// Bestimmung der Inclination des TR steps
			XYZtoDecInc(&dec_tr, &inc_tr, xTR, yTR, zTR);
/*			if (xTR == 0 && yTR == 0)
			{
				if (zTR > 0)
					inc_tr = pi/2;
				else
					inc_tr = -pi/2;
				if (zTR == 0)
					inc_tr = 0;
			}
			else
				inc_tr = atan(zTR/(sqrt(xTR*xTR + yTR*yTR)));
*/
			if (tempTH == tempTR)
			{
				double inc_labfield = 0.0;
				double pTRMInt = 0.0;

				// (1) Bestimmung der R-Komponente (Gesamtintensität)
				Rdiff = (magTH - magTR) * 100.0/minmax.maxmagTH; // Vorzeichenabhängige Differenz (neu in Vers. 1.8)

				// NEU !!!!!!!!!!! (26.03.03)
				// (2) Bestimmung der H-differenz (absolut Wert, nicht normiert)
				dH = (sqrt(xTH*xTH + yTH*yTH) - sqrt(xTR*xTR + yTR*yTR));
				// (3) Bestimmung der Z-differenz (immer negativ für Tail, auf positiv umgerechnet, nicht normiert)
				dZ = zTH - zTR;
				// (4) Bestimmung der Richtung des TH-steps
				XYZtoDecInc(&dec_th, &inc_th, xTH, yTH, zTH);
/*				if (xTH == 0 && yTH == 0)
				{
					if (zTH > 0)
						inc_th = pi/2;
					else
						inc_th = -pi/2;
					if (zTH == 0)
						inc_th = 0;
				}
				else
					inc_th = atan(zTH/(sqrt(xTH*xTH + yTH*yTH)));
*/				// (4a) Inclinationsdifference zwischen TH und TR
//				inc_th_tr = (inc_th - inc_tr)*180/pi;
				inc_th_tr = (inc_th - inc_tr);

				// (5) Bestimmung der Richtung des anglegten Feldes
				for (k = 0; k < datalist3->GetSize(); k++)
				{
					CThellierResStruct* daten3 = ( CThellierResStruct* )datalist3->GetAt(k);
					tempPT = daten3->m_temp;
					xPT = daten3->m_x;
					yPT = daten3->m_y;
					zPT = daten3->m_z;
					magPT = daten3->m_mag;
					if (tempTH == tempPT)
					{
/*						if (xPT == 0 && yPT == 0)
						{
							if (zPT > 0)
								inc_labfield = pi/2;
							else
								inc_labfield = -pi/2;
							if (zPT == 0)
								inc_labfield = 0;
						}
						else
							inc_labfield = atan(zPT/(sqrt(xPT*xPT + yPT*yPT)));
*/
						XYZtoDecInc(&dec_pt, &inc_labfield, xPT, yPT, zPT);

						if (inc_labfield > 0)
							inc_labfield = 90;
						else
							inc_labfield = -90;
						inc_diff = fabs((inc_labfield - inc_th)*pi/180);
						pTRMInt = magPT;

						// (7) Bestimmung des Tails mithlife von dH und dZ (normiert)
						if (floor(inc_diff*1000.0) != 0 && floor(inc_diff*1000) != 3141 && floor(inc_diff*1000) != 1570)  // Kritischen Winkel einführen
							dHtan = dH/tan(inc_diff);

						// Ausnahmen:
						// incdiff = 90 oder -90
						if (floor(inc_diff*1000) == 1570)
							dHtan = 0;
						// if (fabs(floor(inc_diff*1000)) != 3141 && floor(inc_diff*1000) != 0) // Version 4.0
						if (floor(inc_diff*1000) < 2968 && floor(inc_diff*1000) > 175) // Version 4.1
						{
							if (inc_labfield - inc_th > 0)
								Zdiff = (-dZ + dHtan) * minmax.maxmagTH/minmax.maxmagPT * 100.0/minmax.maxmagTH; // Vorzeichenabhängige Differenz (neu in Vers. 1.8)
							else
								Zdiff = (dZ - dHtan) * minmax.maxmagTH/minmax.maxmagPT * 100.0/minmax.maxmagTH; // Vorzeichenabhängige Differenz (neu in Vers. 1.8)
						}
						else
						{
							if (floor(inc_diff*1000) < 176)
								Zdiff = 0;
							//if (fabs(floor(inc_diff*1000)) == 3141) // Version 4.0
							if (floor(inc_diff*1000) > 2967) // Version 4.1
								Zdiff = -minmax.maxmagTH/(minmax.maxmagTH+minmax.maxmagPT)*dZ * 100.0/minmax.maxmagTH;
						}
					}

				//Test (nur H und Z Komponente ausgeben)
//				Hdiff = dH * 100.0/minmax.maxmagTH;
//				Zdiff = dZ * 100.0/minmax.maxmagTH;
				//Test (Nichtnormiert)
//				Hdiff = dH/sin(inc_diff);
				Hdiff = inc_th_tr;
//				Zdiff = Zdiff * fielddata.labfield;

				}

				TRResList.Add(new CThellierResStruct (0, tempTR, tempTR, (inc_diff)*180/pi, Hdiff, Zdiff, Rdiff));

				// Maximale Z-differenz
				//if (sqrt(Zdiff*Zdiff) > maxzdiff)
				if (Zdiff > maxzdiff)
					maxzdiff = Zdiff;
				// Maximale H-differenz
				if (sqrt(Hdiff*Hdiff) > maxhdiff)
					maxhdiff = sqrt(Hdiff*Hdiff);
				// Maximale Intensitätsdifferenz
				if (sqrt(Rdiff*Rdiff) > maxrdiff)
					maxrdiff = sqrt(Rdiff*Rdiff);


			}
		}
	}

	if (maxhdiff > maxzdiff)
		maxzhdiff = ceil(maxhdiff);
	else
		maxzhdiff = ceil(maxzdiff);
	if (maxzhdiff > maxrdiff)
		maxrzhdiff = ceil(maxzhdiff);
	else
		maxrzhdiff = ceil(maxrdiff);

	// Übergabe an MinMax Struktur
	minmax.maxhdiffTR = maxhdiff;
	minmax.maxzdiffTR = maxzdiff;
	minmax.maxrdiffTR = maxrdiff;
	minmax.maxzhdiffTR = maxzhdiff;
	minmax.maxrzhdiffTR = maxrzhdiff;
}

void CThellierToolDoc::ACCheckAnalysis(CThellierResList *datalist1, CThellierResList *datalist2, CThellierResList *datalist3)
{
// ********************************************************************
// ******** AC checks  
// ********************************************************************

	double magAC, magPT, magPT_AC, magPT_AC2;
	int tempAC, tempACstart, tempPT;
	double diffmag_AC_PT;
	double maxdiffAC = 0.0;
	double x1,y1,z1,x2,y2,z2;
	double xdiff, ydiff, zdiff, newxAC, newyAC, newzAC;
	double xsum_prev, ysum_prev, zsum_prev;


	ACResList.RemoveAll(); 

	for (int i = 0; i < datalist1->GetSize(); i++)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist1->GetAt(i);
		tempACstart = daten1->m_temp;
		tempAC = daten1->m_sptemp;
		magAC = daten1->m_mag;
		// neu (Modell, 23.09.03)
		x1 = (daten1->m_x);
		y1 = (daten1->m_y);
		z1 = (daten1->m_z);
		int tempCK,tempCKstart;
		double C, newmagAC, ckdiff;
		// end neu
		for (int k = 0; k < datalist2->GetSize(); k++)
		{
			CThellierResStruct* daten2 = ( CThellierResStruct* )datalist2->GetAt(k);
			tempPT = daten2->m_temp;
			magPT = daten2->m_mag;
			// neu (Modell, 23.09.03)
			x2 = daten2->m_x;
			y2 = daten2->m_y;
			z2 = daten2->m_z;

			double xsum = 0.0;
			double ysum = 0.0;
			double zsum = 0.0;
			// end neu
			if (tempPT == tempAC)
			{
				if (vopt.ckcorr)
				{
					C = 0.0;
					int N = 1;
					for (int j = 0; j < datalist3->GetSize(); j++)
					{
						CThellierResStruct* daten3 = ( CThellierResStruct* )datalist3->GetAt(j);
						int signCKPT = daten3->m_tr;
						tempCK = daten3->m_sptemp;
						tempCKstart = daten3->m_temp;
						xdiff = daten3->m_x;
						ydiff = daten3->m_y;
						zdiff = daten3->m_z;
						ckdiff = daten3->m_mag;
						xsum += xdiff;
						ysum += ydiff;
						zsum += zdiff;

						if (tempCKstart == tempACstart && N == 1)
						{
							N++;
							newxAC = x1 - xsum;
							newyAC = y1 - ysum;
							newzAC = z1 - zsum;

							if (!vopt.zonly)
								newmagAC = sqrt(newxAC*newxAC + newyAC*newyAC + newzAC*newzAC);
							else
								newmagAC = sqrt(newzAC*newzAC);
							//newmagAC = magAC - C;
						}
						if (tempCKstart > tempACstart && N == 1) // falls kein Ck an AC position, dann vorigen Check verwenden.
						{
							N++;
							newxAC = x1 - xsum_prev;
							newyAC = y1 - ysum_prev;
							newzAC = z1 - zsum_prev;

							if (!vopt.zonly)
								newmagAC = sqrt(newxAC*newxAC + newyAC*newyAC + newzAC*newzAC);
							else
								newmagAC = sqrt(newzAC*newzAC);
							//newmagAC = magAC - C;
						}
						xsum_prev = xsum;
						ysum_prev = ysum;
						zsum_prev = zsum;
					}
					if (datalist3->GetSize() > 0)
						magAC = newmagAC;
				}
				magPT_AC2 = magPT;
				diffmag_AC_PT = magAC - magPT; // neu 23.09.03 // Fehler wird Skalar berechnet
				//diffmag_AC_PT = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));  // neu 4.01.04
			}
			if (tempPT == tempACstart)
				magPT_AC = magPT;
		}


		// neuer Code leon (23.09.03)
		if (fabs(diffmag_AC_PT) > maxdiffAC)
			maxdiffAC = fabs(diffmag_AC_PT);

		minmax.maxdiffAC = maxdiffAC;
		ACResList.Add(new CThellierResStruct (4, tempACstart, tempAC, magPT_AC, magPT_AC2, magAC, diffmag_AC_PT));

		if (vopt.ckcorr)
			int integ = 1;
	}
}

void CThellierToolDoc::CheckCorrection(CThellierResList *datalist1, CThellierResList *datalist2)
{

	PTCkCorrDataList.RemoveAll();
	PTCkCorrCompList.RemoveAll(); // Componentenliste - nicht verwendet
	CkErrorList.RemoveAll();
	CKRemainingDataList.RemoveAll();

	double C = 0.0;
	double newmagPT;
	double magPT, magCK, xPT, yPT, zPT, xCK, yCK, zCK;
	double xCORR, yCORR, zCORR; // Variablen für Veränderung der x,y,z-Werte; wird für CK-Corr von AC-checks benötigt und in PTCKCorrCompList gespeichert (16.12.03)
	double xC = 0.0;
	double yC = 0.0;
	double zC = 0.0;
	double ckdiff; 
	double max_ckdiff = 0.0;
	int tempPT, tempCK, tempCKstart;
	double x_C,y_C,z_C;
	// Richtung des angelegten Feldes
	double decPT, incPT, decCK, incCK, incPT_actual, decPT_actual; 
	decPT = 999.0;
	double alpha;
	int signCK = 1;
	int signCKPT;


	for (int i = 0; i < datalist1->GetSize(); i++)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist1->GetAt(i);
		tempPT = daten1->m_temp;
		magPT = daten1->m_mag;
		// X,Y,Z werden unverändert gelassen (für Richtung zwischen Feld und pTRM)
		xPT = daten1->m_x;
		yPT = daten1->m_y;
		zPT = daten1->m_z;

		// Richtung des aktuellen Laborfeldes
		if (decPT < 900)
		{
			XYZtoDecInc(&decPT_actual, &incPT_actual, xPT, yPT, zPT);
			alpha = fabs(AngleBetweenDirs(decPT, incPT, decPT_actual, incPT_actual));
			if (alpha < 90)
				signCK = 1;
			else
				signCK = -1;
		}

		// Scalar (old): newmagPT = magPT - C;
		// Vectorial (new): 4.01.04
		xCORR = xPT - signCK*xC;
		yCORR = yPT - signCK*yC;
		zCORR = zPT - signCK*zC;
		if (!vopt.zonly)
			newmagPT = sqrt(xCORR*xCORR + yCORR*yCORR + zCORR*zCORR);
		else
			newmagPT = sqrt(zCORR*zCORR);

//		newmagPT = magPT - C;
		int N = 0;

		for (int j = 0; j < datalist2->GetSize(); j++)
		{
			CThellierResStruct* daten2 = ( CThellierResStruct* )datalist2->GetAt(j);
			tempCKstart = daten2->m_temp;
			tempCK = daten2->m_sptemp;
			magCK = daten2->m_mag;
			xCK = daten2->m_x;
			yCK = daten2->m_y;
			zCK = daten2->m_z;

			if (tempPT == tempCK)
			{
				N++;
				if (N == 1) // Nur erstes auftreten der Temperatur verwenden
				{
					XYZtoDecInc(&decPT, &incPT, xPT, yPT, zPT);
					XYZtoDecInc(&decCK, &incCK, xCK, yCK, zCK);
					double alphaCKPT = fabs(AngleBetweenDirs(decPT, incPT, decCK, incCK));
					if (alphaCKPT < 90)
						signCKPT = 1;
					else
						signCKPT = -1;
					//Scalar: 
					C += (magCK - magPT);
					// Wichtig: Richtung des angelegten Feldes bestimmen
					//			falls im nächsten Schritt Feldrichtung verändert wird (z.B. entgegengesetzt) 
					//			muss das für die Korrektur berücksichtigt werden !! (Vorzeichen ändert sich)
					ckdiff = (magCK - magPT);
					//neu (16.12.03)
					xC += signCKPT*(xCK - xPT);
					yC += signCKPT*(yCK - yPT);
					zC += signCKPT*(zCK - zPT);
					x_C = signCKPT*(xCK - xPT);
					y_C = signCKPT*(yCK - yPT);
					z_C = signCKPT*(zCK - zPT);

					//ckdiff = sqrt(x_C*x_C + y_C*y_C +z_C*z_C);
					// end neu
					CkErrorList.Add(new CThellierResStruct (signCKPT, tempCKstart, tempCK, x_C, y_C, z_C, ckdiff));
					if (max_ckdiff < fabs(ckdiff))
						max_ckdiff = fabs(ckdiff);
				}
				else
				{
					double newmagCK;
					double xCKCORR = xCK - signCK*xC;
					double yCKCORR = yCK - signCK*yC;
					double zCKCORR = zCK - signCK*zC;
					if (!vopt.zonly)
						newmagCK = sqrt(xCKCORR*xCKCORR + yCKCORR*yCKCORR + zCKCORR*zCKCORR);
					else
						newmagCK = sqrt(zCKCORR*zCKCORR);
					CKRemainingDataList.Add(new CThellierResStruct (2, tempCKstart, tempCK, xCKCORR, yCKCORR, zCKCORR, newmagCK));
				}
			}

		}

		PTCkCorrDataList.Add(new CThellierResStruct (1, tempPT, tempPT, xPT, yPT, zPT, newmagPT));
		PTCkCorrCompList.Add(new CThellierResStruct (1, tempPT, tempPT, xCORR, yCORR, zCORR, newmagPT));
	}
	minmax.maxdiffCK = max_ckdiff;
}

void CThellierToolDoc::CKCorrToPTData(CThellierResList *datalist1, CThellierResList *datalist2)
{
	double new_magPT;
	double xPT, yPT, zPT;
	int new_tempPT;
	double magCK;
	double xCK, yCK, zCK;
	int tempCK, tempCKstart;

	PTDataList.RemoveAll();

	for (int i = 0; i < datalist1->GetSize(); i++)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist1->GetAt(i);
		new_tempPT = daten1->m_temp;
		new_magPT = daten1->m_mag;
		xPT = daten1->m_x;
		yPT = daten1->m_y;
		zPT = daten1->m_z;
		PTDataList.Add(new CThellierResStruct (1, new_tempPT, new_tempPT, xPT, yPT, zPT, new_magPT));
	}

	CKDataList.RemoveAll();

	for (i = 0; i < datalist2->GetSize(); i++)
	{
		CThellierResStruct* daten2 = ( CThellierResStruct* )datalist2->GetAt(i);
		tempCK = daten2->m_sptemp;
		tempCKstart = daten2->m_temp;
		magCK = daten2->m_mag;
		xCK = daten2->m_x;
		yCK = daten2->m_y;
		zCK = daten2->m_z;
		CKDataList.Add(new CThellierResStruct (2, tempCKstart, tempCK, xCK, yCK, zCK, magCK));
	}

	MaxMinValues(&THDataList, &PTDataList, &CKDataList);
}

void CThellierToolDoc::ThellierCalc(CThellierResList *datalist1, CThellierResList *datalist2, CThellierResList *datalist3, CThellierResList *datalist4, CThellierResList *datalist5, int selectclass)
{
// ********************************************************************
// ******** Berechnung
// ********************************************************************

	// Benötigt die Funktion "ThellierCkTrAcCalc"
	// für die Berechnung von CK, TR und AC Fehlern

	// Benötigt die Funktion "ThellierLinear"

	// Benötigt die Funktion "ThellierPCA"

	// Für maximalen Wichtungserfolg
	double wmax = 0.0; 
	double weightpar;

	// Für Berechnung der Difference zwischen CK-korr und nichtkorr. Wert
	double m_ckcorrpalint;
	m_ckcorrpalint = 0.0;

	// Für Bestimmung der Auswerteklasse ( Verwendung von Class A oder B Kriterien)
	int crit_points;
	if (selectclass == 0)
		crit_points = criteria.m_crit_A_n;
	else
		crit_points = criteria.m_crit_B_n;

	// Allgemein
	int tempTH1, tempTH2;

	// Variable zur temporären speicherung des Temperaturintervalls
	int tmp_temp_range_max;
	int tmp_temp_range_min;


	if (vopt.automatic == 0) // ******** Automatische Berechnung
	{
		for (int i = 0; i < datalist1->GetSize(); i++)
		{
			CThellierResStruct* daten1 = ( CThellierResStruct* )datalist1->GetAt(i);
			tempTH1 = daten1->m_temp;
			for (int j = crit_points-1; j < datalist1->GetSize(); j++)
			{
				CThellierResStruct* daten2 = ( CThellierResStruct* )datalist1->GetAt(j);
				tempTH2 = daten2->m_temp;
				if (tempTH1 < tempTH2 && j-i >= crit_points-1)
				{
					// Erster Durchlauf (Bestimmung der Paleoinentistäten für alle möglichen Temperaturintervalle)
					if (!vopt.ckcorr)
					{
						ThellierLinear(tempTH1, tempTH2, &THDataList, &PTCkCorrDataList);
						m_ckcorrpalint = results.m_paleoint;
					}
					ThellierLinear(tempTH1, tempTH2, &THDataList, &PTDataList);

					// Berechnung der (richtig) normierten CK, TR und AC Fehler
					ThellierCkTrAcCalc(datalist3, datalist4, datalist5, m_ckcorrpalint, tempTH2);

					// Auswahl des Wichtungskriteriums
					if (criteria.m_maximizingpar == 0)
						weightpar = results.m_w;
					else
						weightpar = results.m_q;

					// Überprüfung der Kritrien
					if (CriteriaCheck() <= selectclass) // Kriterien
					{
						if (wmax < sqrt(weightpar*weightpar))
						{
							wmax = sqrt(weightpar*weightpar);
							tmp_temp_range_min = results.m_mintemp;
							tmp_temp_range_max = results.m_maxtemp;
						}
					}
				}
			}
		}

		// Bestimmung der Paleoinentistät mit maximaler Wichtung

		if (wmax != 0)
		{

			if (!vopt.ckcorr)
			{
				ThellierLinear(tmp_temp_range_min, tmp_temp_range_max, &THDataList, &PTCkCorrDataList);
				m_ckcorrpalint = results.m_paleoint;
			}
			ThellierLinear(tmp_temp_range_min, tmp_temp_range_max, &THDataList, &PTDataList);

			ThellierCkTrAcCalc(datalist3, datalist4, datalist5, m_ckcorrpalint, tmp_temp_range_max);

		}
		else 
		{
			// Keine Bestimmung möglich
			// Ergebnisse auf Null setzten
			ClearResults();
			// Für folgende Handberechnug Start und Endtemperatur auf Gesamttemperaturbereich setzen
			results.m_mintemp = minmax.minstep;
			results.m_maxtemp = minmax.maxstep;
		};

	}
	else // ******** Berechnung von Hand ************
	{
		if (results.m_mintemp < results.m_maxtemp)
		{
			if (!vopt.ckcorr)
			{
				ThellierLinear(results.m_mintemp, results.m_maxtemp, &THDataList, &PTCkCorrDataList);
				m_ckcorrpalint = results.m_paleoint;
			}
			ThellierLinear(results.m_mintemp, results.m_maxtemp, &THDataList, &PTDataList);

			ThellierCkTrAcCalc(datalist3, datalist4, datalist5, m_ckcorrpalint, results.m_maxtemp);
		}
		else
			ClearResults();
	}
}

void CThellierToolDoc::ThellierLinear(int t_start, int t_end, CThellierResList *datalist1, CThellierResList *datalist2)
{
	int i;
	int tempPT, tempTH;
	double magPT, magTH;
	double summe_magPT = 0.0;
	double summe_magTH = 0.0;
	double mittelwert_magPT;
	double mittelwert_magTH;
	double x_xav[999], x_xav2[999], y_yav[999], y_yav2[999];
	int l = 1;
	int m = 1;
	int paleowindow;
	double summe_x_xav2 = 0.0;
	double summe_y_yav2 = 0.0;
	double summe_xav_yav = 0.0;
	double stderror;

	// Variablen zur Übergabe an Ergebnisklasse
	double x_gerade;
	double y_gerade;
	double x_1;
	double x_2;
	double paleofield;
	double slope;
	int number_of_points;
	double stderror_vs_slope;
	double stddev;
	double f, g, Q;
	double w;
	double NRM_TRM;
	double NRMt;
	double length_of_fit;

	// Für eindeutig falsche Eingabe korrigieren
	if (minmax.maxstep < t_end)
		t_end = minmax.maxstep;
	if (minmax.minstep > t_start)
		t_start = minmax.minstep;

	// Überprüfung der Start und Endtemperaturen
	int low1 = 0;
	int hit1 = 0;
	int low2 = 0;
	int hit2 = 0;
	for (i = 0; i < datalist1->GetSize(); i++)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist1->GetAt(i);
		tempTH = daten1->m_temp;
		if (tempTH < t_start)
			low1++;
		if (tempTH == t_start)
			hit1++;
		if (tempTH < t_end)
			low2++;
		if (tempTH == t_end)
			hit2++;
	}
	if (hit1 == 0)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist1->GetAt(low1);
		t_start = daten1->m_temp;
	}
	if (hit2 == 0)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist1->GetAt(low2);
		t_end = daten1->m_temp;
	}

	// Bestimmung der Summen
	int nTH = 0;
	int nPT = 0;
	for (i = 0; i < datalist1->GetSize(); i++)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist1->GetAt(i);
		tempTH = daten1->m_temp;
		if (tempTH >= t_start && tempTH <= t_end)
		{
			magTH = daten1->m_mag;
			summe_magTH += magTH;
			nTH++;
		}
	}
	for (i = 0; i < datalist2->GetSize(); i++)
	{
		CThellierResStruct* daten2 = ( CThellierResStruct* )datalist2->GetAt(i);
		tempPT = daten2->m_temp;
		if (tempPT >= t_start && tempPT <= t_end)
		{
			magPT = daten2->m_mag;
			summe_magPT += magPT;
			nPT++;
		}
	}

	mittelwert_magTH = summe_magTH/(nTH);
	mittelwert_magPT = summe_magPT/(nPT);

	for (i = 0; i < datalist2->GetSize(); i++)
	{
		CThellierResStruct* daten2 = ( CThellierResStruct* )datalist2->GetAt(i);
		tempPT = daten2->m_temp;
		magPT = daten2->m_mag;
		if (tempPT >= t_start && tempPT <= t_end)
		{
			x_xav[l] = magPT - mittelwert_magPT;
			x_xav2[l] = pow(x_xav[l], 2);
			summe_x_xav2  += x_xav2[l];
			l++;
			paleowindow = l;
		}
	}
	for (i = 0; i < datalist1->GetSize(); i++)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist1->GetAt(i);
		tempTH = daten1->m_temp;
		magTH = daten1->m_mag;
		if (tempTH >= t_start && tempTH <= t_end)
		{
			y_yav[m] = magTH - mittelwert_magTH;
			y_yav2[m] = pow(y_yav[m], 2);
			summe_y_yav2  += y_yav2[m];
			m++;
			paleowindow = m;
		}
	}
	for (i = 1; i < paleowindow; i++)
	{
		summe_xav_yav += x_xav[i] * y_yav[i]; //// * 
	}

	slope = -sqrt(summe_y_yav2/summe_x_xav2);

	y_gerade = mittelwert_magTH;
	x_gerade = mittelwert_magPT;

	NRMt = (mittelwert_magTH - (slope * mittelwert_magPT));
	NRM_TRM = -NRMt/slope;

	number_of_points = paleowindow - 1;

	stderror = sqrt(((2*summe_y_yav2) - (2*slope*summe_xav_yav))/((number_of_points-2)*summe_x_xav2));
 
	stderror_vs_slope = stderror/fabs(slope);

	// Fehlerrechnung neu für version 1.8 (leon, 12.12.02)

	double y_sm[999]; // SquareFit: mittlere y-Werte
	int y_sm_count = 1;
	double y_sm_prev;
	double sum_del_y2 = 0.0;
	double y_sm_max = 0.0;
	double y_sm_min = 100000000.0;
	double actualmagPT;

	double delYt, delY_av;

	for (i = 0; i < datalist1->GetSize(); i++)
	{
		CThellierResStruct* daten1 = ( CThellierResStruct* )datalist1->GetAt(i);
		tempTH = daten1->m_temp;
		magTH = daten1->m_mag;
		if (tempTH >= t_start && tempTH <= t_end)
		{
			for (int j = 0; j < datalist2->GetSize(); j++)
			{
				CThellierResStruct* daten2 = ( CThellierResStruct* )datalist2->GetAt(j);
				tempPT = daten2->m_temp;
				magPT = daten2->m_mag;
				if (tempPT >= t_start && tempPT <= t_end)
				{
					if (tempTH == tempPT)
						actualmagPT = magPT;
				}
			}
			y_sm[y_sm_count] = slope*actualmagPT + NRMt +(magTH - (slope*actualmagPT + NRMt))/2;
			// Bedingung: y grösser 0 und kleiner NRMt
			if (y_sm[y_sm_count] < 0)
				y_sm[y_sm_count] = 0;
			if (y_sm[y_sm_count] > NRMt)
				y_sm[y_sm_count] = NRMt;
			// Für Berechnung von g (gap-factor)
			if (y_sm_count > 1)
				sum_del_y2 += pow((y_sm_prev - y_sm[y_sm_count]),2);
			// Maximal und Minimalwert bestimmen: Differenz ergibt delYt
			if (y_sm[y_sm_count] > y_sm_max)
				y_sm_max = y_sm[y_sm_count];
			if (y_sm[y_sm_count] < y_sm_min)
				y_sm_min = y_sm[y_sm_count];
			y_sm_prev = y_sm[y_sm_count];
			y_sm_count++;
		}
	}

	delYt = y_sm_max - y_sm_min;

	f = delYt/NRMt;

	delY_av = sum_del_y2/delYt;

	g = 1 - (delY_av/delYt);

	// Variablen für Anfang und Ende der Gerade im Plot
	x_1 = (y_sm_max-NRMt)/slope;
	x_2 = (y_sm_min-NRMt)/slope;

	// Länge der Gerade für Berechnung von Drat
	length_of_fit = sqrt(delYt*delYt + (x_2-x_1)*(x_2-x_1));

	Q = fabs(slope * f * g / stderror);

	w = f * g /(sqrt(number_of_points-2) * stderror_vs_slope);

	paleofield = fielddata.labfield * sqrt(slope*slope);

	stddev = paleofield * stderror_vs_slope;


	// ******************************
	// Aufruf der Klasse PcaAnalysis:
	// ******************************

	// Berechnung für non-anchored
	PcaCalc(t_start, t_end, &THDataList, FALSE);

	double inc_tmp = results.m_inc;
	double dec_tmp = results.m_dec;
	double mad_tmp = results.m_mad;

	results.m_inc_na = inc_tmp;
	results.m_dec_na = dec_tmp;
	results.m_mad_na = mad_tmp;

	// Berechnung für anchored
	PcaCalc(t_start, t_end, &THDataList, TRUE);


	results.m_alpha = AngleBetweenDirs(dec_tmp, inc_tmp, results.m_dec, results.m_inc);

	// Übergabe an Ergebniss file
	results.m_numberofpoints = number_of_points;
	results.m_slope = slope;
	results.m_stdslope = stderror_vs_slope;
	results.m_trm = NRM_TRM;
	results.m_nrmt = NRMt;
	results.m_f = f;
	results.m_g = g;
	results.m_q = Q;
	results.m_w = w;
	results.m_paleoint = paleofield;
	results.m_stddev = stddev;
	results.m_mintemp = t_start;
	results.m_maxtemp = t_end;
	results.m_length_of_fit = length_of_fit;
	// Darstellung der Fit Gerade	
	results.x_1 = x_1;
	results.x_2 = x_2;
	results.x_gerade = x_gerade;
	results.y_gerade = y_gerade;

}

void CThellierToolDoc::PcaCalc(int t_start, int t_end, CThellierResList *datalist, BOOL anchored)
{

	double DEG = 180/pi;

	int i,j;
	double ldec,linc,pdec,pinc,e1,e2,e3;
	double B1 = 0.0;
	double B2 = 0.0;
	double B3 = 0.0;
	double B4 = 0.0;
	double B5 = 0.0;
	double B6 = 0.0;
	int k = 0;

	double xTH[999];
	double yTH[999];
	double zTH[999];

	int tempTH;
	double m_dec, m_inc, m_mad;

	// Für Berechnung der Mittelwerte
	double x_mean = 0;
	double y_mean = 0;
	double z_mean = 0;

	// Auslesen der Daten aus Strukturliste
	for (i = 0; i < datalist->GetSize(); i++)
	{
		CThellierResStruct* daten = ( CThellierResStruct* )datalist->GetAt(i);
		tempTH = daten->m_temp;
		if (tempTH >= t_start && tempTH <= t_end)
		{
			xTH[k] = daten->m_x;
			yTH[k] = daten->m_y;
			zTH[k] = daten->m_z;
			k++;
		}
	}

	int start_count = 0;
	int end_count = k;

	// Mittelwerte
	for (i = start_count; i < end_count; i++)
	{
		x_mean += xTH[i]/(end_count-1);
		y_mean += yTH[i]/(end_count-1);
		z_mean += zTH[i]/(end_count-1);
	}

	if (!anchored) // Falls nicht im Ursprung verankert
	{
		for (i = start_count; i < end_count; i++)
		{
			xTH[i] -= x_mean;
			yTH[i] -= y_mean;
			zTH[i] -= z_mean;
		}
	}

	double l = xTH[start_count]-xTH[end_count-1];
	double m = yTH[start_count]-yTH[end_count-1];
	double n = zTH[start_count]-zTH[end_count-1];

	double core_dec;
	double core_inc;

	XYZtoDecInc(&core_dec, &core_inc, l, m, n);

	for(i=0;i<=2;i++)
		for(j=0;j<=2;j++)
			B[i][j] = 0.0;

      for(j = start_count;j < end_count;j++)
		{
			B[0][0]  +=  xTH[j]*xTH[j];
			B[0][1]  +=  xTH[j]*yTH[j];
			B[0][2]  +=  xTH[j]*zTH[j];
			B[1][1]  +=  yTH[j]*yTH[j];
			B[1][2]  +=  yTH[j]*zTH[j];
			B[2][2]  +=  zTH[j]*zTH[j];
		}
	B[1][0] = B[0][1];
	B[2][0] = B[0][2];
	B[2][1] = B[1][2];

	Eigen(&ldec,&linc,&pdec,&pinc,&e1,&e2,&e3,anchored,x_mean,y_mean,z_mean);

	m_dec = ldec;
	m_inc = linc;


	if ( ((e1 + e2) <= 0))
		m_mad = 0;
	else
		m_mad = atan(sqrt((e1+e2)/e3))*(180/pi);

	if   (e1 < 0)
		e1  =  0;                                         
	double m_madp  =  (atan(sqrt(e1/e2)+(e1/e3)))*(180/pi);


	double dd  =  (m_dec-core_dec)*(pi/180);
	double w   =  sin(m_inc*pi/180)*sin(core_inc*pi/180)+cos(m_inc*pi/180)*cos(core_inc*pi/180)*cos(dd);
	if (w >  1)  w= 1;
	if (w < -1) w=-1;
	double pa  =  acos(w)*(DEG);
	if ( pa>90 )
	{
	  m_dec  = m_dec + 180;
	  m_inc  =  -(m_inc);
	}

	if ( m_dec > 360)
		m_dec  =  m_dec - 360;

	results.m_inc = m_inc;
	results.m_dec = m_dec;
	results.m_mad = m_mad;

}

void CThellierToolDoc::XYZtoDecInc(double *dec, double *inc, double x, double y, double z)
{
	// Berechnet Richtung aus kartesischen Kooredinaten
	double DEG = 180.0/pi;
	double local_dec, local_inc;

	if (x == 0.0)
	{
		if (y <= 0.0) 
			local_dec = 270.0;
		else
			local_dec = 90.0;
	}
	else
	{
		local_dec = (atan(y/x))*DEG;
		if (x <= 0.0) 
			local_dec += 180.0;
		else
			if (y < 0.0) 
				local_dec += 360.0;
	}
	if (x != 0.0 || y != 0.0)
		local_inc = atan(z/(sqrt(x*x+y*y)))*DEG;
	else
		if(z>0.0) 
			local_inc = 90.0;
	else
		local_inc = -90.0;

	*dec = local_dec;
	*inc = local_inc;

}

double CThellierToolDoc::AngleBetweenDirs(double dec1, double inc1, double dec2, double inc2)
{

	double alpha;
	double deg = pi/180;

	alpha = (acos(cos(deg*inc1)*cos(deg*dec1)*cos(deg*inc2)*cos(deg*dec2) + cos(deg*inc1)*sin(deg*dec1)*cos(deg*inc2)*sin(deg*dec2) + sin(deg*inc1)*sin(deg*inc2)))*180/pi;

	return alpha;
}

double *CThellierToolDoc::vector(long nl, long nh)
/* allocate a double vector with subscript range v[nl..nh] */
{
	double *v;

	v=(double *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(double)));
	return v-nl+NR_END;
}

double **CThellierToolDoc::matrix(long nrl, long nrh, long ncl, long nch)
/* allocate a double matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	double **m;

	/* allocate pointers to rows */
	m=(double **) malloc((size_t)((nrow+NR_END)*sizeof(double*)));
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(double *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}

double **CThellierToolDoc::convert_matrix(double *a, long nrl, long nrh, long ncl, long nch)
/* allocate a double matrix m[nrl..nrh][ncl..nch] that points to the matrix
declared in the standard C manner as a[nrow][ncol], where nrow=nrh-nrl+1
and ncol=nch-ncl+1. The routine should be called with the address
&a[0][0] as the first argument. */
{
	long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1;
	double **m;

	/* allocate pointers to rows */
	m=(double **) malloc((size_t) ((nrow+NR_END)*sizeof(double*)));
	m += NR_END;
	m -= nrl;

	/* set pointers to rows */
	m[nrl]=a-ncl;
	for(i=1,j=nrl+1;i<nrow;i++,j++) m[j]=m[j-1]+ncol;
	/* return pointer to array of pointers to rows */
	return m;
}

void CThellierToolDoc::free_vector(double *v, long nl, long nh)
/* free a double vector allocated with vector() */
{
	free((FREE_ARG) (v+nl-NR_END));
}

void CThellierToolDoc::free_matrix(double **m, long nrl, long nrh, long ncl, long nch)
/* free a double matrix allocated by matrix() */
{
	free((FREE_ARG) (m[nrl]+ncl-NR_END));
	free((FREE_ARG) (m+nrl-NR_END));
}

void CThellierToolDoc::free_convert_matrix(double **b, long nrl, long nrh, long ncl, long nch)
/* free a matrix allocated by convert_matrix() */
{
	free((FREE_ARG) (b+nrl-NR_END));
}

void CThellierToolDoc::jacobi(double **a, int n, double d[], double **v, int *nrot)
{
	int j,iq,ip,i;
	double tresh,theta,tau,t,sm,s,h,g,c,*b,*z;

	b=vector(1,n);
	z=vector(1,n);
	for (ip=1;ip<=n;ip++) {
		for (iq=1;iq<=n;iq++) v[ip][iq]=0.0;
		v[ip][ip]=1.0;
	}
	for (ip=1;ip<=n;ip++) {
		b[ip]=d[ip]=a[ip][ip];
		z[ip]=0.0;
	}
	*nrot=0;
	for (i=1;i<=50;i++) {
		sm=0.0;
		for (ip=1;ip<=n-1;ip++) {
			for (iq=ip+1;iq<=n;iq++)
				sm += fabs(a[ip][iq]);
		}
		if (sm == 0.0) {
			free_vector(z,1,n);
			free_vector(b,1,n);
			return;
		}
		if (i < 4)
			tresh=0.2*sm/(n*n);
		else
			tresh=0.0;
		for (ip=1;ip<=n-1;ip++) {
			for (iq=ip+1;iq<=n;iq++) {
				g=100.0*fabs(a[ip][iq]);
				if (i > 4 && (double)(fabs(d[ip])+g) == (double)fabs(d[ip])
					&& (double)(fabs(d[iq])+g) == (double)fabs(d[iq]))
					a[ip][iq]=0.0;
				else if (fabs(a[ip][iq]) > tresh) {
					h=d[iq]-d[ip];
					if ((double)(fabs(h)+g) == (double)fabs(h))
						t=(a[ip][iq])/h;
					else {
						theta=0.5*h/(a[ip][iq]);
						t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
						if (theta < 0.0) t = -t;
					}
					c=1.0/sqrt(1+t*t);
					s=t*c;
					tau=s/(1.0+c);
					h=t*a[ip][iq];
					z[ip] -= h;
					z[iq] += h;
					d[ip] -= h;
					d[iq] += h;
					a[ip][iq]=0.0;
					for (j=1;j<=ip-1;j++) {
						ROTATE(a,j,ip,j,iq)
					}
					for (j=ip+1;j<=iq-1;j++) {
						ROTATE(a,ip,j,j,iq)
					}
					for (j=iq+1;j<=n;j++) {
						ROTATE(a,ip,j,iq,j)
					}
					for (j=1;j<=n;j++) {
						ROTATE(v,j,ip,j,iq)
					}
					++(*nrot);
				}
			}
		}
		for (ip=1;ip<=n;ip++) 
		{
			b[ip] += z[ip];
			d[ip]=b[ip];
			z[ip]=0.0;
		}
	}
}

void CThellierToolDoc::Eigen(double *LD, double *LI, double *PD, double *PI, double *E1, double *E2, double *E3, BOOL anchored, double XX, double YY, double ZZ)
{
	int i,j,nrot,i_max,i_int,i_min;
	double *d,*r,**v,**e,sum=0.0,e_max=0.0,e_min=1000000000000.0;
	double x,y,z;
	double pi = 3.141592654;
	double DEG = 180/pi;

	d=vector(1,NP);
	r=vector(1,NP);
	v=matrix(1,NP,1,NP);
	e=convert_matrix(&B[0][0],1,3,1,3);
	jacobi(e,3,d,v,&nrot);
	for (j=1;j<=3;j++)
		sum += d[j];
	for (j=1;j<=3;j++)
	{
		if (d[j] > e_max)
		{
			e_max = d[j];
			i_max = j;
		}
		if (d[j] < e_min)
		{
			e_min = d[j];
			i_min = j;
		}
	}
	for (j=1;j<=3;j++)
		if (d[j] > e_min && d[j] < e_max)
			i_int = j;


	*E1 = d[i_min]/sum;
	if (i_int <= 3 && i_int >= 1)
		*E2 = d[i_int]/sum;
	else
		*E2 = 0.0;
	*E3 = d[i_max]/sum;

	x = v[1][i_max];
	y = v[2][i_max];
	z = v[3][i_max];

	double inc;
	double dec;
	XYZtoDecInc(&dec,&inc,x,y,z);


	*LD = dec;
	*LI = inc;

	if (!anchored)
	{
		x  =  ZZ*v[2][i_max]-YY*v[3][i_max];
		y  =  XX*v[3][i_max]-ZZ*v[1][i_max];
	  	z  =  YY*v[1][i_max]-XX*v[2][i_max];
	}
	else
	{
		x = v[1][i_min];
		y = v[2][i_min];
		z = v[3][i_min];
	}

	XYZtoDecInc(&dec,&inc,x,y,z);

	*PD = dec;
	*PI = inc;
	free_convert_matrix(e,1,3,1,3);
	free_matrix(v,1,NP,1,NP);
	free_vector(r,1,NP);
	free_vector(d,1,NP);
}

int CThellierToolDoc::CriteriaCheck()
{
	// ***********************************
	// Überprüft ob Kriterien erfüllt sind
	// ***********************************

	int critcheck;

	// Daten aus Resultfile auslesen
	// -----------------------------

	// NRM-TRM Kriterien
	int n = results.m_numberofpoints;
	double f = results.m_f;
	double q = results.m_q;
	double stdslope = results.m_stdslope;
	// Alterationskriterien
	double ckerror = results.m_ckerror;
	double ckdiff = results.m_ckdiff;
	double drat = results.m_drat;
	// Richtungskriterien
	double mad = results.m_mad;
	double alpha = results.m_alpha;
	// MD Kriterien
	// (noch nicht berücksichtigt)
	double acerror = results.m_ACerror;
	double rdiff = results.m_rTRerror;
	double tstar = results.m_tstar;
	
	if (n >= criteria.m_crit_A_n && stdslope <= criteria.m_crit_A_std && f >= criteria.m_crit_A_f && q >= criteria.m_crit_A_q && mad <= criteria.m_crit_A_mad && ckerror <= criteria.m_crit_A_ckerror && ckdiff <= criteria.m_crit_A_ckdiff && acerror <= criteria.m_crit_A_acerror && rdiff <= criteria.m_crit_A_rdiff && drat <= criteria.m_crit_A_drat && alpha <= criteria.m_crit_A_alpha && tstar <= criteria.m_crit_A_tstar)
		critcheck = 0;
	else
		if (n >= criteria.m_crit_B_n && stdslope <= criteria.m_crit_B_std && f >= criteria.m_crit_B_f && q >= criteria.m_crit_B_q && mad <= criteria.m_crit_B_mad && ckerror <= criteria.m_crit_B_ckerror && ckdiff <= criteria.m_crit_B_ckdiff && acerror <= criteria.m_crit_B_acerror && rdiff <= criteria.m_crit_B_rdiff && drat <= criteria.m_crit_B_drat && alpha <= criteria.m_crit_B_alpha && tstar <= criteria.m_crit_B_tstar)
			critcheck = 1;
		else
			critcheck = 2;

	return critcheck;
}

void CThellierToolDoc::NormTRRes(CThellierResList *datalist1, double truenrm)
{
	double magTR, xTR, yTR, zTR;
	int tempTR;

	if( truenrm > 0.0)
	{
		// temporäre liste Erstellen
		CThellierResList tmpTRlist;
		tmpTRlist.RemoveAll();

		for (int i = 0; i < datalist1->GetSize(); i++)
		{
			CThellierResStruct* daten1 = ( CThellierResStruct* )datalist1->GetAt(i);
			tempTR = daten1->m_temp;
			magTR = daten1->m_mag*minmax.maxmagTH/truenrm;
			xTR = daten1->m_x; //*minmax.maxmagTH/truenrm;  Winkel zwichen Lab and TH
			yTR = daten1->m_y; //*minmax.maxmagTH/truenrm;  Winkel zwichen TH and TR
			zTR = daten1->m_z*minmax.maxmagTH/truenrm;
			tmpTRlist.Add(new CThellierResStruct (0, tempTR, tempTR, xTR, yTR, zTR, magTR));
		}

		TRResList.RemoveAll();

		for (i = 0; i < tmpTRlist.GetSize(); i++)
		{
			CThellierResStruct* daten1 = ( CThellierResStruct* )tmpTRlist.GetAt(i);
			tempTR = daten1->m_temp;
			magTR = daten1->m_mag;
			// X,Y,Z werden unverändert gelassen (für Richtung zwischen Feld und pTRM)
			xTR = daten1->m_x;
			yTR = daten1->m_y;
			zTR = daten1->m_z;
			TRResList.Add(new CThellierResStruct (0, tempTR, tempTR, xTR, yTR, zTR, magTR));
		}

		// Übergabe der neu normierten Werte an MinMax Struktur
		minmax.maxhdiffTR = minmax.maxhdiffTR*minmax.maxmagTH/truenrm;
		minmax.maxzdiffTR = minmax.maxzdiffTR*minmax.maxmagTH/truenrm;
		minmax.maxrdiffTR = minmax.maxrdiffTR*minmax.maxmagTH/truenrm;
		minmax.maxzhdiffTR = minmax.maxzhdiffTR*minmax.maxmagTH/truenrm;
		minmax.maxrzhdiffTR = minmax.maxrzhdiffTR*minmax.maxmagTH/truenrm;

	}

}

void CThellierToolDoc::OnCriteria() 
{
	CCriteriaDlg m_cdlg ( this );
	// Class A Kriterien
	m_cdlg.m_crit_A_n = criteria.m_crit_A_n;
	m_cdlg.m_crit_A_f = criteria.m_crit_A_f;
	m_cdlg.m_crit_A_q = criteria.m_crit_A_q;
	m_cdlg.m_crit_A_std = criteria.m_crit_A_std;
	m_cdlg.m_crit_A_mad = criteria.m_crit_A_mad;
	m_cdlg.m_crit_A_mad_na = criteria.m_crit_A_mad_na;
	m_cdlg.m_crit_A_alpha = criteria.m_crit_A_alpha;
	m_cdlg.m_crit_A_ckerror = criteria.m_crit_A_ckerror;
	m_cdlg.m_crit_A_ckdiff = criteria.m_crit_A_ckdiff;
	m_cdlg.m_crit_A_drat = criteria.m_crit_A_drat;
	m_cdlg.m_crit_A_rdiff = criteria.m_crit_A_rdiff;
	m_cdlg.m_crit_A_tstar = criteria.m_crit_A_tstar;
	m_cdlg.m_crit_A_acerror = criteria.m_crit_A_acerror;
	// Class B Kriterien
	m_cdlg.m_crit_B_n = criteria.m_crit_B_n;
	m_cdlg.m_crit_B_f = criteria.m_crit_B_f;
	m_cdlg.m_crit_B_q = criteria.m_crit_B_q;
	m_cdlg.m_crit_B_std = criteria.m_crit_B_std;
	m_cdlg.m_crit_B_mad = criteria.m_crit_B_mad;
	m_cdlg.m_crit_B_mad_na = criteria.m_crit_B_mad_na;
	m_cdlg.m_crit_B_alpha = criteria.m_crit_B_alpha;
	m_cdlg.m_crit_B_ckerror = criteria.m_crit_B_ckerror;
	m_cdlg.m_crit_B_ckdiff = criteria.m_crit_B_ckdiff;
	m_cdlg.m_crit_B_drat = criteria.m_crit_B_drat;
	m_cdlg.m_crit_B_rdiff = criteria.m_crit_B_rdiff;
	m_cdlg.m_crit_B_tstar = criteria.m_crit_B_tstar;
	m_cdlg.m_crit_B_acerror = criteria.m_crit_B_acerror;
	// Berechnungsparameter
	m_cdlg.m_maximizingpar = criteria.m_maximizingpar;
	m_cdlg.m_autock_enable = criteria.m_autock_enable;
//	m_cdlg.m_crifile = m_crifile;
	// General View Options
	m_cdlg.m_crit_arai_norm = vopt.m_arai_norm;

	m_cdlg.DoModal();

	UpdateAllViews( NULL );
	
}

void CThellierToolDoc::ClearResults()
{
	results.m_numberofpoints = 0;
	results.m_slope = 0.0;
	results.m_stdslope = 0.0;
	results.m_trm = 0.0;
	results.m_nrmt = 0.0;
	results.m_f = 0.0;
	results.m_g = 0.0;
	results.m_q = 0.0;
	results.m_w = 0.0;
	results.m_paleoint = 0.0;
	results.m_stddev = 0.0;
	results.m_mintemp = 0;
	results.m_maxtemp = 0;
	results.m_inc = 0.0;
	results.m_dec = 0.0;
	results.m_mad = 0.0;
	results.m_inc_na = 0.0;
	results.m_dec_na = 0.0;
	results.m_mad_na = 0.0;
	results.m_alpha = 0.0;
	results.m_class.Empty();
	results.m_ckdiff = 0.0;
	results.m_ckerror = 0.0;
	results.m_drat = 0.0;
	results.m_ACerror = 0.0;
	results.m_rTRerror = 0.0;
	results.m_tstar = 0.0;
	// Darstellung der Fit Gerade	
	results.x_1 = 0.0;
	results.x_2 = 0.0;
	results.x_gerade = 0.0;
	results.y_gerade = 0.0;
}

void CThellierToolDoc::ThellierCkTrAcCalc(CThellierResList *datalist3, CThellierResList *datalist4, CThellierResList *datalist5, double corrpalint, int maxtemp)
{
	// Für Berechnung der Difference zwischen CK-korr und nichtkorr. Wert
	double ckerror;
	double max_CK_error;
	// Berechnung von Drat
	double drat;
	double max_drat;

	// Für MD Berechnung
	double rdiff, zdiff, hdiff;
	double acerror;
	double max_rTR_error;
	double max_AC_error;

	// Allgemein
	int tempCK, tempTR, tempAC;

	// Initialisierung
	max_CK_error = 0.0;
	max_rTR_error = 0.0;
	max_AC_error = 0.0;
	max_drat = 0.0;

	// Bestimmung des CK errors und der CK diff
	if (!vopt.ckcorr)
	{
		results.m_ckdiff = fabs(corrpalint-results.m_paleoint)*100/results.m_paleoint;
		for (int k = 0; k < datalist3->GetSize(); k++)
		{
			CThellierResStruct* daten3 = ( CThellierResStruct* )datalist3->GetAt(k);
			tempCK = daten3->m_sptemp;
			if (tempCK < maxtemp)
			{
				ckerror = fabs(daten3->m_mag * 100 / results.m_trm);
				if (max_CK_error <  ckerror)
					max_CK_error = ckerror;
				drat = fabs(daten3->m_mag * 100 / results.m_length_of_fit);
				if (max_drat <  drat)
					max_drat = drat;
			}
		};
		results.m_ckerror = max_CK_error;
		results.m_drat = max_drat;
	}
	else
	{
		results.m_ckdiff = 0.0;
		results.m_ckerror = 0.0;
		results.m_drat = 0.0;
	}

	// Bestimmung des MD tail Anteile
	if (datalist4->GetSize() > 0)
	{
		for (int l = 0; l < datalist4->GetSize(); l++)
		{
			CThellierResStruct* daten4 = ( CThellierResStruct* )datalist4->GetAt(l);
			tempTR = daten4->m_temp;
			if (tempTR <= maxtemp)
			{
				rdiff = fabs(daten4->m_mag * minmax.maxmagTH / results.m_nrmt);
				zdiff = fabs(daten4->m_z * minmax.maxmagTH / results.m_nrmt);
				hdiff = fabs(daten4->m_y * minmax.maxmagTH / results.m_nrmt);
				if (max_rTR_error <  rdiff)
					max_rTR_error = rdiff;
			}
		};
		results.m_rTRerror = max_rTR_error;
		// Übergabe des maximalen t-star Fehlers an results object
		results.m_tstar = minmax.maxzdiffTR  * minmax.maxmagTH / results.m_nrmt;


	}
	else
	{
		results.m_rTRerror = 0.0;
	}

	// Bestimmung der AC check Differenzen
	if (datalist5->GetSize() > 0)
	{
		for (int m = 0; m < datalist5->GetSize(); m++)
		{
			CThellierResStruct* daten5 = ( CThellierResStruct* )datalist5->GetAt(m);
			tempAC = daten5->m_sptemp;
			if (tempAC < maxtemp)
			{
				acerror = fabs(daten5->m_mag * 100 / results.m_trm);
				if (max_AC_error <  acerror)
					max_AC_error = acerror;
			}
		};
		results.m_ACerror = max_AC_error;
	}
	else
	{
		results.m_ACerror = 0.0;
	}
}


void CThellierToolDoc::CkErrorSpline(CThellierResList *datalist, float yp1, float ypn)
{
//Given arrays x[1..n] and y[1..n] containing a tabulated function, i.e., y i = f(xi), with
//x1<x2< :::<xN , and given values yp1 and ypn for the _rst derivative of the interpolating
//function at points 1 and n, respectively, this routine returns an array y2[1..n] that contains
//the second derivatives of the interpolating function at the tabulated points xi. Ifyp1 and/or
//ypn are equal to 1 _ 10 30 or larger, the routine is signaled to set the corresponding boundary
//condition for a natural spline, with zero second derivative on that boundary.

// Eigener Bereich
	double ckdiff;
	int tempCK;
	int n = 1;

	// Initialisierung;
	//ckspline_y2[];

	float x[999];
	float y[999];
	float u[999];
//	float ckspline_y2[999];

	for (int m = 0; m < datalist->GetSize(); m++)
	{
		CThellierResStruct* daten = ( CThellierResStruct* )datalist->GetAt(m);
		tempCK = daten->m_sptemp;
		ckdiff = daten->m_mag;
		x[n] = tempCK;
		y[n] = ckdiff;
		n++;
	}

	// Geänderter code
	int i,k;
	float p,qn,sig,un;

	if (yp1 > 0.99e30) //The lower boundary condition is set either to be \nat-ural" 
		ckspline_y2[1]=u[1]=0.0;
	else  //or else to have a speci_ed _rst derivative.
	{
		ckspline_y2[1] = -0.5;
		u[1]=(3.0/(x[2]-x[1]))*((y[2]-y[1])/(x[2]-x[1])-yp1);
	}

	for (i=2;i<=n-1;i++) //This is the decomposition loop of the tridiagonal algorithm. y2 and u are used for temporary storage of the decomposed factors.
	{ 
		sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
		p=sig*ckspline_y2[i-1]+2.0;
		ckspline_y2[i]=(sig-1.0)/p;
		u[i]=(y[i+1]-y[i])/(x[i+1]-x[i]) - (y[i]-y[i-1])/(x[i]-x[i-1]);
		u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1])/p;
	}

	if (ypn > 0.99e30) //The upper boundary condition is set either to be\natural" 
		qn=un=0.0;
	else //or else to have a speci_ed _rst derivative.
	{
		qn=0.5;
		un=(3.0/(x[n]-x[n-1]))*(ypn-(y[n]-y[n-1])/(x[n]-x[n-1]));
	}

	ckspline_y2[n]=(un-qn*u[n-1])/(qn*ckspline_y2[n-1]+1.0);

	for (k=n-1;k>=1;k--) // This is the backsubstitution loop of the tridiagonal algorithm. 
		ckspline_y2[k]=ckspline_y2[k]*ckspline_y2[k+1]+u[k];

	ckspline_length = n;
}

float CThellierToolDoc::CkErrorSplinet(CThellierResList *datalist, float y2a[], int n, float x)
{
//Given the arrays xa[1..n] and ya[1..n], which tabulate a function (with the xai's in order),
//and given the array y2a[1..n], which is the output from spline above, and given a value of
//x, this routine returns a cubic-spline interpolated value y.

	float y;

	int klo,khi,k;
	float h,b,a;

	double ckdiff;
	int tempCK;
	int i = 1;

	float xa[999];
	float ya[999];

	for (int m = 0; m < datalist->GetSize(); m++)
	{
		CThellierResStruct* daten = ( CThellierResStruct* )datalist->GetAt(m);
		tempCK = daten->m_sptemp;
		ckdiff = daten->m_mag;
		xa[i] = tempCK;
		ya[i] = ckdiff;
		i++;
	}

	klo=1; 
	//We will nd the right place in the table by means of
	//bisection. This is optimal if sequential calls to this
	//routine are at random values of x. If sequential calls
	//are in order, and closely spaced, one would do better
	//tostoreprevious values ofklo and khi and test if
	//they remain appropriate on the next call.
	khi=n;
	while (khi-klo > 1) 
	{
		k=(khi+klo) >> 1;
		if (xa[k] > x) 
			khi=k;
		else klo=k;
	} // klo and khi now bracket the input value of x.
	h=xa[khi]-xa[klo];
	//if (h == 0.0) nrerror("Bad xa input to routine splint"); The xa's must be distinct. 
	a=(xa[khi]-x)/h;
	b=(x-xa[klo])/h; //Cubic spline polynomial is now evaluated.
	y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;

	return y;	
}

