#include "TcpServerHandlerCenter.h"
#include "TcpPackage.h"

TcpServerHandlerCenter::TcpServerHandlerCenter(ITcpServer* tcpServer)
{
	m_TcpServer = tcpServer;
}


TcpServerHandlerCenter::~TcpServerHandlerCenter()
{
}


int  TcpServerHandlerCenter::OnTcpRead(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status)
{
	if (data)
	{
		cout << "readed data:" << data << endl;
	}
	return 0;
}

int  TcpServerHandlerCenter::OnTcpWrite(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status)
{
	if (data)
	{
		cout << "writed data:" << data << endl;
	}
	return 0;
}

int  TcpServerHandlerCenter::OnTcpConnect(shared_ptr<ITcpConnect> connect, int status)
{
	cout << "have connected, status:" << status << endl;
	if (m_TcpServer)
	{
		cout << "connects count:" << m_TcpServer->GetConnectsCount() << endl;
	}	
	return 0;
}

int  TcpServerHandlerCenter::OnTcpDisconnect(shared_ptr<ITcpConnect> connect, int status)
{
	cout << "have disconnected, status:" << status << endl;
	if (m_TcpServer)
	{
		cout << "connects count:" << m_TcpServer->GetConnectsCount() << endl;
	}
	return 0;
}