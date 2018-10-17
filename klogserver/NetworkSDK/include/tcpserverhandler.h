#pragma once

#include <string>
#include <memory>

using namespace std;

class ITcpConnect
{
public:	
	virtual int Write(const char* data, size_t size) = 0;
	virtual int AsyncWrite(const char* data, size_t size) = 0;
	virtual string RemoteIP() = 0;
	virtual int RemotePort() = 0;
};

class ITcpServerHandler
{ 
public:
	virtual int  OnTcpRead(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status) = 0;
	virtual int  OnTcpWrite(shared_ptr<ITcpConnect> connect, const char* data, size_t size, int status) = 0;
	virtual int  OnTcpConnect(shared_ptr<ITcpConnect> connect, int status) = 0;
	virtual int  OnTcpDisconnect(shared_ptr<ITcpConnect> connect, int status) = 0;
};




