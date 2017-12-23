// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KLOGLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KLOGLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef KLOGLIB_EXPORTS
#define KLOGLIB_API __declspec(dllexport)
#else
#define KLOGLIB_API __declspec(dllimport)
#endif

// This class is exported from the kloglib.dll
class KLOGLIB_API Ckloglib {
public:
	Ckloglib(void);
	// TODO: add your methods here.
};

extern KLOGLIB_API int nkloglib;

KLOGLIB_API int fnkloglib(void);
