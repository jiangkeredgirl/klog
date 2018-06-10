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


int CJsonParser::GetTraceConfig(const string& jsonContent, kk::TraceConfig& trace_config)
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
		DecodeValue(doc, "trace_out", trace_config.trace_out);
		DecodeValue(doc, "track_out", trace_config.track_out);
		DecodeValue(doc, "trace_target_compile", trace_config.trace_target_compile);
		DecodeValue(doc, "trace_target_console", trace_config.trace_target_console);
		DecodeValue(doc, "trace_target_com", trace_config.trace_target_com);
		DecodeValue(doc, "trace_target_file", trace_config.trace_target_file);
		DecodeValue(doc, "trace_target_socket", trace_config.trace_target_socket);
		DecodeValue(doc, "trace_target_level", trace_config.trace_target_level);
		DecodeValue(doc, "trace_target_module", trace_config.trace_target_module);
		DecodeValue(doc, "trace_target_date", trace_config.trace_target_date);
		DecodeValue(doc, "async", trace_config.async);
		DecodeValue(doc, "sync_lock", trace_config.sync_lock);
		DecodeValue(doc, "head", trace_config.head);
		DecodeValue(doc, "head_index", trace_config.head_index);
		DecodeValue(doc, "head_level", trace_config.head_level);
		DecodeValue(doc, "head_label", trace_config.head_label);
		DecodeValue(doc, "head_thread_id", trace_config.head_thread_id);
		DecodeValue(doc, "head_datetime", trace_config.head_datetime);
		DecodeValue(doc, "head_runtime", trace_config.head_runtime);
		DecodeValue(doc, "head_function_time", trace_config.head_function_time);
		DecodeValue(doc, "head_process_name", trace_config.head_process_name);
		DecodeValue(doc, "head_module_name", trace_config.head_module_name);
		DecodeValue(doc, "head_file_name", trace_config.head_file_name);
		DecodeValue(doc, "head_function_name", trace_config.head_function_name);
		DecodeValue(doc, "head_line", trace_config.head_line);
		DecodeValue(doc, "head_async", trace_config.head_async);
		DecodeValue(doc, "head_sync_lock", trace_config.head_sync_lock);
		DecodeValue(doc, "valid_level", trace_config.valid_level);
		DecodeValue(doc, "trace_file_size", trace_config.trace_file_size);
		DecodeValue(doc, "head_label_text", trace_config.head_label_text);
		DecodeValue(doc, "trace_file_dir", trace_config.trace_file_dir);
		DecodeValue(doc, "trace_com_name", trace_config.trace_com_name);

		if (!doc.HasMember("level_on_off"))
		{
			break;
		}
		if (!doc["level_on_off"].IsArray())
		{
			break;
		}
		for (rapidjson::SizeType i = 0; i < doc["level_on_off"].Size(); ++i)
		{
			if (!doc["level_on_off"][i].IsObject())
			{
				break;
			}
			pair<int/*level*/, bool> on_off;
			if (!doc["level_on_off"][i].HasMember("key"))
			{
				break;
			}
			if (!doc["level_on_off"][i]["key"].IsInt())
			{
				break;
			}
			on_off.first = doc["level_on_off"][i]["key"].GetInt();
			if (!doc["level_on_off"][i].HasMember("value"))
			{
				break;
			}
			if (!doc["level_on_off"][i]["value"].IsBool())
			{
				break;
			}
			on_off.second = doc["level_on_off"][i]["value"].GetBool();
			trace_config.level_on_off[on_off.first] = on_off.second;
		}
		errorCode = 0;
	} while (0);
	return errorCode;
}

int CJsonParser::SetTraceConfig(const kk::TraceConfig& trace_config, string& jsonContent)
{
	int errorCode = 1;
	rapidjson::Document doc;
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	doc.Parse(jsonContent.c_str());
	if (!doc.IsObject())
	{
		doc.SetObject();
	}
	do
	{
		EncodeValue(doc, allocator, "trace_out", trace_config.trace_out);
		EncodeValue(doc, allocator, "track_out", trace_config.track_out);
		EncodeValue(doc, allocator, "trace_target_compile", trace_config.trace_target_compile);
		EncodeValue(doc, allocator, "trace_target_console", trace_config.trace_target_console);
		EncodeValue(doc, allocator, "trace_target_com", trace_config.trace_target_com);
		EncodeValue(doc, allocator, "trace_target_file", trace_config.trace_target_file);
		EncodeValue(doc, allocator, "trace_target_socket", trace_config.trace_target_socket);
		EncodeValue(doc, allocator, "trace_target_level", trace_config.trace_target_level);
		EncodeValue(doc, allocator, "trace_target_module", trace_config.trace_target_module);
		EncodeValue(doc, allocator, "trace_target_date", trace_config.trace_target_date);
		EncodeValue(doc, allocator, "async", trace_config.async);
		EncodeValue(doc, allocator, "sync_lock", trace_config.sync_lock);
		EncodeValue(doc, allocator, "head", trace_config.head);
		EncodeValue(doc, allocator, "head_index", trace_config.head_index);
		EncodeValue(doc, allocator, "head_level", trace_config.head_level);
		EncodeValue(doc, allocator, "head_label", trace_config.head_label);
		EncodeValue(doc, allocator, "head_thread_id", trace_config.head_thread_id);
		EncodeValue(doc, allocator, "head_datetime", trace_config.head_datetime);
		EncodeValue(doc, allocator, "head_runtime", trace_config.head_runtime);
		EncodeValue(doc, allocator, "head_function_time", trace_config.head_function_time);
		EncodeValue(doc, allocator, "head_process_name", trace_config.head_process_name);
		EncodeValue(doc, allocator, "head_module_name", trace_config.head_module_name);
		EncodeValue(doc, allocator, "head_file_name", trace_config.head_file_name);
		EncodeValue(doc, allocator, "head_function_name", trace_config.head_function_name);
		EncodeValue(doc, allocator, "head_line", trace_config.head_line);
		EncodeValue(doc, allocator, "head_async", trace_config.head_async);
		EncodeValue(doc, allocator, "head_sync_lock", trace_config.head_sync_lock);
		EncodeValue(doc, allocator, "valid_level", trace_config.valid_level);
		EncodeValue(doc, allocator, "trace_file_size", trace_config.trace_file_size);
		EncodeValue(doc, allocator, "head_label_text", trace_config.head_label_text);
		EncodeValue(doc, allocator, "trace_file_dir", trace_config.trace_file_dir);
		EncodeValue(doc, allocator, "trace_com_name", trace_config.trace_com_name);

		if (doc.HasMember("level_on_off") && doc["level_on_off"].IsArray())
		{
			doc["level_on_off"].SetArray();
		}
		else
		{
			rapidjson::Value array(rapidjson::kArrayType);
			doc.AddMember("level_on_off", array, allocator);
		}
		for (auto item : trace_config.level_on_off)
		{
			rapidjson::Value item_object(rapidjson::kObjectType);
			item_object.AddMember("key", item.first, allocator);
			item_object.AddMember("value", item.second, allocator);			
			doc["level_on_off"].PushBack(item_object, allocator);			
		}
		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer); //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json
		doc.Accept(writer);
		jsonContent = buffer.GetString();
		errorCode = 0;
	} while (0);
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
		object.AddMember(rapidjson::StringRef(key.c_str()), value, allocator);
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
		object.AddMember(rapidjson::StringRef(key.c_str()), value, allocator);
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
		object.AddMember(rapidjson::StringRef(key.c_str()), value, allocator);
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
		object.AddMember(rapidjson::StringRef(key.c_str()), rapidjson::StringRef(value.c_str()), allocator);
	}
	return 0;
}