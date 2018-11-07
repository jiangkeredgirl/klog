#include "KlogSyncMessageServer.h"
#include "TcpPackage.h"
#include "cstandard.h"
#include "protocolserialpackage.h"
#include "TcpServerCenter.h"


KlogSyncMessageServer::KlogSyncMessageServer()
{
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
	cout << "klog message server port:" << port << endl;
	do
	{
		m_TcpServer = TcpLibrary::instance()->NewTcpServer(port);
		if (m_TcpServer == nullptr)
		{
			cout << "klog message server create failed" << endl;
			break;
		}
		m_TcpServer->RegisterHandler(this);
		if (async)
		{
			m_TcpServer->AsyncStart();
			cout << "klog message server async runing" << endl;
		}
		else
		{
			m_TcpServer->Start();
			cout << "klog message server sync runing" << endl;
		}
		m_serial_parse = KlogNetProtocolLibrary::instance()->GetProtocolSerial();
	} while (false);
	return 0;
}

int KlogSyncMessageServer::ServerStop()
{
	if (m_TcpServer)
	{
		m_TcpServer->Stop();
		TcpLibrary::instance()->DeleteTcpServer(m_TcpServer);
	}
	cout << "klog message serve have closed" << endl;
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
	if (m_TcpServer)
	{
		cout << "connects count:" << m_TcpServer->GetConnectsCount() << endl;
	}
	return 0;
}

int KlogSyncMessageServer::OnTcpDisconnect(shared_ptr<ITcpConnect> connect, int status)
{
	cout << "have disconnected, status:" << status << endl;
	if (m_TcpServer)
	{
		cout << "connects count:" << m_TcpServer->GetConnectsCount() << endl;
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
