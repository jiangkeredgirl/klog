#pragma once

#include "trace.h"
#include "utility.h"
#include "traceconfig.h"
#pragma warning( disable: 4251 )

namespace kk
{

	typedef struct TRACE_API _TTraceHead
	{
	public:
		string index;                        ///< log序号
		string level;                        ///< log等级
		string label;                        ///< log标识		
		string datetime;                     ///< log打印日期时间
		string runtime;                      ///< log打印时程序运行时间
		string executetime;                  ///< 函数体执行时间
		string process_name;                 ///< 进程名
		//string module_name;                  ///< 模块名	
		string file_name;                    ///< file name;
		string function_name;                ///< function name;
		string line;                         ///< line number;
		string func_back;                    ///< function follow flag >> or <<
		string async;                        ///< 是否为异步log			

		string head_text() const;
	}TTraceHead;

	typedef struct TRACE_API _TTraceBody
	{
	public:
		string body;

		string body_text() const;
	}TTraceBody;

	typedef struct TRACE_API _TTraceData
	{
	public:
		_TTraceData()
		{
			trace_level_ = 0;
		}
	public:
		TTraceHead trace_head_;
		TTraceBody trace_body_;
		int            trace_level_;
	public:
		int trace_head(const TTraceHead& _trace_head)
		{
			trace_head_ = _trace_head;
			return 0;
		}
		const TTraceHead& trace_head() const
		{
			return trace_head_;
		}
		int trace_body(const TTraceBody& _trace_body)
		{
			trace_body_ = _trace_body;
			return 0;
		}
		const TTraceBody& trace_body() const
		{
			return trace_body_;
		}
		string trace_text() const;

	}TTraceData;

	typedef struct TRACE_API _TLevelInfo
	{
		bool is_out;
		int  color;
		_TLevelInfo()
		{
			is_out = true;
			color = 0;
		}
		_TLevelInfo(bool _is_out, int  _color)
		{
			is_out = _is_out;
			color = _color;
		}
	}LevelInfo;
	typedef struct TRACE_API _TTraceConfig
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
		bool head;
		bool head_index;
		bool head_level;
		bool head_label;
		bool head_datetime;
		bool head_runtime;
		bool head_functiontime;
		bool head_process_name;
		//bool head_module_name;
		bool head_file_name;
		bool head_function_name;
		bool head_line;
		bool head_async;
		string head_label_text;
		string trace_file_name;
		map<int/*level*/, LevelInfo> levels_info;
		_TTraceConfig()
		{
			trace_out = TRACE_OUT ? true : false;
			trace_back = TRACE_BACK_OUT ? true : false;
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
	}TTraceConfig;

	class  TRACE_API TracePrint
	{
	private:
		TracePrint(void);
		TracePrint(IN const TracePrint& other_object);
		const TracePrint& operator = (IN const TracePrint& other_object);
		virtual ~TracePrint(void);
	public:
		static TracePrint& instance();
	public:
		TTraceHead TraceFormatHead(IN const string& level = "", IN const string& label = "", IN const string& file_name = "", IN const string& func_name = "", IN int line = -1, bool is_back = false);
		TTraceBody TraceFormatBody(IN const char* log_format, ...);
		int TraceOutLog(IN int level, IN const TTraceHead& log_head, IN const TTraceBody& log_body);
		const TTraceConfig& trace_config() const;
		const TTraceConfig& trace_config(const TTraceConfig& config);
		int trace_out_level(IN int level, IN bool out);
		int trace_level_color(IN int level, IN int color);
		int WaitTraceThreadEnd();

	private:
		int TraceThreadStart();
		void TraceThread();
		int OutTrace(IN const TTraceData&  trace);
		int OutToCompile(IN const TTraceData&  trace);
		int OutToConsole(IN const TTraceData&  trace);
		int OutToFile(IN const TTraceData&  trace);
		int OutToSocket(IN const TTraceData&  trace);
		int OutToPutty(IN const TTraceData&  trace);
		int InitConsole();

	private:
		mutex                 trace_mutex_;
		condition_variable    trace_condition_;
		thread                trace_thread_;
		bool                  trace_thread_kill_;
		list<TTraceData>      traces_list_;
		mutex                 trace_list_mutex_;
		TTraceConfig          trace_config_;
		string                process_name_;
		//string                module_name_;
	};

	//template<class sCout_type>
	class TRACE_API TraceOne
	{
	public:
		TraceOne(IN bool is_back, IN int level, IN const TTraceHead& trace_head, IN const TTraceBody& trace_body = TTraceBody());
		~TraceOne();
		stringstream& trace_stream();

	private:
		bool                is_back_;
		int                 trace_level_;
		TTraceData          trace_info_;
		__int64             begin_call_time_;
		stringstream        trace_stream_;
	};

}