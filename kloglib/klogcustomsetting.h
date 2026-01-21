#pragma once 


// 是否生成trace 函数
#define TRACE_OUT             1                     ///< 0 not output log, 1 output log
#define TRACK_OUT             1                     ///< whether output trace of function called
// 是否使用glog
#define USE_GLOG              0

// 预定义8种trace等级，数字越大输出等级越低
#define TRACE_TRACk           1                     ///< track out,0 not output
#define TRACE_ERROR           2                     ///< error out,0 not output
#define TRACE_WARNING         3                     ///< warning out,0 not output
#define TRACE_OK              4                     ///< ok out,0 not output
#define TRACE_NOTICE          5                     ///< notice out,0 not output
#define TRACE_INFO            6                     ///< info out,0 not output
#define TRACE_DEBUG           7                     ///< debug out,0 not output
#define TRACE_TEMP            8                     ///< temporary out,0 not output

// log 标签
#define TRACE_LABEL          ("kk")                 ///< my output label

// 定义一些常用的trace宏
// c风格char类型 编译期可以去掉trace代码
#define KlogError(log_format, ...)          Trace(TRACE_ERROR,          log_format, ##__VA_ARGS__)
#define KlogWarn(log_format, ...)           Trace(TRACE_WARNING,        log_format, ##__VA_ARGS__)
#define KlogOK(log_format, ...)             Trace(TRACE_OK,             log_format, ##__VA_ARGS__)
#define KlogNotice(log_format, ...)         Trace(TRACE_NOTICE,         log_format, ##__VA_ARGS__)
#define KlogInfo(log_format, ...)           Trace(TRACE_INFO,           log_format, ##__VA_ARGS__)
#define KlogDebug(log_format, ...)          Trace(TRACE_DEBUG,          log_format, ##__VA_ARGS__)
#define KlogTemp(log_format, ...)           Trace(TRACE_TEMP,           log_format, ##__VA_ARGS__)

// c++风格char类型 编译期不可以去掉trace代码
#define KlogErrorCout                       TraceCout(TRACE_ERROR     )
#define KlogWarnCout                        TraceCout(TRACE_WARNING   )
#define KlogOKCout                          TraceCout(TRACE_OK        )
#define KlogNoticeCout                      TraceCout(TRACE_NOTICE    )
#define KlogInfoCout                        TraceCout(TRACE_INFO      )
#define KlogDebugCout                       TraceCout(TRACE_DEBUG     )
#define KlogTempCout                        TraceCout(TRACE_TEMP      )

//c 风格char类型 函数进入退出trace
#define KlogTrack(log_format, ...)          TraceTrack(TRACE_TRACk,  log_format, ##__VA_ARGS__)
//c++ 风格char类型 函数进入退出trace
#define KlogTrackCout                       TraceTrackCout(TRACE_TRACk)

#define KlogWaitAsyncEnd                    TraceWaitAsyncEnd
#define KlogCreateStdout                    TraceCreateStdout
#define KlogSetStdoutUTF8                   TraceSetStdoutUTF8
#define KlogGenerateDump                    TraceGenerateDump