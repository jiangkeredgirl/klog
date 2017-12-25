// TracePrinter.cpp : Defines the exported functions for the DLL application.
//

#include "TracePrinterimpl.h"

namespace kk
{

	const string& TraceHead::head_text()
	{
		if (TracePrinterImpl::instance().trace_config().trace_out
			&& ((TracePrinterImpl::instance().trace_config().head && func_back.empty()) || (TracePrinterImpl::instance().trace_config().trace_back && !func_back.empty())))
		{
			head_text_ = "\"head\": {";
			bool have_field = false;
			if (!func_back.empty())
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"func_back\":" + "\"" + func_back + "\"";
				have_field = true;
			}
			if (TracePrinterImpl::instance().trace_config().head_index)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"index\":" + "\"" + index + "\"";
				have_field = true;
			}
			if (TracePrinterImpl::instance().trace_config().head_level)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"level\":" + "\"" + level + "\"";
				have_field = true;
			}
			if (TracePrinterImpl::instance().trace_config().head_label)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"label\":" + "\"" + label + "\"";
				have_field = true;
			}
			if (TracePrinterImpl::instance().trace_config().head_process_name)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"process_name\":" + "\"" + process_name + "\"";
				have_field = true;
			}
			//if (TracePrinterImpl::instance().trace_config().head_module_name)
			//{
			//	text = text + (have_field ? ", " : "") + "\"module_name\":" + "\"" + module_name + "\"";
			//	have_field = true;
			//}
			if (TracePrinterImpl::instance().trace_config().head_file_name)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"file_name\":" + "\"" + file_name + "\"";
				have_field = true;
			}
			if (TracePrinterImpl::instance().trace_config().head_function_name)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"function_name\":" + "\"" + function_name + "\"";
				have_field = true;
			}
			if (TracePrinterImpl::instance().trace_config().head_line)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"line\":" + "\"" + line + "\"";
				have_field = true;
			}
			if (TracePrinterImpl::instance().trace_config().head_datetime)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"datetime\":" + "\"" + datetime + "\"";
				have_field = true;
			}
			if (TracePrinterImpl::instance().trace_config().head_runtime)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"runtime\":" + "\"" + runtime + "\"";
				have_field = true;
			}
			if (TracePrinterImpl::instance().trace_config().head_async)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"async\":" + "\"" + async + "\"";
				have_field = true;
			}
			head_text_ = head_text_ + "}";
		}
		return head_text_;
	}

	const string& TraceBody::body_text()
	{
		if (!body.empty())
		{
			body_text_ = body_text_ + "\"body\": " + "\"" + body + "\"" + ("");
		}
		return body_text_;
	}

	const string& TraceEntry::trace_text()
	{
		if (!trace_head_->head_text().empty() || !trace_body_->body_text().empty())
		{
			trace_text_ = "{";
			bool have_field = false;
			if (!trace_head_->head_text().empty())
			{
				trace_text_ = trace_text_ + (have_field ? ", " : "") + trace_head_->head_text();
				have_field = true;
			}
			if (!trace_body_->body_text().empty())
			{
				trace_text_ = trace_text_ + (have_field ? "\n," : "") + trace_body_->body_text();
				have_field = true;
			}
			trace_text_ = trace_text_ + "}\n\n";
		}
		return trace_text_;
	}

	TracePrinterImpl::TracePrinterImpl(void)
	{
		process_name_ = kk::Utility::GetFileName(kk::Utility::GetProgramPath());

		if (trace_config().async)
		{
			TraceThreadStart();
		}
		kk::Utility::CreateDir(kk::Utility::GetDirectoryName(trace_config().trace_file_name));
		InitConsole();
	}

	TracePrinterImpl::~TracePrinterImpl(void)
	{
		WaitTraceThreadEnd();
	}

	TraceHead* TracePrinterImpl::TraceFormatHead(IN const string& level, IN const string& label, IN const string& file_name, IN const string& func_name, IN int line, bool is_back)
	{
		TraceHead* head = new TraceHead;
		if (trace_config().trace_out
			&& ((trace_config().head && !is_back) || (trace_config().trace_back && is_back)))
		{
			static atomic<__int64> log_index(0);
			if (trace_config().head_index)
			{
				head->index = kk::Utility::Int64ToStr(log_index++, 10);
			}
			if (trace_config().head_level)
			{
				head->level = level;
			}
			if (trace_config().head_label)
			{
				head->label = label;
				if (head->label.empty())
				{
					head->label = trace_config().head_label_text;
				}
			}
			if (trace_config().head_datetime)
			{
				head->datetime = kk::Utility::GetDateTimeStr();
			}
			if (trace_config().head_runtime)
			{
				head->runtime = kk::Utility::GetRunTimeStr();
			}
			if (trace_config().head_process_name)
			{
				head->process_name = process_name_;
			}
			//if (trace_config().head_module_name)
			//{
			//	head->module_name = module_name_;
			//}
			if (trace_config().head_file_name)
			{
				head->file_name = file_name;
			}
			if (trace_config().head_function_name)
			{
				head->function_name = func_name;
			}
			if (trace_config().head_line)
			{
				head->line = kk::Utility::Int64ToStr(line, 10);
			}
			if (trace_config().head_async)
			{
				head->async = trace_config().async ? "async" : "sync";
			}
		}
		return head;
	}

	TraceBody* TracePrinterImpl::TraceFormatBody(IN const char* log_format, ...)
	{
		TraceBody* trace_body = new TraceBody;
		if (trace_config().trace_out)
		{
			string log_body;
			if (log_format)
			{
				size_t log_length = 1024;
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
			trace_body->body = log_body;
		}
		return trace_body;
	}

	int TracePrinterImpl::TraceOutLog(IN int level, IN TraceHead* log_head, IN TraceBody* log_body)
	{
		if (trace_config().trace_out
			&& level >= 0
			&& level <= trace_config().out_level
			&& (trace_config().levels_info.count(level) ? trace_config().levels_info.find(level)->second.is_out : true))
		{
			TraceEntry* trace = new TraceEntry;
			trace->trace_head(log_head);
			trace->trace_body(log_body);
			trace->trace_level_ = level;
			if (!trace->trace_text().empty())
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
					OutTrace(*trace);
					delete trace;
				}
			}

		}
		return 0;
	}

	const TraceConfig& TracePrinterImpl::trace_config() const
	{
		return trace_config_;
	}

	const TraceConfig& TracePrinterImpl::trace_config(const TraceConfig& config)
	{
		trace_config_ = config;
		return trace_config_;
	}

	int TracePrinterImpl::trace_out_level(IN int level, IN bool out)
	{
		trace_config_.levels_info[level].is_out = out;
		return 0;
	}

	int TracePrinterImpl::trace_level_color(IN int level, IN int color)
	{
		trace_config_.levels_info[level].color = color;
		return 0;
	}

	TracePrinterImpl& TracePrinterImpl::instance()
	{
		static TracePrinterImpl _instance;
		return _instance;
	}

	int TracePrinterImpl::TraceThreadStart()
	{
		if (!trace_thread_.joinable())
		{
			trace_thread_kill_ = false;
			trace_thread_ = thread(bind(&TracePrinterImpl::TraceThread, this));
		}
		return 0;
	}

	int TracePrinterImpl::WaitTraceThreadEnd()
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

	void TracePrinterImpl::TraceThread()
	{
		unique_lock<mutex> trace_lock(trace_mutex_);
		while (1)
		{
			trace_condition_.wait(trace_lock);
			while (!traces_list_.empty())
			{
				lock_guard<mutex> trace_list_lock(trace_list_mutex_);
				TraceEntry* trace = traces_list_.front();
				traces_list_.pop_front();
				OutTrace(*trace);
				delete trace;
			}
			if (trace_thread_kill_)
			{
				break;
			}
		}
	}

	int TracePrinterImpl::OutTrace(IN TraceEntry&  trace)
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

	int TracePrinterImpl::OutToCompile(TraceEntry&  trace)
	{
		OutputDebugStringA(trace.trace_text().c_str());
		return 0;
	}

	int TracePrinterImpl::OutToConsole(TraceEntry&  trace)
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

	int TracePrinterImpl::OutToFile(TraceEntry&  trace)
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
			string trace_file_name = trace_config().trace_file_name + "_" + trace.trace_head()->level + ".txt";
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

	int TracePrinterImpl::OutToSocket(TraceEntry&  /*trace*/)
	{
		return 0;
	}

	int TracePrinterImpl::OutToPutty(TraceEntry&  /*trace*/)
	{
		return 0;
	}

	int TracePrinterImpl::InitConsole()
	{
		COORD coord;
		coord.X = 100;
		coord.Y = 10000;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		return 0;
	}

}
