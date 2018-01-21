// TracePrinter.cpp : Defines the exported functions for the DLL application.
//

#include "TracePrinterimpl.h"

namespace kk
{
	TraceConfig::TraceConfig()
	{
		trace_out = TRACE_OUT;
		track_out = TRACK_OUT;
		trace_target_compile = TRACE_TARGET_COMPILE;
		trace_target_console = TRACE_TARGET_CONSOLE;
		trace_target_com = TRACE_TARGET_COM;
		trace_target_file = TRACE_TARGET_FILE;
		trace_target_socket = TRACE_TARGET_SOCKET;
		valid_level = TRACE_VALID_LEVEL;
		async = TRACE_ASYNC;
		head = TRACE_HEAD;
		head_index = TRACE_HEAD_INDEX;
		head_level = TRACE_HEAD_LEVEL;
		head_label = TRACE_HEAD_LABEL;
		head_thread_id = TRACE_HEAD_THREAD_ID;
		head_datetime = TRACE_HEAD_DATETIME;
		head_runtime = TRACE_HEAD_RUNTIME;
		head_functiontime = TRACE_HEAD_FUNCTIONTIME;
		head_process_name = TRACE_HEAD_PROCESS_NAME;
		head_module_name = TRACE_HEAD_MODULE_NAME;
		head_file_name = TRACE_HEAD_FILE_NAME;
		head_function_name = TRACE_HEAD_FUNCTION_NAME;
		head_line = TRACE_HEAD_LINE;
		head_async = TRACE_HEAD_ASYNC;
		head_label_text = TRACE_LABEL;
		if (trace_file_dir.empty())
		{
			string program_path = kk::Utility::GetProgramPath();
			string program_directory = kk::Utility::GetDirectoryName(program_path);
			trace_file_dir = program_directory + ("klogs\\");
		}
		level_on_off[TRACE_TRACk]   = TRACE_TRACk;
		level_on_off[TRACE_ERROR]   = TRACE_ERROR;
		level_on_off[TRACE_WARNING] = TRACE_WARNING;
		level_on_off[TRACE_OK]      = TRACE_OK;
		level_on_off[TRACE_NOTICE]  = TRACE_NOTICE;
		level_on_off[TRACE_INFO]    = TRACE_INFO;
		level_on_off[TRACE_DEBUG]   = TRACE_DEBUG;
		level_on_off[TRACE_TEMP]    = TRACE_TEMP;
	}


	const string& TraceHead::head_text()
	{
		do
		{
			if (!is_track && !TracePrinterImpl::instance().trace_config().head)
			{
				break;
			}
			if (is_track && !TracePrinterImpl::instance().trace_config().track_out)
			{
				break;
			}
			head_text_ = "\"head\": {";
			bool have_field = false;
			if (!func_enter.empty())
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"func_track\":" + "\"" + func_enter + "\"";
				have_field = true;
			}
			else if (!func_exit.empty())
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"func_track\":" + "\"" + func_exit + "\"";
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
			if (TracePrinterImpl::instance().trace_config().head_thread_id)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"thread_id\":" + "\"" + thread_id + "\"";
				have_field = true;
			}
			if (TracePrinterImpl::instance().trace_config().head_process_name)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"process_name\":" + "\"" + process_name + "\"";
				have_field = true;
			}
			if (TracePrinterImpl::instance().trace_config().head_module_name)
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"module_name\":" + "\"" + module_name + "\"";
				have_field = true;
			}
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
		} while (false);
		return head_text_;
	}

	const string& TraceBody::body_text()
	{
		if (!body.empty())
		{
			body_text_ = "\"body\": \"" + body + "\"";
		}
		return body_text_;
	}

	const string& TraceEntry::trace_text()
	{
		trace_text_ = "{";
		bool have_field = false;
		do
		{			
			if (trace_head_ == nullptr)
			{
				break;
			}
			if (trace_head_->head_text().empty())
			{
				break;
			}
			trace_text_ = trace_head_->head_text();
			have_field = true;
		} while (false);
		do
		{
			if (trace_body_ == nullptr)
			{
				break;
			}
			if (trace_body_->body_text().empty())
			{
				break;
			}
			trace_text_ = trace_text_ + (have_field ? "\n," : "") + trace_body_->body_text();
		} while (false);
		trace_text_ = trace_text_ + "}\n\n";
		return trace_text_;
	}

	TracePrinterImpl::TracePrinterImpl(void)
	{
		process_name_ = kk::Utility::GetFileName(kk::Utility::GetProgramPath());	
		string::size_type pos = process_name_.rfind(".exe");
		if (pos != string::npos)
		{
			process_name_ = process_name_.substr(0, process_name_.size()-4);
		}
		process_time_ = kk::Utility::GetLogDateTimeStr();
		InitTrace();
	}

	TracePrinterImpl::~TracePrinterImpl(void)
	{
		WaitTraceThreadEnd();
	}

	int TracePrinterImpl::TraceOutLog(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...)
	{
		do
		{
			if (!IsOut(is_track, level))
			{
				break;
			}
			///
			string log_body;
			do
			{
				if (log_format == nullptr)
				{
					break;
				}
				size_t log_length = ONE_TRACE_SIZE;
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
			} while (false);
			///
			shared_ptr<TraceEntry> trace_entry = TraceFormatEntry(is_track, level, strlevel, label, module_name, file_name, func_name, line, log_body);
			if (trace_entry == nullptr)
			{
				break;
			}			
			//if (trace_entry->trace_text().empty())
			//{
			//	break;
			//}
			OutTraceEntry(trace_entry);
		} while (false);
		return 0;
	}

	shared_ptr<TraceEntry> TracePrinterImpl::TraceFormatEntry(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const string& log_body)
	{
		shared_ptr<TraceEntry> trace_entry = nullptr;
		do
		{
			if (!IsOut(is_track, level))
			{
				break;
			}
			trace_entry = shared_ptr<TraceEntry>(new TraceEntry());
			TraceHead* trace_head = TraceFormatHead(is_track, level, strlevel, label, module_name, file_name, func_name, line);
			TraceBody* trace_body = TraceFormatBody(log_body);
			trace_entry->trace_head(trace_head);
			trace_entry->trace_body(trace_body);
		} while (false);
		return trace_entry;
	}

	int TracePrinterImpl::OutTraceEntry(shared_ptr<TraceEntry> trace_entry)
	{
		do
		{
			if (trace_entry == nullptr)
			{
				break;
			}
			//if (trace_entry->trace_text().empty())
			//{
			//	break;
			//}
			if (trace_config().async && trace_thread_.joinable())
			{
				if (traces_list_.size() < TRACE_LIST_SIZE)
				{
					//lock_guard<mutex> trace_list_lock(trace_list_mutex_);
					traces_list_.push_back(trace_entry);
					//unique_lock<mutex> trace_lock(trace_mutex_);
					trace_condition_.notify_one();
				}
			}
			else
			{
				if (trace_config().sync_lock)
				{
					lock_guard<mutex> trace_out_lock(trace_sync_mutex_);
				}
				OutTrace(trace_entry);
			}
		} while (false);
		return 0;
	}

	TraceHead* TracePrinterImpl::TraceFormatHead(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line)
	{
		TraceHead* head = nullptr;
		do
		{
			if (!IsOut(is_track, level))
			{
				break;
			}
			if (!is_track && !trace_config().head)
			{
				break;
			}
			head = new TraceHead;
			head->is_track = is_track;
			head->trace_level = level;
			static atomic<__int64> log_index(0);
			if (trace_config().head_index)
			{
				head->index = kk::Utility::Int64ToStr(log_index++, 10);
			}
			if (trace_config().head_level)
			{
				head->level = strlevel;
			}
			if (trace_config().head_label)
			{
				head->label = label;
				if (head->label.empty())
				{
					head->label = trace_config().head_label_text;
				}
			}
			if (trace_config().head_thread_id)
			{
				std::thread::id this_id = std::this_thread::get_id();
				std::stringstream ss;
				ss << this_id;
				head->thread_id = ss.str();
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
			if (trace_config().head_module_name)
			{
				head->module_name = module_name;
			}
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
		} while (false);
		return head;
	}

	TraceBody* TracePrinterImpl::TraceFormatBody(const string& log_body)
	{
		TraceBody* trace_body = nullptr;
		do
		{
			//if (log_body.empty())
			//{
			//	break;
			//}
			trace_body = new TraceBody;
			trace_body->body = std::move(log_body);
		} while (false);
		return trace_body;
	}
	
	bool TracePrinterImpl::IsOut(bool is_track, int level)
	{
		bool is_out = false;
		do
		{
			if (!is_track && !trace_config().trace_out)
			{
				break;
			}
			if (is_track && !trace_config().track_out)
			{
				break;
			}
			if (level < 1)
			{
				break;
			}
			if (level > trace_config().valid_level)
			{
				break;
			}
			if (!is_track
				&& trace_config().level_on_off.count(level)
				&& !trace_config().level_on_off.find(level)->second)
			{
				break;
			}
			is_out = true;
		} while (false);
		return is_out;
	}

	const TraceConfig& TracePrinterImpl::trace_config() const
	{
		return trace_config_;
	}

	const TraceConfig& TracePrinterImpl::trace_config(const TraceConfig& config)
	{
		trace_config_ = config;
		InitTrace();
		return trace_config_;
	}

	int TracePrinterImpl::trace_valid_level(int level, bool out)
	{
		trace_config_.level_on_off[level] = out;
		return 0;
	}

	int TracePrinterImpl::trace_level_color(int level, int color)
	{
		default_level_color[level] = color;
		return 0;
	}

	int TracePrinterImpl::InitTrace()
	{
		if (trace_config().trace_target_file)
		{
			kk::Utility::CreateDir(kk::Utility::GetDirectoryName(trace_config().trace_file_dir));
		}
		if (trace_config().trace_target_console)
		{
			InitConsole();
		}
		if (trace_config().async)
		{
			TraceThreadStart();
		}
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
			//unique_lock<mutex> trace_lock(trace_mutex_);
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
				//lock_guard<mutex> trace_list_lock(trace_list_mutex_);
				shared_ptr<TraceEntry> trace_entry = traces_list_.front();
				traces_list_.pop_front();
				OutTrace(trace_entry);
			}
			if (trace_thread_kill_)
			{
				break;
			}
		}
	}

	int TracePrinterImpl::OutTrace(shared_ptr<TraceEntry> trace_entry)
	{
		if (trace_config().trace_out)
		{
			if (trace_config().trace_target_compile)
			{
				OutToCompile(trace_entry);
			}
			if (trace_config().trace_target_console)
			{
				OutToConsole(trace_entry);
			}
			if (trace_config().trace_target_file)
			{
				OutToFile(trace_entry);
			}
			if (trace_config().trace_target_socket)
			{
				OutToSocket(trace_entry);
			}
			if (trace_config().trace_target_com)
			{
				OutToCom(trace_entry);
			}
			if (trace_entry->trace_head())
			{
				trace_entry->trace_head()->func_enter = "";
			}
		}
		return 0;
	}

	int TracePrinterImpl::OutToCompile(shared_ptr<TraceEntry> trace_entry)
	{
		OutputDebugStringA(trace_entry->trace_text().c_str());
		return 0;
	}

	int TracePrinterImpl::OutToConsole(shared_ptr<TraceEntry> trace_entry)
	{
		//int defult_color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		if (default_level_color.count(trace_entry->trace_head()->trace_level))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_level_color[trace_entry->trace_head()->trace_level]);
			//fprintf(stdout, ("%s"), trace_entry->trace_text().c_str());
			//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defult_color);
		}
		//else
		//{
		fprintf(stdout, ("%s"), trace_entry->trace_text().c_str());
		//}
		return 0;
	}

	int TracePrinterImpl::OutToFile(shared_ptr<TraceEntry> trace_entry)
	{
		const string& trace_entry_text = trace_entry->trace_text();
		// 整个进程所有模块的输出
		string trace_file_name = trace_config().trace_file_dir
			+ process_name_ + "_" + process_time_
			+ "_TRACE_ALL.log";
		OutToFile(trace_file_name, trace_entry_text);
		trace_file_name = trace_config().trace_file_dir
			+ process_name_ + "_" + process_time_
			+ "_" + trace_entry->trace_head()->level + ".log";
		OutToFile(trace_file_name, trace_entry_text);
		// 按模块名输出
		trace_file_name = trace_config().trace_file_dir
			+ process_name_ + "_" + trace_entry->trace_head()->module_name + "_" + process_time_
			+ "_TRACE_ALL.log";
		OutToFile(trace_file_name, trace_entry_text);
		trace_file_name = trace_config().trace_file_dir
			+ process_name_ + "_" + trace_entry->trace_head()->module_name + "_" + process_time_
			+ "_" + trace_entry->trace_head()->level + ".log";
		OutToFile(trace_file_name, trace_entry_text);
		return 0;
	}

	int TracePrinterImpl::OutToFile(const string& trace_file_name, const string& trace_entry)
	{
		static const int file_max_size = TRACE_FILE_SIZE;
		do {
			FILE* log_file = nullptr;
			errno_t err = fopen_s(&log_file, trace_file_name.c_str(), ("at"));
			if (err)
			{
				fprintf(stdout, ("open file error, path:%s"), trace_file_name.c_str());
				break;
			}
			fseek(log_file, 0, SEEK_END);
			if (ftell(log_file) > file_max_size)
			{
				fclose(log_file);
				if (fopen_s(&log_file, trace_file_name.c_str(), ("wt")))
				{
					break;
				}
				fputs(("[trace size beyond file_max_size, so truncate]\n"), log_file);
			}
			fputs(trace_entry.c_str(), log_file);
			fclose(log_file);
		} while (false);
		return 0;
	}

	int TracePrinterImpl::OutToSocket(shared_ptr<TraceEntry> trace_entry)
	{
		return 0;
	}

	int TracePrinterImpl::OutToCom(shared_ptr<TraceEntry> trace_entry)
	{
		return 0;
	}

	int TracePrinterImpl::InitConsole()
	{
		COORD coord;
		coord.X = 200;
		coord.Y = 10000;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		default_level_color[TRACE_TRACk] = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		default_level_color[TRACE_ERROR] = FOREGROUND_INTENSITY | FOREGROUND_RED;
		default_level_color[TRACE_WARNING] = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
		default_level_color[TRACE_OK] = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
		default_level_color[TRACE_NOTICE] = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
		default_level_color[TRACE_INFO] = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		default_level_color[TRACE_DEBUG] = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		default_level_color[TRACE_TEMP] = FOREGROUND_INTENSITY;
		return 0;
	}

	KLOGLIB_API TracePrinter* TracePrinterInstance(void)
	{
		return &TracePrinterImpl::instance();
	}
}
