#include "logfile.h"
#include "kutility.h"
#include "rapidjsonparser.h"

LogFile::LogFile()
{
}

LogFile &LogFile::instance()
{
    static LogFile _instance;
    return _instance;
}

int LogFile::ReadTraceEntry(const string& logfile_name, TraceEntryParserCallback trace_entry_callback)
{
	int errorCode = 1;
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
			m_thread_read = std::thread(bind(&LogFile::ReadThread, this, trace_entry_callback));
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

void LogFile::ReadThread(TraceEntryParserCallback trace_entry_callback)
{
	string one_trace_entry_record;
	while (true)
	{
		if (m_thread_exit)
		{
			break;
		}
		string a_line_record;
		getline(m_logfile, a_line_record);
		one_trace_entry_record += a_line_record;
		if (!CJsonParser::instance().IsJsonObject(one_trace_entry_record))
		{
			one_trace_entry_record += "\n";
			continue;
		}
		TraceEntry trace_entry;
		int errorCode = CJsonParser::instance().DecodeTraceEntry(one_trace_entry_record, trace_entry);
		if (trace_entry_callback)
		{
			trace_entry_callback(trace_entry, 0);
		}
		one_trace_entry_record = "";
	}
	m_logfile.close();
}