// klogserver.cpp : Defines the entry point for the console application.
//

//#include "targetver.h"
//
//#include <stdio.h>
//#include <tchar.h>
#include "cstandard.h"
#include "TcpServerCenter.h"
#include "klognetprotocol.h"
#include "protocolserial.h"
#include "protocolserialpackage.h"

int main()
{
	//SendKlogConfig config;
	//config.source_info.source_port = 33;
	//string data;
	//IProtocolSerial* serial = KlogNetProtocolLibrary::instance()->GetProtocolSerial();
	//if (serial)
	//{
	//	serial->Serial(config, data);
	//}
	//SendKlogConfig config1;
	//if (serial)
	//{
	//	serial->Serial(data, config1);
	//}

	cout << "klog server start" << endl;
	TcpServerCenter::instance().Run(true);	
	cout << "klog server end" << endl;
	//system("pause");
    return 0;
}

