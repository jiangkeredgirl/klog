#include "KlogManageServer.h"
#include "TcpPackage.h"
#include "cstandard.h"
#include "protocolserialpackage.h"
#include "TcpServerCenter.h"


KlogManageServer::KlogManageServer()
{
	m_serial_parse = KlogNetProtocolLibrary::instance()->GetProtocolSerial();
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
	m_server_port = port;
	do
	{		
		m_tcp_server = TcpLibrary::instance()->NewTcpServer(port);
		if (m_tcp_server == nullptr)
		{
			cout << "klog manager server create failed" << endl;
			break;
		}
		m_tcp_server->RegisterHandler(this);
		if (async)
		{
			m_tcp_server->AsyncStart();
			cout << "klog manager server async runing port:" << m_server_port << endl;
		}
		else
		{
			m_tcp_server->Start();
			cout << "klog manager server sync runing port:" << m_server_port << endl;
		}	

	} while (false);
	return 0;
}

int KlogManageServer::ServerStop()
{
	if (m_tcp_server)
	{
		m_tcp_server->Stop();
		TcpLibrary::instance()->DeleteTcpServer(m_tcp_server);
	}
	cout << "klog manager server have closed port:" << m_server_port << endl;
	return 0;
}

int KlogManageServer::OnTcpRead(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status)
{
	if (data)
	{
		//cout << "readed data:" << data << endl;
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
		//cout << "writed data:" << data << endl;
	}
	return 0;
}

int KlogManageServer::OnTcpConnect(shared_ptr<ITcpConnect> connect, int status)
{
	cout << "have connected, status:" << status << endl;
	if (m_tcp_server)
	{
		cout << "connects count:" << m_tcp_server->GetConnectsCount() << endl;
	}
	return 0;
}

int KlogManageServer::OnTcpDisconnect(shared_ptr<ITcpConnect> connect, int status)
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

int KlogManageServer::ParseKlogManageEvent(const NetEvent& net_event, const string& serial_event_data, shared_ptr<ITcpConnect> connect)
{
	switch (net_event.event_type)
	{
	case NetEventType::SEND_KLOG_CLIENT_TYPE:
	{
		if (m_serial_parse)
		{
			SendKlogClientTypeEvent client_type_event;
			m_serial_parse->Serial(serial_event_data, client_type_event);
			HandleKlogManageEvent(client_type_event, connect);
		}
		break;
	}
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
	case NetEventType::SEND_KLOG_CLIENT_TYPE:
	{
		const SendKlogClientTypeEvent* client_type_event = dynamic_cast<const SendKlogClientTypeEvent*>(&net_event);
		if (client_type_event)
		{
			if (client_type_event->client_type == KlogClientType::SOURCE_ENDPOINT)
			{
				m_source_connects.push_back(connect);
			}
			else
			{
				m_sinck_connects.push_back(connect);
			}
		}
		break;
	}
	case NetEventType::GET_KLOG_SERVER_PORT:
	{
		const GetKlogServerPortEvent& get_port_event = static_cast<const GetKlogServerPortEvent&>(net_event);
		SendKlogServerPortEvent send_event;
		send_event.sync_message_port  = KLOG_SERVER_SYNC_TRACE_PORT;
		send_event.async_message_port = KLOG_SERVER_ASYNC_TRACE_PORT;
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