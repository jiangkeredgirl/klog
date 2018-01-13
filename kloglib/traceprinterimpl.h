#pragma once

#include "kutility.h"
#include "tracedefine.h"
#include "TracePrinter.h"

#pragma warning( disable: 4251 )

namespace kk
{

	struct TraceHead
	{
	public:
		string index;                        ///< log序号
		string level;                        ///< log等级
		string label;                        ///< log标识	
		string thread_id;                    ///< 线程id
		string datetime;                     ///< log打印日期时间
		string runtime;                      ///< log打印时程序运行时间
		string executetime;                  ///< 函数体执行时间
		string process_name;                 ///< 进程名
		string module_name;                  ///< 模块名
		string file_name;                    ///< file name;
		string function_name;                ///< function name;
		string line;                         ///< line number;
		string func_track;                    ///< function follow flag >> or <<
		string async;                        ///< 是否为异步log
		string sync_lock;                    ///< 同步模式下是否加锁
		string head_text_;
		bool   is_track = false;
		int    trace_level = 0;
		const string& head_text();
	};

	struct TraceBody
	{
	public:
		string body;
		string body_text_;
		const string& body_text();
	};

	struct TraceEntry
	{
	public:
		TraceEntry()
		{
		}
		~TraceEntry()
		{
			if (trace_head_)
			{
				delete trace_head_;
				trace_head_ = nullptr;
			}
			if (trace_body_)
			{
				delete trace_body_;
				trace_body_ = nullptr;
			}
		}
	public:
		TraceHead* trace_head_ = nullptr;
		TraceBody* trace_body_ = nullptr;
		string     trace_text_;
	public:
		int trace_head(TraceHead* _trace_head)
		{
			trace_head_ = _trace_head;
			return 0;
		}
		TraceHead* trace_head()
		{
			return trace_head_;
		}
		int trace_body(TraceBody* _trace_body)
		{
			trace_body_ = _trace_body;
			return 0;
		}
		TraceBody* trace_body()
		{
			return trace_body_;
		}
		const string& trace_text();

	};


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
		virtual int TraceOutLog(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...) override;
		virtual const TraceConfig& trace_config() const override;
		virtual const TraceConfig& trace_config(const TraceConfig& config) override;
	public:
		TraceEntry* TraceFormatEntry(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...);
		int OutTraceEntry(TraceEntry* trace_entry);
	private:
		TraceHead* TraceFormatHead(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line);
		TraceBody* TraceFormatBody(bool is_track, int level, const char* log_format, ...);
	public:
		bool IsOut(bool is_track, int level);
	private:
		int trace_valid_level(int level, bool out);
		int trace_level_color(int level, int color);
		int WaitTraceThreadEnd();

	private:
		int TraceThreadStart();
		void TraceThread();
		int OutTrace(TraceEntry&  trace);
		int OutToCompile(TraceEntry&  trace);
		int OutToConsole(TraceEntry&  trace);
		int OutToFile(TraceEntry&  trace);
		int OutToSocket(TraceEntry&  trace);
		int OutToPutty(TraceEntry&  trace);
		int InitConsole();

	private:
		mutex                 trace_mutex_;
		condition_variable    trace_condition_;
		thread                trace_thread_;
		bool                  trace_thread_kill_;
		list<TraceEntry*>     traces_list_;
		mutex                 trace_list_mutex_;
		TraceConfig           trace_config_;
		string                process_name_;
		//string                module_name_;
	};
}