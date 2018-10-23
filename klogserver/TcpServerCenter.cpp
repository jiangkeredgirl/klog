#include "TcpServerCenter.h"
#include "cstandard.h"
#include "KlogManageServer.h"

#define KLOG_SERVER_PORT 2012

TcpServerCenter::TcpServerCenter()
{
}


TcpServerCenter::~TcpServerCenter()
{
}

TcpServerCenter& TcpServerCenter::instance()
{
	static TcpServerCenter _instance;
	return _instance;
}

int TcpServerCenter::Run()
{
	cout << "please input klog server port, default is " << KLOG_SERVER_PORT << endl;
	string strport;
	getline(std::cin, strport);
	int port = KLOG_SERVER_PORT;
	if (!strport.empty())
	{
		port = stoi(strport);
	}
	do
	{
		KlogManageServer::instance().ServerStart(port, true);
		string input_flag;
		do
		{
			cout << "input \'c\' will close server" << endl;
			cin >> input_flag;
			if (input_flag == "c")
			{
				break;
			}
		} while (true);
		KlogManageServer::instance().ServerStop();
		cout << "klog server closed" << endl;
	} while (false);
	return 0;
}