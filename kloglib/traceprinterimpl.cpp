// TracePrinter.cpp : Defines the exported functions for the DLL application.
//

#include "TracePrinterimpl.h"
#include "config.h"
#include "GenerateDumpInfo.h"
#include "rapidjsonparser.h"
#include "tracemacr.h"
#include "klogsource.h"
#include "klognetprotocol.h"
#include "protocolserialpackage.h"


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
		head = TRACE_HEAD;
		head_index = TRACE_HEAD_INDEX;
		head_functrack = TRACE_HEAD_FUNCTRACK;
		head_functime = TRACE_HEAD_FUNCTIME;
		head_level = TRACE_HEAD_LEVEL;
		head_label = TRACE_HEAD_LABEL;
		head_threadid = TRACE_HEAD_THREADID;
		head_processname = TRACE_HEAD_PROCESSNAME;
		head_modulename = TRACE_HEAD_MODULENAME;
		head_filename = TRACE_HEAD_FILENAME;
		head_funcname = TRACE_HEAD_FUNCNAME;
		head_line = TRACE_HEAD_LINE;
		head_datetime = TRACE_HEAD_DATETIME;
		head_runtime = TRACE_HEAD_RUNTIME;
		head_async = TRACE_HEAD_ASYNC;
		valid_level = TRACE_VALID_LEVEL;
		valid_console_level = TRACE_VALID_CONSOLE_LEVEL;
		console_format = TRACE_CONSOLE_FORMAT;
		trace_file_size = TRACE_FILE_SIZE;
		head_label_text = TRACE_LABEL;
		//string program_path = kk::Utility::GetProgramPath();
		//string program_directory = kk::Utility::GetDirectoryName(program_path);
		//trace_file_dir = program_directory + ("klogs\\");
		//trace_file_dir = ".\\klogs\\";
		level_on_off[TRACE_TRACk] = static_cast<bool>(TRACE_TRACk);
		level_on_off[TRACE_ERROR] = static_cast<bool>(TRACE_ERROR);
		level_on_off[TRACE_WARNING] = static_cast<bool>(TRACE_WARNING);
		level_on_off[TRACE_OK] = static_cast<bool>(TRACE_OK);
		level_on_off[TRACE_NOTICE] = static_cast<bool>(TRACE_NOTICE);
		level_on_off[TRACE_INFO] = static_cast<bool>(TRACE_INFO);
		level_on_off[TRACE_DEBUG] = static_cast<bool>(TRACE_DEBUG);
		level_on_off[TRACE_TEMP] = static_cast<bool>(TRACE_TEMP);
	}

	const string& TraceEntry::trace_json_text()
	{
		do
		{
			if (is_track && !TracePrinterImpl::instance().trace_config().track_out)
			{
				break;
			}
			trace_json_text_ = "";
			stringstream ss;
			ss << "{";
			if (is_track || TracePrinterImpl::instance().trace_config().head)
			{
				if (TracePrinterImpl::instance().trace_config().head_index)
				{
					ss << ", \"index\":" << to_string(index);
				}
				if (!functrack.empty() && TracePrinterImpl::instance().trace_config().head_functrack)
				{
					ss << ", \"functrack\":\"" << functrack << "\"";
				}
				if (is_track && TracePrinterImpl::instance().trace_config().head_functime)
				{
					ss << ", \"functime\":\"" << to_string(functime) << "ms" << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_level)
				{
					ss << ", \"level\":\"" << TracePrinterImpl::instance().LevelToStr(level) << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_label)
				{
					ss << ", \"label\":\"" << label << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_threadid)
				{
					ss << ", \"threadid\":\"" << threadid << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_processname)
				{
					ss << ", \"processname\":\"" << processname << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_modulename)
				{
					ss << ", \"modulename\":\"" << modulename << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_filename)
				{
					ss << ", \"filename\":\"" << filename << "\"";
				}
				if (TracePrinterImpl::instance().trace_config().head_funcname)
				{
					ss << ", \"funcname\":\"" << funcname << "\"";
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
			}
			if (!content.empty())
			{
				string _content(content);
				if (_content.size() != strlen(_content.c_str()))
				{
					_content = "contain invalid character, string size: " + to_string(_content.size()) + " by klog provide";
				}
#if 0
				ss << ", \"content\":\"" << _content << "\"";
#else
				string json_content;
				CJsonParser::instance().EncodeTraceContent(_content, json_content);
				ss << ", " << json_content;
#endif
			}
			ss << "}\n\n";
			trace_json_text_ = ss.str();
			if (trace_json_text_.size() > 3)
			{
				trace_json_text_.erase(1, 2);
			}
		} while (false);
		return trace_json_text_;
	}

	const string& TraceEntry::trace_console_text()
	{
		do
		{
			if (is_track)
			{
				break;
			}
			trace_console_text_ = "";
			stringstream ss;
			ss << "[";
			if (TracePrinterImpl::instance().trace_config().head)
			{
				if (TracePrinterImpl::instance().trace_config().head_level)
				{
					ss << ", " << TracePrinterImpl::instance().LevelToStr(level);
				}
				if (TracePrinterImpl::instance().trace_config().head_threadid)
				{
					ss << ", " << threadid;
				}
				if (TracePrinterImpl::instance().trace_config().head_filename)
				{
					ss << ", " << filename;
				}
				if (TracePrinterImpl::instance().trace_config().head_funcname)
				{
					ss << ", " << funcname;
				}
				if (TracePrinterImpl::instance().trace_config().head_line)
				{
					ss << ", #" << line;
				}
			}
			ss << "]";
			if (!content.empty())
			{
				ss << content;
			}
			ss << "\n";
			trace_console_text_ = ss.str();
			if (trace_console_text_.size() > 3)
			{
				trace_console_text_.erase(1, 2);
			}
		} while (false);
		return trace_console_text_;
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
			process_name_dir = process_name_dir.substr(0, process_name_dir.size() - 4);
		}
		process_time_ = kk::Utility::GetLogDateTimeStr();
		int errorCode = Config::instance().GetTraceConfig(process_name_, trace_config_);
		if (errorCode)
		{
			Config::instance().SetTraceConfig(process_name_, trace_config_);
		}
		trace_config_.trace_file_dir = ".\\klogs\\" + process_name_dir + "\\";
		InitTrace();
		//TraceOutLog(false, TRACE_OK, TRACE_LABEL, GetModuleName(), GetFileName(__FILE__), __FUNCTION__, __LINE__, "Welcome using klog");
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
				trace_entry->index = ++log_index;
				trace_entry->is_track = is_track;
				trace_entry->level = level;
				trace_entry->label = label;
				if (trace_entry->label.empty())
				{
					trace_entry->label = trace_config().head_label_text;
				}
				std::stringstream ss;
				ss << std::this_thread::get_id();
				ss >> trace_entry->threadid;
				trace_entry->datetime = kk::Utility::GetDateTime();
				trace_entry->runtime = kk::Utility::GetRunTime();
				trace_entry->processname = process_name_;
				trace_entry->modulename = module_name;
				trace_entry->filename = file_name;
				trace_entry->funcname = func_name;
				trace_entry->line = line;
				trace_entry->async = trace_config().async;
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
				if (traces_list_.size() > TRACE_LIST_SIZE)
				{
					lock_guard<mutex> trace_list_lock(trace_list_mutex_);
					traces_list_.clear();
					trace_entry->content = "traces_list_.size() > " + to_string(TRACE_LIST_SIZE) + " ,so clear list by klog provide";
				}
				{
					lock_guard<mutex> trace_list_lock(trace_list_mutex_);
					traces_list_.push_back(trace_entry);
				}
				//unique_lock<mutex> trace_lock(trace_mutex_);
				trace_condition_.notify_one();
			}
			else
			{
				lock_guard<mutex> trace_out_lock(trace_sync_mutex_);
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
		Config::instance().SetTraceConfig(process_name_, trace_config_);
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
		if (trace_config().output_socket)
		{
			InitSocket();
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

	int TracePrinterImpl::CreateKlogConsole()
	{
		AllocConsole();
		FILE *stream;
		freopen_s(&stream, "CONOUT$", "w+t", stdout);
		// 以下2行代码导致qDebug() crash
		//freopen_s(&stream, "CONIN$", "r+t", stdin);
		//freopen_s(&stream, "CONERR$", "r+t", stderr);
		SetConsoleTitle(TEXT("klog输出"));
		//SetConsoleUTF8();
		return 0;
	}

	int TracePrinterImpl::GenerateDumpInfo()
	{
		GenerateDumpInfo::instance().Generate(process_name_);
		return 0;
	}

	int TracePrinterImpl::SetKlogConsoleUTF8()
	{
		SetConsoleUTF8();
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
				shared_ptr<TraceEntry> trace_entry = nullptr;
				{
					lock_guard<mutex> trace_list_lock(trace_list_mutex_);
					trace_entry = traces_list_.front();
					traces_list_.pop_front();
				}
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
			if (trace_config().output_console && trace_entry->level <= trace_config().valid_console_level)
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
			if (trace_config().output_compile)
			{
				OutToCompile(trace_entry);
			}
			if (trace_config().output_com)
			{
				OutToCom(trace_entry);
			}
			if (trace_entry)
			{
				trace_entry->functrack = "";
			}
		}
		return 0;
	}

	int TracePrinterImpl::OutToCompile(shared_ptr<TraceEntry> trace_entry)
	{
		OutputDebugStringA(trace_entry->trace_json_text().c_str());
		return 0;
	}

	int TracePrinterImpl::OutToConsole(shared_ptr<TraceEntry> trace_entry)
	{
		if (default_level_color_.count(trace_entry->level))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_level_color_[trace_entry->level]);
		}
		if (trace_config().console_format == 0)
		{
			fputs(trace_entry->trace_json_text().c_str(), stdout);
		}
		else
		{
			if (!trace_entry->trace_console_text().empty())
			{
				fwrite(trace_entry->trace_console_text().c_str(), 1, trace_entry->trace_console_text().size(), stdout);
			}
		}
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
			const string& trace_entry_text = trace_entry->trace_json_text();

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
					+ process_name_ + "_" + trace_entry->modulename + "_" + process_time_
					+ "_trace_all.log";
				OutToFile(trace_file_name, trace_entry_text);
				// 按模块按等级输出
				if (trace_config().file_level)
				{
					trace_file_name = trace_file_dir
						+ process_name_ + "_" + trace_entry->modulename + "_" + process_time_
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
		if (trace_entry)
		{
			string local_ip;
			int    local_port = 0;
			if (trace_entry->async)
			{
				KlogSource::instance().GetAsyncTraceIPandPort(local_ip, local_port);
			}
			else
			{
				KlogSource::instance().GetSyncTraceIPandPort(local_ip, local_port);
			}
			SendKlogMessageEvent message_event;
			message_event.event_type = NetEventType::SEND_KLOG_MESSAGE;
			message_event.source_info.source_program_name = trace_entry->processname;
			message_event.source_info.sourece_ip = local_ip;
			message_event.source_info.source_port = local_port;
			message_event.klog_message = trace_entry->trace_json_text();
			string klog_serial_data;
			serial_parse_->Serial(message_event, klog_serial_data);
			if (trace_entry->async)
			{
				KlogSource::instance().AsyncTraceWrite(klog_serial_data);
			}
			else
			{
				KlogSource::instance().SyncTraceWrite(klog_serial_data);
			}
			cout << "writed log data:" << message_event.klog_message << endl;
		}
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
		//SetConsoleUTF8();
		return 0;
	}

	int TracePrinterImpl::SetConsoleUTF8()
	{
		SetConsoleOutputCP(CP_UTF8);
		SetConsoleCP(CP_UTF8);
		CONSOLE_FONT_INFOEX fontInfo;
		memset(&fontInfo, 0, sizeof(CONSOLE_FONT_INFOEX));
		fontInfo.cbSize = sizeof(fontInfo);
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetCurrentConsoleFontEx(hConsole, false, &fontInfo);
		fontInfo.FontFamily = 54;
		fontInfo.dwFontSize.X = 8;
		fontInfo.dwFontSize.Y = 14;
		fontInfo.FontWeight = FW_NORMAL;
		wcscpy_s(fontInfo.FaceName, L"KaiTi");
		SetCurrentConsoleFontEx(hConsole, false, &fontInfo);
		TCHAR old_title[64] = { 0 };
		GetConsoleTitle(old_title, 63);
		tstring title = old_title;
		title = title + TEXT("_UTF8格式");
		SetConsoleTitle(title.c_str());
		return 0;
	}

	int TracePrinterImpl::InitSocket()
	{
		serial_parse_ = KlogNetProtocolLibrary::instance()->GetProtocolSerial();
		string server_ip = trace_config().trace_server_ip;
		int server_control_port = trace_config().trace_server_control_port;
		int erver_sync_trace_port = trace_config().trace_server_sync_trace_port;
		int server_async_trace_port = trace_config().trace_server_async_trace_port;
		std::thread t([server_ip, server_control_port, erver_sync_trace_port, server_async_trace_port]() {
			KlogSource::instance().Connect(server_ip, server_control_port, erver_sync_trace_port, server_async_trace_port, true);
			});
		t.detach();
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
