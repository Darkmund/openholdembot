#ifndef INC_DEBUG_H
#define INC_DEBUG_H

// To enable seh:
// uncomment this 
// and add /EHa flag to the compiler options
// For automatic minidumps to work, this must be left configured "on"
// all the time now.
#define	SEH_ENABLE	1

// This lets transform.cpp know which source tree is #include'ing it
#ifndef OPENHOLDEM_PROGRAM
#define OPENHOLDEM_PROGRAM
#endif

//  Three macros for exception handling,
//    replacing the old copy- and pasted code
//    at the beginning and end of every function.
//    (Maintenance 2008.04.17 by THF)
//
//  Docu:
//    http://en.wikipedia.org/wiki/C_preprocessor
//    http://en.wikipedia.org/wiki/Variadic_macro
//
//  First one: __SEH_HEADER
//    Replacing:
//      
//    #ifdef SEH_ENABLE
//        try {
//    #endif
//
#ifdef SEH_ENABLE
#define __SEH_HEADER try {
#else
#define __SEH_HEADER
#endif


//  Second one: __SEH_LOGFATAL
//    In case, you call it with several parameters,
//    the first parameter has to be a format string 
//    Replacing:
//
//    #ifdef SEH_ENABLE
//        }
//	      catch (...)	 { 
//		      logfatal(<SEVERAL_INFO_TO_LOG>); 
//		      throw;
//	      }
//    #endif
//
#ifdef SEH_ENABLE
#define __SEH_LOGFATAL(...) } \
	catch (...) \
	{ \
	    logfatal(__VA_ARGS__); \
		throw; \
	}
#else
#define __SEH_LOGFATAL(...)
#endif


//  Thirs one: __SEH_SET_EXCEPTION_HANDLER
//    Replacing:
//
//    #ifdef SEH_ENABLE
//	      // Set exception handler
//	      SetUnhandledExceptionFilter(MyUnHandledExceptionFilter);
//    #endif
//
#ifdef SEH_ENABLE
#define __SEH_SET_EXCEPTION_HANDLER($1) SetUnhandledExceptionFilter($1);
#else
#define __SEH_SET_EXCEPTION_HANDLER($1)
#endif


LONG WINAPI MyUnHandledExceptionFilter(EXCEPTION_POINTERS *pExceptionPointers);
char * get_time(char * timebuf);
char * get_now_time(char * timebuf);
void logfatal (char* fmt, ...);
BOOL CreateBMPFile(const char *szFile, HBITMAP hBMP);

void start_log(void);
void write_log(char* fmt, ...);
void write_log_nostamp(char* fmt, ...);
void write_logautoplay(const char * action);
void stop_log(void);
int GenerateDump(EXCEPTION_POINTERS *pExceptionPointers);

extern FILE *log_fp;

#endif /* INC_DEBUG_H */
