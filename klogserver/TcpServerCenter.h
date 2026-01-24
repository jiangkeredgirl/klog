#pragma once

#define KLOG_SERVER_CONTROL_PORT        2012
#define KLOG_SERVER_SYNC_TRACE_PORT     2013
#define KLOG_SERVER_ASYNC_TRACE_PORT    2014


class TcpServerCenter
{
public:
	TcpServerCenter();
	~TcpServerCenter();
	static TcpServerCenter& instance();

public:
	int Run();
};

