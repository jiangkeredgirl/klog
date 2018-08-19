﻿#include "logfile.h"
#include "kutility.h"
#include "rapidjsonparser.h"

LogFile::LogFile()
{
	m_level_to_str[TRACE_TRACk] = "trace_track";
	m_level_to_str[TRACE_ERROR] = "trace_error";
	m_level_to_str[TRACE_WARNING] = "trace_warning";
	m_level_to_str[TRACE_OK] = "trace_ok";
	m_level_to_str[TRACE_NOTICE] = "trace_notice";
	m_level_to_str[TRACE_INFO] = "trace_info";
	m_level_to_str[TRACE_DEBUG] = "trace_debug";
	m_level_to_str[TRACE_TEMP] = "trace_temp";

	m_str_to_level["trace_track"] = TRACE_TRACk;
	m_str_to_level["trace_error"] = TRACE_ERROR;
	m_str_to_level["trace_warning"] = TRACE_WARNING;
	m_str_to_level["trace_ok"] = TRACE_OK;
	m_str_to_level["trace_notice"] = TRACE_NOTICE;
	m_str_to_level["trace_info"] = TRACE_INFO;
	m_str_to_level["trace_debug"] = TRACE_DEBUG;
	m_str_to_level["trace_temp"] = TRACE_TEMP;
}

LogFile &LogFile::instance()
{
    static LogFile _instance;
    return _instance;
}

int LogFile::ReadTraceEntry(const string& logfile_name)
{
	int errorCode = 1;
	StopRead();
	do
	{
		m_logfile.open(logfile_name.c_str());
		if (!m_logfile)
		{
			break;
		}
		if (!m_logfile.is_open())
		{
			break;
		}
		// boot thread    
		if (!m_thread_read.joinable())
		{
			m_thread_exit = false;
			m_thread_read = std::thread(bind(&LogFile::ReadThread, this));
		}
		errorCode = 0;
	} while (0);
	return errorCode;
}

int LogFile::StopRead()
{
	if (m_thread_read.joinable())
	{
		m_thread_exit = true;
		m_thread_read.join();
	}
	return 0;
}

int LogFile::WriteTraceEntry(const string& logfile_name, const TraceEntry& trace_entry)
{
	int errorCode = 1;
	//string configContent;	
	//errorCode = CJsonParser::instance().SetTraceEntry(trace_entry, configContent);
	//kk::Utility::WriteFile(logfile_name, configContent);
	return errorCode;
}

int LogFile::StrToLevel(const string& strlevel)
{
	int level = -1;
	if (m_str_to_level.count(strlevel))
	{
		level = m_str_to_level[strlevel];
	}
	else
	{
		level = stoi(strlevel);
	}
	return level;
}

string LogFile::LevelToStr(int level)
{
	string strlevel;
	if (m_level_to_str.count(level))
	{
		strlevel = m_level_to_str[level];
	}
	else
	{
		strlevel = to_string(level);
	}
	return strlevel;
}

void LogFile::ReadThread()
{
	emit SignalReceiveTrace(nullptr, LogFileStatus::LogFileReadBegin);
	string one_trace_entry_record;
	while (true)
	{
		if (m_thread_exit)
		{
			break;
		}
		string a_line_record;
		getline(m_logfile, a_line_record);
		if (m_logfile.eof())
		{
			emit SignalReceiveTrace(nullptr, LogFileStatus::LogFileReadEnd);
			break;
		}
		one_trace_entry_record += a_line_record;
		if (!CJsonParser::instance().IsJsonObject(one_trace_entry_record))
		{
			if (!one_trace_entry_record.empty())
			{
				one_trace_entry_record += "\\n";
			}
			continue;
		}
		shared_ptr<TraceEntry> trace_entry(new TraceEntry);
		int errorCode = CJsonParser::instance().DecodeTraceEntry(one_trace_entry_record, *trace_entry);
		emit SignalReceiveTrace(trace_entry, LogFileStatus::LogFileReading);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));		
		one_trace_entry_record = "";
	}
	m_logfile.close();	
}