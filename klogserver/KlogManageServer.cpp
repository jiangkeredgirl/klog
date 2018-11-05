#include "KlogManageServer.h"
#include "TcpServerHandlerCenter.h"
#include "TcpPackage.h"
#include "cstandard.h"
#include "protocolserialpackage.h"
#include "TcpServerCenter.h"


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
			ParseKlogManageEvent(event, serial_event_data, connect);
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

int KlogManageServer::ParseKlogManageEvent(const NetEvent& net_event, const string& serial_event_data, shared_ptr<ITcpConnect> connect)
{
	switch (net_event.event_type)
	{
	case NetEventType::GET_KLOG_SERVER_PORT:
	{
		if (m_serial_parse)
		{
			GetKlogServerPortEvent get_port_event;
			m_serial_parse->Serial(serial_event_data, get_port_event);
			HandleKlogManageEvent(get_port_event, connect);
		}
		break;
	}
	default:
		break;
	}
	return 0;
}

int KlogManageServer::HandleKlogManageEvent(const NetEvent& net_event, shared_ptr<ITcpConnect> connect)
{
	switch (net_event.event_type)
	{
	case NetEventType::GET_KLOG_SERVER_PORT:
	{
		const GetKlogServerPortEvent& get_port_event = static_cast<const GetKlogServerPortEvent&>(net_event);
		if (get_port_event.client_type == KlogClientType::SOURCE_ENDPOINT)
		{
			m_source_connects.push_back(connect);
		}
		else
		{
			m_sinck_connects.push_back(connect);
		}
		SendKlogServerPortEvent send_event;
		send_event.sync_message_port = KLOG_SYNC_MESSAGE_PORT;
		send_event.async_message_port = KLOG_ASYNC_MESSAGE_PORT;
		string serial_event_data;
		m_serial_parse->Serial(send_event, serial_event_data);
		SendEvent(serial_event_data, connect);
		break;
	}
	default:
		break;
	}
	return 0;
}

int KlogManageServer::SendEvent(const string& serial_event_data, shared_ptr<ITcpConnect> connect)
{
	connect->AsyncWrite(serial_event_data.c_str(), serial_event_data.size());
	return 0;
}