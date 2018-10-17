#include "TcpServerCenter.h"
#include "TcpServerHandlerCenter.h"
#include "TcpPackage.h"
#include "cstandard.h"


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

int TcpServerCenter::Run(bool async)
{
	cout << "please input server port, such as:9000" << endl;
	string strport;
	getline(std::cin, strport);
	int port = 9000;
	if (!strport.empty())
	{
		port = stoi(strport);
	}

	ITcpServer* tcpserver = TcpLibrary::instance()->NewTcpServer(port);
	TcpServerHandlerCenter handler_center(tcpserver);
	tcpserver->RegisterHandler(&handler_center);
	
	if (async)
	{
		tcpserver->AsyncStart();
		cout << "tcp async server runing, port:" << port << endl;
	}
	else
	{
		tcpserver->Start();
		cout << "tcp sync server runing, port:" << port << endl;
	}
	string input_flag;
	do
	{
		cout << "please input text for send to server, \'c\' will close server" << endl;
		cin >> input_flag;
		if (input_flag == "c")
		{
			break;
		}
		if (async)
		{
			tcpserver->AsyncBroadcast(input_flag.c_str(), input_flag.size());
		}
		else
		{
			tcpserver->Broadcast(input_flag.c_str(), input_flag.size());
		}
	} while (true);
	tcpserver->Stop();
	cout << "tcp have closed" << endl;
	if (tcpserver)
	{
		TcpLibrary::instance()->DeleteTcpServer(tcpserver);
	}
	system("pause");
	return 0;
}