#include "KlogSyncMessageServer.h"
#include "TcpPackage.h"
#include "cstandard.h"
#include "protocolserialpackage.h"
#include "TcpServerCenter.h"


KlogSyncMessageServer::KlogSyncMessageServer()
{
	m_serial_parse = KlogNetProtocolLibrary::instance()->GetProtocolSerial();
}


KlogSyncMessageServer::~KlogSyncMessageServer()
{
}

KlogSyncMessageServer& KlogSyncMessageServer::instance()
{
	static KlogSyncMessageServer _instance;
	return _instance;
}

int KlogSyncMessageServer::ServerStart(int port, bool async)
{
	cout << "klog sync message server port:" << port << endl;
	m_server_port = port;
	do
	{
		m_tcp_server = TcpLibrary::instance()->NewTcpServer(port);
		if (m_tcp_server == nullptr)
		{
			cout << "klog sync message server create failed port:" << m_server_port << endl;
			break;
		}
		m_tcp_server->RegisterHandler(this);
		if (async)
		{
			m_tcp_server->AsyncStart();
			cout << "klog sync message server async runing port:" << m_server_port << endl;
		}
		else
		{
			m_tcp_server->Start();
			cout << "klog sync message server sync runing port:" << m_server_port << endl;
		}

	} while (false);
	return 0;
}

int KlogSyncMessageServer::ServerStop()
{
	if (m_tcp_server)
	{
		m_tcp_server->Stop();
		TcpLibrary::instance()->DeleteTcpServer(m_tcp_server);
	}
	cout << "klog sync message server have closed port:" << m_server_port << endl;
	return 0;
}

int KlogSyncMessageServer::OnTcpRead(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status)
{
	if (data)
	{
		cout << "readed data:" << data << endl;
		if (m_serial_parse)
		{
			string serial_event_data(data, size);
			NetEvent event;
			m_serial_parse->Serial(serial_event_data, event);
			ParseKlogMessageEvent(event, serial_event_data, connect);
		}
	}
	return 0;
}

int KlogSyncMessageServer::OnTcpWrite(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status)
{
	if (data)
	{
		cout << "writed data:" << data << endl;
	}
	return 0;
}

int KlogSyncMessageServer::OnTcpConnect(shared_ptr<ITcpConnect> connect, int status)
{
	cout << "have connected, status:" << status << endl;
	if (m_tcp_server)
	{
		cout << "connects count:" << m_tcp_server->GetConnectsCount() << endl;
	}
	return 0;
}

int KlogSyncMessageServer::OnTcpDisconnect(shared_ptr<ITcpConnect> connect, int status)
{
	cout << "have disconnected, status:" << status << endl;
	if (m_tcp_server)
	{
		cout << "connects count:" << m_tcp_server->GetConnectsCount() << endl;
		list<shared_ptr<ITcpConnect> /*connect*/>::iterator iter = m_source_connects.begin();
		for (; iter != m_source_connects.end(); iter++)
		{
			if (*iter == connect)
			{
				m_source_connects.erase(iter);
				break;
			}
		}
		iter = m_sinck_connects.begin();
		for (; iter != m_sinck_connects.end(); iter++)
		{
			if (*iter == connect)
			{
				m_sinck_connects.erase(iter);
				break;
			}
		}
	}
	return 0;
}

int KlogSyncMessageServer::ParseKlogMessageEvent(const NetEvent& net_event, const string& serial_event_data, shared_ptr<ITcpConnect> connect)
{
	switch (net_event.event_type)
	{
	case NetEventType::GET_KLOG_MESSAGE:
	{
		if (m_serial_parse)
		{
			GetKlogServerPortEvent get_port_event;
			m_serial_parse->Serial(serial_event_data, get_port_event);
			HandleKlogMessageEvent(get_port_event, connect);
		}
		break;
	}
	default:
		break;
	}
	return 0;
}

int KlogSyncMessageServer::HandleKlogMessageEvent(const NetEvent& net_event, shared_ptr<ITcpConnect> connect)
{
	switch (net_event.event_type)
	{
	case NetEventType::GET_KLOG_MESSAGE:
	{
		break;
	}
	default:
		break;
	}
	return 0;
}

int KlogSyncMessageServer::SendEvent(const string& serial_event_data, shared_ptr<ITcpConnect> connect)
{
	connect->AsyncWrite(serial_event_data.c_str(), serial_event_data.size());
	return 0;
}
