#pragma once
#include "tcpclienthandler.h"
#include "TcpPackage.h"

class IProtocolSerial;
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
	int GetKlogServerPort();

private:
	ITcpClient*  m_tcp_client = nullptr;
	IProtocolSerial* m_serial_parse = nullptr;
	string m_ip;
	int m_port = 0;
};

