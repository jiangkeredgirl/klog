#pragma once
#include "kutility.h"
#include "TracePrinterimpl.h"

namespace kk
{
	//template<class sCout_type>
	class  TraceLoader
	{
	public:
		TraceLoader(IN bool is_back, IN int level, IN TraceHead* trace_head, IN TraceBody* trace_body = new TraceBody());
		~TraceLoader();
		stringstream& trace_stream();

	private:
		bool                is_back_;
		int                 trace_level_;
		TraceEntry          trace_info_;
		__int64             begin_call_time_;
		stringstream        trace_stream_;
	};
}

