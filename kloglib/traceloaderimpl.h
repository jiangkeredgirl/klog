#pragma once

#include <string>
#include <sstream>
using namespace std;

namespace kk
{
	struct TraceEntry;
	class TraceLoaderImpl
	{
	public:
		TraceLoaderImpl(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...);
		~TraceLoaderImpl();
		stringstream& trace_stream();

	private:
		TraceEntry*         trace_entry_;
		__int64             begin_call_time_;
		stringstream        trace_stream_;
	};
}


