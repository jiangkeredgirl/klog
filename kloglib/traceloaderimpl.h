﻿#pragma once

#include "traceloader.h"
#include <string>
#include <sstream>
#include "cstandard.h"
using namespace std;

namespace kk
{
	struct TraceEntry;
	class TraceLoaderImpl : public TraceLoader
	{
	public:
		TraceLoaderImpl(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...);
		~TraceLoaderImpl();
		virtual stringstream& trace_stream() override;

	private:
		shared_ptr<TraceEntry>   trace_entry_;
		__int64                  begin_call_time_;
		stringstream             trace_stream_;
	};
}


