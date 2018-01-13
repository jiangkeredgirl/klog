#include "traceloader.h"
#include "traceloaderimpl.h"

namespace kk
{
	TraceLoader::TraceLoader(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...)
	{		
		trace_loader_impl_ = new TraceLoaderImpl(is_track, level, strlevel, label, module_name, file_name, func_name, line, log_format);
	}

	TraceLoader::~TraceLoader()
	{
		delete trace_loader_impl_;
	}

	stringstream& TraceLoader::trace_stream()
	{
		return trace_loader_impl_->trace_stream();
	}
}
