#include "stdafx.h"

#include <afxwin.h>
//#include <process.h>
//#include <windows.h>
//#include <WinUser.h>

#include "CAutoConnector.h"
#include "CAutoplayer.h"
#include "CFormula.h"
#include "CHeartbeatThread.h"
#include "CIteratorThread.h"
#include "CPokerTrackerThread.h"
#include "CPreferences.h"
#include "CScraper.h"
#include "CSharedMem.h"
#include "CSymbols.h"
#include "..\CTablemap\CTablemap.h"
#include "..\CTransform\CTransform.h"
#include "DialogScraperOutput.h"
#include "DialogSelectTable.h"
#include "MainFrm.h"
#include "OpenHoldem.h"

const int k_MaxNumberOfTableMaps = 25;

CAutoConnector						*p_autoconnector = NULL;
CArray <STableList, STableList>		g_tlist; 
t_TablemapConnectionData			TablemapConnectionData[k_MaxNumberOfTableMaps];


void CTableMapToSWholeMap(CTablemap *cmap, SWholeMap *smap)
{
	write_log(3, "CTableMapToSWholeMap: %s", p_tablemap->filepath());
	//MessageBox(0, "CTableMapToSWholeMap", "Debug", 0);
	smap->z$ = p_tablemap->z$();
	smap->s$ = p_tablemap->s$();
	smap->r$ = p_tablemap->r$();
	for (int i=0; i<=3; i++)
	{
		smap->t$[i] = p_tablemap->t$(i);
		smap->p$[i] = p_tablemap->p$(i);
		smap->h$[i] = p_tablemap->h$(i);
	}
	smap->i$ = p_tablemap->i$();
	smap->filepath = p_tablemap->filepath();
}



CAutoConnector::CAutoConnector()
{
	write_log(3, "CAutoConnector::CAutoConnector()");
	//MessageBox(0, "CAutoConnector::CAutoConnector()", "Debug", 0);

	p_sharedmem->MarkPokerWindowAsUnAttached();
	set_attached_hwnd(NULL);
	TablemapsInScraperFolderAlreadyParsed = false;
	NumberOfTableMapsLoaded = 0;
}


CAutoConnector::~CAutoConnector()
{
	write_log(3, "CAutoConnector::~CAutoConnector()");
	//MessageBox(0, "CAutoConnector::~CAutoConnector()", "Debug", 0);
	p_sharedmem->MarkPokerWindowAsUnAttached();
	set_attached_hwnd(NULL);
}


bool CAutoConnector::IsConnected()
{
	return ((_attached_hwnd != NULL) && IsWindow(_attached_hwnd));
}


void CAutoConnector::ParseAllOpenScrapeOrWinScrapeTableMapsToLoadConnectionData(CString TableMapWildcard)
{
	CFileFind	hFile;
	SWholeMap	smap;
	int			line = 0;

	write_log(3, "ParseAllOpenScrapeOrWinScrapeTableMapsToLoadConnectionData: %s", TableMapWildcard);
	//MessageBox(0, "ParseAllOpenScrapeOrWinScrapeTableMapsToLoadConnectionData", "Debug", 0);
	CString	current_path = p_tablemap->filepath();
	BOOL bFound = hFile.FindFile(TableMapWildcard.GetString());
	while (bFound)
	{
		if (NumberOfTableMapsLoaded >= k_MaxNumberOfTableMaps)
		{
			// TODO!!! Error!	
			return;
		}
		bFound = hFile.FindNextFile();
		if (!hFile.IsDots() && !hFile.IsDirectory() && hFile.GetFilePath()!=current_path)
		{
			int ret = p_tablemap->LoadTablemap((char *) hFile.GetFilePath().GetString(), VER_OPENSCRAPE_2, false, &line, prefs.disable_msgbox());
			if (ret == SUCCESS)
			{
				// TODO!!! build it!
				CTableMapToSWholeMap(p_tablemap, &smap);
				//MessageBox(0, hFile.GetFilePath().GetString(), "Loading TM", 0); //!!!
				ExtractConnectionDataFromCurrentTablemap(&smap);
				NumberOfTableMapsLoaded++;
			}
		}
	}
}


void CAutoConnector::ParseAllTableMapsToLoadConnectionData()
{
	CString TableMapWildcard;
	
	write_log(3, "ParseAllTableMapsToLoadConnectionData");
	//MessageBox(0, "ParseAllTableMapsToLoadConnectionData", "Debug", 0);
	TableMapWildcard.Format("%s\\scraper\\*.tm", _startup_path);
	ParseAllOpenScrapeOrWinScrapeTableMapsToLoadConnectionData(TableMapWildcard);	
	TableMapWildcard.Format("%s\\scraper\\*.ws", _startup_path);
	ParseAllOpenScrapeOrWinScrapeTableMapsToLoadConnectionData(TableMapWildcard);
	TablemapsInScraperFolderAlreadyParsed = true;
}


void CAutoConnector::ExtractConnectionDataFromCurrentTablemap(SWholeMap *map)
{
	CString s;
	
	write_log(3, "CAutoConnector::ExtractConnectionDataFromCurrentTablemap(): %s", map->filepath);
	//MessageBox(0, "CAutoConnector::ExtractConnectionDataFromCurrentTablemap()", "Debug", 0);

	TablemapConnectionData[NumberOfTableMapsLoaded].FilePath = map->filepath;
	// Extract client size information
	ZMapCI z_iter = map->z$->end();
	z_iter = map->z$->find("clientsize");
	if (z_iter != map->z$->end())
	{
		TablemapConnectionData[NumberOfTableMapsLoaded].ClientSizeX = z_iter->second.width;
		TablemapConnectionData[NumberOfTableMapsLoaded].ClientSizeY = z_iter->second.height;
	}
	z_iter = map->z$->find("clientsizemin");
	if (z_iter != map->z$->end())
	{
		TablemapConnectionData[NumberOfTableMapsLoaded].ClientSizeMinX = z_iter->second.width;
		TablemapConnectionData[NumberOfTableMapsLoaded].ClientSizeMinY = z_iter->second.height;
	}
	z_iter = map->z$->find("clientsizemax");
	if (z_iter != map->z$->end())
	{
		TablemapConnectionData[NumberOfTableMapsLoaded].ClientSizeMaxX = z_iter->second.width;
		TablemapConnectionData[NumberOfTableMapsLoaded].ClientSizeMaxY = z_iter->second.height;
	}

	// Extract title text information
	SMapCI s_iter = map->s$->end();
	s_iter = map->s$->find("titletext");
	if (s_iter!=map->s$->end())
		TablemapConnectionData[NumberOfTableMapsLoaded].TitleText =	s_iter->second.text;
			
	for (int i=0; i<=9; i++)
	{
		s.Format("titletext%d", i);
		s_iter = map->s$->find(s.GetString());
		if (s_iter!=map->s$->end())
			TablemapConnectionData[NumberOfTableMapsLoaded].TitleText_0_9[i] =	s_iter->second.text;
	}

	// Extract negative title texs
	s_iter = map->s$->find("!titletext");
	if (s_iter!=map->s$->end())
		TablemapConnectionData[NumberOfTableMapsLoaded].NegativeTitleText = s_iter->second.text;
	
	for (int i=0; i<=9; i++)
	{
		s.Format("!titletext%d", i);
		s_iter = map->s$->find(s.GetString());
		if (s_iter!=map->s$->end())
			TablemapConnectionData[NumberOfTableMapsLoaded].NegativeTitleText_0_9[i] = s_iter->second.text;
	}

	// Extract the tablepoint
	for (RMapCI r_iter=map->r$->begin(); r_iter!=map->r$->end(); r_iter++)
	{
		if (r_iter->second.name.Find("tablepoint") != -1 &&
			r_iter->second.right - r_iter->second.left == 1 &&
			r_iter->second.bottom - r_iter->second.top == 1 &&
			r_iter->second.transform == "C")
		{
			TablemapConnectionData[NumberOfTableMapsLoaded].TablePoint.bottom = r_iter->second.bottom;
			TablemapConnectionData[NumberOfTableMapsLoaded].TablePoint.top = r_iter->second.top;
			TablemapConnectionData[NumberOfTableMapsLoaded].TablePoint.left = r_iter->second.left;
			TablemapConnectionData[NumberOfTableMapsLoaded].TablePoint.right = r_iter->second.right;
			TablemapConnectionData[NumberOfTableMapsLoaded].TablePoint.transform = r_iter->second.transform;
			TablemapConnectionData[NumberOfTableMapsLoaded].TablePoint.color = r_iter->second.color;
			TablemapConnectionData[NumberOfTableMapsLoaded].TablePoint.radius = r_iter->second.radius;
			// We don't need the rest of the regions data for a tablepoint with colour transform
		}
	}
}


// TODO? Move to CTablemap? // TODO !!! Rewrite for reconnector!
void CAutoConnector::Check_TM_Against_All_Windows(SWholeMap smap, HWND targetHWnd)
{
	write_log(3, "CAutoConnector::Check_TM_Against_All_Windows(..)");
	//MessageBox(0, "CAutoConnector::Check_TM_Against_All_Windows(..)", "Debug", 0);

	CTableMapToSWholeMap(p_tablemap, &smap); // !!! ToDo: remove param?
	if (targetHWnd == NULL)
		EnumWindows(EnumProcTopLevelWindowList, (LPARAM) &smap);
	else
		EnumProcTopLevelWindowList(targetHWnd, (LPARAM) &smap);
}

// TODO? Move to CTablemap?
// This function has to be global and can't be part of the class,
// as it has to be called by the callback-function 
// BOOL CALLBACK EnumProcTopLevelWindowList(HWND hwnd, LPARAM lparam) 
bool Check_TM_Against_Single_Window(int MapIndex, HWND h, RECT r, CString title) 
{
	bool			good_size = false, good_pos_title = false, good_neg_title = false, good_table_points = false;
	int				width = 0, height = 0, x = 0, y = 0;
	HDC				hdcScreen = NULL, hdcCompatible = NULL;
	HBITMAP			hbmScreen = NULL, hOldScreenBitmap = NULL;
	BYTE			*pBits = NULL, alpha = 0, red = 0, green = 0, blue = 0;
	//int				exact_width = 0, exact_height = 0, min_width = 0, min_height = 0, max_width = 0, max_height = 0;
	CTransform		trans;
	CString			s;

	write_log(3, "CAutoConnector::Check_TM_Against_Single_Window(..)");
	//MessageBox(0, "CAutoConnector::Check_TM_Against_Single_Window(..)", "Debug", 0);
	
	// Check for exact match on client size
	good_size = false;
	if (r.right == TablemapConnectionData[MapIndex].ClientSizeX 
		&& r.bottom == TablemapConnectionData[MapIndex].ClientSizeY)
	{
		good_size = true;
	}

	// Check for client size that falls within min/max
	if (TablemapConnectionData[MapIndex].ClientSizeMinX != 0 
		&& TablemapConnectionData[MapIndex].ClientSizeMinY != 0 
		&& TablemapConnectionData[MapIndex].ClientSizeMaxX != 0 
		&& TablemapConnectionData[MapIndex].ClientSizeMaxY != 0 
		&& r.right  >= (int) TablemapConnectionData[MapIndex].ClientSizeMinX
		&& r.right  <= (int) TablemapConnectionData[MapIndex].ClientSizeMinY
		&& r.bottom >= (int) TablemapConnectionData[MapIndex].ClientSizeMaxX
		&& r.bottom <= (int) TablemapConnectionData[MapIndex].ClientSizeMaxY)
	{
		good_size = true;
	}

	if (!good_size)
	{
		write_log(3, "bad size.");
		//MessageBox(0, "bad size", "Debug", 0);
		return false;
	}
	// Check title text for match
	good_pos_title = false;

	if (title.Find(TablemapConnectionData[MapIndex].TitleText)!=-1)
		good_pos_title = true;
	
	for (int i=0; i<=9; i++)
	{
		if (title.Find(TablemapConnectionData[MapIndex].TitleText_0_9[i])!=-1)
			good_pos_title = true;
	}

	if (!good_pos_title)
	{
		write_log(3, "no good title.");
		//MessageBox(0, "no good title", "Debug", 0);
		return false;
	}

	// Check for no negative title text matches
	good_neg_title = false;

	if (title.Find(TablemapConnectionData[MapIndex].NegativeTitleText)!=-1)
		good_neg_title = true;

	for (int i=0; i<=9; i++)
	{
		if (title.Find(TablemapConnectionData[MapIndex].NegativeTitleText_0_9[i])!=-1)
			good_neg_title = true;
	}

	if (good_neg_title)
	{
		write_log(3, "negative title."); 
		//MessageBox(0, "negative title", "Debug", 0);
		return false;
	}


	// Allocate heap space for BITMAPINFO
	BITMAPINFO	*bmi;
	int			info_len = sizeof(BITMAPINFOHEADER) + 1024;
	bmi = (BITMAPINFO *) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, info_len);

	// Check table points for match
	width = TablemapConnectionData[MapIndex].TablePoint.right - TablemapConnectionData[MapIndex].TablePoint.left;
	height = TablemapConnectionData[MapIndex].TablePoint.bottom - TablemapConnectionData[MapIndex].TablePoint.top;
	hdcScreen = GetDC(h);
	hdcCompatible = CreateCompatibleDC(hdcScreen);
	hbmScreen = CreateCompatibleBitmap(hdcScreen, width, height);
	hOldScreenBitmap = (HBITMAP) SelectObject(hdcCompatible, hbmScreen);
	BitBlt(hdcCompatible, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY);

	// Populate BITMAPINFOHEADER
	bmi->bmiHeader.biSize = sizeof(bmi->bmiHeader);
	bmi->bmiHeader.biBitCount = 0;
	GetDIBits(hdcCompatible, hbmScreen, 0, 0, NULL, bmi, DIB_RGB_COLORS);

	// Get the actual argb bit information
	bmi->bmiHeader.biHeight = -bmi->bmiHeader.biHeight;
	pBits = new BYTE[bmi->bmiHeader.biSizeImage];
	GetDIBits(hdcCompatible, hbmScreen, 0, height, pBits, bmi, DIB_RGB_COLORS);

	good_table_points = true;
	bool found = false;
	
	/*if (r_iter->second.name.Find("tablepoint") != -1 &&
		r_iter->second.right - r_iter->second.left == 1 &&
		r_iter->second.bottom - r_iter->second.top == 1 &&
		r_iter->second.transform == "C")*/
	{
		x = TablemapConnectionData[MapIndex].TablePoint.left;
		y = TablemapConnectionData[MapIndex].TablePoint.top;

		int pbits_loc = y*width*4 + x*4;
		alpha = pBits[pbits_loc + 3];
		red = pBits[pbits_loc + 2];
		green = pBits[pbits_loc + 1];
		blue = pBits[pbits_loc + 0];

		COLORREF Color = TablemapConnectionData[MapIndex].TablePoint.color; 
		// positive radius
		if (TablemapConnectionData[MapIndex].TablePoint.radius >= 0)
		{
			
			if (!trans.IsInARGBColorCube((Color>>24)&0xff, // function GetAValue() does not exist
										 GetRValue(Color),
										 GetGValue(Color),
										 GetBValue(Color),
										 TablemapConnectionData[MapIndex].TablePoint.radius,
										 alpha, red, green, blue))
			{
				good_table_points = false;
				found = true;
			}
		}
		// negative radius (logical not)
		else
		{
			if (trans.IsInARGBColorCube((Color>>24)&0xff, // function GetAValue() does not exist
										GetRValue(Color), 
										GetGValue(Color), 
										GetBValue(Color), 
										-TablemapConnectionData[MapIndex].TablePoint.radius,
										alpha, red, green, blue))
			{
				good_table_points = false;
				found = true;
			}
		}
	}

	// Clean up
	HeapFree(GetProcessHeap(), NULL, bmi);
	delete []pBits;
	SelectObject(hdcCompatible, hOldScreenBitmap);
	DeleteObject(hbmScreen);
	DeleteDC(hdcCompatible);
	ReleaseDC(h, hdcScreen);

	if (!good_table_points)
	{
		write_log(3, "bad tablepoint");
		//MessageBox(0, "bad tablepopints", "Debug", 0);
		return false;
	}

	write_log(3, "window ia a match");
	//MessageBox(0, "window is a match", "Debug", 0);
	return true;
}


BOOL CALLBACK EnumProcTopLevelWindowList(HWND hwnd, LPARAM lparam) 
{
	CString				title = "", winclass = "";
	char				text[512] = {0};
	RECT				crect = {0};
	STableList			tablelisthold;
	SWholeMap			*map = (SWholeMap *) (lparam);

	write_log(3, "EnumProcTopLevelWindowList(..)");
	//MessageBox(0, "EnumProcTopLevelWindowList(..)", "Debug", 0);
	// If this is not a top level window, then return
	if (GetParent(hwnd) != NULL)
		return true;

	// If this window is not visible, then return
	if (!IsWindowVisible(hwnd))
		return true;

	// If there is no caption on this window, then return
	GetWindowText(hwnd, text, sizeof(text));
	if (strlen(text)==0)
		return true;
 
	title = text;

	// Found a candidate window, get client area rect
	GetClientRect(hwnd, &crect);

	// See if it matches the currently loaded table map
	if (Check_TM_Against_Single_Window(/*map*/0, hwnd, crect, title)) //!!!
	{
		tablelisthold.hwnd = hwnd;
		tablelisthold.title = title;
		tablelisthold.path = map->filepath;
		tablelisthold.crect.left = crect.left;
		tablelisthold.crect.top = crect.top;
		tablelisthold.crect.right = crect.right;
		tablelisthold.crect.bottom = crect.bottom;
		g_tlist.Add(tablelisthold);
	}

	return true;  // keep processing through entire list of windows
}


bool CAutoConnector::Connect(HWND targetHWnd)
{
	int					i = 0, N = 0, line = 0, ret = 0;
	char				title[512] = {0};
	int					SelectedItem = -1;
	SWholeMap			smap;
	CString				path = "", current_path = "";
	BOOL				bFound = false;
	CFileFind			hFile;

	write_log(3, "CAutoConnector::Connect(..)");
	//MessageBox(0, "CAutoConnector::Connect(..)", "Debug", 0);
	if (!TablemapsInScraperFolderAlreadyParsed)
	{
		ParseAllTableMapsToLoadConnectionData();
	}

	// Clear global list for holding table candidates
	g_tlist.RemoveAll();

	// First check explicitly loaded/last used tablemap
	current_path = "";
	if (p_tablemap->valid())
	{
		Check_TM_Against_All_Windows(smap, targetHWnd);
		current_path = p_tablemap->filepath();
	}

	for (int i=0; i<NumberOfTableMapsLoaded; i++)
	{
		//ret = p_tablemap->LoadTablemap((char *) hFile.GetFilePath().GetString(), VER_OPENSCRAPE_2, false, &line, prefs.disable_msgbox());
		Check_TM_Against_All_Windows(smap, targetHWnd);
	}
	
	// Put global candidate table list in table select dialog variables
	N = (int) g_tlist.GetSize();
	if (N == 0) 
	{
		if (targetHWnd != NULL) {
			int cySize = GetSystemMetrics(SM_CYSIZE);
			int cyMenuSize = GetSystemMetrics(SM_CYMENU);

			if (!prefs.disable_msgbox())
			{
				if (cySize != 18 && cyMenuSize != 19)
					;/*MessageBox(0, "Cannot find table\n\n"
							   "It appears that your settings are not configured according to OpenHoldem specifications.\n"
							   "You must ensure that XP themes are not used (Use Windows Classic style) and\n"
							   "font size is set to normal.\n\n"
							   "For more info, look at the wiki documentation and the user forums", "Cannot find table", MB_OK);*/
				else
					;//MessageBox(0, "No valid tables found", "Cannot find table", MB_OK);
			}
		}
	}
	else 
	{
		{
			// Small extra code block to reduce the lifetime
			// of the protecting mutex to a minimum.
			// ENT; TODO!!!
			SelectedItem = SelectTableMapAndWindow(N);
			if (SelectedItem != -1)
			{
				p_sharedmem->MarkPokerWindowAsAttached(g_tlist[SelectedItem].hwnd);
			}
		}
		if (SelectedItem != -1)
		{
			// Load correct tablemap, and save hwnd/rect/numchairs of table that we are "attached" to
			set_attached_hwnd(g_tlist[SelectedItem].hwnd);
			CString loaded_version;
			p_tablemap->LoadTablemap((char *) g_tlist[SelectedItem].path.GetString(), VER_OPENSCRAPE_2, false, &line, 
									 prefs.disable_msgbox(), &loaded_version);

			if ( (loaded_version == VER_OPENSCRAPE_1 || loaded_version == VER_OPENHOLDEM_2) && !prefs.disable_msgbox())
			{
				;/*MessageBox(0, "You have loaded a version 1 table map for this poker table.\n\n"\
						   "Version 2.0.0 and higher of OpenHoldem use a new format (version 2).  This\n"\
						   "table map has been loaded, but it is highly unlikely to work correctly until\n"\
						   "it has been opened in OpenScrape version 2.0.0 or higher, and adjustments\n"\
						   "have been made to autoplayer settings and region sizes.\n\n"\
						   "Please do not use this table map prior to updating it to version 2 in\n"\
						   "OpenScrape or you run the very serious risk of costly mis-scrapes.",
						   "Table map load warning", MB_OK | MB_ICONEXCLAMATION);*/
			}

			// Create bitmaps
			p_scraper->CreateBitmaps();

			// Clear scraper fields
			p_scraper->ClearScrapeAreas();

			// Reset symbols
			p_symbols->ResetSymbolsFirstTime();

			// Reset "ScraperOutput" dialog, if it is live
			if (m_ScraperOutputDlg) 
			{
				m_ScraperOutputDlg->AddListboxItems();
				m_ScraperOutputDlg->UpdateDisplay();
			}

			// scraper.dll - failure in load is NOT fatal
			theApp.UnloadScraperDLL();
			CString filename = p_tablemap->scraperdll();
			if (!filename.IsEmpty()) {
				int index = p_tablemap->filepath().ReverseFind('\\');
				if (index > 0)
					path.Format("%s\\%s", p_tablemap->filepath().Left(index), filename);
				else
					path = filename;
				theApp._scraper_dll = LoadLibrary(path);
			}
			if (theApp._scraper_dll==NULL)
			{
				if (!filename.IsEmpty() && !prefs.disable_msgbox())		
				{
					CString		t = "";
					t.Format("Unable to load %s\n\nError: %d", path, GetLastError());
					//MessageBox(0, t, "OpenHoldem scraper.dll WARNING", MB_OK | MB_TOPMOST);
				}
			}
			else
			{
				theApp._dll_scraper_process_message = (scraper_process_message_t) GetProcAddress(theApp._scraper_dll, "ProcessMessage");
				theApp._dll_scraper_override = (scraper_override_t) GetProcAddress(theApp._scraper_dll, "OverrideScraper");

				if (theApp._dll_scraper_process_message==NULL || theApp._dll_scraper_override==NULL)
				{
					if (!prefs.disable_msgbox())		
					{
						CString		t = "";
						t.Format("Unable to find all symbols in scraper.dll");
						//MessageBox(0, t, "OpenHoldem scraper.dll ERROR", MB_OK | MB_TOPMOST);
					}

					theApp.UnloadScraperDLL();
				}
				else
				{
					if (!prefs.disable_msgbox())		
					{
					}
				}
			}

			CMainFrame		*pMyMainWnd  = (CMainFrame *) (theApp.m_pMainWnd);
			pMyMainWnd->DisableButtonsOnConnect();

			// Make sure autoplayer is off
			p_autoplayer->set_autoplayer_engaged(false);

			// mark symbol result cache as stale
			p_formula->MarkCacheStale();

			// reset iterator vars
			iter_vars.ResetVars();

			// Send "connect" and HWND to scraper DLL, if loaded
			if (theApp._dll_scraper_process_message)
				(theApp._dll_scraper_process_message) ("connect", &_attached_hwnd);

			// start heartbeat thread
			if (p_heartbeat_thread)
				delete p_heartbeat_thread;

			p_heartbeat_thread = new CHeartbeatThread;

			// Start timer that checks for continued existence of attached HWND
			pMyMainWnd->StartTimer();

			// Reset display
			pMyMainWnd->ResetDisplay();

			// Start logging
			start_log();

			if (targetHWnd == NULL) 
			{
				CWindowDC dc(NULL);
				int nBitsPerPixel = dc.GetDeviceCaps(PLANES) * dc.GetDeviceCaps(BITSPIXEL);

				if (nBitsPerPixel < 24 && !prefs.disable_msgbox())
					;/*MessageBox(0, "It appears that your Display settings are not configured according to OpenHoldem specifications.\n"
							   "24 bit color or higher is needed to reliably extract information from the poker client\n\n"
							   "For more info, look at the wiki documentation and the user forums", 
							   "Caution: Color Depth Too Low", MB_OK|MB_ICONWARNING);*/

				BOOL fontSmoothingEnabled = FALSE;
				SystemParametersInfo(SPI_GETFONTSMOOTHING, 0, (LPVOID)&fontSmoothingEnabled, 0);

				if (fontSmoothingEnabled && !prefs.disable_msgbox())
					;/*MessageBox(0, "It appears that font smoothing is enabled. In order for OpenHoldem to reliably\n"
							   "extract information from the poker client you should disable Font Smoothing", 
							   "Caution: Font smoothing is enabled", MB_OK|MB_ICONWARNING);*/
			}

			// log OH title bar text and table reset
			::GetWindowText(_attached_hwnd, title, 512);

			CString site="";
			SMapCI site_i = p_tablemap->s$()->find("sitename");
			if (site_i != p_tablemap->s$()->end())
				site = site_i->second.text;

			CString formula = p_formula->formula_name();

			write_log(1, "\n*************************************************************\n"
					  "TABLE RESET %s - %s(%s)\n"
					  "*************************************************************\n",
					  formula.GetString(), site.GetString(), title);

			CString sForceChair = p_tablemap->forcechair();
			if (!sForceChair.IsEmpty()) {
				int iForceChair = atoi(sForceChair);
				p_symbols->set_sym_chair(iForceChair);
				p_symbols->set_sym_userchair(iForceChair);
				p_symbols->set_user_chair_confirmed(true); 
			}
		}
	}
	return (SelectedItem != -1);
}


void CAutoConnector::Disconnect()
{
	write_log(3, "CAutoConnector::Disconnect()");
	//MessageBox(0, "CAutoConnector::Disconnect()", "Debug", 0);
	// stop threads
	if (p_heartbeat_thread)
	{
		delete p_heartbeat_thread;
		p_heartbeat_thread = NULL;
	}

	if (p_pokertracker_thread)
		p_pokertracker_thread->StopThread();

	// Make sure autoplayer is off
	p_autoplayer->set_autoplayer_engaged(false);

	// Send "disconnect" to scraper DLL, if loaded
	if (theApp._dll_scraper_process_message)
			(theApp._dll_scraper_process_message) ("disconnect", NULL);

	theApp.UnloadScraperDLL();

	// Clear "attached" info
	set_attached_hwnd(NULL);

	// Stop timer that checks for valid hwnd, then unattach OH.
	CMainFrame		*pMyMainWnd  = (CMainFrame *) (theApp.m_pMainWnd);
	pMyMainWnd->KillTimer();
	pMyMainWnd->UnattachOHFromPokerWindow();
	pMyMainWnd->EnableButtonsOnDisconnect();

	// Delete bitmaps
	p_scraper->DeleteBitmaps();

	// Clear scraper fields
	p_scraper->ClearScrapeAreas();

	// Reset symbols
	p_symbols->ResetSymbolsFirstTime();

	// Change window title
	pMyMainWnd->UpdateWindowTitle();

	// Reset Display 
	pMyMainWnd->ResetDisplay();

	// Reset "ScraperOutput" dialog, if it is live
	if (m_ScraperOutputDlg)
	{
		m_ScraperOutputDlg->AddListboxItems();
		m_ScraperOutputDlg->UpdateDisplay();
	}

	// log OH title bar text and table reset
	CString sitename = (p_tablemap->s$()->find("sitename") != p_tablemap->s$()->end() ? p_tablemap->s$()->find("sitename")->second.text.GetString() : "");
	write_log(1, "%s - %s(NOT ATTACHED)\n", p_formula->formula_name().GetString(), sitename);

	write_log(1, "TABLE RESET\n*************************************************************\n");

	// Stop logging
	stop_log();
	
	// Mark table as not attached
	p_sharedmem->MarkPokerWindowAsUnAttached();

	// Close OH, when table disappears and leaving enabled in preferences.
	if (prefs.autoconnector_close_when_table_disappears())
	{
		PostQuitMessage(0);
	}
}


int CAutoConnector::SelectTableMapAndWindow(int Choices)
{
	write_log(3, "CAutoConnector::SelectTableMapAndWindow(..)");
	if (prefs.autoconnector_connection_method() == k_AutoConnector_Connect_Manually)
	{
		return SelectTableMapAndWindowManually(Choices);
	}
	else // k_AutoConnector_Connect_Automatically
	{
		return SelectTableMapAndWindowAutomatically(Choices);
	}
}


int CAutoConnector::SelectTableMapAndWindowManually(int Choices)
{
	STableList			tablelisthold;
	CDlgSelectTable		cstd;
	int					result = 0;

	write_log(3, "CAutoConnector::SelectTableMapAndWindowManually(..)");
	if (Choices == 1) 
	{
		// First (and only) item selected
		return 0;
	}
	else if (Choices >= 2) 
	{
		for (int i=0; i<Choices; i++) 
		{
			tablelisthold.hwnd = g_tlist[i].hwnd;
			tablelisthold.title = g_tlist[i].title;
			tablelisthold.path = g_tlist[i].path;
			tablelisthold.crect.left = g_tlist[i].crect.left;
			tablelisthold.crect.top = g_tlist[i].crect.top;
			tablelisthold.crect.right = g_tlist[i].crect.right;
			tablelisthold.crect.bottom = g_tlist[i].crect.bottom;
			cstd.tlist.Add(tablelisthold);
		}

		// Display table select dialog
		result = cstd.DoModal();
		if (result == IDOK) 
		{
			return cstd.selected_item;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		// 0 (or even less) windows and TMs.
		return -1;
	}
}


int CAutoConnector::SelectTableMapAndWindowAutomatically(int Choices)
{
	write_log(3, "CAutoConnector::SelectTableMapAndWindowAutomatically(..)");
	for (int i=0; i<Choices; i++) 
	{
		if (!p_sharedmem->PokerWindowAttached(g_tlist[i].hwnd))
		{
			return i;
		}
	}
	// No appropriate table found
	return -1;
}

double CAutoConnector::TimeSinceLastFailedAttemptToConnect()
{
	time_t LastFailedAttemptToConnect = p_sharedmem->GetTimeOfLastFailedAttemptToConnect(); //???
	time_t CurrentTime;
	time(&CurrentTime);
	return difftime(CurrentTime, LastFailedAttemptToConnect);
}