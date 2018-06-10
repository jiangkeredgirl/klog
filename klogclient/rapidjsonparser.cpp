#include "rapidjsonparser.h"
#include "kutility.h"
#include "rapidjson/document.h"  
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"


CJsonParser& CJsonParser::instance()
{
	static CJsonParser _instance;
	return _instance;
}

bool CJsonParser::IsJsonObject(const string& jsonContent)
{
	rapidjson::Document doc;
	doc.Parse(jsonContent.c_str());
	return doc.IsObject();
}

int CJsonParser::DecodeTraceEntry(const string& jsonContent, TraceEntry& trace_entry)
{
	int errorCode = 1;
	rapidjson::Document doc;
	doc.Parse(jsonContent.c_str());
	do
	{
		if (!doc.IsObject())
		{
			break;
		}
		string  datetime;
		string  runtime;
		string  function_time;
		DecodeValue(doc, "index", trace_entry.index);
		DecodeValue(doc, "level", trace_entry.level);
		DecodeValue(doc, "macro_level", trace_entry.macro_level);
		DecodeValue(doc, "label", trace_entry.label);
		DecodeValue(doc, "thread_id", trace_entry.thread_id);
		DecodeValue(doc, "datetime", datetime);
		trace_entry.datetime = kk::Utility::GetDateTime(datetime);
		DecodeValue(doc, "runtime", runtime);
		trace_entry.runtime = kk::Utility::GetRunTime(runtime);
		DecodeValue(doc, "function_time", function_time);
		trace_entry.function_time = stoi(function_time);
		DecodeValue(doc, "process_name", trace_entry.process_name);
		DecodeValue(doc, "module_name", trace_entry.module_name);
		DecodeValue(doc, "file_name", trace_entry.file_name);
		DecodeValue(doc, "function_name", trace_entry.function_name);
		DecodeValue(doc, "line", trace_entry.line);
		DecodeValue(doc, "func_enter", trace_entry.func_enter);
		DecodeValue(doc, "func_exit", trace_entry.func_exit);
		DecodeValue(doc, "async", trace_entry.async);
		DecodeValue(doc, "sync_lock", trace_entry.sync_lock);
		DecodeValue(doc, "is_track", trace_entry.is_track);
		DecodeValue(doc, "content", trace_entry.content);
		errorCode = 0;
	} while (0);
	return errorCode;
}

int CJsonParser::EncodeTraceEntry(const TraceEntry& trace_entry, string& jsonContent)
{
	int errorCode = 1;
	return errorCode;
}

int CJsonParser::DecodeValue(rapidjson::Value& object, const string& key, int& value)
{
	int error_code = 1;
	do
	{
		if (!object.HasMember(key.c_str()))
		{
			break;
		}
		if (!object[key.c_str()].IsInt64())
		{
			break;
		}
		value = object[key.c_str()].GetInt64();
		error_code = 0;
	} while (0);
	return error_code;
}

int CJsonParser::DecodeValue(rapidjson::Value& object, const string& key, __int64& value)
{
	int error_code = 1;
	do
	{
		if (!object.HasMember(key.c_str()))
		{
			break;
		}
		if (!object[key.c_str()].IsInt64())
		{
			break;
		}
		value = object[key.c_str()].GetInt64();
		error_code = 0;
	} while (0);
	return error_code;
}

int CJsonParser::DecodeValue(rapidjson::Value& object, const string& key, bool& value)
{
	int error_code = 1;
	do
	{
		if (!object.HasMember(key.c_str()))
		{
			break;
		}
		if (!object[key.c_str()].IsBool())
		{
			break;
		}
		value = object[key.c_str()].GetBool();
		error_code = 0;
	} while (0);
	return error_code;
}

int CJsonParser::DecodeValue(rapidjson::Value& object, const string& key, string& value)
{
	int error_code = 1;
	do
	{
		if (!object.HasMember(key.c_str()))
		{
			break;
		}
		if (!object[key.c_str()].IsString())
		{
			break;
		}
		value = object[key.c_str()].GetString();
		error_code = 0;
	} while (0);
	return error_code;
}