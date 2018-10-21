// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KLOGNETPROTOCOLLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KLOGNETPROTOCOLLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef KLOGNETPROTOCOLLIB_EXPORTS
#define KLOGNETPROTOCOLLIB_API __declspec(dllexport)
#else
#define KLOGNETPROTOCOLLIB_API __declspec(dllimport)
#endif

// This class is exported from the klognetprotocollib.dll
class KLOGNETPROTOCOLLIB_API Cklognetprotocollib {
public:
	Cklognetprotocollib(void);
	// TODO: add your methods here.
};

extern KLOGNETPROTOCOLLIB_API int nklognetprotocollib;

KLOGNETPROTOCOLLIB_API int fnklognetprotocollib(void);
