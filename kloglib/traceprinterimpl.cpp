// TracePrinter.cpp : Defines the exported functions for the DLL application.
//

#include "TracePrinterimpl.h"

namespace kk
{
	TraceConfig::TraceConfig()
	{
		trace_out = TRACE_OUT ? true : false;
		track_out = TRACK_OUT ? true : false;
		trace_target_compile = TRACE_COMPILE ? true : false;
		trace_target_console = TRACE_CONSOLE ? true : false;
		trace_target_putty = TRACE_PUTTY ? true : false;
		trace_target_file = TRACE_FILE ? true : false;
		trace_target_socket = TRACE_SOCKET ? true : false;
		valid_level = TRACE_VALID_LEVEL;
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
		head_module_name = TRACE_HEAD_MODULE_NAME ? true : false;
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


	const string& TraceHead::head_text()
	{
		if (TracePrinterImpl::instance().trace_config().trace_out
			&& ((TracePrinterImpl::instance().trace_config().head && func_track.empty()) || (TracePrinterImpl::instance().trace_config().track_out && !func_track.empty())))
		{
			head_text_ = "\"head\": {";
			bool have_field = false;
			if (!func_track.empty())
			{
				head_text_ = head_text_ + (have_field ? ", " : "") + "\"func_track\":" + "\"" + func_track + "\"";
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
		}
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
		if ((trace_head_ && !trace_head_->head_text().empty())
			|| (trace_body_ && !trace_body_->body_text().empty()))
		{
			trace_text_ = "{";
			bool have_field = false;
			if (trace_head_ && !trace_head_->head_text().empty())
			{
				trace_text_ = trace_text_ + (have_field ? ", " : "") + trace_head_->head_text();
				have_field = true;
			}
			if (trace_body_ && !trace_body_->body_text().empty())
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

	int TracePrinterImpl::TraceOutLog(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...)
	{
		do
		{
			if (!IsOut(is_track, level))
			{
				break;
			}
			shared_ptr<TraceEntry> trace_entry = TraceFormatEntry(is_track, level, strlevel, label, module_name, file_name, func_name, line, log_format);
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

	shared_ptr<TraceEntry> TracePrinterImpl::TraceFormatEntry(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...)
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
			TraceBody* trace_body = TraceFormatBody(is_track, level, log_format);
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
			if (trace_config().async)
			{
				if (trace_thread_.joinable())
				{
					if (traces_list_.size() < TRACE_LIST_SIZE)
					{
						lock_guard<mutex> trace_list_lock(trace_list_mutex_);
						traces_list_.push_back(trace_entry);
						unique_lock<mutex> trace_lock(trace_mutex_);
						trace_condition_.notify_one();
					}
				}
			}
			else
			{
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

	TraceBody* TracePrinterImpl::TraceFormatBody(bool is_track, int level, const char* log_format, ...)
	{
		TraceBody* trace_body = nullptr;
		do
		{
			if (!IsOut(is_track, level))
			{
				break;
			}
			trace_body = new TraceBody;
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
				&& trace_config().levels_info.count(level)
				&& !trace_config().levels_info.find(level)->second.is_out)
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
		return trace_config_;
	}

	int TracePrinterImpl::trace_valid_level(int level, bool out)
	{
		trace_config_.levels_info[level].is_out = out;
		return 0;
	}

	int TracePrinterImpl::trace_level_color(int level, int color)
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
			if (trace_config().trace_target_putty)
			{
				OutToPutty(trace_entry);
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
		int defult_color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		if (trace_config().levels_info.count(trace_entry->trace_head()->trace_level)
			&& trace_config().levels_info.find(trace_entry->trace_head()->trace_level)->second.color)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), trace_config().levels_info.find(trace_entry->trace_head()->trace_level)->second.color);
			fprintf(stdout, ("%s"), trace_entry->trace_text().c_str());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defult_color);
		}
		else
		{
			fprintf(stdout, ("%s"), trace_entry->trace_text().c_str());
		}
		return 0;
	}

	int TracePrinterImpl::OutToFile(shared_ptr<TraceEntry> trace_entry)
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
			fputs(trace_entry->trace_text().c_str(), log_file);
			fclose(log_file);
		} while (false);

		do {
			string trace_file_name = trace_config().trace_file_name + "_" + trace_entry->trace_head()->level + ".txt";
			FILE* log_file = nullptr;
			if (fopen_s(&log_file, trace_file_name.c_str(), ("at")))
			{
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
			fputs(trace_entry->trace_text().c_str(), log_file);
			fclose(log_file);
		} while (false);
		return 0;
	}

	int TracePrinterImpl::OutToSocket(shared_ptr<TraceEntry> trace_entry)
	{
		return 0;
	}

	int TracePrinterImpl::OutToPutty(shared_ptr<TraceEntry> trace_entry)
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

	KLOGLIB_API TracePrinter* TracePrinterInstance(void)
	{
		return &TracePrinterImpl::instance();
	}
}
