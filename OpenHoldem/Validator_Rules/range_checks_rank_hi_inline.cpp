//
// Rank hi
//

BEGIN_TESTCASE
    TESTCASE_ID ("0164")
    HEURISTIC_RULE (false)
    REASONING ("Range check for symbol rankhi")
    PRECONDITION (true)
    POSTCONDITION (((gws("rankhi") >= 2) && (gws("rankhi") <= 14)) || (gws("rankhi") == UNDEFINED_ZERO))
    SYMBOLS_POSSIBLY_AFFECTED ("rankhi")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0165")
    HEURISTIC_RULE (false)
    REASONING ("Range check for symbol rankhicommon")
    PRECONDITION (true)
    POSTCONDITION (((gws("rankhicommon") >= 2) && (gws("rankhicommon") <= 14)) || (gws("rankhicommon") == UNDEFINED_ZERO))
    SYMBOLS_POSSIBLY_AFFECTED ("rankhicommon")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0166")
    HEURISTIC_RULE (false)
    REASONING ("Range check for symbol rankhiplayer")
    PRECONDITION (true)
    POSTCONDITION (((gws("rankhiplayer") >= 2) && (gws("rankhiplayer") <= 14)) || (gws("rankhiplayer") == UNDEFINED_ZERO))
    SYMBOLS_POSSIBLY_AFFECTED ("rankhiplayer")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0167")
    HEURISTIC_RULE (false)
    REASONING ("Range check for symbol rankhipoker")
    PRECONDITION (true)
    POSTCONDITION (((gws("rankhipoker") >= 2) && (gws("rankhipoker") <= 14)) || (gws("rankhipoker") == UNDEFINED_ZERO))
    SYMBOLS_POSSIBLY_AFFECTED ("rankhipoker")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0168")
    HEURISTIC_RULE (false)
    REASONING ("Range check for symbol srankhi")
    PRECONDITION (true)
    POSTCONDITION (((gws("srankhi") >= 2) && (gws("srankhi") <= 14)) || (gws("srankhi") == UNDEFINED_ZERO))
    SYMBOLS_POSSIBLY_AFFECTED ("srankhi")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0169")
    HEURISTIC_RULE (false)
    REASONING ("Range check for symbol srankhicommon")
    PRECONDITION (true)
    POSTCONDITION (((gws("srankhicommon") >= 2) && (gws("srankhicommon") <= 14)) || (gws("srankhicommon") == UNDEFINED_ZERO))
    SYMBOLS_POSSIBLY_AFFECTED ("srankhicommon")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0170")
    HEURISTIC_RULE (false)
    REASONING ("Range check for symbol srankhiplayer")
    PRECONDITION (true)
    POSTCONDITION (((gws("srankhiplayer") >= 2) && (gws("srankhiplayer") <= 14)) || (gws("srankhiplayer") == UNDEFINED_ZERO))
    SYMBOLS_POSSIBLY_AFFECTED ("srankhiplayer")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0171")
    HEURISTIC_RULE (false)
    REASONING ("Range check for symbol srankhipoker")
    PRECONDITION (true)
    POSTCONDITION (((gws("srankhipoker") >= 2) && (gws("srankhipoker") <= 14)) || (gws("srankhipoker") == UNDEFINED_ZERO))
    SYMBOLS_POSSIBLY_AFFECTED ("srankhipoker")
END_TESTCASE