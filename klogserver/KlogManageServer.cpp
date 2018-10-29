#include "KlogManageServer.h"
#include "TcpServerHandlerCenter.h"
#include "TcpPackage.h"
#include "cstandard.h"
#include "protocolserialpackage.h"


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
		m_serial_parse = KlogNetProtocolLibrary::instance()->GetProtocolSerial();
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
		if (m_serial_parse)
		{
			string serial_event_data(data, size);
			NetEvent event;
			m_serial_parse->Serial(serial_event_data, event);
			HandleKlogManageEvent(event, serial_event_data);
		}
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

int KlogManageServer::HandleKlogManageEvent(const NetEvent& net_event, const string& serial_event_data)
{
	switch (net_event.event_type)
	{
	case NetEventType::GET_KLOG_SERVER_PORT:
	{
		if (m_serial_parse)
		{
			GetKlogServerPortEvent get_port_event;
			m_serial_parse->Serial(serial_event_data, get_port_event);
			HandleKlogManageEvent(&get_port_event);
		}
		break;
	}
	default:
		break;
	}
	return 0;
}

int KlogManageServer::HandleKlogManageEvent(const NetEvent* net_event)
{
	return 0;
}