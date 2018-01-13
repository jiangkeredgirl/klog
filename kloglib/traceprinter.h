#pragma once

#ifdef KLOGLIB_EXPORTS
#define KLOGLIB_API __declspec(dllexport)
#else
#define KLOGLIB_API __declspec(dllimport)
#endif

#include <string>
#include <map>
#include <Windows.h>
using namespace std;

namespace kk
{
	struct LevelInfo
	{
		bool is_out;
		int  color;
		LevelInfo()
		{
			is_out = true;
			color = 0;
		}
		LevelInfo(bool _is_out, int  _color)
		{
			is_out = _is_out;
			color = _color;
		}
	};

	struct TraceConfig
	{
		bool trace_out;
		bool track_out;
		bool trace_target_compile;
		bool trace_target_console;
		bool trace_target_putty;
		bool trace_target_file;
		bool trace_target_socket;		
		bool trace_module;
		bool trace_process;
		bool async;
		bool sync_lock;
		bool head;
		bool head_index;
		bool head_level;
		bool head_label;
		bool head_thread_id;
		bool head_datetime;
		bool head_runtime;
		bool head_functiontime;
		bool head_process_name;
		bool head_module_name;
		bool head_file_name;
		bool head_function_name;
		bool head_line;
		bool head_async;
		bool head_sync_lock;
		string head_label_text;
		string trace_file_name;
		map<int/*level*/, LevelInfo> levels_info;
		int valid_level;
		int trace_file_size;
		TraceConfig();
	};

	class TracePrinter
	{
	public:
		virtual int TraceOutLog(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...) = 0;
		virtual const TraceConfig& trace_config() const = 0;
		virtual const TraceConfig& trace_config(const TraceConfig& config) = 0;
		static string GetModuleName()
		{
			char module_name[100] = { 0 };
			GetModuleFileNameA(GetSelfModuleHandle(), module_name, 100);
			return GetFileName(module_name);
		}
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
	};

#ifdef __cplusplus
	extern "C" {
#endif
		KLOGLIB_API TracePrinter* TracePrinterInstance(void);
#ifdef __cplusplus
	}
#endif
	typedef TracePrinter* (*TracePrinterInstanceFun)(void);
}