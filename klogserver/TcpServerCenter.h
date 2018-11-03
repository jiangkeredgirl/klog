#pragma once

#define KLOG_SERVER_PORT           2012
#define KLOG_SYNC_MESSAGE_PORT     2013
#define KLOG_ASYNC_MESSAGE_PORT    2014


class TcpServerCenter
{
public:
	TcpServerCenter();
	~TcpServerCenter();
	static TcpServerCenter& instance();

public:
	int Run();
};

