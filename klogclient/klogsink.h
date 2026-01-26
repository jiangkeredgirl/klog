#pragma once
#include "tcpclienthandler.h"
#include "TcpPackage.h"
#include "klogsinkcontrol.h"
#include "klogsinksynctrace.h"
#include "klogsinkasynctrace.h"


class KlogSink
{
public:
	KlogSink();
	~KlogSink();
	static KlogSink& instance();

public:
	int Connect(const string& ip, int control_port, int sync_trace_port, int async_trace_port, bool async);
	int Disconnect();

private:
	string m_server_ip;
	int m_server_control_port = 0;
	int m_server_sync_trace_port = 0;
	int m_server_async_trace_port = 0;
};


