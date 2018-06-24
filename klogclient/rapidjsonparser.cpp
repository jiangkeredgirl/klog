#include "rapidjsonparser.h"
#include "kutility.h"
#include "rapidjson/document.h"  
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "logfile.h"


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
		string strlevel;
		string  datetime;
		string  runtime;
		string  function_time;
		DecodeValue(doc, "index", trace_entry.index);
		DecodeValue(doc, "func_track", trace_entry.func_track);
		DecodeValue(doc, "func_time", function_time);
		if (function_time.size() > 2)
		{
			function_time.erase(function_time.end() - 2, function_time.end());
			trace_entry.func_time = stoi(function_time);
		}
		DecodeValue(doc, "level", strlevel);
		trace_entry.level = LogFile::instance().StrToLevel(strlevel);
		DecodeValue(doc, "label", trace_entry.label);
		DecodeValue(doc, "thread_id", trace_entry.thread_id);		
		DecodeValue(doc, "process_name", trace_entry.process_name);
		DecodeValue(doc, "module_name", trace_entry.module_name);
		DecodeValue(doc, "file_name", trace_entry.file_name);
		DecodeValue(doc, "func_name", trace_entry.func_name);
		DecodeValue(doc, "line", trace_entry.line);
		DecodeValue(doc, "datetime", datetime);
		trace_entry.datetime = kk::Utility::GetDateTime(datetime);
		DecodeValue(doc, "runtime", runtime);
		trace_entry.runtime = kk::Utility::GetRunTime(runtime);
		DecodeValue(doc, "async", trace_entry.async);
		DecodeValue(doc, "sync_lock", trace_entry.sync_lock);
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
		if (!object[key.c_str()].IsInt())
		{
			break;
		}
		value = object[key.c_str()].GetInt();
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

int CJsonParser::EncodeValue(rapidjson::Value& object, rapidjson::Document::AllocatorType& allocator, const string& key, int value)
{
	if (object.HasMember(key.c_str()) && object[key.c_str()].IsInt())
	{
		object[key.c_str()].SetInt(value);
	}
	else
	{
		object.AddMember(rapidjson::Value(key.c_str(), allocator), value, allocator);
	}
	return 0;
}

int CJsonParser::EncodeValue(rapidjson::Value& object, rapidjson::Document::AllocatorType& allocator, const string& key, __int64 value)
{
	if (object.HasMember(key.c_str()) && object[key.c_str()].IsInt64())
	{
		object[key.c_str()].SetInt64(value);
	}
	else
	{
		object.AddMember(rapidjson::Value(key.c_str(), allocator), value, allocator);
	}
	return 0;
}

int CJsonParser::EncodeValue(rapidjson::Value& object, rapidjson::Document::AllocatorType& allocator, const string& key, bool value)
{
	if (object.HasMember(key.c_str()) && object[key.c_str()].IsBool())
	{
		object[key.c_str()].SetBool(value);
	}
	else
	{
		object.AddMember(rapidjson::Value(key.c_str(), allocator), value, allocator);
	}
	return 0;
}

int CJsonParser::EncodeValue(rapidjson::Value& object, rapidjson::Document::AllocatorType& allocator, const string& key, const string& value)
{
	if (object.HasMember(key.c_str()) && object[key.c_str()].IsString())
	{
		object[key.c_str()].SetString(rapidjson::StringRef(value.c_str()));
	}
	else
	{
		object.AddMember(rapidjson::Value(key.c_str(), allocator), rapidjson::StringRef(value.c_str()), allocator);
	}
	return 0;
}