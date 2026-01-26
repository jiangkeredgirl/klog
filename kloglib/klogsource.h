#pragma once
#include "tcpclienthandler.h"
#include "TcpPackage.h"
#include "klogsourcecontrol.h"
#include "klogsourcesynctrace.h"
#include "klogsourceasynctrace.h"

class KlogSource 
{
public:
	KlogSource();
	~KlogSource();
	static KlogSource& instance();

public:
	int Connect(const string& ip, int control_port, int sync_trace_port, int async_trace_port, bool async);
	int Disconnect();
	int GetSyncTraceIPandPort(string& ip, int& port);
	int GetAsyncTraceIPandPort(string& ip, int& port);
	int SyncTraceWrite(const string& trace);
	int AsyncTraceWrite(const string& trace);

private:
	string m_server_ip;
	int m_server_control_port = 0;
	int m_server_sync_trace_port = 0;
	int m_server_async_trace_port = 0;
};

