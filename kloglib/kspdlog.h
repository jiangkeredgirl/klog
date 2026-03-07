#pragma once
#ifndef LOG_WRAPPER_H
#define LOG_WRAPPER_H

#include <string>
#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <chrono>
#include <sstream>
#include <cinttypes>
#include <ctime>
#include <iomanip>
#include <map>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/async.h"
#include "spdlog/pattern_formatter.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/common.h"
#include "../kcommonhpp/kcommon.h"
#include "SpdLogWrapper.h"
using namespace spdlog;


//#define SIZE_100M           (1024 * 1024 * 100)  //redmine 上传文件限制最大50M，所以由100M改成49M
//#define FILES_NUM           1000

//#define LOG_INFO   LOG_INFO
//#define LOG_WARN   spd::get("log")->warn
//#define LOG_ERROR  LOG_ERROR

#if 1
#define LOG_ERROR(log_format, ...)                 LOGGERNAME_ERROR("default_logger",      log_format, ##__VA_ARGS__)
#define LOG_WARN(log_format, ...)                  LOGGERNAME_WARN("default_logger",       log_format, ##__VA_ARGS__)
#define LOG_INFO(log_format, ...)                  LOGGERNAME_INFO("default_logger",       log_format, ##__VA_ARGS__)
#define LOG_DEBUG(log_format, ...)                 LOGGERNAME_DEBUG("default_logger",      log_format, ##__VA_ARGS__)
#define LOG_TRACE(log_format, ...)                 LOGGERNAME_TRACE("default_logger",      log_format, ##__VA_ARGS__)
#define LOG_TEMP(log_format, ...)                  LOGGERNAME_INFO("temp_logger",          log_format, ##__VA_ARGS__)
#endif

//#define GUI_FORMAT(log_format, qt_format) std::string(log_format).append(qt_format).c_str()

#define LOG_GUI_CLICK(widget) LOG_INFO("[GUI_CLICK] button name:{}, text:{}", widget->objectName().toLocal8Bit().data(), widget->text().toLocal8Bit().data())
#define LOG_GUI_INPUT(widget) LOG_INFO("[GUI_INPUT] edit name:{}, text:{}", widget->objectName().toLocal8Bit().data(), widget->text().toLocal8Bit().data())
#define LOG_GUI_POPUP(widget) LOG_INFO("[GUI_POPUP] widget or dialog name:{}", widget->objectName().toLocal8Bit().data())

//static map<string, string> g_log_file_paths;
//map<string, std::shared_ptr<spdlog::logger>> g_loggers;

class KLog
{

public:
    /**  */
    inline static std::shared_ptr<spdlog::logger> InitLog(const string& root_log_dir, spdlog::level::level_enum log_level)
    {
        m_default_log_level = log_level;
        string date = KTime<>::GetDate(KTime<>::GetNowDateTime());
        string time = KTime<>::GetTime(KTime<>::GetNowDateTime());
        m_default_log_dir = root_log_dir + "/" + date + "/" + date + "-" + time;
        KFile::CreateDir(m_default_log_dir);
        string default_log_path = m_default_log_dir + "/" + GetProcessName() + ".log";
        // 在模式中包含 %t 来输出线程ID
        // spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%l] [thread %t] %v");
        // 线程ID固定宽度为6，右对齐，用0填充
        // spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%6t] [%l] %v");
        const string  log_pattern("[%n][%6t][%8l][%Y-%m-%d %H:%M:%S.%e][%s:%!:%#] %v");
        SpdlogInit(log_pattern);
        bool is_async = true;
        bool is_daily = true;
        std::shared_ptr<spdlog::logger>  default_logger = CreateLogger("default_logger", true, true, is_async, is_daily, false, default_log_path, log_level, log_pattern, [log_pattern](const filename_t& filename, std::FILE* file_stream) {WriteLogHeader("default_logger", filename, file_stream, log_pattern); });
        //spdlog::set([](const std::string &msg) { spdlog::get("console")->error("*** LOGGER ERROR ***: {}", msg); });
        //spdlog::get("console")->info("some invalid message to trigger an error {}{}{}{}", 3);
        return default_logger;
    }

    inline static std::shared_ptr<spdlog::logger>  SwitchLogFile(const std::string& log_sub_folder_name)
    {
        string date = KTime<>::GetDate(KTime<>::GetNowDateTime());
        string time = KTime<>::GetTime(KTime<>::GetNowDateTime());
        string new_log_dir = m_default_log_dir + "/" + date + "-" + time + "-" + log_sub_folder_name;
        // 检查最后一个字符是否是'.'
        while (!new_log_dir.empty() && new_log_dir.back() == '.')
        {
            new_log_dir.pop_back();  // 删除最后一个字符
        }
        std::cout << "处理后字符串: " << new_log_dir << std::endl;
        KFile::CreateDir(new_log_dir);
        string new_log_path = new_log_dir + "/" + GetProcessName() + ".log";
        // 假设 logger 名字叫 "file_logger"
        spdlog::drop("default_logger");  // 删除旧的 logger
        FlushLog();
        // 创建新的 logger，绑定新的日志文件
        const string  log_pattern("[%n][%6t][%8l][%Y-%m-%d %H:%M:%S.%e][%s:%!:%#] %v");
        bool is_async = true;
        bool is_daily = true;
        std::shared_ptr<spdlog::logger>  new_default_logger = CreateLogger("default_logger", true, true, is_async, is_daily, false, utf8tolocal(new_log_path), m_default_log_level, log_pattern, [log_pattern](const filename_t& filename, std::FILE* file_stream) {WriteLogHeader("default_logger", filename, file_stream, log_pattern); });
        //spdlog::set([](const std::string &msg) { spdlog::get("console")->error("*** LOGGER ERROR ***: {}", msg); });
        //spdlog::get("console")->info("some invalid message to trigger an error {}{}{}{}", 3);
        spdlog::set_default_logger(new_default_logger);
        spdlog::info("日志文件已切换到: {}", new_log_path);
        return new_default_logger;

        //auto new_logger = spdlog::basic_logger_mt("file_logger", new_log_path);
        //spdlog::set_default_logger(new_logger);
        //spdlog::info("日志文件已切换到: {}", new_log_path);
        //return new_logger;
    }

    inline static void FlushLog()
    {
        DropLog();
    }

    inline static void WriteLogHeader(const string& loggername, const filename_t& filename, std::FILE* file_stream, const string& log_pattern)
    {
        char head_buf[1000] = { 0 };
        sprintf(head_buf,
                "log header:logger name:%s log filename:%s log pattern:%s\n"
                , loggername.c_str(), localtoutf8(filename).c_str(), log_pattern.c_str());
        fputs(head_buf, file_stream);
        fflush(file_stream);
    }

    inline static string m_default_log_dir;
    inline static spdlog::level::level_enum m_default_log_level = spdlog::level::level_enum::trace;
};

#endif // LOG_WRAPPER_H

