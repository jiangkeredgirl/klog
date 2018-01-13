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
	class TraceLoaderImpl;
	class KLOGLIB_API TraceLoader
	{
	public:
		TraceLoader(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...);
		~TraceLoader();
		stringstream& trace_stream();

	private:
		TraceLoaderImpl*  trace_loader_impl_;
	};
}

