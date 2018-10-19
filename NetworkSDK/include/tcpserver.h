#pragma once
#ifdef LIBNETWORK_EXPORTS
#define LIBNETWORK_API __declspec(dllexport)
#else
#define LIBNETWORK_API __declspec(dllimport)
#endif

#include "tcpserverhandler.h"

class ITcpServer
{

public:
	virtual int RegisterHandler(ITcpServerHandler* tcpserver_handler) = 0;
	virtual int Start() = 0;
	virtual int AsyncStart() = 0;
	virtual int Stop() = 0;
	virtual int Broadcast(const char* data, size_t size) = 0;
	virtual int AsyncBroadcast(const char* data, size_t size) = 0;
	virtual int GetConnectsCount() = 0;
};

#ifdef __cplusplus
extern "C" {
#endif

	LIBNETWORK_API ITcpServer* NewTcpServer(int port);
	typedef ITcpServer* (*NewTcpServerFun)(int port);
	LIBNETWORK_API void DeleteTcpServer(ITcpServer* tcp_server);
	typedef void(*DeleteTcpServerFun)(ITcpServer* tcp_server);

#ifdef __cplusplus
}
#endif