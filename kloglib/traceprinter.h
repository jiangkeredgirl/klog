#pragma once
#ifdef KLOGLIB_EXPORTS
#define KLOGLIB_API __declspec(dllexport)
#else
#define KLOGLIB_API __declspec(dllimport)
#endif

#include <string>
#include <map>
using namespace std;

namespace kk
{
	struct TraceHead;
	struct TraceBody;

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
		bool trace_target_compile;
		bool trace_target_console;
		bool trace_target_putty;
		bool trace_target_file;
		bool trace_target_socket;
		int  out_level;
		bool trace_module;
		bool trace_process;
		bool trace_back;
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
		TraceConfig();
	};

	class TracePrinter
	{
	public:
		virtual TraceHead* TraceFormatHead(const string& level = "", const string& label = "", const string& module_name = "", const string& file_name = "", const string& func_name = "", int line = -1, bool is_back = false) = 0;
		virtual TraceBody* TraceFormatBody(const char* log_format, ...) = 0;
		virtual int TraceOutLog(int level, TraceHead* log_head, TraceBody* log_body) = 0;
		virtual const TraceConfig& trace_config() const = 0;
		virtual const TraceConfig& trace_config(const TraceConfig& config) = 0;
		virtual int trace_out_level(int level, bool out) = 0;
		virtual int trace_level_color(int level, int color) = 0;
		virtual int WaitTraceThreadEnd() = 0;
		static string GetModuleName()
		{
			char module_name[100] = { 0 };
			GetModuleFileNameA(GetSelfModuleHandle(), module_name, 100);
			return module_name;
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