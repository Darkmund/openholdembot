//***************************************************************************** 
//
// This file is part of the OpenHoldem project
//   Download page:         http://code.google.com/p/openholdembot/
//   Forums:                http://www.maxinmontreal.com/forums/index.php
//   Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//***************************************************************************** 
//
// Purpose: Scraping the poker-table and providing access to the scraped data.
//  As the CScraper is low-level and quite large we created 
//  a interface SCraperAccess that provides higher-level accessors
//  like "UserHasCards()".
//  Better use that interface to access scraper-data whenever possible.
//
//***************************************************************************** 

#ifndef INC_CSCRAPER_H
#define INC_CSCRAPER_H

#include "../../CTransform/hash/stdint.h"
#include "../CTablemap/CTablemap.h"
#include "MagicNumbers.h"
#include "NumericalFunctions.h"

struct SLimitInfo
{
	double	sblind;
	double	bblind;
	double	bbet;
	double	ante;
	int		limit;
	// Handnumber should be a string, as
	//   * it may contain characters
	//   * its lengths my exceed the precision of double
	bool istournament;
	CString	handnumber;
	double	sb_bb;
	double	bb_BB;

	bool	found_sblind;
	bool	found_bblind;
	bool	found_bbet;
	bool	found_ante;
	bool	found_limit;
	bool	found_handnumber;
	bool	found_sb_bb;
	bool	found_bb_BB;
};


extern class CScraper 
{
friend class CLazyScraper;

public:
	// public functions
	CScraper(void);
	~CScraper(void);
public:
	// public accessors
	const char*			title()                    { return _title; }
	const unsigned int	card_common(int n)         { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, (k_number_of_community_cards-1), CARD_NOCARD) return _card_common[n]; }
	const unsigned int	card_player(int p, int c)  { RETURN_DEFAULT_IF_OUT_OF_RANGE(p, k_last_chair, CARD_NOCARD) RETURN_DEFAULT_IF_OUT_OF_RANGE(c, (k_number_of_cards_per_player-1), CARD_NOCARD) return _card_player[p][c]; }
	const CString		seated(int n)              { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, k_last_chair, "false") return _seated[n]; }
	const CString		active(int n)              { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, k_last_chair, "false") return _active[n]; }
	const bool			dealer(int n)              { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, k_last_chair, false)   return _dealer[n]; }
	const double		player_bet(int n)          { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, k_last_chair, 0.0)     return _player_bet[n]; }
	const CString		player_name(int n)         { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, k_last_chair, "")      return _player_name[n]; }
	const bool			name_good_scrape(int n)    { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, k_last_chair, false)   return _name_good_scrape[n]; }
	const double		player_balance(int n);
	const double		balance_good_scrape(int n) { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, k_last_chair, 0.0)     return _balance_good_scrape[n]; }
	const bool			sitting_out(int n)         { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, k_last_chair, false)   return _sitting_out[n]; }
	const double		pot(int n)                 { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, k_last_chair, 0.0)     return _pot[n]; }
	const CString		button_state(int n)        { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, k_last_chair, "")      return _button_state[n]; }
public:	
	CString		i86_button_state()         { return _i86_button_state; }
	CString		i86X_button_state(int n)   { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, (k_max_number_of_i86X_buttons-1), "") return _i86X_button_state[n]; }
	CString		betpot_button_state(int n) { RETURN_DEFAULT_IF_OUT_OF_RANGE(n, (k_max_betpot_buttons-1), "")         return _betpot_button_state[n]; }
protected:
	void ScrapeDealer();
	void ScrapeActionButtons();
	void ScrapeActionButtonLabels();
	void ScrapeInterfaceButtons();
	void ScrapeBetpotButtons();
	void ClearAllPlayerNames();
	void ScrapeName(const int chair);
	void ScrapePlayerCards(int chair);
	void ScrapeSlider();
	void ScrapeCommonCards();
	void ScrapeSeatedActive();
	void ScrapeBetsBalances();
	void ScrapeAllPlayerCards();
private:
	void ScrapeSeated(int chair);
	
	void ScrapeActive(int chair);
	int ScrapeCard(CString name);
private:
	int CardString2CardNumber(CString card);
protected:
	
private:
	bool ProcessRegion(RMapCI r_iter);
	bool EvaluateRegion(CString name, CString *result);
	bool IsExtendedNumberic(CString text);
	CString ProcessBalanceNumbersOnly(CString balance_and_or_potential_text);
private:
	void SetButtonState(CString *button_state, CString text);
private:
	

	// Private data -- buttons
private:
	CString _i86_button_state;
	CString	_i86X_button_state[k_max_number_of_i86X_buttons];
	CString	_button_state[k_max_number_of_buttons];
	CString _button_label[k_max_number_of_buttons];
	CString	_betpot_button_state[k_max_betpot_buttons];






public:
	void ClearScrapeAreas(void);
	void CreateBitmaps(void);
	void DeleteBitmaps(void);
	void SetLimitInfo(const SLimitInfo LI);
	bool GetButtonState(const int button_index);
	bool GetButtonState(CString button_state_as_string);
	bool IsCommonAnimation();

	void CompleteBasicScrapeToFullScrape();
	
	const CString		button_label(int n) { if (n>=0 && n<=9) return _button_label[n]; else return ""; }
	const bool			handle_found_at_xy() { return _handle_found_at_xy; }
	const POINT			handle_xy() { return _handle_xy; }
	const SLimitInfo*	s_limit_info() { return &_s_limit_info; }
	const HBITMAP		entire_window_cur() { return _entire_window_cur; }

public:
#define ENT CSLock lock(m_critsec);
	// public mutators 
	// Used mainly by the scraper override dll to push their updates into the CScraper structures
	void	set_title(const char *s) { ENT strncpy_s(_title, MAX_WINDOW_TITLE, s, MAX_WINDOW_TITLE);}
	void	set_card_common(const int n, const unsigned int c) { ENT if (n>=0 && n<=4) _card_common[n] = c;}
	void	set_card_player(const int s, const int n, const unsigned int c) { ENT if (s>=0 && s<=9 && n>=0 && n<=1) _card_player[s][n] = c;}
	void	set_seated(const int n, CString s) { ENT if (n>=0 && n<=9) _seated[n] = s;}
	void	set_active(const int n, CString s) { ENT if (n>=0 && n<=9) _active[n] = s;}
	void	set_dealer(const int n, const bool b) { ENT if (n>=0 && n<=9) _dealer[n] = b;}
	void	set_player_bet(const int n, const double d) { ENT if (n>=0 && n<=9) _player_bet[n] = d;}
	void	set_player_name(const int n, const CString s) { ENT if (n>=0 && n<=9) _player_name[n] = s;}
	void	set_name_good_scrape(const int n, const bool b) { ENT if (n>=0 && n<=9) _name_good_scrape[n] = b;}
	void	set_player_balance(const int n, const double d) { ENT if (n>=0 && n<=9) _player_balance[n] = d;}
	void	set_balance_good_scrape(const int n, const bool b) { ENT if (n>=0 && n<=9) _balance_good_scrape[n] = b;}
	void	set_sitting_out(const int n, const bool b) { ENT if (n>=0 && n<=9) _sitting_out[n] = b;}
	void	set_pot(const int n, const double d) { ENT if (n>=0 && n<=9) _pot[n] = d;}
	void	set_button_state(const int n, const CString s) { ENT if (n>=0 && n<=9) _button_state[n] = s;}
	void	set_i86X_button_state(const int n, const CString s) { ENT if (n>=0 && n<=9) _i86X_button_state[n] = s;}
	void	set_i86_button_state(const CString s) { ENT _i86_button_state = s;}
	void	set_button_label(const int n, const CString s) { ENT if (n>=0 && n<=9) _button_label[n] = s;}
	void	set_sblind(const double d) { ENT _s_limit_info.sblind = d;}
	void	set_bblind(const double d) { ENT _s_limit_info.bblind = d;}
	void	set_bbet(const double d) { ENT _s_limit_info.bbet = d;}
	void	set_ante(const double d) { ENT _s_limit_info.ante = d;}
	void	set_limit(const int i) { ENT _s_limit_info.limit = i;}
	void	set_istournament(const bool b) { ENT _s_limit_info.istournament = b; }
	void	set_handnumber(const CString s) { ENT _s_limit_info.handnumber = s;}
	void	set_sb_bb(const double d) { ENT _s_limit_info.sb_bb = d;}
	void	set_bb_BB(const double d) { ENT _s_limit_info.bb_BB = d;}
	void	set_found_sblind(const bool b) { ENT _s_limit_info.found_sblind = b;}
	void	set_found_bblind(const bool b) { ENT _s_limit_info.found_bblind = b;}
	void	set_found_bbet(const bool b) { ENT _s_limit_info.found_bbet = b;}
	void	set_found_ante(const bool b) { ENT _s_limit_info.found_ante = b;}
	void	set_found_limit(const bool b) { ENT _s_limit_info.found_limit = b;}
	void	set_found_handnumber(const bool b) { ENT _s_limit_info.found_handnumber = b;}
	void	set_found_sb_bb(const bool b) { ENT _s_limit_info.found_sb_bb = b;}
	void	set_found_bb_BB(const bool b) { ENT _s_limit_info.found_bb_BB = b;}
	void	set_handle_found_at_xy(const bool b) { ENT _handle_found_at_xy = b;}
	void	set_handle_xy(const POINT p) { ENT _handle_xy.x = p.x; _handle_xy.y = p.y;}
	void	set_entire_window_cur(const HBITMAP h) { ENT _entire_window_cur = h;}
	void	delete_entire_window_cur() { ENT DeleteObject(_entire_window_cur);}
#undef ENT
	
private:
	// private variables - use public accessors and public mutators to address these
	char				_title[MAX_WINDOW_TITLE];

	// common cards
	unsigned int		_card_common[k_number_of_community_cards];
	// player cards
	unsigned int		_card_player[k_max_number_of_players][k_number_of_cards_per_player];
	// dealer
	bool				_dealer[k_max_number_of_players];

	// players - sitting out
	bool				_sitting_out[k_max_number_of_players];
	// players - seated / active
	CString				_seated[k_max_number_of_players], _active[k_max_number_of_players];
	// players - names
	bool				_name_good_scrape[k_max_number_of_players];
	CString				_player_name[k_max_number_of_players];
	// players - money
	double				_player_balance[k_max_number_of_players], _player_bet[k_max_number_of_players];
	bool				_balance_good_scrape[k_max_number_of_players];

	// pot
	double				_pot[k_max_number_of_pots];


	
	// handle
	bool				_handle_found_at_xy;
	POINT				_handle_xy;

	// limit
	SLimitInfo			_s_limit_info;
	// misc
	HBITMAP				_entire_window_cur;

private:
	// private functions and variables - not available via accessors or mutators
	
	
	
	void ScrapeBalance(const int chair);
	void ScrapeBet(const int chair);
	void ScrapePots();
	void ScrapeLimits();
	const CString extractHandnumFromString(const CString t);
	const double DoChipScrape(RMapCI r_iter);



	// cards common
	unsigned int	_card_common_last[k_number_of_community_cards];
	// cards player
	unsigned int	_card_player_last[k_max_number_of_players][k_number_of_cards_per_player];

	// dealer
	bool			_dealer_last[k_max_number_of_players];

	// player - seated, active
	CString			_seated_last[k_max_number_of_players], _active_last[k_max_number_of_players];
	// player - name
	CString			_name_last[k_max_number_of_players];
	// player - money
	double			_balance_last[k_max_number_of_players], _playerbet_last[k_max_number_of_players];

	// iXbuttons
	CString			_button_state_last[k_max_number_of_buttons], _button_label_last[k_max_number_of_buttons];
	// i86Xbuttons
	CString			_i86X_button_state_last[k_max_number_of_i86X_buttons], _i86_button_state_last;
	// betpot_buttons
	CString			_betpot_button_state_last[k_max_betpot_buttons];

	// pot
	double			_pot_last[k_max_number_of_pots];

	// limits
	bool			_istournament_last;
	int				_limit_last;
	double			_sblind_last, _bblind_last, _sb_bb_last, _bb_BB_last, _bbet_last, _ante_last;

	// misc
	CString			_handnumber_last;
	char			_title_last[MAX_WINDOW_TITLE];
	int				_scrape_something_changed;
	HBITMAP			_entire_window_last;

	CCritSec		m_critsec;

} *p_scraper;

#endif // INC_CSCRAPER_H