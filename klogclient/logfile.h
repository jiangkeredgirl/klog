#ifndef LOGFILE_H
#define LOGFILE_H
#include "cstandard.h"
#include <QObject>

#define TRACE_TRACk           1                     ///< track out,0 not output
#define TRACE_ERROR           2                     ///< error out,0 not output
#define TRACE_WARNING         3                     ///< warning out,0 not output
#define TRACE_OK              4                     ///< ok out,0 not output
#define TRACE_NOTICE          5                     ///< notice out,0 not output
#define TRACE_INFO            6                     ///< info out,0 not output
#define TRACE_DEBUG           7                     ///< debug out,0 not output
#define TRACE_TEMP            8                     ///< temporary out,0 not output

struct TraceEntry
{
	bool     is_track = false;
	__int64  index = 0;                    ///< log序号
	string   functrack;                    ///< function follow flag >>	or <<
	__int64  functime = 0;                 ///< 函数体执行时间
	int      level = 0;                    ///< log等级
	string   label;                        ///< log标识	
	string   threadid;                     ///< 线程id
	string   processname;                  ///< 进程名
	string   modulename;                   ///< 模块名
	string   filename;                     ///< file name;
	string   funcname;                     ///< function name;
	int      line = 0;                     ///< line number;
	__int64  datetime = 0;                 ///< log打印日期时间
	__int64  runtime = 0;                  ///< log打印时程序运行时间
	bool     async = false;                ///< 是否为异步log
	bool     synclock = false;             ///< 同步模式下是否加锁
	string   content;                      ///< log内容
};

enum LogFileStatus
{
	LogFileIdle,
	LogFileReadBegin,
	LogFileReading,
	LogFileReadEnd
};

class LogFile : public QObject
{
	Q_OBJECT

private:
	LogFile();
public:
    ~LogFile(){};
public:
    static LogFile& instance();

signals:
	void SignalReceiveTrace(shared_ptr<TraceEntry> trace_entry, LogFileStatus status);
	void SignalReceiveTrack(shared_ptr<TraceEntry> track_entry, LogFileStatus status);

public:
	int ReadTraceEntry(const string& logfile_name);
	int StopRead();
	int WriteTraceEntry(const string& logfile_name, const TraceEntry& trace_entry);
	int StrToLevel(const string& strlevel);
	string LevelToStr(int level);

private:
	void ReadThread();
	void DisplayThread();
private:	
	std::thread              m_thread_read;
	bool                     m_thread_exit = false;
	ifstream                 m_logfile;
	map<int, string>         m_level_to_str;
	map<string, int>         m_str_to_level;
	//mutex                    m_thread_mutex;
	list<shared_ptr<TraceEntry>> m_trace_entry_list;
	std::thread              m_thread_display;
	mutex                    m_thread_display_mutex;
	condition_variable       m_thread_display_condition;
	mutex                    m_trace_entry_list_mutex;
};

#endif // LOGFILE_H
