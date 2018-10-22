#pragma once
#include <string>
#include <map>
#include <Windows.h>
using namespace std;

#include "protocolserial.h"


#define KLOGNETPROTOCOL_USE_DYNAMIC_DLL    1

#if KLOGNETPROTOCOL_USE_DYNAMIC_DLL
#ifdef _WIN64
#ifdef _DEBUG
#define KLOGNETPROTOCOL_DLL_NAME  "klognetprotocollib_x64_Debug.dll"
#else
#define KLOGNETPROTOCOL_DLL_NAME  "klognetprotocollib_x64_Release.dll"
#endif
#else
#ifdef _DEBUG
#define KLOGNETPROTOCOL_DLL_NAME  "klognetprotocollib_x32_Debug.dll"
#else
#define KLOGNETPROTOCOL_DLL_NAME  "klognetprotocollib_x32_Release.dll"
#endif
#endif
#endif


class KlogNetProtocolLibrary
{
private:
	KlogNetProtocolLibrary()
	{
		LoadKlogNetProtocolDll();
	}
public:
	~KlogNetProtocolLibrary()
	{
		FreeKlogNetProtocolDll();
	}

public:
	static KlogNetProtocolLibrary* instance()
	{
		static KlogNetProtocolLibrary _instance;
		return &_instance;
	}

public:
	IProtocolSerial* GetProtocolSerial()
	{
		return m_serial;
	}

private:
	int LoadKlogNetProtocolDll()
	{
		int errorCode = 1;
		do
		{
			if (m_hDll)
			{
				break;
			}
#if KLOGNETPROTOCOL_USE_DYNAMIC_DLL
			m_hDll = LoadLibraryA(KLOGNETPROTOCOL_DLL_NAME);
#endif
			if (m_hDll == nullptr)
			{
				break;
			}
			m_NewSerial = (NewSerialFun)GetProcAddress(m_hDll, "NewSerial");
			if (m_NewSerial == nullptr)
			{
				int error = GetLastError();
				FreeLibrary(m_hDll);
				m_hDll = nullptr;
				break;
			}
			m_DeleteSerial = (DeleteSerialFun)GetProcAddress(m_hDll, "DeleteSerial");
			if (m_DeleteSerial == nullptr)
			{
				int error = GetLastError();
				FreeLibrary(m_hDll);
				m_hDll = nullptr;
				break;
			}
			errorCode = 1;
		} while (0);
#if KLOGNETPROTOCOL_USE_DYNAMIC_DLL
		if (m_NewSerial)
		{
			m_serial = m_NewSerial();
		}
#else
		m_serial = ::NewSerial();
#endif
		return errorCode;
	}

	int FreeKlogNetProtocolDll()
	{
#if KLOGNETPROTOCOL_USE_DYNAMIC_DLL
		if (m_DeleteSerial)
		{
			m_DeleteSerial(m_serial);
		}
#else
		::DeleteSerial(m_serial);
#endif
		m_serial = nullptr;
		if (m_hDll)
		{
			FreeLibrary(m_hDll);
		}
		m_hDll = nullptr;
		m_NewSerial = nullptr;
		m_DeleteSerial = nullptr;
		return 0;
	}

public:
	HMODULE m_hDll = nullptr;
	NewSerialFun m_NewSerial = nullptr;
	DeleteSerialFun m_DeleteSerial = nullptr;
	IProtocolSerial* m_serial = nullptr;
};