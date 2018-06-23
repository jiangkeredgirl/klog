#pragma once

#ifdef KLOGLIB_EXPORTS
#define KLOGLIB_API __declspec(dllexport)
#else
#define KLOGLIB_API __declspec(dllimport)
#endif

#include <string>
#include <sstream>
using namespace std;

namespace kk
{
	class TraceLoader
	{
	public:
		virtual stringstream& trace_stream() = 0;
	};


#ifdef __cplusplus
	extern "C" {
#endif
		KLOGLIB_API TraceLoader* NewTraceLoader(bool is_track, int level, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...);
		KLOGLIB_API void DeleteTraceLoader(TraceLoader* loader);
#ifdef __cplusplus
	}
#endif

	typedef TraceLoader* (*NewTraceLoaderFun)(bool is_track, int level, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...);
	typedef void (*DeleteTraceLoaderFun)(TraceLoader* loader);
}