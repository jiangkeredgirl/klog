// traceprint.cpp : Defines the exported functions for the DLL application.
//

#include "traceprintimpl.h"

namespace kk
{

	string TTraceHead::head_text() const
	{
		string text;
		if (TracePrint::instance().trace_config().trace_out
			&& ((TracePrint::instance().trace_config().head && func_back.empty()) || (TracePrint::instance().trace_config().trace_back && !func_back.empty())))
		{
			text = "\"head\": {";
			bool have_field = false;
			if (!func_back.empty())
			{
				text = text + (have_field ? ", " : "") + "\"func_back\":" + "\"" + func_back + "\"";
				have_field = true;
			}
			if (TracePrint::instance().trace_config().head_index)
			{
				text = text + (have_field ? ", " : "") + "\"index\":" + "\"" + index + "\"";
				have_field = true;
			}
			if (TracePrint::instance().trace_config().head_level)
			{
				text = text + (have_field ? ", " : "") + "\"level\":" + "\"" + level + "\"";
				have_field = true;
			}
			if (TracePrint::instance().trace_config().head_label)
			{
				text = text + (have_field ? ", " : "") + "\"label\":" + "\"" + label + "\"";
				have_field = true;
			}
			if (TracePrint::instance().trace_config().head_process_name)
			{
				text = text + (have_field ? ", " : "") + "\"process_name\":" + "\"" + process_name + "\"";
				have_field = true;
			}
			//if (TracePrint::instance().trace_config().head_module_name)
			//{
			//	text = text + (have_field ? ", " : "") + "\"module_name\":" + "\"" + module_name + "\"";
			//	have_field = true;
			//}
			if (TracePrint::instance().trace_config().head_file_name)
			{
				text = text + (have_field ? ", " : "") + "\"file_name\":" + "\"" + file_name + "\"";
				have_field = true;
			}
			if (TracePrint::instance().trace_config().head_function_name)
			{
				text = text + (have_field ? ", " : "") + "\"function_name\":" + "\"" + function_name + "\"";
				have_field = true;
			}
			if (TracePrint::instance().trace_config().head_line)
			{
				text = text + (have_field ? ", " : "") + "\"line\":" + "\"" + line + "\"";
				have_field = true;
			}
			if (TracePrint::instance().trace_config().head_datetime)
			{
				text = text + (have_field ? ", " : "") + "\"datetime\":" + "\"" + datetime + "\"";
				have_field = true;
			}
			if (TracePrint::instance().trace_config().head_runtime)
			{
				text = text + (have_field ? ", " : "") + "\"runtime\":" + "\"" + runtime + "\"";
				have_field = true;
			}
			if (TracePrint::instance().trace_config().head_async)
			{
				text = text + (have_field ? ", " : "") + "\"async\":" + "\"" + async + "\"";
				have_field = true;
			}
			text = text + "}";
		}
		return text;
	}

	string TTraceBody::body_text() const
	{
		string text;
		if (!body.empty())
		{
			text = text + "\"body\": " + "\"" + body + "\"" + ("");
		}
		return text;
	}

	string TTraceData::trace_text() const
	{
		string text;
		if (!trace_head_.head_text().empty() || !trace_body_.body_text().empty())
		{
			text = "{";
			bool have_field = false;
			if (!trace_head_.head_text().empty())
			{
				text = text + (have_field ? ", " : "") + trace_head_.head_text();
				have_field = true;
			}
			if (!trace_body_.body_text().empty())
			{
				text = text + (have_field ? "\n," : "") + trace_body_.body_text();
				have_field = true;
			}
			text = text + "}\n\n";
		}
		return text;
	}

	TracePrint::TracePrint(void)
	{
		process_name_ = kk::Utility::GetFileName(kk::Utility::GetProgramPath());

		if (trace_config().async)
		{
			TraceThreadStart();
		}
		kk::Utility::CreateDir(kk::Utility::GetDirectoryName(trace_config().trace_file_name));
		InitConsole();
	}

	TracePrint::~TracePrint(void)
	{
		WaitTraceThreadEnd();
	}

	TTraceHead TracePrint::TraceFormatHead(IN const string& level, IN const string& label, IN const string& file_name, IN const string& func_name, IN int line, bool is_back)
	{
		TTraceHead head;
		if (trace_config().trace_out
			&& ((trace_config().head && !is_back) || (trace_config().trace_back && is_back)))
		{
			static atomic<__int64> log_index(0);
			if (trace_config().head_index)
			{
				head.index = kk::Utility::Int64ToStr(log_index++, 10);
			}
			if (trace_config().head_level)
			{
				head.level = level;
			}
			if (trace_config().head_label)
			{
				head.label = label;
				if (head.label.empty())
				{
					head.label = trace_config().head_label_text;
				}
			}
			if (trace_config().head_datetime)
			{
				head.datetime = kk::Utility::GetDateTimeStr();
			}
			if (trace_config().head_runtime)
			{
				head.runtime = kk::Utility::GetRunTimeStr();
			}
			if (trace_config().head_process_name)
			{
				head.process_name = process_name_;
			}
			//if (trace_config().head_module_name)
			//{
			//	head.module_name = module_name_;
			//}
			if (trace_config().head_file_name)
			{
				head.file_name = file_name;
			}
			if (trace_config().head_function_name)
			{
				head.function_name = func_name;
			}
			if (trace_config().head_line)
			{
				head.line = kk::Utility::Int64ToStr(line, 10);
			}
			if (trace_config().head_async)
			{
				head.async = trace_config().async ? "async" : "sync";
			}
		}
		return head;
	}

	TTraceBody TracePrint::TraceFormatBody(IN const char* log_format, ...)
	{
		TTraceBody trace_body;
		if (trace_config().trace_out)
		{
			string log_body;
			if (log_format)
			{
				int log_length = 1024;
				if (strlen(log_format) >= static_cast<size_t>(log_length))
				{
					log_length += strlen(log_format);
				}
				char* log_exp = new char[log_length];
				memset(log_exp, 0, sizeof(char) * log_length);
				va_list va;
				va_start(va, log_format);
				_vsnprintf_s(log_exp, /*sizeof(char) * */(log_length - 1), log_length - 1, log_format, va);
				va_end(va);
				log_body = log_body + log_exp;
				delete[] log_exp;
			}
			trace_body.body = log_body;
		}
		return trace_body;
	}

	int TracePrint::TraceOutLog(IN int level, IN const TTraceHead& log_head, IN const TTraceBody& log_body)
	{
		if (trace_config().trace_out
			&& level >= 0
			&& level <= trace_config().out_level
			&& (trace_config().levels_info.count(level) ? trace_config().levels_info.find(level)->second.is_out : true))
		{
			TTraceData trace;
			trace.trace_head(log_head);
			trace.trace_body(log_body);
			trace.trace_level_ = level;
			if (!trace.trace_text().empty())
			{
				if (trace_config().async)
				{
					if (trace_thread_.joinable())
					{
						if (traces_list_.size() < TRACE_LIST_SIZE)
						{
							lock_guard<mutex> trace_list_lock(trace_list_mutex_);
							traces_list_.push_back(trace);
							unique_lock<mutex> trace_lock(trace_mutex_);
							trace_condition_.notify_one();
						}
					}
				}
				else
				{
					OutTrace(trace);
				}
			}

		}
		return 0;
	}

	const TTraceConfig& TracePrint::trace_config() const
	{
		return trace_config_;
	}

	const TTraceConfig& TracePrint::trace_config(const TTraceConfig& config)
	{
		trace_config_ = config;
		return trace_config_;
	}

	int TracePrint::trace_out_level(IN int level, IN bool out)
	{
		trace_config_.levels_info[level].is_out = out;
		return 0;
	}

	int TracePrint::trace_level_color(IN int level, IN int color)
	{
		trace_config_.levels_info[level].color = color;
		return 0;
	}

	TracePrint& TracePrint::instance()
	{
		static TracePrint _instance;
		return _instance;
	}

	int TracePrint::TraceThreadStart()
	{
		if (!trace_thread_.joinable())
		{
			trace_thread_kill_ = false;
			trace_thread_ = thread(bind(&TracePrint::TraceThread, this));
		}
		return 0;
	}

	int TracePrint::WaitTraceThreadEnd()
	{
		if (trace_thread_.joinable())
		{
			unique_lock<mutex> trace_lock(trace_mutex_);
			trace_thread_kill_ = true;
			trace_condition_.notify_one();
			trace_thread_.join();
		}
		return 0;
	}

	void TracePrint::TraceThread()
	{
		unique_lock<mutex> trace_lock(trace_mutex_);
		while (1)
		{
			trace_condition_.wait(trace_lock);
			while (!traces_list_.empty())
			{
				lock_guard<mutex> trace_list_lock(trace_list_mutex_);
				TTraceData trace = traces_list_.front();
				traces_list_.pop_front();
				OutTrace(trace);
			}
			if (trace_thread_kill_)
			{
				break;
			}
		}
	}

	int TracePrint::OutTrace(IN const TTraceData&  trace)
	{
		if (trace_config().trace_out)
		{
			if (trace_config().trace_target_compile)
			{
				OutToCompile(trace);
			}
			if (trace_config().trace_target_console)
			{
				OutToConsole(trace);
			}
			if (trace_config().trace_target_file)
			{
				OutToFile(trace);
			}
			if (trace_config().trace_target_socket)
			{
				OutToSocket(trace);
			}
			if (trace_config().trace_target_putty)
			{
				OutToPutty(trace);
			}
		}
		return 0;
	}

	int TracePrint::OutToCompile(const TTraceData&  trace)
	{
		OutputDebugStringA(trace.trace_text().c_str());
		return 0;
	}

	int TracePrint::OutToConsole(const TTraceData&  trace)
	{
		int defult_color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		if (trace_config().levels_info.count(trace.trace_level_) && trace_config().levels_info.find(trace.trace_level_)->second.color)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), trace_config().levels_info.find(trace.trace_level_)->second.color);
			fprintf(stdout, ("%s"), trace.trace_text().c_str());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defult_color);
		}
		else
		{
			fprintf(stdout, ("%s"), trace.trace_text().c_str());
		}
		return 0;
	}

	int TracePrint::OutToFile(const TTraceData&  trace)
	{
		static const int file_max_size = TRACE_FILE_SIZE;

		do {
			string trace_file_name = trace_config().trace_file_name + "_TRACE_ALL.txt";
			FILE* log_file = nullptr;
			errno_t err = fopen_s(&log_file, trace_file_name.c_str(), ("at"));
			if (err)
			{
				fprintf(stdout, ("open file error, path:%s"), trace_file_name.c_str());
				break;
			}
			if (ftell(log_file) > file_max_size)
			{
				fclose(log_file);
				if (fopen_s(&log_file, trace_file_name.c_str(), ("wt")))
				{
					break;
				}
				fputs(("[trace size beyond file_max_size, so truncate]\n"), log_file);
			}
			fputs(trace.trace_text().c_str(), log_file);
			fclose(log_file);
		} while (false);

		do {
			string trace_file_name = trace_config().trace_file_name + "_" + trace.trace_head().level + ".txt";
			FILE* log_file = nullptr;
			if (fopen_s(&log_file, trace_file_name.c_str(), ("at")))
			{
				break;
			}
			if (ftell(log_file) > file_max_size)
			{
				fclose(log_file);
				if (fopen_s(&log_file, trace_file_name.c_str(), ("wt")))
				{
					break;
				}
				fputs(("[trace size beyond file_max_size, so truncate]\n"), log_file);
			}
			fputs(trace.trace_text().c_str(), log_file);
			fclose(log_file);
		} while (false);
		return 0;
	}

	int TracePrint::OutToSocket(const TTraceData&  /*trace*/)
	{
		return 0;
	}

	int TracePrint::OutToPutty(const TTraceData&  /*trace*/)
	{
		return 0;
	}

	int TracePrint::InitConsole()
	{
		COORD coord;
		coord.X = 100;
		coord.Y = 10000;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		return 0;
	}


	TraceOne::TraceOne(IN bool is_back, IN int level, IN const TTraceHead& trace_head, IN const TTraceBody& trace_body)
	{
		is_back_ = is_back;
		trace_level_ = level;
		trace_info_.trace_head(trace_head);
		trace_info_.trace_body(trace_body);
		if (is_back_ && TracePrint::instance().trace_config().trace_back)
		{
			if (TracePrint::instance().trace_config().head_functiontime)
			{
				begin_call_time_ = kk::Utility::GetRunTime();
			}
			trace_info_.trace_head_.func_back = (">>");
			TracePrint::instance().TraceOutLog(trace_level_, trace_info_.trace_head(), trace_info_.trace_body());
		}
	}

	TraceOne::~TraceOne()
	{
		if (!is_back_ || (is_back_ && TracePrint::instance().trace_config().trace_back))
		{
			if (is_back_ && TracePrint::instance().trace_config().trace_back)
			{
				if (TracePrint::instance().trace_config().head_functiontime)
				{
					trace_info_.trace_head_.runtime = kk::Utility::GetRunTimeStr();
					trace_info_.trace_head_.executetime = kk::Utility::Int64ToStr(kk::Utility::GetRunTime() - begin_call_time_, 10) + (" ms");
				}
				trace_info_.trace_head_.func_back = ("<<");
			}
			trace_info_.trace_body_.body += trace_stream_.str();
			TracePrint::instance().TraceOutLog(trace_level_, trace_info_.trace_head(), trace_info_.trace_body());
		}
	}

	stringstream& TraceOne::trace_stream()
	{
		return trace_stream_;
	}

}
