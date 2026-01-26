#include "klogsource.h"
#include "cstandard.h"
#include "protocolserialpackage.h"

KlogSource::KlogSource()
{
}


KlogSource::~KlogSource()
{
}


KlogSource& KlogSource::instance()
{
	static KlogSource _instance;
	return _instance;
}

int KlogSource::Connect(const string& ip, int control_port, int sync_trace_port, int async_trace_port, bool async)
{
	int error_code = 1;
	m_server_ip = ip;
	m_server_control_port = control_port;
	m_server_sync_trace_port = sync_trace_port;
	m_server_async_trace_port = async_trace_port;
	do
	{
		error_code = KlogSourceControl::instance().Connect(m_server_ip, m_server_control_port, true);
		if (error_code)
		{
			cerr << "connect failed" << endl;
			break;
		}
		error_code = KlogSourceSyncTrace::instance().Connect(m_server_ip, m_server_sync_trace_port, false);
		if (error_code)
		{
			cerr << "connect failed" << endl;
			break;
		}
		error_code = KlogSourceAsyncTrace::instance().Connect(m_server_ip, m_server_async_trace_port, true);
		if (error_code)
		{
			cerr << "connect failed" << endl;
			break;
		}
		cout << "tcp client have connected" << endl;
	} while (false);
	return error_code;
}

int KlogSource::Disconnect()
{
	KlogSourceControl::instance().Disconnect();
	KlogSourceSyncTrace::instance().Disconnect();
	KlogSourceAsyncTrace::instance().Disconnect();
	cout << "tcp client have disconnected" << endl;
	return 0;
}

int KlogSource::GetSyncTraceIPandPort(string& ip, int& port)
{
	KlogSourceSyncTrace::instance().GetLocalIPandPort(ip, port);
	return 0;
}

int KlogSource::GetAsyncTraceIPandPort(string& ip, int& port)
{
	KlogSourceAsyncTrace::instance().GetLocalIPandPort(ip, port);
	return 0;
}

int KlogSource::SyncTraceWrite(const string& trace)
{
	KlogSourceSyncTrace::instance().SyncWrite(trace);
	return 0;
}

int KlogSource::AsyncTraceWrite(const string& trace)
{
	KlogSourceAsyncTrace::instance().AsyncWrite(trace);
	return 0;
}

