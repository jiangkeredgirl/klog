#pragma once

#ifdef KLOGLIB_EXPORTS
#define KLOGLIB_API __declspec(dllexport)
#else
#define KLOGLIB_API __declspec(dllimport)
#endif

#include "kutility.h"

namespace kk
{
	struct TraceHead;
	struct TraceBody;
	struct TraceEntry;
	//template<class sCout_type>
	class KLOGLIB_API TraceLoader
	{
	public:
		TraceLoader(IN bool is_back, IN int level, IN TraceHead* trace_head, IN TraceBody* trace_body = nullptr);
		~TraceLoader();
		stringstream& trace_stream();

	private:
		bool                is_back_;
		int                 trace_level_;
		TraceEntry*         trace_info_;
		__int64             begin_call_time_;
		stringstream        trace_stream_;
	};
}

