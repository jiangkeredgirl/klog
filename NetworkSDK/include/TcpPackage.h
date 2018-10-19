#pragma once
#include <string>
#include <map>
#include <Windows.h>
using namespace std;

#include "tcpclient.h"
#include "tcpserver.h"


#define KNETWORK_USE_DYNAMIC_DLL    1

#if KNETWORK_USE_DYNAMIC_DLL
#ifdef _WIN64
#ifdef _DEBUG
#define KNETWORK_DLL_NAME  "LibNetwork_x64_Debug.dll"
#else
#define KNETWORK_DLL_NAME  "LibNetwork_x64_Release.dll"
#endif
#else
#ifdef _DEBUG
#define KNETWORK_DLL_NAME  "LibNetwork_x32_Debug.dll"
#else
#define KNETWORK_DLL_NAME  "LibNetwork_x32_Release.dll"
#endif
#endif
#endif


class TcpLibrary
{
private:
	TcpLibrary()
	{
		LoadTcpDll();
	}
public:
	~TcpLibrary()
	{
		FreeTcpDll();
	}

public:
	static TcpLibrary* instance()
	{
		static TcpLibrary _instance;
		return &_instance;
	}

public:
	ITcpServer* NewTcpServer(int port)
	{
		ITcpServer* server = nullptr;
#if KNETWORK_USE_DYNAMIC_DLL
		if (m_NewTcpServer)
		{
			server = m_NewTcpServer(port);
		}
#else
		server = ::NewTcpServer(port);
#endif
		return server;
	}

	void DeleteTcpServer(ITcpServer* tcp_server)
	{
#if KNETWORK_USE_DYNAMIC_DLL
		if (m_DeleteTcpServer)
		{
			m_DeleteTcpServer(tcp_server);
		}
#else
		::DeleteTcpServer(tcp_server);
#endif
	}

	ITcpClient* NewTcpClient(void)
	{
		ITcpClient* client = nullptr;
#if KNETWORK_USE_DYNAMIC_DLL
		if (m_NewTcpClient)
		{
			client = m_NewTcpClient();
		}
#else
		client = ::NewTcpClient();
#endif
		return client;
	}

	void DeleteTcpClient(ITcpClient* tcp_client)
	{
#if KNETWORK_USE_DYNAMIC_DLL
		if (m_DeleteTcpClient)
		{
			m_DeleteTcpClient(tcp_client);
		}
#else
		::DeleteTcpClient(tcp_client);
#endif
	}


private:
	int LoadTcpDll()
	{
		int errorCode = 1;
		do
		{
			if (m_hDll)
			{
				break;
			}
#if KNETWORK_USE_DYNAMIC_DLL
			m_hDll = LoadLibraryA(KNETWORK_DLL_NAME);
#endif
			if (m_hDll == nullptr)
			{
				break;
			}
			m_NewTcpServer = (NewTcpServerFun)GetProcAddress(m_hDll, "NewTcpServer");
			if (m_NewTcpServer == nullptr)
			{
				int error = GetLastError();
				FreeLibrary(m_hDll);
				m_hDll = nullptr;
				break;
			}
			m_DeleteTcpServer = (DeleteTcpServerFun)GetProcAddress(m_hDll, "DeleteTcpServer");
			if (m_DeleteTcpServer == nullptr)
			{
				int error = GetLastError();
				FreeLibrary(m_hDll);
				m_hDll = nullptr;
				break;
			}
			m_NewTcpClient = (NewTcpClientFun)GetProcAddress(m_hDll, "NewTcpClient");
			if (m_NewTcpClient == nullptr)
			{
				int error = GetLastError();
				FreeLibrary(m_hDll);
				m_hDll = nullptr;
				break;
			}
			m_DeleteTcpClient = (DeleteTcpClientFun)GetProcAddress(m_hDll, "DeleteTcpClient");
			if (m_DeleteTcpClient == nullptr)
			{
				int error = GetLastError();
				FreeLibrary(m_hDll);
				m_hDll = nullptr;
				break;
			}
			errorCode = 1;
		} while (0);
		return errorCode;
	}
	int FreeTcpDll()
	{
		if (m_hDll)
		{
			FreeLibrary(m_hDll);
		}
		m_hDll = nullptr;
		m_NewTcpServer = nullptr;
		m_DeleteTcpServer = nullptr;
		m_NewTcpClient = nullptr;
		m_DeleteTcpClient = nullptr;
		return 0;
	}
public:
	HMODULE m_hDll = nullptr;
	NewTcpServerFun m_NewTcpServer = nullptr;
	DeleteTcpServerFun m_DeleteTcpServer = nullptr;
	NewTcpClientFun m_NewTcpClient = nullptr;
	DeleteTcpClientFun m_DeleteTcpClient = nullptr;
};