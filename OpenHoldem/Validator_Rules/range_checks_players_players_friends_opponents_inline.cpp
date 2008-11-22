//
// Players, Friends, Opponents
//

BEGIN_TESTCASE
    TESTCASE_ID ("0087")
    REASONING ("Range check for symbol nopponentsmax")
    PRECONDITION (true)
    POSTCONDITION ((gws("nopponentsmax") >= 0) && (gws("nopponentsmax") <= 22))
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentsmax")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0088")
    REASONING ("Range check for symbol nplayersseated")
    PRECONDITION (true)
    POSTCONDITION ((gws("nplayersseated") >= 0) && (gws("nplayersseated") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nplayersseated")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0089")
    REASONING ("Range check for symbol nplayersseated")
    PRECONDITION (true)
    POSTCONDITION ((gws("nplayersseated") >= 0) && (gws("nplayersseated") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nplayersseated")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0090")
    REASONING ("Range check for symbol nplayersactive")
    PRECONDITION (true)
    POSTCONDITION ((gws("nplayersactive") >= 0) && (gws("nplayersactive") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nplayersactive")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0091")
    REASONING ("Range check for symbol nplayersdealt")
    PRECONDITION (true)
    POSTCONDITION ((gws("nplayersdealt") >= 0) && (gws("nplayersdealt") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nplayersdealt")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0092")
    REASONING ("Range check for symbol nplayersplaying")
    PRECONDITION (true)
    POSTCONDITION ((gws("nplayersplaying") >= 0) && (gws("nplayersplaying") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nplayersplaying")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0093")
    REASONING ("Range check for symbol nplayersblind")
    PRECONDITION (true)
    POSTCONDITION ((gws("nplayersblind") >= 0) && (gws("nplayersblind") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nplayersblind")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0094")
    REASONING ("Range check for symbol nfriendsseated")
    PRECONDITION (true)
    POSTCONDITION ((gws("nfriendsseated") == 0) || (gws("nfriendsseated") == 1))
    SYMBOLS_POSSIBLY_AFFECTED ("nfriendsseated")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0095")
    REASONING ("Range check for symbol nfriendssactive")
    PRECONDITION (true)
    POSTCONDITION ((gws("nfriendssactive") == 0) || (gws("nfriendssactive") == 1))
    SYMBOLS_POSSIBLY_AFFECTED ("nfriendssactive")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0096")
    REASONING ("Range check for symbol nfriendsdealt")
    PRECONDITION (true)
    POSTCONDITION ((gws("nfriendsdealt") == 0) || (gws("nfriendsdealt") == 1))
    SYMBOLS_POSSIBLY_AFFECTED ("nfriendsdealt")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0097")
    REASONING ("Range check for symbol nfriendsplaying")
    PRECONDITION (true)
    POSTCONDITION ((gws("nfriendsplaying") == 0) || (gws("nfriendsplaying") == 1))
    SYMBOLS_POSSIBLY_AFFECTED ("nfriendsplaying")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0098")
    REASONING ("Range check for symbol nfriendsblind")
    PRECONDITION (true)
    POSTCONDITION ((gws("nfriendsblind") == 0) || (gws("nfriendsblind") == 1))
    SYMBOLS_POSSIBLY_AFFECTED ("nfriendsblind")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0099")
    REASONING ("Range check for symbol nopponentsseated")
    PRECONDITION (true)
    POSTCONDITION ((gws("nopponentsseated") >= 0) && (gws("nopponentsseated") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentsseated")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("00100")
    REASONING ("Range check for symbol nopponentssactive")
    PRECONDITION (true)
    POSTCONDITION ((gws("nopponentssactive") >= 0) && (gws("nopponentssactive") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentssactive")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0101")
    REASONING ("Range check for symbol nopponentsdealt")
    PRECONDITION (true)
    POSTCONDITION ((gws("nopponentsdealt") >= 0) && (gws("nopponentsdealt") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentsdealt")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0102")
    REASONING ("Range check for symbol nopponentsplaying")
    PRECONDITION (true)
    POSTCONDITION ((gws("nopponentsplaying") >= 0) && (gws("nopponentsplaying") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentsplaying")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0103")
    REASONING ("Range check for symbol nopponentsblind")
    PRECONDITION (true)
    POSTCONDITION ((gws("nopponentsblind") >= 0) && (gws("nopponentsblind") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentsblind")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0104")
    REASONING ("Range check for symbol nopponentschecking")
    PRECONDITION (true)
    POSTCONDITION ((gws("nopponentschecking") >= 0) && (gws("nopponentschecking") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentschecking")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0105")
    REASONING ("Range check for symbol nopponentscalling")
    PRECONDITION (true)
    POSTCONDITION ((gws("nopponentscalling") >= 0) && (gws("nopponentscalling") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentscalling")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0106")
    REASONING ("Range check for symbol nopponentsraising")
    PRECONDITION (true)
    POSTCONDITION ((gws("nopponentsraising") >= 0) && (gws("nopponentsraising") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentsraising")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0107")
    REASONING ("Range check for symbol nopponentsbetting")
    PRECONDITION (true)
    POSTCONDITION ((gws("nopponentsbetting") >= 0) && (gws("nopponentsbetting") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentsbetting")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0108")
    REASONING ("Range check for symbol nopponentsfolded")
    PRECONDITION (true)
    POSTCONDITION ((gws("nopponentsfolded") >= 0) && (gws("nopponentsfolded") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentsfolded")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0109")
    REASONING ("Range check for symbol nplayerscallshort")
    PRECONDITION (true)
    POSTCONDITION ((gws("nplayerscallshort") >= 0) && (gws("nplayerscallshort") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nplayerscallshort")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0110")
    REASONING ("Range check for symbol nchairsdealtright")
    PRECONDITION (true)
    POSTCONDITION ((gws("nchairsdealtright") >= 0) && (gws("nchairsdealtright") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0111")
    REASONING ("Range check for symbol nchairsdealtleft")
    PRECONDITION (true)
    POSTCONDITION ((gws("nchairsdealtleft") >= 0) && (gws("nchairsdealtleft") <= 9))
    SYMBOLS_POSSIBLY_AFFECTED ("nchairsdealtleft")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0112")
    REASONING ("Range check for symbol playersseatedbits")
    PRECONDITION (true)
    POSTCONDITION ((gws("playersseatedbits") >= 0) && (gws("playersseatedbits") <= 1023))
    SYMBOLS_POSSIBLY_AFFECTED ("playersseatedbits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0113")
    REASONING ("Range check for symbol playersactivebits")
    PRECONDITION (true)
    POSTCONDITION ((gws("playersactivebits") >= 0) && (gws("playersactivebits") <= 1023))
    SYMBOLS_POSSIBLY_AFFECTED ("playersactivebits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0114")
    REASONING ("Range check for symbol playersdealtbits")
    PRECONDITION (true)
    POSTCONDITION ((gws("playersdealtbits") >= 0) && (gws("playersdealtbits") <= 1023))
    SYMBOLS_POSSIBLY_AFFECTED ("playersdealtbits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0115")
    REASONING ("Range check for symbol playersplayingbits")
    PRECONDITION (true)
    POSTCONDITION ((gws("playersplayingbits") >= 0) && (gws("playersplayingbits") <= 1023))
    SYMBOLS_POSSIBLY_AFFECTED ("playersplayingbits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0116")
    REASONING ("Range check for symbol playersblindbits")
    PRECONDITION (true)
    POSTCONDITION ((gws("playersblindbits") >= 0) && (gws("playersblindbits") <= 1023))
    SYMBOLS_POSSIBLY_AFFECTED ("playersblindbits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0117")
    REASONING ("Range check for symbol opponentsseatedbits")
    PRECONDITION (true)
    POSTCONDITION ((gws("opponentsseatedbits") >= 0) && (gws("opponentsseatedbits") <= 1023))
    SYMBOLS_POSSIBLY_AFFECTED ("opponentsseatedbits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0118")
    REASONING ("Range check for symbol opponentsactivebits")
    PRECONDITION (true)
    POSTCONDITION ((gws("opponentsactivebits") >= 0) && (gws("opponentsactivebits") <= 1023))
    SYMBOLS_POSSIBLY_AFFECTED ("opponentsactivebits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0119")
    REASONING ("Range check for symbol opponentsdealtbits")
    PRECONDITION (true)
    POSTCONDITION ((gws("opponentsdealtbits") >= 0) && (gws("opponentsdealtbits") <= 1023))
    SYMBOLS_POSSIBLY_AFFECTED ("opponentsdealtbits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0120")
    REASONING ("Range check for symbol opponentsplayingbits")
    PRECONDITION (true)
    POSTCONDITION ((gws("opponentsplayingbits") >= 0) && (gws("opponentsplayingbits") <= 1023))
    SYMBOLS_POSSIBLY_AFFECTED ("opponentsplayingbits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0121")
    REASONING ("Range check for symbol ")
    PRECONDITION (true)
    POSTCONDITION ((gws("opponentsblindbits") >= 0) && (gws("opponentsblindbits") <= 1023))
    SYMBOLS_POSSIBLY_AFFECTED ("opponentsblindbits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0122")
    REASONING ("Range check for symbol friendsseatedbits")
    PRECONDITION (true)
    POSTCONDITION ((gws("friendsseatedbits") >= 0) && (gws("friendsseatedbits") <= 512))
    SYMBOLS_POSSIBLY_AFFECTED ("friendsseatedbits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0123")
    REASONING ("Range check for symbol friendsactivebits")
    PRECONDITION (true)
    POSTCONDITION ((gws("friendsactivebits") >= 0) && (gws("friendsactivebits") <= 512))
    SYMBOLS_POSSIBLY_AFFECTED ("friendsactivebits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0124")
    REASONING ("Range check for symbol friendsdealtbits")
    PRECONDITION (true)
    POSTCONDITION ((gws("friendsdealtbits") >= 0) && (gws("friendsdealtbits") <= 512))
    SYMBOLS_POSSIBLY_AFFECTED ("friendsdealtbits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0125")
    REASONING ("Range check for symbol friendsplayingbits")
    PRECONDITION (true)
    POSTCONDITION ((gws("friendsplayingbits") >= 0) && (gws("friendsplayingbits") <= 512))
    SYMBOLS_POSSIBLY_AFFECTED ("friendsplayingbits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("0126")
    REASONING ("Range check for symbol friendsblindbits")
    PRECONDITION (true)
    POSTCONDITION ((gws("friendsblindbits") >= 0) && (gws("friendsblindbits") <= 1023))
    SYMBOLS_POSSIBLY_AFFECTED ("friendsblindbits")
END_TESTCASE

