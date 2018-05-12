#pragma once

//#include "traceprinter.h"
//#include "traceloader.h"
#define KLOG_USE_DYNAMIC_DLL    1

#if KLOG_USE_DYNAMIC_DLL
#ifdef _WIN64
#ifdef _DEBUG
#define KLOG_DLL_NAME  "kloglib_x64_v141_Debug.dll"
#else
#define KLOG_DLL_NAME  "kloglib_x64_v141_Release.dll"
#endif
#else
#ifdef _DEBUG
#define KLOG_DLL_NAME  "kloglib_x32_v141_Debug.dll"
#else
#define KLOG_DLL_NAME  "kloglib_x32_v141_Release.dll"
#endif
#endif
#endif

#include "tracepackage.h"

// 是否生成trace 函数
#define  TRACE_OUT             1                     ///< 0 not output log, 1 output log
#define  TRACK_OUT             1                     ///< whether output trace of function called
// 是否使用glog
#define  USE_GLOG              0

// 预定义8种trace等级，数字越大输出等级越低
#define  TRACE_TRACk           1                     ///< track out,0 not output
#define  TRACE_ERROR           2                     ///< error out,0 not output
#define  TRACE_WARNING         3                     ///< warning out,0 not output
#define  TRACE_OK              4                     ///< ok out,0 not output
#define  TRACE_NOTICE          5                     ///< notice out,0 not output
#define  TRACE_INFO            6                     ///< info out,0 not output
#define  TRACE_DEBUG           7                     ///< debug out,0 not output
#define  TRACE_TEMP            8                     ///< temporary out,0 not output

// log 标签
#define  TRACE_LABEL          ("Log'sOwner")           ///< my output label

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
#define  Track(log_format, ...)               TraceTrack(TRACE_TRACk,  log_format, ##__VA_ARGS__)

//c++ 风格char类型 函数进入退出trace
#define  TrackCout()                          TraceTrackCout(TRACE_TRACk)

#define  KKASSERT  _ASSERT
#define  KKVERIFY(x, r) if (!(x)){TraceError((#x));return r;}


#if      TRACE_OUT
// c风格 编译期可以去掉trace代码
#define  Trace(level, log_format, ...)               ((level) ? (KKTracePackage::TracePrinter::instance()->TraceOutLog(false, level, #level, TRACE_LABEL, KKTracePackage::TracePrinter::GetModuleName(), KKTracePackage::TracePrinter::GetFileName(__FILE__), __FUNCTION__, __LINE__, log_format, ##__VA_ARGS__)) : 0)
// c++风格 编译期不可以去掉trace代码
#define  TraceCout(level)                            (KKTracePackage::TraceLoader(false, level, #level, TRACE_LABEL, KKTracePackage::TracePrinter::GetModuleName(), KKTracePackage::TracePrinter::GetFileName(__FILE__), __FUNCTION__, __LINE__, nullptr).trace_stream())
#else
#define  Trace(level, log_format, ...)
#define  TraceCout(level) stringstream()
#endif // !TRACE_OUT

#if      TRACK_OUT
// c风格 编译期可以去掉trace代码
#define  TraceTrack(level, log_format, ...)           KKTracePackage::TraceLoader TraceLoaderTrack(true, level, #level, TRACE_LABEL, KKTracePackage::TracePrinter::GetModuleName(), KKTracePackage::TracePrinter::GetFileName(__FILE__), __FUNCTION__, __LINE__, log_format, ##__VA_ARGS__)
// c++风格 编译期不可以去掉trace代码
#define  TraceTrackCout(level)                        KKTracePackage::TraceLoader TraceLoaderTrack(true, level, #level, TRACE_LABEL, KKTracePackage::TracePrinter::GetModuleName(), KKTracePackage::TracePrinter::GetFileName(__FILE__), __FUNCTION__, __LINE__, nullptr); TraceLoaderTrack.trace_stream()
#else
#define  TraceTrack(level, log_format, ...)
#define  TraceTrackCout(level) stringstream()
#endif // !TRACK_OUT
#define WaitTrace()  KKTracePackage::TracePrinter::instance()->WaitTraceThreadEnd()