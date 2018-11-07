#pragma once
#include "tcpserverhandler.h"
#include "cstandard.h"
#include "klognetprotocol.h"

class ITcpServer;
class IProtocolSerial;
class NetEvent;

class KlogAsyncMessageServer : public ITcpServerHandler
{
public:
	KlogAsyncMessageServer();
	~KlogAsyncMessageServer();
	static KlogAsyncMessageServer& instance();

public:
	int ServerStart(int port, bool async);
	int ServerStop();

public:
	virtual int  OnTcpRead(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status) override;
	virtual int  OnTcpWrite(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status) override;
	virtual int  OnTcpConnect(shared_ptr<ITcpConnect> connect, int status) override;
	virtual int  OnTcpDisconnect(shared_ptr<ITcpConnect> connect, int status) override;

private:
	int ParseKlogMessageEvent(const NetEvent& net_event, const string& serial_event_data, shared_ptr<ITcpConnect> connect);
	int HandleKlogMessageEvent(const NetEvent& net_event, shared_ptr<ITcpConnect> connect);

private:
	int SendEvent(const string& serial_event_data, shared_ptr<ITcpConnect> connect);

private:
	ITcpServer* m_TcpServer = nullptr;
	IProtocolSerial* m_serial_parse = nullptr;
	list<shared_ptr<ITcpConnect> /*connect*/> m_source_connects;
	list<shared_ptr<ITcpConnect> /*connect*/> m_sinck_connects;
};

