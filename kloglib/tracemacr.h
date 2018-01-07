#pragma once

#include "TracePrinter.h"

// 是否生成trace 函数
#define  TRACE_OUT             1                     ///< 0 not output log, 1 output log
#define  TRACK_OUT             1                     ///< whether output trace of function called
// 是否使用glog
#define  USE_GLOG              1

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
#define  TraceBackDebug(log_format, ...)      TraceBack(TRACE_DEBUG,  log_format, ##__VA_ARGS__)

//c++ 风格char类型 函数进入退出trace
#define  TraceBackDebugCout()                 TraceBackCout(TRACE_DEBUG)

#define  KKASSERT  _ASSERT
#define  KKVERIFY(x, r) if (!(x)){TraceError((#x));return r;}


#if      TRACE_OUT
// c风格 编译期可以去掉trace代码
#define  Trace(level, log_format, ...)               ((level) ? (kk::TracePrinterInstance()->TraceOutLog(level, (kk::TracePrinterInstance()->TraceFormatHead(#level, TRACE_LABEL, TracePrinter::GetModuleName(), kk::Utility::GetFileName(__FILE__), __FUNCTION__, __LINE__)), kk::TracePrinterInstance()->TraceFormatBody (log_format, ##__VA_ARGS__))), 1 : 0)
// c++风格 编译期不可以去掉trace代码
#define  TraceCout(level)                            kk::TraceLoader(false, level, (kk::TracePrinterInstance()->TraceFormatHead(#level, TRACE_LABEL, TracePrinter::GetModuleName(), kk::Utility::GetFileName(__FILE__), __FUNCTION__, __LINE__))).trace_stream()

#if      TRACK_OUT
// c风格 编译期可以去掉trace代码
#define  Track(level, log_format, ...)               kk::TraceLoader TraceLoaderBack(true, level, ((level) ? ((kk::TracePrinterInstance()->TraceFormatHead(#level, TRACE_LABEL, TracePrinter::GetModuleName(), kk::Utility::GetFileName(__FILE__), __FUNCTION__, __LINE__, true))) : kk::TraceHead()/*""*/), ((level) ? (kk::TracePrinterInstance()->TraceFormatBody (log_format, ##__VA_ARGS__)) : kk::TraceBody()/*""*/))
// c++风格 编译期不可以去掉trace代码
#define  TrackCout(level)                            kk::TraceLoader TraceLoaderBackCout(true, level, ((level) ? ((kk::TracePrinterInstance()->TraceFormatHead(#level, TRACE_LABEL, TracePrinter::GetModuleName(), kk::Utility::GetFileName(__FILE__), __FUNCTION__, __LINE__, true))) : kk::TraceHead()/*""*/)); TraceLoaderBackCout.trace_stream()
#else
#define  TraceBack(level, printf_exp)
#endif // !TRACK_OUT
#else
#define  Trace(level, printf_exp)
#define  TraceBack(level, printf_exp)
#endif // !TRACE_OUT


//#define WaitTrace()  kk::TracePrinterInstance()->WaitTraceThreadEnd()