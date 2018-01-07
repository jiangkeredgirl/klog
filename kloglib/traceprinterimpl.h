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
		string func_back;                    ///< function follow flag >> or <<
		string async;                        ///< 是否为异步log	
		string sync_lock;                    ///< 同步模式下是否加锁
		string head_text_;
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
			trace_level_ = 0;
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
		int        trace_level_= 0;
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
		TracePrinterImpl(IN const TracePrinterImpl& other_object);
		const TracePrinterImpl& operator = (IN const TracePrinterImpl& other_object);
		virtual ~TracePrinterImpl(void);
	public:
		static TracePrinterImpl& instance();
	public:
		virtual TraceHead* TraceFormatHead(IN const string& level = "", IN const string& label = "", const string& module_name = "", IN const string& file_name = "", IN const string& func_name = "", IN int line = -1, bool is_back = false) override;
		virtual TraceBody* TraceFormatBody(IN const char* log_format, ...) override;
		virtual int TraceOutLog(IN int level, IN TraceHead* log_head, IN TraceBody* log_body) override;
		virtual const TraceConfig& trace_config() const override;
		virtual const TraceConfig& trace_config(const TraceConfig& config) override;
		virtual int trace_out_level(IN int level, IN bool out) override;
		virtual int trace_level_color(IN int level, IN int color) override;
		virtual int WaitTraceThreadEnd() override;

	private:
		int TraceThreadStart();
		void TraceThread();
		int OutTrace(IN TraceEntry&  trace);
		int OutToCompile(IN TraceEntry&  trace);
		int OutToConsole(IN TraceEntry&  trace);
		int OutToFile(IN TraceEntry&  trace);
		int OutToSocket(IN TraceEntry&  trace);
		int OutToPutty(IN TraceEntry&  trace);
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