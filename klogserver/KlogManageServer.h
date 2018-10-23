#pragma once
#include "tcpserverhandler.h"

class ITcpServer;
class KlogManageServer : public ITcpServerHandler
{
public:
	KlogManageServer();
	~KlogManageServer();
	static KlogManageServer& instance();

public:
	int ServerStart(int port, bool async);
	int ServerStop();

public:
	virtual int  OnTcpRead(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status) override;
	virtual int  OnTcpWrite(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status) override;
	virtual int  OnTcpConnect(shared_ptr<ITcpConnect> connect, int status) override;
	virtual int  OnTcpDisconnect(shared_ptr<ITcpConnect> connect, int status) override;

private:
	ITcpServer* m_TcpServer = nullptr;
};

