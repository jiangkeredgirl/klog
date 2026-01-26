#include "klogsourcesynctrace.h"
#include "cstandard.h"
#include "protocolserialpackage.h"

KlogSourceSyncTrace::KlogSourceSyncTrace()
{
	m_serial_parse = KlogNetProtocolLibrary::instance()->GetProtocolSerial();
}


KlogSourceSyncTrace::~KlogSourceSyncTrace()
{
}


KlogSourceSyncTrace& KlogSourceSyncTrace::instance()
{
	static KlogSourceSyncTrace _instance;
	return _instance;
}

int KlogSourceSyncTrace::Connect(const string& ip, int port, bool async)
{
	int error_code = 1;
	m_server_ip = ip;
	m_server_port = port;
	do
	{
		m_tcp_client = TcpLibrary::instance()->NewTcpClient();
		if (m_tcp_client == nullptr)
		{
			cout << "NewTcpClient failed" << endl;
			break;
		}
		cout << "remote klog server ip:" << ip << ", port:" << port << endl;
		m_tcp_client->RegisterHandler(this);
		while (true)
		{
			if (async)
			{
				error_code = m_tcp_client->AsyncTcpConnect(ip, port);
				break;
			}
			else
			{
				error_code = m_tcp_client->TcpConnect(ip, port);
			}
			if (error_code)
			{
				cout << "connect failed, sleep 3s and continue connect" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
			else
			{
				cout << "have connected" << endl;
				break;
			}
		}

	} while (false);
	return error_code;
}

int KlogSourceSyncTrace::Disconnect()
{
	if (m_tcp_client)
	{
		m_tcp_client->TcpDisconnect();
		TcpLibrary::instance()->DeleteTcpClient(m_tcp_client);
	}
	cout << "tcp client have disconnected" << endl;
	return 0;
}

int KlogSourceSyncTrace::SyncWrite(const string& trace)
{
	if (m_tcp_client)
	{
		m_tcp_client->TcpWrite(trace.data(), trace.size());
	}
	return 0;
}

int KlogSourceSyncTrace::AsyncWrite(const string& trace)
{
	if (m_tcp_client)
	{
		m_tcp_client->AsyncTcpWrite(trace.data(), trace.size());
	}
	return 0;
}

int KlogSourceSyncTrace::GetLocalIPandPort(string& ip, int& port)
{
	if (m_tcp_client)
	{
		m_tcp_client->GetLocalIPandPort(ip, port);
	}
	return 0;
}

int KlogSourceSyncTrace::OnTcpConnect(int status)
{
	if (status == 0)
	{
		cout << "have connected, status:" << status << endl;
	}
	else
	{
		cout << "connect failed, status:" << status << endl;
		cout << "connect failed, sleep 3s and continue connect" << endl;
		std::thread t([this]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			m_tcp_client->AsyncTcpConnect(m_server_ip, m_server_port);
		});
		t.detach();
	}
	return 0;
}

int KlogSourceSyncTrace::OnTcpDisconnect(int status)
{
	cout << "have disconnected, status:" << status << endl;
	if (status != 1236)
	{
		cout << "abnormal disconnect, reconnect" << endl;
		std::thread t([this]()
		{
			m_tcp_client->AsyncTcpConnect(m_server_ip, m_server_port);
		});
		t.detach();
	}
	return 0;
}

int KlogSourceSyncTrace::OnTcpRead(const char* data, size_t size, int status)
{
	if (data)
	{
		//cout << "readed data:" << data << endl;
		if (m_serial_parse)
		{
			string serial_event_data(data, size);
			NetEvent event;
			m_serial_parse->Serial(serial_event_data, event);
			ParseKlogManageEvent(event, serial_event_data);
		}
	}
	return 0;
}

int KlogSourceSyncTrace::OnTcpWrite(const char* data, size_t size, int status)
{
	if (data)
	{
		//cout << "writed data:" << data << endl;
	}
	return 0;
}

int KlogSourceSyncTrace::ParseKlogManageEvent(const NetEvent& net_event, const string& serial_event_data)
{
	switch (net_event.event_type)
	{
	case NetEventType::SEND_KLOG_SERVER_PORT:
	{
		if (m_serial_parse)
		{
			SendKlogServerPortEvent send_port_event;
			m_serial_parse->Serial(serial_event_data, send_port_event);
			HandleKlogManageEvent(send_port_event);
		}
		break;
	}
	default:
		break;
	}
	return 0;
}

int KlogSourceSyncTrace::HandleKlogManageEvent(const NetEvent& net_event)
{
	switch (net_event.event_type)
	{
	case NetEventType::SEND_KLOG_SERVER_PORT:
	{
		const SendKlogServerPortEvent& send_port_event = static_cast<const SendKlogServerPortEvent&>(net_event);
		break;
	}
	default:
		break;
	}
	return 0;
}

int KlogSourceSyncTrace::SendEvent(const string& serial_event_data)
{
	m_tcp_client->AsyncTcpWrite(serial_event_data.c_str(), serial_event_data.size());
	return 0;
}