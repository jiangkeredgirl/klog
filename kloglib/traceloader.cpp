#include "traceloader.h"
#include "TracePrinterimpl.h"

namespace kk
{
	TraceLoader::TraceLoader(bool is_track, int level, const string& strlevel, const string& label, const string& module_name, const string& file_name, const string& func_name, int line, const char* log_format, ...)
	{		
		do
		{
			if (!TracePrinterImpl::instance().IsOut(is_track, level))
			{
				break;
			}
			trace_entry_ = TracePrinterImpl::instance().TraceFormatEntry(is_track, level, strlevel, label, module_name, file_name, func_name, line, log_format);
			if (trace_entry_ == nullptr)
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
			if (TracePrinterImpl::instance().trace_config().head_functiontime)
			{
				begin_call_time_ = kk::Utility::GetRunTime();
			}
			trace_entry_->trace_head_->func_track = (">>");
			TracePrinterImpl::instance().OutTraceEntry(trace_entry_);
		} while (false);
	}

	TraceLoader::~TraceLoader()
	{
		do
		{
			if (trace_entry_ == nullptr)
			{
				break;
			}
			//if (trace_entry_->trace_text().empty())
			//{
			//	break;
			//}	
			if (trace_entry_->trace_head()->is_track)
			{
				if (TracePrinterImpl::instance().trace_config().head_functiontime)
				{
					trace_entry_->trace_head_->runtime = kk::Utility::GetRunTimeStr();
					trace_entry_->trace_head_->executetime = kk::Utility::Int64ToStr(kk::Utility::GetRunTime() - begin_call_time_, 10) + (" ms");
				}
				trace_entry_->trace_head_->func_track = ("<<");
			}
			trace_entry_->trace_body_->body += trace_stream_.str();
			TracePrinterImpl::instance().OutTraceEntry(trace_entry_);
			delete trace_entry_;
		} while (false);
	}

	stringstream& TraceLoader::trace_stream()
	{
		return trace_stream_;
	}
}
