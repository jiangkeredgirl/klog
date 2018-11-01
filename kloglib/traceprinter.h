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
	struct TraceConfig
	{
		bool trace_out;
		bool track_out;
		bool output_compile;
		bool output_console;
		bool output_file;
		bool output_socket;
		bool output_com;
		bool file_level;  ///< 是否分等级显示
		bool file_module; ///< 是否分模块显示
		bool file_date;   ///< 是否分日期显示
		bool async;
		bool sync_lock;
		bool head;
		bool head_index;
		bool head_functrack;
		bool head_functime;
		bool head_level;
		bool head_label;
		bool head_threadid;
		bool head_processname;
		bool head_modulename;
		bool head_filename;
		bool head_funcname;
		bool head_line;
		bool head_datetime;
		bool head_runtime;
		bool head_async;
		bool head_synclock;
		int valid_level;	      // 有效输出等级
		int valid_console_level;  // 控制台有效输出等级
		int console_format;       // 默认 0 json模式， 1 print或者cout模式
		int trace_file_size;
		string head_label_text;
		string trace_file_dir;
		string trace_com_name;
		map<int/*level*/, bool> level_on_off;
		TraceConfig();
	};

	class TracePrinter
	{
	public:
		virtual int TraceOutLog(bool is_track, int level, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...) = 0;
		virtual const TraceConfig& trace_config() const = 0;
		virtual const TraceConfig& trace_config(const TraceConfig& config) = 0;
		virtual int WaitTraceThreadEnd() = 0;
		virtual int CreateKlogConsole() = 0;
		virtual int GenerateDumpInfo() = 0;
		virtual int SetKlogConsoleUTF8() = 0;

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