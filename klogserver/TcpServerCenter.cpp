#include "TcpServerCenter.h"
#include "cstandard.h"
#include "KlogManageServer.h"
#include "KlogSyncMessageServer.h"
#include "KlogAsyncMessageServer.h"


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
	string strport;
	int control_port     = KLOG_SERVER_CONTROL_PORT;
	int sync_trace_port  = KLOG_SERVER_SYNC_TRACE_PORT;
	int async_trace_port = KLOG_SERVER_ASYNC_TRACE_PORT;

	cout << "please input klog server control port, default is " << KLOG_SERVER_CONTROL_PORT << endl;	
	getline(std::cin, strport);	
	if (!strport.empty())
	{
		control_port = stoi(strport);
	}
	cout << "please input klog server sync trace port, default is " << KLOG_SERVER_SYNC_TRACE_PORT << endl;
	getline(std::cin, strport);
	if (!strport.empty())
	{
		sync_trace_port = stoi(strport);
	}
	cout << "please input klog server async trace port, default is " << KLOG_SERVER_ASYNC_TRACE_PORT << endl;
	getline(std::cin, strport);
	if (!strport.empty())
	{
		async_trace_port = stoi(strport);
	}
	do
	{
		KlogManageServer::instance().ServerStart(control_port, true);
		KlogSyncMessageServer::instance().ServerStart(sync_trace_port, false);
		KlogAsyncMessageServer::instance().ServerStart(async_trace_port, true);
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
		KlogSyncMessageServer::instance().ServerStop();
		KlogAsyncMessageServer::instance().ServerStop();
		cout << "klog server closed" << endl;
	} while (false);
	return 0;
}