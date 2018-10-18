// klogserver.cpp : Defines the entry point for the console application.
//

//#include "targetver.h"
//
//#include <stdio.h>
//#include <tchar.h>
#include "cstandard.h"
#include "TcpServerCenter.h"

int main()
{
	cout << "klog server start" << endl;
	TcpServerCenter::instance().Run(true);	
	cout << "klog server end" << endl;
	//system("pause");
    return 0;
}

