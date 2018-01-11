#pragma once

#include "TracePrinter.h"
#include "traceloader.h"

// 是否生成trace 函数
#define  TRACE_OUT             1                     ///< 0 not output log, 1 output log
#define  TRACK_OUT             1                     ///< whether output trace of function called
// 是否使用glog
#define  USE_GLOG              1

// 预定义7种trace等级，数字越大输出等级越低
#define  TRACE_ERROR           1                     ///< error out,0 not output
#define  TRACE_WARNING         2                     ///< warning out,0 not output
#define  TRACE_OK              3                     ///< ok out,0 not output
#define  TRACE_NOTICE          4                     ///< notice out,0 not output
#define  TRACE_INFO            5                     ///< info out,0 not output
#define  TRACE_DEBUG           6                     ///< debug out,0 not output
#define  TRACE_TEMP            7                     ///< temporary out,0 not output

// log 标签
#define  TRACE_LABEL          ("kk")                 ///< my output label

// 定义一些常用的trace宏
// c风格char类型 编译期可以去掉trace代码
#define  TraceError(log_format, ...)          Trace(TRACE_ERROR,          log_format, ##__VA_ARGS__)
#define  TraceWarning(log_format, ...)        Trace(TRACE_WARNING,        log_format, ##__VA_ARGS__)
#define  TraceOK(log_format, ...)             Trace(TRACE_OK,             log_format, ##__VA_ARGS__)
#define  TraceNotice(log_format, ...)         Trace(TRACE_NOTICE,         log_format, ##__VA_ARGS__)
#define  TraceInfo(log_format, ...)           Trace(TRACE_INFO,           log_format, ##__VA_ARGS__)
#define  TraceDebug(log_format, ...)          Trace(TRACE_DEBUG,          log_format, ##__VA_ARGS__)
#define  TraceTemp(log_format, ...)           Trace(TRACE_TEMP,           log_format, ##__VA_ARGS__)

// c++风格char类型 编译期不可以去掉trace代码
#define  TraceErrorCout()                     TraceCout(TRACE_ERROR     )
#define  TraceWarningCout()                   TraceCout(TRACE_WARNING   )
#define  TraceOKCout()                        TraceCout(TRACE_OK        )
#define  TraceNoticeCout()                    TraceCout(TRACE_NOTICE    )
#define  TraceInfoCout()                      TraceCout(TRACE_INFO      )
#define  TraceDebugCout()                     TraceCout(TRACE_DEBUG     )
#define  TraceTempCout()                      TraceCout(TRACE_TEMP      )

//c 风格char类型 函数进入退出trace
#define  TrackDebug(log_format, ...)          Track(TRACE_DEBUG,  log_format, ##__VA_ARGS__)

//c++ 风格char类型 函数进入退出trace
#define  TrackDebugCout()                     TrackCout(TRACE_DEBUG)

#define  KKASSERT  _ASSERT
#define  KKVERIFY(x, r) if (!(x)){TraceError((#x));return r;}


#if      TRACE_OUT
// c风格 编译期可以去掉trace代码
#define  Trace(level, log_format, ...)               ((level) ? (kk::TracePrinterInstance()->TraceOutLog(level, (kk::TracePrinterInstance()->TraceFormatHead(#level, TRACE_LABEL, kk::TracePrinter::GetModuleName(), kk::Utility::GetFileName(__FILE__), __FUNCTION__, __LINE__)), kk::TracePrinterInstance()->TraceFormatBody (log_format, ##__VA_ARGS__))), 1 : 0)
// c++风格 编译期不可以去掉trace代码
#define  TraceCout(level)                            kk::TraceLoader(false, level, (kk::TracePrinterInstance()->TraceFormatHead(#level, TRACE_LABEL, kk::TracePrinter::GetModuleName(), kk::Utility::GetFileName(__FILE__), __FUNCTION__, __LINE__))).trace_stream()
#else
#define  Trace(level, printf_exp)
#define  TraceCout(level)
#endif // !TRACE_OUT

#if      TRACK_OUT
// c风格 编译期可以去掉trace代码
#define  Track(level, log_format, ...)               kk::TraceLoader TraceLoaderTrack(true, level, ((level) ? ((kk::TracePrinterInstance()->TraceFormatHead(#level, TRACE_LABEL, kk::TracePrinter::GetModuleName(), kk::Utility::GetFileName(__FILE__), __FUNCTION__, __LINE__, true))) : nullptr), ((level) ? (kk::TracePrinterInstance()->TraceFormatBody (log_format, ##__VA_ARGS__)) : nullptr))
// c++风格 编译期不可以去掉trace代码
#define  TrackCout(level)                            kk::TraceLoader TraceLoaderTrackCout(true, level, ((level) ? ((kk::TracePrinterInstance()->TraceFormatHead(#level, TRACE_LABEL, kk::TracePrinter::GetModuleName(), kk::Utility::GetFileName(__FILE__), __FUNCTION__, __LINE__, true))) : nullptr)); TraceLoaderTrackCout.trace_stream()
#else
#define  Track(level, printf_exp)
#define  TrackCout(level)
#endif // !TRACK_OUT


//#define WaitTrace()  kk::TracePrinterInstance()->WaitTraceThreadEnd()