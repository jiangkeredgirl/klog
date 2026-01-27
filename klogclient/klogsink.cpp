#include "pch.h"
#include "klogsink.h"
#include "cstandard.h"
#include "protocolserialpackage.h"
#include "klogsinkcontrol.h"
#include "klogsinksynctrace.h"
#include "klogsinkasynctrace.h"

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
		KlogSinkSyncTrace::instance().RegisterNetSinkFunction(std::bind(&KlogSink::OnReceiveSyncTrace, this, std::placeholders::_1));
		error_code = KlogSinkSyncTrace::instance().Connect(m_server_ip, m_server_sync_trace_port, false);
		if (error_code)
		{
			cerr << "connect failed" << endl;
			break;
		}
		KlogSinkAsyncTrace::instance().RegisterNetSinkFunction(std::bind(&KlogSink::OnReceiveAsyncTrace, this, std::placeholders::_1));
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

int KlogSink::OnReceiveSyncTrace(shared_ptr<KlogMessage> klog_message)
{
	shared_ptr<TraceEntry> trace_entry(new TraceEntry());
	{
		*trace_entry = klog_message->trace_entry;
	}
	emit SignalReceiveTrace(trace_entry, LogFileStatus::LogFileReading);
	if (trace_entry->is_track)
	{
		emit SignalReceiveTrack(trace_entry, LogFileStatus::LogFileReading);
	}
	return 0;
}

int KlogSink::OnReceiveAsyncTrace(shared_ptr<KlogMessage> klog_message)
{
	shared_ptr<TraceEntry> trace_entry(new TraceEntry());
	{
		*trace_entry = klog_message->trace_entry;
	}
	emit SignalReceiveTrace(trace_entry, LogFileStatus::LogFileReading);
	if (trace_entry->is_track)
	{
		emit SignalReceiveTrack(trace_entry, LogFileStatus::LogFileReading);
	}
	return 0;
}

