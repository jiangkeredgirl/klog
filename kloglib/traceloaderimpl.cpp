#include "traceloaderimpl.h"
#include "TracePrinterimpl.h"

namespace kk
{
	TraceLoaderImpl::TraceLoaderImpl(bool is_track, int level, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...)
	{
		do
		{
			if (!TracePrinterImpl::instance().IsOut(is_track, level))
			{
				break;
			}
			///
			string log_body;
			do
			{
				if (log_format == nullptr)
				{
					break;
				}
				size_t log_length = ONE_TRACE_SIZE;
				if (strlen(log_format) >= static_cast<size_t>(log_length))
				{
					log_length += strlen(log_format);
				}
				char* log_exp = new char[log_length];
				memset(log_exp, 0, sizeof(char) * log_length);
				int write_size = 0;
				va_list va;
				va_start(va, log_format);
				write_size = _vsnprintf_s(log_exp, log_length, _TRUNCATE, log_format, va);
				va_end(va);
				log_body += log_exp;
				if (write_size == -1)
				{
					log_body += "[...truncate, use Trace(xxx) replace Trace(\"%s\", xxx) by klog author]";
				}
				delete[] log_exp;
			} while (false);
			///
			trace_entry_enter_ = TracePrinterImpl::instance().TraceFormatEntry(is_track, level, label, module_name, file_name, func_name, line, log_body);
			if (trace_entry_enter_ == nullptr)
			{
				break;
			}
			//if (trace_entry_->trace_text().empty())
			//{
			//	break;
			//}			
			if (!is_track)
			{
				break;
			}
			if (!trace_entry_enter_->content.empty())
			{
				trace_stream_ << trace_entry_enter_->content;
				trace_entry_enter_->content = "";
			}
			trace_entry_exit_ = shared_ptr<TraceEntry>(new TraceEntry);
			*trace_entry_exit_ = *trace_entry_enter_;
			trace_entry_enter_->functrack = ">>";
			TracePrinterImpl::instance().OutTraceEntry(trace_entry_enter_);
		} while (false);
	}

	TraceLoaderImpl::~TraceLoaderImpl()
	{
		do
		{
			if (trace_entry_enter_ == nullptr)
			{
				break;
			}
			//if (trace_entry_->trace_text().empty())
			//{
			//	break;
			//}
			if (!trace_entry_enter_->is_track)
			{
				trace_entry_enter_->content += trace_stream_.str();
				TracePrinterImpl::instance().OutTraceEntry(trace_entry_enter_);
			}
			else if (trace_entry_enter_->is_track)
			{
				if (TracePrinterImpl::instance().trace_config().head_functime)
				{
					__int64 begin_call_time = trace_entry_exit_->runtime;
					trace_entry_exit_->runtime = kk::Utility::GetRunTime();
					trace_entry_exit_->functime = trace_entry_exit_->runtime - begin_call_time;
				}
				trace_entry_exit_->functrack = "<<";
				trace_entry_exit_->content += trace_stream_.str();
				TracePrinterImpl::instance().OutTraceEntry(trace_entry_exit_);
			}

		} while (false);
	}

	stringstream& TraceLoaderImpl::trace_stream()
	{
		return trace_stream_;
	}

	KLOGLIB_API TraceLoader* NewTraceLoader(bool is_track, int level, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...)
	{
		string log_body;
		do
		{
			if (!TracePrinterImpl::instance().IsOut(is_track, level))
			{
				break;
			}
			if (log_format == nullptr)
			{
				break;
			}
			size_t log_length = ONE_TRACE_SIZE;
			if (strlen(log_format) >= static_cast<size_t>(log_length))
			{
				log_length += strlen(log_format);
			}
			char* log_exp = new char[log_length];
			memset(log_exp, 0, sizeof(char) * log_length);
			int write_size = 0;
			va_list va;
			va_start(va, log_format);
			write_size = _vsnprintf_s(log_exp, log_length, _TRUNCATE, log_format, va);
			va_end(va);
			log_body += log_exp;
			if (write_size == -1)
			{
				log_body += "[...truncate, use Trace(xxx) replace Trace(\"%s\", xxx) by klog author]";
			}
			delete[] log_exp;
		} while (false);
		return new TraceLoaderImpl(is_track, level, label, module_name, file_name, func_name, line, log_body.c_str());
	}

	KLOGLIB_API void DeleteTraceLoader(TraceLoader* loader)
	{
		if (loader)
		{
			delete dynamic_cast<TraceLoaderImpl*>(loader);
			loader = nullptr;
		}
	}
}

