#pragma once

#define KLOG_USE_DYNAMIC_DLL    1

#if KLOG_USE_DYNAMIC_DLL
#ifdef _WIN64
#ifdef _DEBUG
#define KLOG_DLL_NAME  "kloglib_x64_Debug.dll"
#else
#define KLOG_DLL_NAME  "kloglib_x64_Release.dll"
#endif
#else
#ifdef _DEBUG
#define KLOG_DLL_NAME  "kloglib_x32_Debug.dll"
#else
#define KLOG_DLL_NAME  "kloglib_x32_Release.dll"
#endif
#endif
#endif


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
#define TRACE_LABEL          ("Log'sOwner")           ///< my output label

// 定义一些常用的trace宏
// c风格char类型 编译期可以去掉trace代码
#define TraceError(log_format, ...)          Trace(TRACE_ERROR,          log_format, ##__VA_ARGS__)
#define TraceWarning(log_format, ...)        Trace(TRACE_WARNING,        log_format, ##__VA_ARGS__)
#define TraceOK(log_format, ...)             Trace(TRACE_OK,             log_format, ##__VA_ARGS__)
#define TraceNotice(log_format, ...)         Trace(TRACE_NOTICE,         log_format, ##__VA_ARGS__)
#define TraceInfo(log_format, ...)           Trace(TRACE_INFO,           log_format, ##__VA_ARGS__)
#define TraceDebug(log_format, ...)          Trace(TRACE_DEBUG,          log_format, ##__VA_ARGS__)
#define TraceTemp(log_format, ...)           Trace(TRACE_TEMP,           log_format, ##__VA_ARGS__)

// c++风格char类型 编译期不可以去掉trace代码
#define TraceErrorCout                       TraceCout(TRACE_ERROR     )
#define TraceWarningCout                     TraceCout(TRACE_WARNING   )
#define TraceOKCout                          TraceCout(TRACE_OK        )
#define TraceNoticeCout                      TraceCout(TRACE_NOTICE    )
#define TraceInfoCout                        TraceCout(TRACE_INFO      )
#define TraceDebugCout                       TraceCout(TRACE_DEBUG     )
#define TraceTempCout                        TraceCout(TRACE_TEMP      )

//c 风格char类型 函数进入退出trace
#define Track(log_format, ...)               TraceTrack(TRACE_TRACk,  log_format, ##__VA_ARGS__)

//c++ 风格char类型 函数进入退出trace
#define TrackCout                            TraceTrackCout(TRACE_TRACk)

#define WaitTrace                            WaitAsyncTraceEnd
#define CreateConsole                        CreateKlogConsole
#define GenerateDump                         GenerateDumpInfo
#define SetConsoleUTF8                       SetKlogConsoleUTF8