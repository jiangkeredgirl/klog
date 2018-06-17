#ifndef LOGFILE_H
#define LOGFILE_H
#include "cstandard.h"

struct TraceEntry
{
	__int64  index = 0;                    ///< log序号
	int      level = 0;                    ///< log等级
	string   macro_level;                  ///< log等级的宏形式
	string   label;                        ///< log标识	
	string   thread_id;                    ///< 线程id
	__int64  datetime;                     ///< log打印日期时间
	__int64  runtime = 0;                  ///< log打印时程序运行时间
	__int64  function_time = 0;            ///< 函数体执行时间
	string   process_name;                 ///< 进程名
	string   module_name;                  ///< 模块名
	string   file_name;                    ///< file name;
	string   function_name;                ///< function name;
	int      line = 0;                     ///< line number;
	string   func_enter;                   ///< function follow flag >>
	string   func_exit;                    ///< function follow flag <<
	bool     async = false;                ///< 是否为异步log
	bool     sync_lock = false;            ///< 同步模式下是否加锁		
	bool     is_track = false;
	string   content;                      ///< log内容
};

typedef std::function<int(const TraceEntry& trace_entry, int status)> TraceEntryParserCallback;

class LogFile
{
private:
	LogFile();
public:
    ~LogFile(){};
public:
    static LogFile& instance();

public:
	int ReadTraceEntry(const string& logfile_name, TraceEntryParserCallback trace_entry_callback);
	int StopRead();
	int WriteTraceEntry(const string& logfile_name, const TraceEntry& trace_entry);

private:
	void ReadThread(TraceEntryParserCallback trace_entry_callback);
private:	
	std::thread              m_thread_read;
	atomic_bool              m_thread_exit = false;
	ifstream                 m_logfile;
};

#endif // LOGFILE_H
