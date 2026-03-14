#ifndef KLOG_TRACEPACKAGE_INL_H_
#define  KLOG_TRACEPACKAGE_INL_H_


#ifndef KLOG_FUNC
#define KLOG_FUNC
#endif


//FMT_FUNC void vprint(std::FILE* f, string_view fmt, format_args args) {
//  if (!detail::file_ref(f).is_buffered() || !detail::has_flockfile<>())
//    return vprint_buffered(f, fmt, args);
//  auto&& buffer = detail::file_print_buffer<>(f);
//  return detail::vformat_to(buffer, fmt, args);
//}


#endif  //  KLOG_TRACEPACKAGE_INL_H_
