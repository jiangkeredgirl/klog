#pragma once

#include<string>
using namespace std;

namespace kk
{
	struct TraceHead;
	struct TraceBody;
	struct TraceConfig;

	class TracePrinter
	{
	public:
		virtual TraceHead* TraceFormatHead(const string& level = "", const string& label = "", const string& file_name = "", const string& func_name = "", int line = -1, bool is_back = false) = 0;
		virtual TraceBody* TraceFormatBody(const char* log_format, ...) = 0;
		virtual int TraceOutLog(int level, TraceHead* log_head, TraceBody* log_body) = 0;
		virtual const TraceConfig& trace_config() const = 0;
		virtual const TraceConfig& trace_config(const TraceConfig& config) = 0;
		virtual int trace_out_level(int level, bool out) = 0;
		virtual int trace_level_color(int level, int color) = 0;
		virtual int WaitTraceThreadEnd() = 0;
	};
}

