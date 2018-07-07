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
		string  functime;
		DecodeValue(doc, "index", trace_entry.index);
		DecodeValue(doc, "functrack", trace_entry.functrack);
		DecodeValue(doc, "functime", functime);
		if (functime.size() > 2)
		{
			functime.erase(functime.end() - 2, functime.end());
			trace_entry.functime = stoi(functime);
		}
		DecodeValue(doc, "level", strlevel);
		trace_entry.level = LogFile::instance().StrToLevel(strlevel);
		DecodeValue(doc, "label", trace_entry.label);
		DecodeValue(doc, "threadid", trace_entry.threadid);		
		DecodeValue(doc, "processname", trace_entry.processname);
		DecodeValue(doc, "modulename", trace_entry.modulename);
		DecodeValue(doc, "filename", trace_entry.filename);
		DecodeValue(doc, "funcname", trace_entry.funcname);
		DecodeValue(doc, "line", trace_entry.line);
		DecodeValue(doc, "datetime", datetime);
		trace_entry.datetime = kk::Utility::GetDateTime(datetime);
		DecodeValue(doc, "runtime", runtime);
		trace_entry.runtime = kk::Utility::GetRunTime(runtime);
		DecodeValue(doc, "async", trace_entry.async);
		DecodeValue(doc, "synclock", trace_entry.synclock);
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