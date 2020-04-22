========================================================================
       MICROSOFT FOUNDATION CLASS BIBLIOTHEK : ThellierTool
========================================================================


Diese ThellierTool-Anwendung hat der Klassen-Assistent f�r Sie erstellt. Diese Anwendung
zeigt nicht nur die prinzipielle Verwendung der Microsoft Foundation Classes, 
sondern dient auch als Ausgangspunkt f�r die Erstellung Ihrer eigenen DLLs.

Diese Datei enth�lt die Zusammenfassung der Bestandteile aller Dateien, die 
Ihre ThellierTool-Anwendung bilden.

ThellierTool.dsp
    Diese Datei (Projektdatei) enth�lt Informationen auf Projektebene und wird zur
    Erstellung eines einzelnen Projekts oder Teilprojekts verwendet. Andere Benutzer k�nnen
    die Projektdatei (.dsp) gemeinsam nutzen, sollten aber die Makefiles lokal exportieren.

ThellierTool.h
    Hierbei handelt es sich um die Haupt-Header-Datei der Anwendung. Diese enth�lt 
	andere projektspezifische Header (einschlie�lich Resource.h) und deklariert die
	Anwendungsklasse CThellierToolApp.

ThellierTool.cpp
    Hierbei handelt es sich um die Haupt-Quellcodedatei der Anwendung. Diese enth�lt die
    Anwendungsklasse CThellierToolApp.

ThellierTool.rc
	Hierbei handelt es sich um eine Auflistung aller Ressourcen von Microsoft Windows, die 
	vom Programm verwendet werden. Sie enth�lt die Symbole, Bitmaps und Cursors, die im 
	Unterverzeichnis RES abgelegt sind. Diese Datei l�sst sich direkt in Microsoft
	Visual C++ bearbeiten.

ThellierTool.clw
    Diese Datei enth�lt Informationen, die vom Klassen-Assistenten verwendet wird, um bestehende
    Klassen zu bearbeiten oder neue hinzuzuf�gen.  Der Klassen-Assistent verwendet diese Datei auch,
    um Informationen zu speichern, die zum Erstellen und Bearbeiten von Nachrichtentabellen und
    Dialogdatentabellen ben�tigt werden und um Prototyp-Member-Funktionen zu erstellen.

res\ThellierTool.ico
    Dies ist eine Symboldatei, die als Symbol f�r die Anwendung verwendet wird. Dieses 
	Symbol wird durch die Haupt-Ressourcendatei ThellierTool.rc eingebunden.

res\ThellierTool.rc2
    Diese Datei enth�lt Ressourcen, die nicht von Microsoft Visual C++ bearbeitet wurden.
	In diese Datei werden alle Ressourcen abgelegt, die vom Ressourcen-Editor nicht bearbeitet 
	werden k�nnen.

ThellierTool.reg
    	Dies ist eine .REG-Beispieldatei, die Ihnen anzeigt, welche Registrierungseinstellungen 
	durch die Programmumgebung festlegt werden. Diese k�nnen Sie als .REG-
    	-Datei f�r Ihre Anwendung festlegen, oder diese l�schen und die Standardregistrierung 
	RegisterShellFileTypes verwenden.

ThellierTool.odl
    Diese Datei enth�lt den Quellcode der Object Description Language (ODL) f�r die
    Typbibliothek Ihrer Anwendung.


/////////////////////////////////////////////////////////////////////////////

F�r das Hauptfenster:

MainFrm.h, MainFrm.cpp
    	Diese Dateien enthalten die Frame-Klasse CMainFrame, die von
    	CMDIFrameWnd abgeleitet wurde und alle MDI-Frame-Merkmale steuert.

res\Toolbar.bmp
    Diese Bitmap-Datei wird zum Erstellen unterteilter Bilder f�r die Symbolleiste verwendet.
    Die erste Symbol- und Statusleiste wird in der Klasse CMainFrame erstellt.
    Bearbeiten Sie diese Bitmap der Symbolleiste mit dem Ressourcen-Editor, und
    aktualisieren Sie IDR_MAINFRAME TOOLBAR in ThellierTool.rc, um Schaltfl�chen f�r die
    Symbolleiste hinzuzuf�gen.

res\IToolbar.bmp
	Mit dieser Bitmap-Datei werden nebeneinander angeordnete Bilder f�r 
	die Symbolleiste erstellt, wenn die Server-Anwendung innerhalb eines
	anderen Containers "vor Ort" aktiviert wird. Die Symbolleiste wird
	in der Klasse CInPlaceFrame konstruiert. Diese Bitmap ist der Bitmap in 
	res\Toolbar.bmp �hnlich, jedoch fehlen verschiedene Nicht-Server-Befehle.

/////////////////////////////////////////////////////////////////////////////

F�r das untergeordnete Rahmenfenster:

ChildFrm.h, ChildFrm.cpp
    Diese Dateien definieren und implementieren die Klasse CChildFrame, die
    die untergeordneten Fenster in einer MDI-Anwendung unterst�tzt.

/////////////////////////////////////////////////////////////////////////////

Der Klassen-Assistent erstellt einen Dokumenttyp und eine Ansicht(View):

ThellierToolDoc.h, ThellierToolDoc.cpp - das Dokument
    	Diese Dateien enthalten die Klasse CThellierToolDoc. Bearbeiten Sie diese Dateien,
  	um Ihre speziellen Dokumentdaten hinzuzuf�gen und das Speichern und Laden von 
	Dateien zu implementieren (mit Hilfe von CThellierToolDoc::Serialize).

ThellierToolView.h, ThellierToolView.cpp - die Ansicht des Dokuments
    	Diese Dateien enthalten die Klasse CThellierToolView.
    	CThellierToolView-Objekte werden verwendet, um CThellierToolDoc-Objekte anzuzeigen.

res\ThellierToolDoc.ico
    	Dies ist eine Symboldatei, die als Symbol f�r untergeordnete MDI-Fenster 
	der Klasse CThellierToolDoc verwendet wird. Dieses Symbol wird durch die
	Haupt-Ressourcendatei ThellierTool.rc eingebunden.

/////////////////////////////////////////////////////////////////////////////

Dar�ber hinaus hat der Klassen-Assistent OLE-spezifische Klassen erzeugt.

SrvrItem.h, SrvrItem.cpp - diese Klasse dient der Verbindung
	der Klasse CThellierToolDoc mit dem OLE-System und stellt auf Wunsch eine 
	Verkn�pfung zu Ihrem Dokument zur Verf�gung.
IpFrame.h, IpFrame.cpp - diese Klasse ist abgeleitet
	von COleIPFrameWnd und steuert alle Rahmenmerkmale w�hrend der Vor-Ort-
	Aktivierung.

/////////////////////////////////////////////////////////////////////////////
Andere Standarddateien:

StdAfx.h, StdAfx.cpp
    	Mit diesen Dateien werden vorkompilierte Header-Dateien (PCH) mit der Bezeichnung 
	ThellierTool.pch und eine vorkompilierte Typdatei mit der Bezeichnung StdAfx.obj
	erstellt.

Resource.h
    	Dies ist die Standard-Header-Datei, die neue Ressourcen-IDs definiert.
    	Microsoft Visual C++ liest und aktualisiert diese Datei.

/////////////////////////////////////////////////////////////////////////////
Weitere Hinweise:

Der Klassen-Assistent f�gt "ZU ERLEDIGEN:" im Quellcode ein, um die Stellen anzuzeigen, 
an denen Sie Erweiterungen oder Anpassungen vornehmen k�nnen.

Wenn Ihre Anwendung die MFC in einer gemeinsam genutzten DLL verwendet und Ihre Anwendung
eine andere als die aktuell auf dem Betriebssystem eingestellte Sprache verwendet, muss 
die entsprechend lokalisierte Ressource MFC42XXX.DLL von der Microsoft Visual C++ CD-ROM 
in das Verzeichnis system oder system32 kopiert und in MFCLOC.DLL umbenannt werden ("XXX" 
steht f�r die Abk�rzung der Sprache. So enth�lt beispielsweise MFC42DEU.DLL die ins Deutsche 
�bersetzten Ressourcen). Anderenfalls erscheinen einige Oberfl�chenelemente Ihrer Anwendung 
in der Sprache des Betriebssystems.

/////////////////////////////////////////////////////////////////////////////
