#pragma once

#include "kutility.h"
#include "tracedefine.h"
#include "TracePrinter.h"

#pragma warning( disable: 4251 )

namespace kk
{

	struct TraceEntry
	{
		bool     is_track = false;
		__int64  index = 0;                    ///< log序号
		string   func_track;                   ///< function follow flag >>	or <<
		__int64  func_time = 0;                ///< 函数体执行时间
		int      level = 0;                    ///< log等级
		string   label;                        ///< log标识	
		__int64  thread_id;                    ///< 线程id
		string   process_name;                 ///< 进程名
		string   module_name;                  ///< 模块名
		string   file_name;                    ///< file name;
		string   func_name;                    ///< function name;
		int      line = 0;                     ///< line number;
		__int64  datetime = 0;                 ///< log打印日期时间
		__int64  runtime = 0;                  ///< log打印时程序运行时间
		bool     async = false;                ///< 是否为异步log
		bool     sync_lock = false;            ///< 同步模式下是否加锁
		string   content;                      ///< log内容
		const    string& trace_text();
	private:
		string trace_text_;
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
		virtual int TraceOutLog(bool is_track, int level, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...) override;
		virtual const TraceConfig& trace_config() const override;
		virtual const TraceConfig& trace_config(const TraceConfig& config) override;
		virtual int WaitTraceThreadEnd() override;
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
	public:
		string LevelToStr(int level);
		int StrToLevel(const string& str);

	private:
		mutex                 trace_mutex_;
		condition_variable    trace_condition_;
		thread                trace_thread_;
		bool                  trace_thread_kill_;
		list<shared_ptr<TraceEntry>>     traces_list_;
		//mutex                 trace_list_mutex_;
		mutex                 trace_sync_mutex_;
		string                process_name_;
		string                process_time_;
		TraceConfig           trace_config_;		
		map<int/*level*/, int/*color*/> default_level_color_;
		map<int, string>         level_to_str_;
		map<string, int>         str_to_level_;
	};
}