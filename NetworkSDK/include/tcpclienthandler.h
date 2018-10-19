#pragma once

#include <string>
#include <memory>

using namespace std;

class ITcpClientHandler
{ 
public:
	virtual int OnTcpConnect(int status) = 0;
	virtual int OnTcpDisconnect(int status) = 0;
	virtual int OnTcpRead(const char* data, size_t size, int status) = 0;
	virtual int OnTcpWrite(const char* data, size_t size, int status) = 0;
};




