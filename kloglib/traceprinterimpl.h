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
	public:
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
		TraceConfig()
		{
			trace_out = TRACE_OUT ? true : false;
			trace_back = TRACK_OUT ? true : false;
			trace_target_compile = TRACE_COMPILE ? true : false;
			trace_target_console = TRACE_CONSOLE ? true : false;
			trace_target_putty = TRACE_PUTTY ? true : false;
			trace_target_file = TRACE_FILE ? true : false;
			trace_target_socket = TRACE_SOCKET ? true : false;
			out_level = TRACE_OUT_LEVEL;
			trace_module = TRACE_MODULE ? true : false;
			trace_process = TRACE_PROCESS ? true : false;
			async = TRACE_ASYNC ? true : false;
			head = TRACE_HEAD ? true : false;
			head_index = TRACE_HEAD_INDEX ? true : false;
			head_level = TRACE_HEAD_LEVEL ? true : false;
			head_label = TRACE_HEAD_LABEL ? true : false;
			head_datetime = TRACE_HEAD_DATETIME ? true : false;
			head_runtime = TRACE_HEAD_RUNTIME ? true : false;
			head_functiontime = TRACE_HEAD_FUNCTIONTIME ? true : false;
			head_process_name = TRACE_HEAD_PROCESS_NAME ? true : false;
			//head_module_name = TRACE_HEAD_MODULE_NAME ? true : false;
			head_file_name = TRACE_HEAD_FILE_NAME ? true : false;
			head_function_name = TRACE_HEAD_FUNCTION_NAME ? true : false;
			head_line = TRACE_HEAD_LINE ? true : false;
			head_async = TRACE_HEAD_ASYNC ? true : false;
			head_label_text = TRACE_LABEL;
			string program_path = kk::Utility::GetProgramPath();
			string program_directory = kk::Utility::GetDirectoryName(program_path);
			string program_name = kk::Utility::GetFileName(program_path);
			trace_file_name = program_directory + ("logs\\log_") + program_name
				+ "_" + kk::Utility::GetLogDateTimeStr();
			if (head_label_text.empty())
			{
				head_label_text = program_name;
			}
			levels_info[TRACE_ERROR] = LevelInfo((TRACE_ERROR ? true : false), FOREGROUND_INTENSITY | FOREGROUND_RED);
			levels_info[TRACE_WARNING] = LevelInfo((TRACE_WARNING ? true : false), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			levels_info[TRACE_OK] = LevelInfo((TRACE_OK ? true : false), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			levels_info[TRACE_NOTICE] = LevelInfo((TRACE_NOTICE ? true : false), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			levels_info[TRACE_INFO] = LevelInfo((TRACE_INFO ? true : false), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			levels_info[TRACE_DEBUG] = LevelInfo((TRACE_DEBUG ? true : false), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			levels_info[TRACE_TEMP] = LevelInfo((TRACE_TEMP ? true : false), FOREGROUND_INTENSITY);
		}
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
		virtual TraceHead* TraceFormatHead(IN const string& level = "", IN const string& label = "", IN const string& file_name = "", IN const string& func_name = "", IN int line = -1, bool is_back = false) override;
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