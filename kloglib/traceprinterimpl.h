#pragma once

#include "kutility.h"
#include "tracedefine.h"
#include "TracePrinter.h"

#pragma warning( disable: 4251 )

class IProtocolSerial;

namespace kk
{
	class TracePrinterImpl : public TracePrinter
	{
	private:
		TracePrinterImpl(void);
		TracePrinterImpl(const TracePrinterImpl& other_object);
		const TracePrinterImpl& operator = (const TracePrinterImpl& other_object);
		virtual ~TracePrinterImpl(void);
	public:
		static TracePrinterImpl& instance();
	public:
		virtual int TraceOutLog(bool is_track, int level, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...) override;
		virtual const TraceConfig& trace_config() const override;
		virtual const TraceConfig& trace_config(const TraceConfig& config) override;
		virtual int WaitTraceThreadEnd() override;
		virtual int CreateKlogConsole() override;
		virtual int GenerateDumpInfo() override;
		virtual int SetKlogConsoleUTF8() override;

	public:
		shared_ptr<TraceEntry> TraceFormatEntry(bool is_track, int level, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const string& log_body);
		int OutTraceEntry(shared_ptr<TraceEntry> trace_entry);
	public:
		bool IsOut(bool is_track, int level);
	private:
		int trace_valid_level(int level, bool out);
		int trace_level_color(int level, int color);
		int InitTrace();				

	private:
		int TraceThreadStart();
		void TraceThread();
		int OutTrace(shared_ptr<TraceEntry> trace_entry);
		int OutToCompile(shared_ptr<TraceEntry> trace_entry);
		int OutToConsole(shared_ptr<TraceEntry> trace_entry);
		int OutToFile(shared_ptr<TraceEntry> trace_entry);
		int OutToSocket(shared_ptr<TraceEntry> trace_entry);
		int OutToCom(shared_ptr<TraceEntry> trace_entry);
		int OutToFile(const string& trace_file_name, const string& trace_entry);
		int InitConsole();
		int SetConsoleUTF8();
		int InitSocket();
	public:
		string LevelToStr(int level);
		int StrToLevel(const string& str);

	private:
		mutex                 trace_mutex_;
		condition_variable    trace_condition_;
		thread                trace_thread_;
		bool                  trace_thread_kill_;
		list<shared_ptr<TraceEntry>>     traces_list_;
		mutex                 trace_list_mutex_;
		mutex                 trace_sync_mutex_;
		string                process_name_;
		string                process_time_;
		TraceConfig           trace_config_;		
		map<int/*level*/, int/*color*/> default_level_color_;
		map<int, string>         level_to_str_;
		map<string, int>         str_to_level_;
		IProtocolSerial*         serial_parse_ = nullptr;
	};
}



#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include <fmt/printf.h>

#if 0
static inline std::string FormatLogV(const char* log_format, va_list args)
{
	if (!log_format)
		return "";

	try
	{
		if (strchr(log_format, '{'))
		{
			return fmt::vformat(log_format, fmt::make_format_args(args));
		}
		else
		{
			return fmt::vsprintf(log_format, args);
		}
	}
	catch (...)
	{
		return std::string("format error: ") + log_format;
	}
}
#endif
#include <string>
#include <cstdarg>
#include <fmt/core.h>
#include <fmt/printf.h>

#if 0
static inline std::string FormatLogV(const char* log_format, va_list args)
{
	if (!log_format)
		return "";

	try
	{
		// 判断 {} 风格
		if (strchr(log_format, '{'))
		{
			return fmt::vformat(log_format, fmt::make_format_args(args));
		}
		else
		{
			return fmt::vsprintf(log_format, args);
		}
	}
	catch (...)
	{
		return std::string("format error: ") + log_format;
	}
}
#endif

#include <string>
#include <cstdarg>
#include <vector>
#include <cstdio>

#if 0
static inline std::string FormatLogV(const char* log_format, va_list args)
{
	if (!log_format)
		return "";

	va_list args_copy;
	va_copy(args_copy, args);

	int size = std::vsnprintf(nullptr, 0, log_format, args_copy);
	va_end(args_copy);

	if (size <= 0)
		return "";

	std::vector<char> buf(size + 1);
	std::vsnprintf(buf.data(), buf.size(), log_format, args);

	return std::string(buf.data());
}
#endif

#include <string>
#include <cstdarg>
#include <vector>
#include <cstdio>

static inline std::string FormatLogV(const char* log_format, va_list args)
{
	if (!log_format)
		return "";

	va_list args_copy;
	va_copy(args_copy, args);

	int size = std::vsnprintf(nullptr, 0, log_format, args_copy);
	va_end(args_copy);

	if (size <= 0)
		return "";

	std::vector<char> buf(size + 1);
	std::vsnprintf(buf.data(), buf.size(), log_format, args);

	return std::string(buf.data());
}
