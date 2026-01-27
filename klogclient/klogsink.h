#pragma once
#include "pch.h"
#include "tcpclienthandler.h"
#include "TcpPackage.h"
#include "klognetprotocol.h"
#include "logfile.h"
#include "traceprinter.h"
using namespace kk;

class KlogMessage
{
public:
	KlogMessage()
	{

	}
	virtual ~KlogMessage() {};
	KlogSourceInfo source_info;
	TraceEntry     trace_entry; // klog 日志	
};

typedef std::function<int(const shared_ptr<KlogMessage>& net_log_message)> KlogNetSinkFunction;

class KlogSink : public QObject
{
	Q_OBJECT
public:
	KlogSink();
	~KlogSink();
	static KlogSink& instance();

public:
	int Connect(const string& ip, int control_port, int sync_trace_port, int async_trace_port, bool async);
	int Disconnect();

signals:
	void SignalReceiveTrace(shared_ptr<TraceEntry> trace_entry, LogFileStatus status);
	void SignalReceiveTrack(shared_ptr<TraceEntry> track_entry, LogFileStatus status);

private:
	int OnReceiveSyncTrace(shared_ptr<KlogMessage> klog_message);
	int OnReceiveAsyncTrace(shared_ptr<KlogMessage> klog_message);

private:
	string m_server_ip;
	int m_server_control_port = 0;
	int m_server_sync_trace_port = 0;
	int m_server_async_trace_port = 0;
};


