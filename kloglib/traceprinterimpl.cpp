// TracePrinter.cpp : Defines the exported functions for the DLL application.
//

#include "TracePrinterimpl.h"
#include "config.h"

namespace kk
{
	TraceConfig::TraceConfig()
	{
		trace_out = TRACE_OUT;
		track_out = TRACK_OUT;
		output_compile = OUTPUT_COMPILE;
		output_console = OUTPUT_CONSOLE;
		output_com = OUTPUT_COM;
		output_file = OUTPUT_FILE;
		output_socket = OUTPUT_SOCKET;
		file_level = FILE_LEVEL;
		file_module = FILE_MODULE;
		file_date = FILE_DATE;
		
		async = TRACE_ASYNC;
		sync_lock = TRACE_SYNC_LOCK;
		head = TRACE_HEAD;
		head_index = TRACE_HEAD_INDEX;
		head_level = TRACE_HEAD_LEVEL;
		head_label = TRACE_HEAD_LABEL;
		head_thread_id = TRACE_HEAD_THREAD_ID;
		head_datetime = TRACE_HEAD_DATETIME;
		head_runtime = TRACE_HEAD_RUNTIME;
		head_function_time = TRACE_HEAD_FUNCTION_TIME;
		head_process_name = TRACE_HEAD_PROCESS_NAME;
		head_module_name = TRACE_HEAD_MODULE_NAME;
		head_file_name = TRACE_HEAD_FILE_NAME;
		head_function_name = TRACE_HEAD_FUNCTION_NAME;
		head_line = TRACE_HEAD_LINE;
		head_async = TRACE_HEAD_ASYNC;
		head_sync_lock = TRACE_HEAD_SYNC_LOCK;		
		valid_level = TRACE_VALID_LEVEL;
		trace_file_size = TRACE_FILE_SIZE;
		head_label_text = TRACE_LABEL;		
		//string program_path = kk::Utility::GetProgramPath();
		//string program_directory = kk::Utility::GetDirectoryName(program_path);
		//trace_file_dir = program_directory + ("klogs\\");
		//trace_file_dir = ".\\klogs\\";
		level_on_off[TRACE_TRACk]   = static_cast<bool>(TRACE_TRACk);
		level_on_off[TRACE_ERROR]   = static_cast<bool>(TRACE_ERROR);
		level_on_off[TRACE_WARNING] = static_cast<bool>(TRACE_WARNING);
		level_on_off[TRACE_OK]      = static_cast<bool>(TRACE_OK);
		level_on_off[TRACE_NOTICE]  = static_cast<bool>(TRACE_NOTICE);
		level_on_off[TRACE_INFO]    = static_cast<bool>(TRACE_INFO);
		level_on_off[TRACE_DEBUG]   = static_cast<bool>(TRACE_DEBUG);
		level_on_off[TRACE_TEMP]    = static_cast<bool>(TRACE_TEMP);
	}


	const string& TraceEntry::trace_text()
	{
		do
		{
			if (is_track && !TracePrinterImpl::instance().trace_config().track_out)
			{
				break;
			}
			trace_text_ = "";
			stringstream ss;
			ss << "{";
			if (is_track || TracePrinterImpl::instance().trace_config().head)
			{
				if (TracePrinterImpl::instance().trace_config().head_index)
				{
					ss << ", \"index\":" << to_string(index);
				}
				if (!func_track.empty())
				{
					ss << ", \"func_track\":\"" << func_track << "\"";
				}
				if (is_track && TracePrinterImpl::instance().trace_config().head_function_time)
				{
					ss << ", \"func_time\":\"" << to_string(func_time) << "ms" << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_level)
				{
					ss << ", \"level\":\"" << TracePrinterImpl::instance().LevelToStr(level) << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_label)
				{
					ss << ", \"label\":\"" << label << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_thread_id)
				{
					ss << ", \"thread_id\":" << thread_id;
				}
				if (TracePrinterImpl::instance().trace_config().head_process_name)
				{
					ss << ", \"process_name\":\"" << process_name << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_module_name)
				{
					ss << ", \"module_name\":\"" << module_name << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_file_name)
				{
					ss << ", \"file_name\":\"" << file_name << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_function_name)
				{
					ss << ", \"func_name\":\"" << func_name << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_line)
				{
					ss << ", \"line\":" << line;
				}
				if (TracePrinterImpl::instance().trace_config().head_datetime)
				{
					ss << ", \"datetime\":\"" << kk::Utility::GetDateTimeStr(datetime) << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_runtime)
				{
					ss << ", \"runtime\":\"" << kk::Utility::GetRunTimeStr(runtime) << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_async)
				{
					ss << ", \"async\":" << (async ? "true" : "false");
				}
				if (TracePrinterImpl::instance().trace_config().head_sync_lock)
				{
					ss << ", \"sync_lock\":" << (sync_lock ? "true" : "false");
				}
			}
			if (!content.empty())
			{
				ss << ",\"content\": \"" << content << "\"";
			}
			ss << "}\n\n";
			trace_text_ = ss.str();
			if (trace_text_.size() > 6)
			{
				trace_text_.erase(1, 2);
			}
		} while (false);
		return trace_text_;
	}

	TracePrinterImpl::TracePrinterImpl(void)
	{
		level_to_str_[TRACE_TRACk] = "trace_track";
		level_to_str_[TRACE_ERROR] = "trace_error";
		level_to_str_[TRACE_WARNING] = "trace_warning";
		level_to_str_[TRACE_OK] = "trace_ok";
		level_to_str_[TRACE_NOTICE] = "trace_notice";
		level_to_str_[TRACE_INFO] = "trace_info";
		level_to_str_[TRACE_DEBUG] = "trace_debug";
		level_to_str_[TRACE_TEMP] = "trace_temp";

		str_to_level_["trace_track"] = TRACE_TRACk;
		str_to_level_["trace_error"] = TRACE_ERROR;
		str_to_level_["trace_warning"] = TRACE_WARNING;
		str_to_level_["trace_ok"] = TRACE_OK;
		str_to_level_["trace_notice"] = TRACE_NOTICE;
		str_to_level_["trace_info"] = TRACE_INFO;
		str_to_level_["trace_debug"] = TRACE_DEBUG;
		str_to_level_["trace_temp"] = TRACE_TEMP;

		process_name_ = kk::Utility::GetFileName(kk::Utility::GetProgramPath());
		string process_name_dir = process_name_;
		string::size_type pos = process_name_dir.rfind(".exe");
		if (pos != string::npos)
		{
			process_name_dir = process_name_dir.substr(0, process_name_dir.size()-4);
		}
		process_time_ = kk::Utility::GetLogDateTimeStr();
		int errorCode = Config::instance().GetTraceConfig(trace_config_);
		if(errorCode)
		{
			Config::instance().SetTraceConfig(trace_config_);
		}
		trace_config_.trace_file_dir = ".\\klogs\\" + process_name_dir + "\\";
		InitTrace();
	}

	TracePrinterImpl::~TracePrinterImpl(void)
	{
		WaitTraceThreadEnd();
	}

	int TracePrinterImpl::TraceOutLog(bool is_track, int level, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...)
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
				int write_size = 0;
				va_list va;
				va_start(va, log_format);
				write_size = _vsnprintf_s(log_exp, log_length, _TRUNCATE, log_format, va);
				va_end(va);
				log_body += log_exp;
				if (write_size == -1)
				{
					log_body += "[...truncate, use Trace(xxx) replace Trace(\"%s\", xxx) by klog author]";
				}
				delete[] log_exp;
			} while (false);
			///
			shared_ptr<TraceEntry> trace_entry = TraceFormatEntry(is_track, level, label, module_name, file_name, func_name, line, log_body);
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

	shared_ptr<TraceEntry> TracePrinterImpl::TraceFormatEntry(bool is_track, int level, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const string& log_body)
	{
		shared_ptr<TraceEntry> trace_entry = nullptr;
		do
		{
			if (!IsOut(is_track, level))
			{
				break;
			}
			trace_entry = shared_ptr<TraceEntry>(new TraceEntry());
			do
			{
				if (!is_track && !trace_config().head)
				{
					break;
				}
				static atomic<__int64> log_index(0);
				trace_entry->index = log_index++;
				trace_entry->is_track = is_track;
				trace_entry->level = level;
				trace_entry->label = label;
				if (trace_entry->label.empty())
				{
					trace_entry->label = trace_config().head_label_text;
				}
				std::stringstream ss;
				ss << std::this_thread::get_id();
				ss >> trace_entry->thread_id;
				trace_entry->datetime = kk::Utility::GetDateTime();
				trace_entry->runtime = kk::Utility::GetRunTime();
				trace_entry->process_name = process_name_;
				trace_entry->module_name = module_name;
				trace_entry->file_name = file_name;
				trace_entry->func_name = func_name;
				trace_entry->line = line;
				trace_entry->async = trace_config().async;
				trace_entry->sync_lock = trace_config().sync_lock;

			} while (false);
			do
			{
				if (log_body.empty())
				{
					break;
				}
				trace_entry->content = std::move(log_body);
			} while (false);
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
		Config::instance().SetTraceConfig(trace_config_);
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
		default_level_color_[level] = color;
		return 0;
	}

	int TracePrinterImpl::InitTrace()
	{
		if (trace_config().output_file)
		{
			kk::Utility::CreateDir(trace_config().trace_file_dir);
		}
		if (trace_config().output_console)
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
			if (trace_config().output_compile)
			{
				OutToCompile(trace_entry);
			}
			if (trace_config().output_console)
			{
				OutToConsole(trace_entry);
			}
			if (trace_config().output_file)
			{
				OutToFile(trace_entry);
			}
			if (trace_config().output_socket)
			{
				OutToSocket(trace_entry);
			}
			if (trace_config().output_com)
			{
				OutToCom(trace_entry);
			}
			if (trace_entry)
			{
				trace_entry->func_track = "";
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
		if (default_level_color_.count(trace_entry->level))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_level_color_[trace_entry->level]);
		}
		fprintf(stdout, ("%s"), trace_entry->trace_text().c_str());
		if (default_level_color_.count(trace_entry->level))
		{
			int defult_color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defult_color);
		}
		return 0;
	}

	int TracePrinterImpl::OutToFile(shared_ptr<TraceEntry> trace_entry)
	{
		do
		{
			// 按日期创建文件夹
			string trace_file_dir = trace_config().trace_file_dir;
			if (trace_config().file_date)
			{
				trace_file_dir += kk::Utility::GetDateStr() + "\\";
				int error_code = kk::Utility::CreateDir(trace_file_dir);
				if (error_code)
				{
					fprintf(stdout, ("create dir error, path:%s\n"), trace_file_dir.c_str());
					break;
				}
			}
			const string& trace_entry_text = trace_entry->trace_text();

			// 整个进程所有模块的所有等级log输出
			string trace_file_name = trace_file_dir
				+ process_name_ + "_" + process_time_
				+ "_trace_all.log";
			OutToFile(trace_file_name, trace_entry_text);
			// 整个进程按等级输出
			if (trace_config().file_level)
			{
				trace_file_name = trace_file_dir
					+ process_name_ + "_" + process_time_
					+ "_" + TracePrinterImpl::instance().LevelToStr(trace_entry->level) + ".log";
				OutToFile(trace_file_name, trace_entry_text);
			}

			// 按模块输出所有等级log
			if (trace_config().file_module)
			{
				trace_file_name = trace_file_dir
					+ process_name_ + "_" + trace_entry->module_name + "_" + process_time_
					+ "_trace_all.log";
				OutToFile(trace_file_name, trace_entry_text);
				// 按模块按等级输出
				if (trace_config().file_level)
				{
					trace_file_name = trace_file_dir
						+ process_name_ + "_" + trace_entry->module_name + "_" + process_time_
						+ "_" + TracePrinterImpl::instance().LevelToStr(trace_entry->level) + ".log";
					OutToFile(trace_file_name, trace_entry_text);
				}
			}

		} while (false);
		return 0;
	}

	int TracePrinterImpl::OutToFile(const string& trace_file_name, const string& trace_entry)
	{
		static const int file_max_size = trace_config().trace_file_size * 1024 * 1024;
		do {
			FILE* log_file = nullptr;
			errno_t err = fopen_s(&log_file, trace_file_name.c_str(), ("a+"));
			if (err)
			{
				fprintf(stdout, ("open file error, path:%s\n"), trace_file_name.c_str());
				break;
			}
			fseek(log_file, 0, SEEK_END);
			if (ftell(log_file) > file_max_size)
			{
				fclose(log_file);
				if (fopen_s(&log_file, trace_file_name.c_str(), ("w+")))
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
		default_level_color_[TRACE_TRACk] = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		default_level_color_[TRACE_ERROR] = FOREGROUND_INTENSITY | FOREGROUND_RED;
		default_level_color_[TRACE_WARNING] = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
		default_level_color_[TRACE_OK] = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
		default_level_color_[TRACE_NOTICE] = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
		default_level_color_[TRACE_INFO] = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		default_level_color_[TRACE_DEBUG] = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		default_level_color_[TRACE_TEMP] = FOREGROUND_INTENSITY;
		return 0;
	}

	string TracePrinterImpl::LevelToStr(int level)
	{
		string str;
		if (level_to_str_.count(level))
		{
			str = level_to_str_[level];
		}
		else
		{
			str = to_string(level);
		}
		return str;
	}

	int TracePrinterImpl::StrToLevel(const string& str)
	{
		int level = -1;
		if (str_to_level_.count(str))
		{
			level = str_to_level_[str];
		}
		else
		{
			level = stoi(str);
		}
		return level;
	}


	KLOGLIB_API TracePrinter* TracePrinterInstance(void)
	{
		return &TracePrinterImpl::instance();
	}
}
