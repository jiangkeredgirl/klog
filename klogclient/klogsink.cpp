#include "klogsink.h"
#include "cstandard.h"


klogsink::klogsink()
{
}


klogsink::~klogsink()
{
}


klogsink& klogsink::instance()
{
	static klogsink _instance;
	return _instance;
}

int klogsink::Connect(const string& ip, int port, bool async)
{
	int error_code = 1;
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

int klogsink::Disconnect()
{
	if (m_tcp_client)
	{
		m_tcp_client->TcpDisconnect();
		TcpLibrary::instance()->DeleteTcpClient(m_tcp_client);
	}
	cout << "tcp client have disconnected" << endl;
	return 0;
}

int klogsink::OnTcpConnect(int status)
{
	cout << "have connected, status:" << status << endl;
	return 0;
}

int klogsink::OnTcpDisconnect(int status)
{
	cout << "have disconnected, status:" << status << endl;
	return 0;
}

int klogsink::OnTcpRead(const char* data, size_t size, int status)
{
	if (data)
	{
		cout << "readed data:" << data << endl;
	}
	return 0;
}

int klogsink::OnTcpWrite(const char* data, size_t size, int status)
{
	if (data)
	{
		cout << "writed data:" << data << endl;
	}
	return 0;
}
