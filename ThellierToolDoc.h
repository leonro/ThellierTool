// ThellierToolDoc.h : Schnittstelle der Klasse CThellierToolDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THELLIERTOOLDOC_H__169B8CE1_3F61_451F_BAE9_52C173A8A122__INCLUDED_)
#define AFX_THELLIERTOOLDOC_H__169B8CE1_3F61_451F_BAE9_52C173A8A122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//neue Klasse für Datenstruktur, eingefügt von leon
class CThellierDataStruct : public CObject
{
protected:
	class CThellierDataStruct* datastruct;
public:
	CThellierDataStruct (float step, float mag, float inc, float dec ):
	  m_step(step), m_mag(mag), m_inc(inc), m_dec(dec) {}
	float m_step, m_mag, m_inc, m_dec;
};

//neue Klasse für Datenstruktur, eingefügt von leon
class CThellierResStruct : public CObject
{
protected:
	class CThellierResStruct* datastruct;
public:
	CThellierResStruct (int tr, int temp, int sptemp, double x, double y, double z, double mag ):
	  m_tr(tr), m_temp(temp), m_sptemp(sptemp), m_x(x), m_y(y), m_z(z), m_mag(mag) {}
	double m_x, m_y, m_z, m_mag;
	int m_tr, m_temp, m_sptemp;
};

//neue Klasse für Felddatenstruktur
class CFieldDataStruct : public CObject
{
public:
	float labfield, bearing, plunge, strike, dip;
	CString name;
	CString checktype;
	float GetBearing(CObject * myObject)
	{ return bearing; }
	float GetPlunge(CObject * myObject)
	{ return plunge; }
	float GetStrike(CObject * myObject)
	{ return strike; }
	float GetDip(CObject * myObject)
	{ return dip; }
	float GetLabfield(CObject * myObject)
	{ return labfield; }
	CString GetName(CObject * myObject)
	{ return name; }
};

//neue Klasse für Ergebnisse
class CResultsStruct : public CObject
{
public:
	int m_mintemp;
	int m_maxtemp;
	double m_mad;
	double m_dec;
	double m_inc;
	double m_mad_na;
	double m_dec_na;
	double m_inc_na;
	double m_trm;
	double m_nrmt;
	int m_numberofpoints;
	double m_stddev;
	double m_slope;
	double m_stdslope;
	double m_ckerror;
	double m_ckdiff;
	double m_w;
	double m_q;
	double m_g;
	double m_f;
	double m_paleoint;
	CString m_type;
	CString m_class;
	double m_rTRerror;
	double m_ACerror;
	double x_1;
	double x_2;
	double x_gerade;
	double y_gerade;
	double m_length_of_fit;
	double m_drat;
	double m_alpha;
	double m_tstar;
};


//neue Klasse für Kriterien
class CCriteriaStruct : public CObject
{
public:
	int m_crit_A_n;
	double m_crit_A_std;
	double m_crit_A_f;
	int m_crit_A_q;
	int m_crit_A_mad;
	int m_crit_A_mad_na;
	int m_crit_A_alpha;
	int m_crit_A_ckerror;
	int m_crit_A_ckdiff;
	int m_crit_A_drat;
	int m_crit_A_tstar;
	int m_crit_A_zdiff;
	int m_crit_A_rdiff;
	int m_crit_A_acerror;
	int m_crit_B_n;
	double m_crit_B_std;
	double m_crit_B_f;
	int m_crit_B_q;
	int m_crit_B_mad;
	int m_crit_B_mad_na;
	int m_crit_B_alpha;
	int m_crit_B_ckerror;
	int m_crit_B_ckdiff;
	int m_crit_B_drat;
	int m_crit_B_tstar;
	int m_crit_B_zdiff;
	int m_crit_B_rdiff;
	int m_crit_B_acerror;
	int m_maximizingpar;
	BOOL m_autock_enable;
};

//neue Klasse für Maximal-Minimalwerte
class CThellierMinMaxStruct : public CObject
{
public:
	int minstep;
	int maxstep;
	double minmagTH;
	double maxmagTH;
	double maxmagPT;
	double maxx, maxy, maxz, maxh;
	double minx, miny, minz, minh;
	double maxrdiffTR, maxzdiffTR, maxhdiffTR;
	double maxrzhdiffTR, maxzhdiffTR;
	double maxdiffCK;
	double maxdiffAC;
	int GetMinStep (CObject* myobject)
	{return minstep;}
	int GetMaxStep (CObject* myobject)
	{return maxstep;}
	double GetMinH (CObject* myobject)
	{return minh;}
	double GetMaxH (CObject* myobject)
	{return maxh;}
};

//neue Klasse für Ansichten
class CViewOpt : public CObject
{
public:
	int coordinates;
	int mainview;
	int automatic;
	BOOL ckcorr;
	BOOL accheck;
	BOOL zonly;
	BOOL use_autock;
	CString pathdata;
	int m_arai_norm;

};

//Klasse für Liste der Datenstruktur, eingefügt von leon
class CThellierDataList : public CObArray
{
public:
	CThellierDataList();
	virtual ~CThellierDataList();
};

//Klasse für Liste der Ergebnisstruktur, eingefügt von leon
class CThellierResList : public CObArray
{
public:
	CThellierResList();
	virtual ~CThellierResList();
};

class CThellierToolSrvrItem;

class CThellierToolDoc : public COleServerDoc
{
protected: // Nur aus Serialisierung erzeugen
	CThellierToolDoc();
	DECLARE_DYNCREATE(CThellierToolDoc)

// Attribute
public:
	CThellierToolSrvrItem* GetEmbeddedItem()
		{ return (CThellierToolSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operationen
public:


// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CThellierToolDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	//}}AFX_VIRTUAL

// Implementierung
public:
	double AngleBetweenDirs(double dec1, double inc1, double dec2, double inc2);
	void XYZtoDecInc(double *dec, double *inc, double x, double y, double z);
	int ckspline_length;
	float ckspline_y2[999];
	float CkErrorSplinet(CThellierResList *datalist, float y2a[], int n, float x);
	void CkErrorSpline(CThellierResList *datalist, float yp1, float ypn);
	void ThellierCkTrAcCalc(CThellierResList *datalist3, CThellierResList *datalist4, CThellierResList *datalist5, double corrpalint, int maxtemp);
	void ClearResults();
	void NormTRRes(CThellierResList *datalist1, double truenrm);
	int CriteriaCheck();
	CThellierResList CkErrorList;
	// Funktionen für PCA Berechnung
	double B[3][3];
	void PcaCalc(int t_start, int t_end, CThellierResList *datalist, BOOL anchored);
	void Eigen(double *LD, double *LI, double *PD, double *PI, double *E1, double *E2, double *E3, BOOL anchored, double XX, double YY, double ZZ);
	void free_convert_matrix(double **b, long nrl, long nrh, long ncl, long nch);
	void free_matrix(double **m, long nrl, long nrh, long ncl, long nch);
	void free_vector(double *v, long nl, long nh);
	double **convert_matrix(double *a, long nrl, long nrh, long ncl, long nch);
	double **matrix(long nrl, long nrh, long ncl, long nch);
	double *vector(long nl, long nh);
	void jacobi(double **a, int n, double d[], double **v, int *nrot);
	CResultsStruct results;
	void ThellierLinear(int t_start, int t_end, CThellierResList *datalist1, CThellierResList *datalist2);
	void ThellierCalc(CThellierResList *datalist1, CThellierResList *datalist2, CThellierResList *datalist3, CThellierResList *datalist4, CThellierResList *datalist5, int selectclass);
	void CKCorrToPTData(CThellierResList *datalist1,CThellierResList *datalist2);
	CThellierResList ACResList;
	CThellierResList PTCkCorrDataList;
	CThellierResList PTCkCorrCompList;
	CThellierResList CKRemainingDataList;
	void CheckCorrection(CThellierResList *datalist1, CThellierResList *datalist2);
	void ACCheckAnalysis(CThellierResList *datalist1, CThellierResList *datalist2, CThellierResList *datalist3);
	CCriteriaStruct criteria;
	CThellierResList TRResList;
	void TRCheckAnalysis(CThellierResList *datalist1, CThellierResList *datalist2, CThellierResList *datalist3);
	CThellierMinMaxStruct minmax;
	void MaxMinValues(CThellierResList *datalist1,CThellierResList *datalist2,CThellierResList *datalist3);
	void VectorSub(CThellierResList *datalist);
	CThellierResList ACDataList;
	CThellierResList TRDataList;
	CThellierResList CKDataList;
	CThellierResList PTDataList;
	CThellierResList THDataList;
	CViewOpt vopt;
	CThellierResList AllDataList;
	void CoorTrans(CThellierDataList *datalist);
	CThellierDataList ThellierData;
	void FileExtract(CStringList *datalist);
	CFieldDataStruct fielddata;
	virtual ~CThellierToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	static double pi;

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CThellierToolDoc)
	afx_msg void OnCriteria();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generierte OLE-Dispatch-Map-Funktionen
	//{{AFX_DISPATCH(CThellierToolDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_THELLIERTOOLDOC_H__169B8CE1_3F61_451F_BAE9_52C173A8A122__INCLUDED_)
