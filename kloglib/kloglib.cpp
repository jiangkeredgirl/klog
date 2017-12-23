// kloglib.cpp : Defines the exported functions for the DLL application.
//

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include "kloglib.h"


// This is an example of an exported variable
KLOGLIB_API int nkloglib=0;

// This is an example of an exported function.
KLOGLIB_API int fnkloglib(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see kloglib.h for the class definition
Ckloglib::Ckloglib()
{
    return;
}
