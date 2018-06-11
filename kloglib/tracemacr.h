#pragma once

#include "tracepackage.h"

#define KKASSERT  _ASSERT
#define KKVERIFY(x, r) if (!(x)){TraceError((#x));return r;}


#if      TRACE_OUT
// c风格 编译期可以去掉trace代码
#define Trace(level, log_format, ...)               ((level) ? (KKTracePackage::TracePrinter::instance()->TraceOutLog(false, level, #level, TRACE_LABEL, KKTracePackage::TracePrinter::GetModuleName(), KKTracePackage::TracePrinter::GetFileName(__FILE__), __FUNCTION__, __LINE__, log_format, ##__VA_ARGS__)) : 0)
// c++风格 编译期不可以去掉trace代码
#define TraceCout(level)                            (KKTracePackage::TraceLoader(false, level, #level, TRACE_LABEL, KKTracePackage::TracePrinter::GetModuleName(), KKTracePackage::TracePrinter::GetFileName(__FILE__), __FUNCTION__, __LINE__, nullptr).trace_stream())
#else
#define Trace(level, log_format, ...)
#define TraceCout(level) stringstream()
#endif // !TRACE_OUT

#if      TRACK_OUT
// c风格 编译期可以去掉trace代码
#define TraceTrack(level, log_format, ...)           KKTracePackage::TraceLoader TraceLoaderTrack(true, level, #level, TRACE_LABEL, KKTracePackage::TracePrinter::GetModuleName(), KKTracePackage::TracePrinter::GetFileName(__FILE__), __FUNCTION__, __LINE__, log_format, ##__VA_ARGS__)
// c++风格 编译期不可以去掉trace代码
#define TraceTrackCout(level)                        KKTracePackage::TraceLoader TraceLoaderTrack(true, level, #level, TRACE_LABEL, KKTracePackage::TracePrinter::GetModuleName(), KKTracePackage::TracePrinter::GetFileName(__FILE__), __FUNCTION__, __LINE__, nullptr); TraceLoaderTrack.trace_stream()
#else
#define TraceTrack(level, log_format, ...)
#define TraceTrackCout(level) stringstream()
#endif // !TRACK_OUT

#define WaitAsyncTraceEnd  KKTracePackage::TracePrinter::instance()->WaitTraceThreadEnd()