#include "KlogManageServer.h"
#include "TcpServerHandlerCenter.h"
#include "TcpPackage.h"
#include "cstandard.h"


KlogManageServer::KlogManageServer()
{
}


KlogManageServer::~KlogManageServer()
{
}


KlogManageServer& KlogManageServer::instance()
{
	static KlogManageServer _instance;
	return _instance;
}

int KlogManageServer::ServerStart(int port, bool async)
{
	cout << "klog manager server port:" << port << endl;
	do
	{
		m_TcpServer = TcpLibrary::instance()->NewTcpServer(port);
		if (m_TcpServer == nullptr)
		{
			cout << "klog manager server create failed" << endl;
			break;
		}
		m_TcpServer->RegisterHandler(this);
		if (async)
		{
			m_TcpServer->AsyncStart();
			cout << "klog manager server async runing" << endl;
		}
		else
		{
			m_TcpServer->Start();
			cout << "klog manager server sync runing" << endl;
		}
	} while (false);
	return 0;
}

int KlogManageServer::ServerStop()
{
	if (m_TcpServer)
	{
		m_TcpServer->Stop();
		TcpLibrary::instance()->DeleteTcpServer(m_TcpServer);
	}
	cout << "klog manager serve have closed" << endl;
	return 0;
}

int KlogManageServer::OnTcpRead(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status)
{
	if (data)
	{
		cout << "readed data:" << data << endl;
	}
	return 0;
}

int KlogManageServer::OnTcpWrite(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status)
{
	if (data)
	{
		cout << "writed data:" << data << endl;
	}
	return 0;
}

int KlogManageServer::OnTcpConnect(shared_ptr<ITcpConnect> connect, int status)
{
	cout << "have connected, status:" << status << endl;
	if (m_TcpServer)
	{
		cout << "connects count:" << m_TcpServer->GetConnectsCount() << endl;
	}
	return 0;
}

int KlogManageServer::OnTcpDisconnect(shared_ptr<ITcpConnect> connect, int status)
{
	cout << "have disconnected, status:" << status << endl;
	if (m_TcpServer)
	{
		cout << "connects count:" << m_TcpServer->GetConnectsCount() << endl;
	}
	return 0;
}