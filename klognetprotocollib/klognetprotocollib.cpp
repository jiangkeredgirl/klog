// klognetprotocollib.cpp : Defines the exported functions for the DLL application.
//

#include "klognetprotocollib.h"


// This is an example of an exported variable
KLOGNETPROTOCOLLIB_API int nklognetprotocollib=0;

// This is an example of an exported function.
KLOGNETPROTOCOLLIB_API int fnklognetprotocollib(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see klognetprotocollib.h for the class definition
Cklognetprotocollib::Cklognetprotocollib()
{
    return;
}
