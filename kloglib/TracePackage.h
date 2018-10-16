#pragma once
#include <string>
#include <map>
#include <Windows.h>
using namespace std;

#include "traceprinter.h"
#include "traceloader.h"

#define KLOG_USE_DYNAMIC_DLL    1

#if KLOG_USE_DYNAMIC_DLL
#ifdef _WIN64
#ifdef _DEBUG
#define KLOG_DLL_NAME  "kloglib_x64_Debug.dll"
#else
#define KLOG_DLL_NAME  "kloglib_x64_Release.dll"
#endif
#else
#ifdef _DEBUG
#define KLOG_DLL_NAME  "kloglib_x32_Debug.dll"
#else
#define KLOG_DLL_NAME  "kloglib_x32_Release.dll"
#endif
#endif
#endif

namespace KKTracePackage
{ 
	class TraceLibrary
	{
	private:
		TraceLibrary()
		{
			LoadTraceDll();
		}
	public:
		~TraceLibrary()
		{
			FreeTraceDll();
		}

	public:
		static TraceLibrary* instance()
		{
			static TraceLibrary _instance;
			return &_instance;
		}

	private:
		int LoadTraceDll()
		{
			int errorCode = 1;
			do
			{
				if (m_hDll)
				{
					break;
				}
#if KLOG_USE_DYNAMIC_DLL
				m_hDll = LoadLibraryA(KLOG_DLL_NAME);
#endif
				if (m_hDll == nullptr)
				{
					break;
				}				
				m_TracePrinterInstance = (kk::TracePrinterInstanceFun)GetProcAddress(m_hDll, "TracePrinterInstance");
				if (m_TracePrinterInstance == nullptr)
				{
					int error = GetLastError();
					FreeLibrary(m_hDll);
					m_hDll = nullptr;
					break;
				}				
				m_NewTraceLoader = (kk::NewTraceLoaderFun)GetProcAddress(m_hDll, "NewTraceLoader");
				if (m_NewTraceLoader == nullptr)
				{
					int error = GetLastError();
					FreeLibrary(m_hDll);
					m_hDll = nullptr;
					break;
				}
				m_DeleteTraceLoader = (kk::DeleteTraceLoaderFun)GetProcAddress(m_hDll, "DeleteTraceLoader");
				if (m_DeleteTraceLoader == nullptr)
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
		int FreeTraceDll()
		{
			if (m_hDll)
			{
				FreeLibrary(m_hDll);
			}
			m_hDll = nullptr;
			m_TracePrinterInstance = nullptr;
			m_NewTraceLoader = nullptr;
			m_DeleteTraceLoader = nullptr;
			return 0;
		}
	public:
		HMODULE m_hDll = nullptr;
		kk::TracePrinterInstanceFun m_TracePrinterInstance = nullptr;
		kk::NewTraceLoaderFun m_NewTraceLoader = nullptr;
		kk::DeleteTraceLoaderFun m_DeleteTraceLoader = nullptr;
	};

	class TracePrinter
	{
	private:
		TracePrinter()
		{
#if KLOG_USE_DYNAMIC_DLL
			if (TraceLibrary::instance()->m_TracePrinterInstance)
			{
				m_TracePrinter = TraceLibrary::instance()->m_TracePrinterInstance();
			}
#else
			m_TracePrinter = kk::TracePrinterInstance();
#endif
		}

	public:
		static TracePrinter* instance()
		{
			static TracePrinter _instance;
			return &_instance;
		}
		template <typename... Args>
		int TraceOutLog(bool is_track, int level, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, Args... args)
		{
			if (m_TracePrinter)
			{
				m_TracePrinter->TraceOutLog(is_track, level, label, module_name, file_name, func_name, line, log_format, args...);
			}
			return 0;
		}

		virtual int WaitTraceThreadEnd()
		{
			if (m_TracePrinter)
			{
				m_TracePrinter->WaitTraceThreadEnd();
			}
			return 0;
		}

		virtual int CreateKlogConsole()
		{
			if (m_TracePrinter)
			{
				m_TracePrinter->CreateKlogConsole();
			}
			return 0;
		}

		virtual int SetKlogConsoleUTF8()
		{
			if (m_TracePrinter)
			{
				m_TracePrinter->SetKlogConsoleUTF8();
			}
			return 0;
		}

		virtual int GenerateDumpInfo()
		{
			if (m_TracePrinter)
			{
				m_TracePrinter->GenerateDumpInfo();
			}
			return 0;
		}

	public:
		static string GetModuleName()
		{
			char module_name[100] = { 0 };
			GetModuleFileNameA(GetSelfModuleHandle(), module_name, 100);
			return GetFileName(module_name);
		}
	public:
		static string GetFileName(const string& path_name)
		{
			string file_name(path_name);
			string::size_type pos = file_name.find_last_of("\\/");
			if (pos != string::npos)
			{
				file_name = file_name.substr(pos + 1);
			}
			return file_name;
		}
	private:
		static HMODULE GetSelfModuleHandle()
		{
			MEMORY_BASIC_INFORMATION mbi;
			return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0) ? (HMODULE)mbi.AllocationBase : NULL);
		}
	private:
		kk::TracePrinter* m_TracePrinter = nullptr;		
	};

	class TraceLoader
	{
	public:
		template <typename... Args>
		TraceLoader(bool is_track, int level, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, Args... args)
		{
#if KLOG_USE_DYNAMIC_DLL
			if (TraceLibrary::instance()->m_NewTraceLoader)
			{
				m_TraceLoader = TraceLibrary::instance()->m_NewTraceLoader(is_track, level, label, module_name, file_name, func_name, line, log_format, args...);
			}
#else
			m_TraceLoader = kk::NewTraceLoader(is_track, level, label, module_name, file_name, func_name, line, log_format, args...);
#endif
		}
		~TraceLoader()
		{
			if (m_TraceLoader)
			{
#if KLOG_USE_DYNAMIC_DLL
				if (TraceLibrary::instance()->m_DeleteTraceLoader)
				{
					TraceLibrary::instance()->m_DeleteTraceLoader(m_TraceLoader);
				}
#else
				kk::DeleteTraceLoader(m_TraceLoader);
#endif
				m_TraceLoader = nullptr;
			}
		}
		stringstream& trace_stream()
		{
			static stringstream ss;
			if (m_TraceLoader)
			{
				return m_TraceLoader->trace_stream();
			}
			ss.str("");
			return ss;
		}

	private:
		kk::TraceLoader* m_TraceLoader = nullptr;
	};
}
