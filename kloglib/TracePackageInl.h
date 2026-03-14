#ifndef KLOG_TRACEPACKAGE_INL_H_
#define  KLOG_TRACEPACKAGE_INL_H_


#ifndef KLOG_FUNC
#define KLOG_FUNC
#endif


//#include "klogcustomsetting.h"
//#include "kloglib.h"
//#include "traceloader.h"
//#include "tracemacr.h"
//#include "TracePackage.h"
//#include "traceprinter.h"
//#include "klogsource.h"
//#include "klogsourceasynctrace.h"
//#include "klogsourcecontrol.h"
//#include "klogsourcesynctrace.h"
//#include "klogsource.cpp"
//#include "klogsourceasynctrace.cpp"
//#include "klogsourcecontrol.cpp"
//#include "klogsourcesynctrace.cpp"
#include "config.h"
#include "GenerateDumpInfo.h"
#include "rapidjsonparser.h"
#include "tracedefine.h"
#include "traceloaderimpl.h"
#include "traceprinterimpl.h"
#include "config.cpp"
#include "GenerateDumpInfo.cpp"
#include "rapidjsonparser.cpp"
#include "traceloaderimpl.cpp"
#include "traceprinterimpl.cpp"


//FMT_FUNC void vprint(std::FILE* f, string_view fmt, format_args args) {
//  if (!detail::file_ref(f).is_buffered() || !detail::has_flockfile<>())
//    return vprint_buffered(f, fmt, args);
//  auto&& buffer = detail::file_print_buffer<>(f);
//  return detail::vformat_to(buffer, fmt, args);
//}


#endif  //  KLOG_TRACEPACKAGE_INL_H_
