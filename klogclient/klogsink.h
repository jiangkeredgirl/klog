#pragma once
#include "tcpclienthandler.h"
#include "TcpPackage.h"

class IProtocolSerial;
class NetEvent;

class klogsink : public ITcpClientHandler
{
public:
	klogsink();
	~klogsink();
	static klogsink& instance();

public:
	int Connect(const string& ip, int port, bool async);
	int Disconnect();

public:
	virtual int OnTcpConnect(int status) override;
	virtual int OnTcpDisconnect(int status) override;
	virtual int OnTcpRead(const char* data, size_t size, int status) override;
	virtual int OnTcpWrite(const char* data, size_t size, int status) override;

private:
	int HandleKlogManageEvent(const NetEvent& net_event, const string& serial_event_data);
	int HandleKlogManageEvent(const NetEvent& net_event);

private:
	int GetKlogServerPort();

private:
	int SendEvent(const string& serial_event_data);

private:
	ITcpClient*  m_tcp_client = nullptr;
	IProtocolSerial* m_serial_parse = nullptr;
	string m_ip;
	int m_port = 0;
	int m_sync_message_port = 0;
	int m_async_message_port = 0;
};

