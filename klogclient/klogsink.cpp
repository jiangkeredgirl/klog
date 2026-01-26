#include "pch.h"
#include "klogsink.h"
#include "cstandard.h"
#include "protocolserialpackage.h"

KlogSink::KlogSink()
{
}


KlogSink::~KlogSink()
{
}


KlogSink& KlogSink::instance()
{
	static KlogSink _instance;
	return _instance;
}

int KlogSink::Connect(const string& ip, int control_port, int sync_trace_port, int async_trace_port, bool async)
{
	int error_code = 1;
	m_server_ip = ip;
	m_server_control_port = control_port;
	m_server_sync_trace_port = sync_trace_port;
	m_server_async_trace_port = async_trace_port;
	do
	{
		error_code = KlogSinkControl::instance().Connect(m_server_ip, m_server_control_port, true);
		if (error_code)
		{
			cerr << "connect failed" << endl;
			break;
		}
		error_code = KlogSinkSyncTrace::instance().Connect(m_server_ip, m_server_sync_trace_port, false);
		if (error_code)
		{
			cerr << "connect failed" << endl;
			break;
		}
		error_code = KlogSinkAsyncTrace::instance().Connect(m_server_ip, m_server_async_trace_port, true);
		if (error_code)
		{
			cerr << "connect failed" << endl;
			break;
		}
		cout << "tcp client have connected" << endl;
	} while (false);
	return error_code;
}

int KlogSink::Disconnect()
{
	KlogSinkControl::instance().Disconnect();
	KlogSinkSyncTrace::instance().Disconnect();
	KlogSinkAsyncTrace::instance().Disconnect();
	cout << "tcp client have disconnected" << endl;
	return 0;
}
