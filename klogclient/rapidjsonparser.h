#pragma once

#include <string>
#include "logfile.h"
#include "rapidjson/document.h"
using namespace std;

//namespace rapidjson 
//{
//	class Value;
//};

class CJsonParser
{
public:
	static CJsonParser& instance();
public:
	bool IsJsonObject(const string& jsonContent);
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

