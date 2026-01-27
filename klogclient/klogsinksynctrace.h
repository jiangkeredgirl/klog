#pragma once
#include "tcpclienthandler.h"
#include "TcpPackage.h"
#include "klognetprotocol.h"
#include "klogsink.h"

class IProtocolSerial;
class NetEvent;

class KlogSinkSyncTrace : public ITcpClientHandler
{
public:
	KlogSinkSyncTrace();
	~KlogSinkSyncTrace();
	static KlogSinkSyncTrace& instance();

public:
	int Connect(const string& ip, int port, bool async);
	int Disconnect();
	int RegisterNetSinkFunction(KlogNetSinkFunction callback);

public:
	virtual int OnTcpConnect(int status) override;
	virtual int OnTcpDisconnect(int status) override;
	virtual int OnTcpRead(const char* data, size_t size, int status) override;
	virtual int OnTcpWrite(const char* data, size_t size, int status) override;

private:
	int ParseKlogEvent(const NetEvent& net_event, const string& serial_event_data);
	int HandleKlogEvent(const NetEvent& net_event);

private:
	int SendKlogClientType();

private:
	int SendEvent(const string& serial_event_data);

private:
	IProtocolSerial* m_serial_parse = nullptr;
	ITcpClient* m_tcp_client = nullptr;
	string m_server_ip;
	int m_server_port = 0;
	KlogNetSinkFunction m_callbackf = nullptr;
};
