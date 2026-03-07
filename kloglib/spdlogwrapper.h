#pragma once

#include <string>
#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <chrono>
#include <sstream>
#include <string>
#include <chrono>
#include <cinttypes>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <map>
using namespace std;
using namespace chrono;
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"
#include "spdlog/pattern_formatter.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/common.h"
using namespace spdlog;


#define SIZE_100M           (1024 * 1024 * 100)  
#define FILES_NUM           1000

//#define LOG_INFO   LOG_INFO
//#define LOG_WARN   spd::get("log")->warn
//#define LOG_ERROR  LOG_ERROR



#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1):__FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#endif

#define logsuffix(log_format)  std::string("[").append(__FILENAME__).append(":").append(__FUNCTION__).append("()#").append(std::to_string(__LINE__)).append("] ").append(log_format).c_str()

//#define STDOUT_LOG_TRACE(log_format, ...)              if (spdlog::get("stdout_log") != NULL) { spdlog::get("stdout_log")->trace( logsuffix(log_format), ##__VA_ARGS__); }
//#define STDOUT_LOG_DEBUG(log_format, ...)              if (spdlog::get("stdout_log") != NULL) { spdlog::get("stdout_log")->debug( logsuffix(log_format), ##__VA_ARGS__); }
//#define STDOUT_LOG_INFO(log_format, ...)               if (spdlog::get("stdout_log") != NULL) { spdlog::get("stdout_log")->info( logsuffix(log_format), ##__VA_ARGS__); }
//#define STDOUT_LOG_WARN(log_format, ...)               if (spdlog::get("stdout_log") != NULL) { spdlog::get("stdout_log")->warn( logsuffix(log_format), ##__VA_ARGS__); }
//#define STDOUT_LOG_ERROR(log_format, ...)              if (spdlog::get("stdout_log") != NULL) { spdlog::get("stdout_log")->error( logsuffix(log_format), ##__VA_ARGS__); }

//#if 0
//#define LOG_TRACE(log_format, ...)              if (spdlog::get("multisink") != NULL) { spdlog::get("multisink")->trace( logsuffix(log_format), ##__VA_ARGS__); }
//#define LOG_DEBUG(log_format, ...)              if (spdlog::get("multisink") != NULL) { spdlog::get("multisink")->debug( logsuffix(log_format), ##__VA_ARGS__); }
//#define LOG_INFO(log_format, ...)               if (spdlog::get("multisink") != NULL) { spdlog::get("multisink")->info(  logsuffix(log_format), ##__VA_ARGS__); }
//#define LOG_WARN(log_format, ...)               if (spdlog::get("multisink") != NULL) { spdlog::get("multisink")->warn(  logsuffix(log_format), ##__VA_ARGS__); }
//#define LOG_ERROR(log_format, ...)              if (spdlog::get("multisink") != NULL) { spdlog::get("multisink")->error( logsuffix(log_format), ##__VA_ARGS__); }
//#define LOG_DATA(loghandle, log_format, ...)  	if (spdlog::get(loghandle)   != NULL) { spdlog::get(loghandle)->info(              log_format , ##__VA_ARGS__); }
//#elif 1
//#define LOG_TRACE(log_format, ...)              if (spdlog::get("trace_default_log") != NULL) { spdlog::get("trace_default_log")->trace( logsuffix(log_format), ##__VA_ARGS__); }
//#define LOG_DEBUG(log_format, ...)              if (spdlog::get("debug_default_log") != NULL) { spdlog::get("debug_default_log")->debug( logsuffix(log_format), ##__VA_ARGS__); }
//#define LOG_INFO(log_format, ...)               if (spdlog::get("info_default_log") != NULL) { spdlog::get("info_default_log")->info(  logsuffix(log_format), ##__VA_ARGS__); }
//#define LOG_WARN(log_format, ...)               if (spdlog::get("warn_default_log") != NULL) { spdlog::get("warn_default_log")->warn(  logsuffix(log_format), ##__VA_ARGS__); }
//#define LOG_ERROR(log_format, ...)              if (spdlog::get("error_default_log") != NULL) { spdlog::get("error_default_log")->error( logsuffix(log_format), ##__VA_ARGS__); }
//#define LOG_DATA(loghandle, log_format, ...)  	if (spdlog::get(loghandle)   != NULL) { spdlog::get(loghandle)->info(              log_format , ##__VA_ARGS__); }
//#endif





#define LOGGER_ERROR(logger, log_format, ...)    if (logger != nullptr) { logger->error( logsuffix(log_format), ##__VA_ARGS__); }
#define LOGGER_WARN(logger,  log_format, ...)    if (logger != nullptr) { logger->warn(  logsuffix(log_format), ##__VA_ARGS__); }
#define LOGGER_INFO(logger,  log_format, ...)    if (logger != nullptr) { logger->info(  logsuffix(log_format), ##__VA_ARGS__); }
#define LOGGER_DEBUG(logger, log_format, ...)    if (logger != nullptr) { logger->debug( logsuffix(log_format), ##__VA_ARGS__); }
#define LOGGER_TRACE(logger, log_format, ...)    if (logger != nullptr) { logger->trace( logsuffix(log_format), ##__VA_ARGS__); }
#define LOGGER_DATA(logger,  log_format, ...)    if (logger != nullptr) { logger->info(            log_format , ##__VA_ARGS__); }

#define LOGGERNAME_ERROR(logger_name, log_format, ...)    if (spdlog::get(logger_name) != nullptr) { std::shared_ptr<spdlog::logger> logger = spdlog::get(logger_name);logger->error( logsuffix(log_format), ##__VA_ARGS__); }
#define LOGGERNAME_WARN(logger_name,  log_format, ...)    if (spdlog::get(logger_name) != nullptr) { std::shared_ptr<spdlog::logger> logger = spdlog::get(logger_name);logger->warn(  logsuffix(log_format), ##__VA_ARGS__); }
#define LOGGERNAME_INFO(logger_name,  log_format, ...)    if (spdlog::get(logger_name) != nullptr) { std::shared_ptr<spdlog::logger> logger = spdlog::get(logger_name);logger->info(  logsuffix(log_format), ##__VA_ARGS__); }
#define LOGGERNAME_DEBUG(logger_name, log_format, ...)    if (spdlog::get(logger_name) != nullptr) { std::shared_ptr<spdlog::logger> logger = spdlog::get(logger_name);logger->debug( logsuffix(log_format), ##__VA_ARGS__); }
#define LOGGERNAME_TRACE(logger_name, log_format, ...)    if (spdlog::get(logger_name) != nullptr) { std::shared_ptr<spdlog::logger> logger = spdlog::get(logger_name);logger->trace( logsuffix(log_format), ##__VA_ARGS__); }
#define LOGGERNAME_DATA(logger_name,  log_format, ...)    if (spdlog::get(logger_name) != nullptr) { std::shared_ptr<spdlog::logger> logger = spdlog::get(logger_name);logger->info(            log_format , ##__VA_ARGS__); }



const string  g_spdlog_default_pattern("[%n][%6t][%8l][%Y-%m-%d %H:%M:%S.%e][%s:%!:%#] %v"/*"[%i][%P][%t]%+"*/);
typedef std::function<void(const filename_t &filename, std::FILE *file_stream)> after_open_eventf;


inline int SpdlogInit(const string & log_pattern)
{
    spdlog::init_thread_pool(819200, 1);
    //当遇到错误级别以上的立刻刷新到日志
    spdlog::flush_on(spdlog::level::err);
    //每三秒刷新一次
    // periodically flush all *registered* loggers every 3 seconds:
    // warning: only use if all your loggers are thread safe ("_mt" loggers)
    spdlog::flush_every(std::chrono::seconds(3));
    // 在模式中包含 %t 来输出线程ID
    // spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%l] [thread %t] %v");
    spdlog::set_pattern(log_pattern);

    return 0;
}

inline std::shared_ptr<spdlog::logger> CreateLogger(const string & logger_name, bool is_stdout, bool is_fileout, bool is_async, bool is_daily, bool is_rotate, const string & file_path
                                                    , spdlog::level::level_enum log_level = spdlog::level::info, const string & _log_pattern = g_spdlog_default_pattern
                                                    , after_open_eventf open_eventf = nullptr)
{

    //当遇到错误级别以上的立刻刷新到日志
    //spdlog::flush_on(spdlog::level::err);
    //每三秒刷新一次
    // periodically flush all *registered* loggers every 3 seconds:
    // warning: only use if all your loggers are thread safe ("_mt" loggers)
    //spdlog::flush_every(std::chrono::seconds(3));

    std::shared_ptr<spdlog::logger> logger = nullptr;

    //spdlog::init_thread_pool(819200, 1);

    string log_pattern(_log_pattern);
    if(log_pattern.empty())
    {
        log_pattern = g_spdlog_default_pattern;
    }

    if(is_async)
    {
        std::vector<spdlog::sink_ptr> sinks;
        logger = std::make_shared<spdlog::async_logger>(logger_name, sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    }
    else
    {
        logger = std::make_shared<spdlog::logger>(logger_name);
    }
    logger->set_level(log_level);
    logger->set_pattern(log_pattern);
    spdlog::register_logger(logger);

    if(is_stdout)
    {
        auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        stdout_sink->set_level(spdlog::level::info);
        logger->sinks().push_back(stdout_sink);
    }

    if(is_fileout)
    {
        std::shared_ptr<spdlog::sinks::sink> sink = nullptr;
        if(is_daily)
        {
            if(open_eventf)
            {
                spdlog::file_event_handlers handlers;
                handlers.after_open = open_eventf;
                auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(file_path, 0, 0, false, 0, handlers);
                sink = daily_sink;
            }
            else
            {
                auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(file_path, 0, 0);
                sink = daily_sink;
            }
        }
        else if(is_rotate)
        {
           auto rotate_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_path, SIZE_100M, FILES_NUM);
           sink = rotate_sink;
        }
        else
        {
           auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file_path, true);
           sink = file_sink;
        }
        logger->sinks().push_back(sink);
    }
    logger->set_level(log_level);
    logger->set_pattern(log_pattern);
    logger->info("logger created logger name:{}, log file path:{}", logger_name, localtoutf8(file_path));

    return logger;
}


inline std::shared_ptr<spdlog::logger> CreateLoggerWithSplitFileByLogLevel(const string & logger_name, bool is_stdout, bool is_fileout, bool is_async, bool is_daily, bool is_rotate, const string & file_path, spdlog::level::level_enum log_level = spdlog::level::info, const string & _log_pattern = g_spdlog_default_pattern)
{
    std::shared_ptr<spdlog::logger> logger = nullptr;

    string log_pattern(_log_pattern);
    if(log_pattern.empty())
    {
        log_pattern = g_spdlog_default_pattern;
    }

    if(is_async)
    {
        spdlog::init_thread_pool(8192, 1);
        std::vector<spdlog::sink_ptr> sinks;
        logger = std::make_shared<spdlog::async_logger>(logger_name, sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    }
    else
    {
        logger = std::make_shared<spdlog::logger>(logger_name);
    }
    logger->set_level(log_level);
    logger->set_pattern(log_pattern);
    spdlog::register_logger(logger);


    if(is_stdout)
    {
        auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        stdout_sink->set_level(spdlog::level::info);
        logger->sinks().push_back(stdout_sink);
    }

    if(is_fileout)
    {
        string base_file_path = file_path;
        string suffix;
        string::size_type dot_pos = base_file_path.rfind(".");
        if(dot_pos != string::npos)
        {
            base_file_path = base_file_path.erase(dot_pos, base_file_path.size() - dot_pos);
            suffix = base_file_path.substr(dot_pos);
        }

        string critical_file_path = base_file_path + "_critical" + suffix;
        string error_file_path    = base_file_path + "_error" + suffix;
        string warn_file_path     = base_file_path + "_warn" + suffix;
        string info_file_path     = base_file_path + "_info" + suffix;
        string debug_file_path    = base_file_path + "_debug" + suffix;
        string trace_file_path    = base_file_path + "_trace" + suffix;
        map<int, string> log_level_file_paths;
        log_level_file_paths[spdlog::level::critical] = critical_file_path;
        log_level_file_paths[spdlog::level::err]      = error_file_path;
        log_level_file_paths[spdlog::level::warn]     = warn_file_path;
        log_level_file_paths[spdlog::level::info]     = info_file_path;
        log_level_file_paths[spdlog::level::debug]    = debug_file_path;
        log_level_file_paths[spdlog::level::trace]    = trace_file_path;

        switch (log_level) {
        case spdlog::level::critical:
        {
            std::shared_ptr<spdlog::sinks::sink> sink = nullptr;
            if(is_daily)
            {
                auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(log_level_file_paths[log_level], 0, 0);
                sink = daily_sink;
            }
            else if(is_rotate)
            {
                auto rotate_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_level_file_paths[log_level], SIZE_100M, FILES_NUM);
                sink = rotate_sink;
            }
            else
            {
                auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_level_file_paths[log_level], true);
                sink = file_sink;
            }
            sink->set_level(log_level);
            logger->sinks().push_back(sink);
        }

        case spdlog::level::err:
        {
            std::shared_ptr<spdlog::sinks::sink> sink = nullptr;
            if(is_daily)
            {
                auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(log_level_file_paths[log_level], 0, 0);
                sink = daily_sink;
            }
            else if(is_rotate)
            {
                auto rotate_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_level_file_paths[log_level], SIZE_100M, FILES_NUM);
                sink = rotate_sink;
            }
            else
            {
                auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_level_file_paths[log_level], true);
                sink = file_sink;
            }
            sink->set_level(log_level);
            logger->sinks().push_back(sink);
        }

        case spdlog::level::warn:
        {
            std::shared_ptr<spdlog::sinks::sink> sink = nullptr;
            if(is_daily)
            {
                auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(log_level_file_paths[log_level], 0, 0);
                sink = daily_sink;
            }
            else if(is_rotate)
            {
                auto rotate_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_level_file_paths[log_level], SIZE_100M, FILES_NUM);
                sink = rotate_sink;
            }
            else
            {
                auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_level_file_paths[log_level], true);
                sink = file_sink;
            }
            sink->set_level(log_level);
            logger->sinks().push_back(sink);
        }

        case spdlog::level::info:
        {
            std::shared_ptr<spdlog::sinks::sink> sink = nullptr;
            if(is_daily)
            {
                auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(log_level_file_paths[log_level], 0, 0);
                sink = daily_sink;
            }
            else if(is_rotate)
            {
                auto rotate_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_level_file_paths[log_level], SIZE_100M, FILES_NUM);
                sink = rotate_sink;
            }
            else
            {
                auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_level_file_paths[log_level], true);
                sink = file_sink;
            }
            sink->set_level(log_level);
            logger->sinks().push_back(sink);
        }

        case spdlog::level::debug:
        {
            std::shared_ptr<spdlog::sinks::sink> sink = nullptr;
            if(is_daily)
            {
                auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(log_level_file_paths[log_level], 0, 0);
                sink = daily_sink;
            }
            else if(is_rotate)
            {
                auto rotate_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_level_file_paths[log_level], SIZE_100M, FILES_NUM);
                sink = rotate_sink;
            }
            else
            {
                auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_level_file_paths[log_level], true);
                sink = file_sink;
            }
            sink->set_level(log_level);
            logger->sinks().push_back(sink);
        }

        case spdlog::level::trace:
        {
            std::shared_ptr<spdlog::sinks::sink> sink = nullptr;
            if(is_daily)
            {
                auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(log_level_file_paths[log_level], 0, 0);
                sink = daily_sink;
            }
            else if(is_rotate)
            {
                auto rotate_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_level_file_paths[log_level], SIZE_100M, FILES_NUM);
                sink = rotate_sink;
            }
            else
            {
                auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_level_file_paths[log_level], true);
                sink = file_sink;
            }
            sink->set_level(log_level);
            logger->sinks().push_back(sink);
        }
            break;
        default:
            break;
        }
    }

    logger->info("logger created logger name:{}, log file path:{}", logger_name, localtoutf8(file_path));

    return logger;
}


inline void DropLog()
{
    spdlog::drop_all();
}



