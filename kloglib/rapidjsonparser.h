#pragma once

#include <string>
#include "config.h"
#include "rapidjson/document.h"
#include "TracePrinterimpl.h"
using namespace std;

namespace kk
{

	class CJsonParser
	{
	public:
		static CJsonParser& instance();
	public:
		int GetTraceConfig(const string& jsonContent, kk::TraceConfig& trace_config);
		int SetTraceConfig(const kk::TraceConfig& trace_config, string& jsonContent);
		int DecodeTraceEntry(const string& jsonContent, TraceEntry& trace_entry);
		int EncodeTraceEntry(const TraceEntry& trace_entry, string& jsonContent);

	private:
		int DecodeValue(rapidjson::Value& object, const string& key, int& value);
		int DecodeValue(rapidjson::Value& object, const string& key, __int64& value);
		int DecodeValue(rapidjson::Value& object, const string& key, bool& value);
		int DecodeValue(rapidjson::Value& object, const string& key, string& value);
		int EncodeValue(rapidjson::Value& object, rapidjson::Document::AllocatorType& allocator, const string& key, int value);
		int EncodeValue(rapidjson::Value& object, rapidjson::Document::AllocatorType& allocator, const string& key, __int64 value);
		int EncodeValue(rapidjson::Value& object, rapidjson::Document::AllocatorType& allocator, const string& key, bool value);
		int EncodeValue(rapidjson::Value& object, rapidjson::Document::AllocatorType& allocator, const string& key, const string& value);
	};

}

