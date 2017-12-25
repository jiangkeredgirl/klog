#include "traceloader.h"

namespace kk
{
	TraceLoader::TraceLoader(IN bool is_back, IN int level, IN TraceHead* trace_head, IN TraceBody* trace_body)
	{
		is_back_ = is_back;
		trace_level_ = level;
		trace_info_.trace_head(trace_head);
		trace_info_.trace_body(trace_body);
		if (is_back_ && TracePrinterImpl::instance().trace_config().trace_back)
		{
			if (TracePrinterImpl::instance().trace_config().head_functiontime)
			{
				begin_call_time_ = kk::Utility::GetRunTime();
			}
			trace_info_.trace_head_->func_back = (">>");
			TracePrinterImpl::instance().TraceOutLog(trace_level_, trace_info_.trace_head(), trace_info_.trace_body());
		}
	}

	TraceLoader::~TraceLoader()
	{
		if (!is_back_ || (is_back_ && TracePrinterImpl::instance().trace_config().trace_back))
		{
			if (is_back_ && TracePrinterImpl::instance().trace_config().trace_back)
			{
				if (TracePrinterImpl::instance().trace_config().head_functiontime)
				{
					trace_info_.trace_head_->runtime = kk::Utility::GetRunTimeStr();
					trace_info_.trace_head_->executetime = kk::Utility::Int64ToStr(kk::Utility::GetRunTime() - begin_call_time_, 10) + (" ms");
				}
				trace_info_.trace_head_->func_back = ("<<");
			}
			trace_info_.trace_body_->body += trace_stream_.str();
			TracePrinterImpl::instance().TraceOutLog(trace_level_, trace_info_.trace_head(), trace_info_.trace_body());
		}
	}

	stringstream& TraceLoader::trace_stream()
	{
		return trace_stream_;
	}
}
