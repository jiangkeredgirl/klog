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

		if (!doc.HasMember("trace_out"))
		{
			break;
		}
		if (!doc["trace_out"].IsBool())
		{
			break;
		}
		trace_config.trace_out = doc["trace_out"].GetBool();
		if (!doc.HasMember("track_out"))
		{
			break;
		}
		if (!doc["track_out"].IsBool())
		{
			break;
		}
		trace_config.track_out = doc["track_out"].GetBool();
		if (!doc.HasMember("trace_target_compile"))
		{
			break;
		}
		if (!doc["trace_target_compile"].IsBool())
		{
			break;
		}
		trace_config.trace_target_compile = doc["trace_target_compile"].GetBool();
		if (!doc.HasMember("trace_target_console"))
		{
			break;
		}
		if (!doc["trace_target_console"].IsBool())
		{
			break;
		}
		trace_config.trace_target_console = doc["trace_target_console"].GetBool();
		if (!doc.HasMember("trace_target_com"))
		{
			break;
		}
		if (!doc["trace_target_com"].IsBool())
		{
			break;
		}
		trace_config.trace_target_com = doc["trace_target_com"].GetBool();
		if (!doc.HasMember("trace_target_file"))
		{
			break;
		}
		if (!doc["trace_target_file"].IsBool())
		{
			break;
		}
		trace_config.trace_target_file = doc["trace_target_file"].GetBool();
		if (!doc.HasMember("trace_target_socket"))
		{
			break;
		}
		if (!doc["trace_target_socket"].IsBool())
		{
			break;
		}
		trace_config.trace_target_socket = doc["trace_target_socket"].GetBool();
		if (!doc.HasMember("async"))
		{
			break;
		}
		if (!doc["async"].IsBool())
		{
			break;
		}
		trace_config.async = doc["async"].GetBool();
		if (!doc.HasMember("sync_lock"))
		{
			break;
		}
		if (!doc["sync_lock"].IsBool())
		{
			break;
		}
		trace_config.sync_lock = doc["sync_lock"].GetBool();
		if (!doc.HasMember("head"))
		{
			break;
		}
		if (!doc["head"].IsBool())
		{
			break;
		}
		trace_config.head = doc["head"].GetBool();
		if (!doc.HasMember("head_index"))
		{
			break;
		}
		if (!doc["head_index"].IsBool())
		{
			break;
		}
		trace_config.head_index = doc["head_index"].GetBool();
		if (!doc.HasMember("head_level"))
		{
			break;
		}
		if (!doc["head_level"].IsBool())
		{
			break;
		}
		trace_config.head_level = doc["head_level"].GetBool();
		if (!doc.HasMember("head_label"))
		{
			break;
		}
		if (!doc["head_label"].IsBool())
		{
			break;
		}
		trace_config.head_label = doc["head_label"].GetBool();
		if (!doc.HasMember("head_thread_id"))
		{
			break;
		}
		if (!doc["head_thread_id"].IsBool())
		{
			break;
		}
		trace_config.head_thread_id = doc["head_thread_id"].GetBool();
		if (!doc.HasMember("head_datetime"))
		{
			break;
		}
		if (!doc["head_datetime"].IsBool())
		{
			break;
		}
		trace_config.head_datetime = doc["head_datetime"].GetBool();
		if (!doc.HasMember("head_runtime"))
		{
			break;
		}
		if (!doc["head_runtime"].IsBool())
		{
			break;
		}
		trace_config.head_runtime = doc["head_runtime"].GetBool();
		if (!doc.HasMember("head_functiontime"))
		{
			break;
		}
		if (!doc["head_functiontime"].IsBool())
		{
			break;
		}
		trace_config.head_functiontime = doc["head_functiontime"].GetBool();
		if (!doc.HasMember("head_process_name"))
		{
			break;
		}
		if (!doc["head_process_name"].IsBool())
		{
			break;
		}
		trace_config.head_process_name = doc["head_process_name"].GetBool();
		if (!doc.HasMember("head_module_name"))
		{
			break;
		}
		if (!doc["head_module_name"].IsBool())
		{
			break;
		}
		trace_config.head_module_name = doc["head_module_name"].GetBool();
		if (!doc.HasMember("head_file_name"))
		{
			break;
		}
		if (!doc["head_file_name"].IsBool())
		{
			break;
		}
		trace_config.head_file_name = doc["head_file_name"].GetBool();
		if (!doc.HasMember("head_function_name"))
		{
			break;
		}
		if (!doc["head_function_name"].IsBool())
		{
			break;
		}
		trace_config.head_function_name = doc["head_function_name"].GetBool();
		if (!doc.HasMember("head_line"))
		{
			break;
		}
		if (!doc["head_line"].IsBool())
		{
			break;
		}
		trace_config.head_line = doc["head_line"].GetBool();
		if (!doc.HasMember("head_async"))
		{
			break;
		}
		if (!doc["head_async"].IsBool())
		{
			break;
		}
		trace_config.head_async = doc["head_async"].GetBool();
		if (!doc.HasMember("head_sync_lock"))
		{
			break;
		}
		if (!doc["head_sync_lock"].IsBool())
		{
			break;
		}
		trace_config.head_sync_lock = doc["head_sync_lock"].GetBool();
		if (!doc.HasMember("valid_level"))
		{
			break;
		}
		if (!doc["valid_level"].IsInt())
		{
			break;
		}
		trace_config.valid_level = doc["valid_level"].GetInt();
		if (!doc.HasMember("trace_file_size"))
		{
			break;
		}
		if (!doc["trace_file_size"].IsInt())
		{
			break;
		}
		trace_config.trace_file_size = doc["trace_file_size"].GetInt();
		if (!doc.HasMember("head_label_text"))
		{
			break;
		}
		if (!doc["head_label_text"].IsString())
		{
			break;
		}
		trace_config.head_label_text = doc["head_label_text"].GetString();
		if (!doc.HasMember("trace_file_dir"))
		{
			break;
		}
		if (!doc["trace_file_dir"].IsString())
		{
			break;
		}
		trace_config.trace_file_dir = doc["trace_file_dir"].GetString();
		if (!doc.HasMember("trace_com_name"))
		{
			break;
		}
		if (!doc["trace_com_name"].IsString())
		{
			break;
		}
		trace_config.trace_com_name = doc["trace_com_name"].GetString();
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
		if (doc.HasMember("trace_out") && doc["trace_out"].IsBool())
		{
			doc["trace_out"].SetBool(trace_config.trace_out);
		}
		else
		{
			doc.AddMember("trace_out", trace_config.trace_out, allocator);
		}
		if (doc.HasMember("track_out") && doc["track_out"].IsBool())
		{
			doc["track_out"].SetBool(trace_config.track_out);
		}
		else
		{
			doc.AddMember("track_out", trace_config.track_out, allocator);
		}
		if (doc.HasMember("trace_target_compile") && doc["trace_target_compile"].IsBool())
		{
			doc["trace_target_compile"].SetBool(trace_config.trace_target_compile);
		}
		else
		{
			doc.AddMember("trace_target_compile", trace_config.trace_target_compile, allocator);
		}
		if (doc.HasMember("trace_target_console") && doc["trace_target_console"].IsBool())
		{
			doc["trace_target_console"].SetBool(trace_config.trace_target_console);
		}
		else
		{
			doc.AddMember("trace_target_console", trace_config.trace_target_console, allocator);
		}
		if (doc.HasMember("trace_target_file") && doc["trace_target_file"].IsBool())
		{
			doc["trace_target_file"].SetBool(trace_config.trace_target_file);
		}
		else
		{
			doc.AddMember("trace_target_file", trace_config.trace_target_file, allocator);
		}
		if (doc.HasMember("trace_target_socket") && doc["trace_target_socket"].IsBool())
		{
			doc["trace_target_socket"].SetBool(trace_config.trace_target_socket);
		}
		else
		{
			doc.AddMember("trace_target_socket", trace_config.trace_target_socket, allocator);
		}
		if (doc.HasMember("trace_target_com") && doc["trace_target_com"].IsBool())
		{
			doc["trace_target_com"].SetBool(trace_config.trace_target_com);
		}
		else
		{
			doc.AddMember("trace_target_com", trace_config.trace_target_com, allocator);
		}
		if (doc.HasMember("async") && doc["async"].IsBool())
		{
			doc["async"].SetBool(trace_config.async);
		}
		else
		{
			doc.AddMember("async", trace_config.async, allocator);
		}
		if (doc.HasMember("sync_lock") && doc["sync_lock"].IsBool())
		{
			doc["sync_lock"].SetBool(trace_config.sync_lock);
		}
		else
		{
			doc.AddMember("sync_lock", trace_config.sync_lock, allocator);
		}
		if (doc.HasMember("head") && doc["head"].IsBool())
		{
			doc["head"].SetBool(trace_config.head);
		}
		else
		{
			doc.AddMember("head", trace_config.head, allocator);
		}
		if (doc.HasMember("head_index") && doc["head_index"].IsBool())
		{
			doc["head_index"].SetBool(trace_config.head_index);
		}
		else
		{
			doc.AddMember("head_index", trace_config.head_index, allocator);
		}
		if (doc.HasMember("head_level") && doc["head_level"].IsBool())
		{
			doc["head_level"].SetBool(trace_config.head_level);
		}
		else
		{
			doc.AddMember("head_level", trace_config.head_level, allocator);
		}
		if (doc.HasMember("head_label") && doc["head_label"].IsBool())
		{
			doc["head_label"].SetBool(trace_config.head_label);
		}
		else
		{
			doc.AddMember("head_label", trace_config.head_label, allocator);
		}
		if (doc.HasMember("head_thread_id") && doc["head_thread_id"].IsBool())
		{
			doc["head_thread_id"].SetBool(trace_config.head_thread_id);
		}
		else
		{
			doc.AddMember("head_thread_id", trace_config.head_thread_id, allocator);
		}
		if (doc.HasMember("head_datetime") && doc["head_datetime"].IsBool())
		{
			doc["head_datetime"].SetBool(trace_config.head_datetime);
		}
		else
		{
			doc.AddMember("head_datetime", trace_config.head_datetime, allocator);
		}
		if (doc.HasMember("head_runtime") && doc["head_runtime"].IsBool())
		{
			doc["head_runtime"].SetBool(trace_config.head_runtime);
		}
		else
		{
			doc.AddMember("head_runtime", trace_config.head_runtime, allocator);
		}
		if (doc.HasMember("head_functiontime") && doc["head_functiontime"].IsBool())
		{
			doc["head_functiontime"].SetBool(trace_config.head_functiontime);
		}
		else
		{
			doc.AddMember("head_functiontime", trace_config.head_functiontime, allocator);
		}
		if (doc.HasMember("head_process_name") && doc["head_process_name"].IsBool())
		{
			doc["head_process_name"].SetBool(trace_config.head_process_name);
		}
		else
		{
			doc.AddMember("head_process_name", trace_config.head_process_name, allocator);
		}
		if (doc.HasMember("head_module_name") && doc["head_module_name"].IsBool())
		{
			doc["head_module_name"].SetBool(trace_config.head_module_name);
		}
		else
		{
			doc.AddMember("head_module_name", trace_config.head_module_name, allocator);
		}
		if (doc.HasMember("head_file_name") && doc["head_file_name"].IsBool())
		{
			doc["head_file_name"].SetBool(trace_config.head_file_name);
		}
		else
		{
			doc.AddMember("head_file_name", trace_config.head_file_name, allocator);
		}
		if (doc.HasMember("head_function_name") && doc["head_function_name"].IsBool())
		{
			doc["head_function_name"].SetBool(trace_config.head_function_name);
		}
		else
		{
			doc.AddMember("head_function_name", trace_config.head_function_name, allocator);
		}
		if (doc.HasMember("head_line") && doc["head_line"].IsBool())
		{
			doc["head_line"].SetBool(trace_config.head_line);
		}
		else
		{
			doc.AddMember("head_line", trace_config.head_line, allocator);
		}
		if (doc.HasMember("head_async") && doc["head_async"].IsBool())
		{
			doc["head_async"].SetBool(trace_config.head_async);
		}
		else
		{
			doc.AddMember("head_async", trace_config.head_async, allocator);
		}
		if (doc.HasMember("head_sync_lock") && doc["head_sync_lock"].IsBool())
		{
			doc["head_sync_lock"].SetBool(trace_config.head_sync_lock);
		}
		else
		{
			doc.AddMember("head_sync_lock", trace_config.head_sync_lock, allocator);
		}
		if (doc.HasMember("valid_level") && doc["valid_level"].IsInt())
		{
			doc["valid_level"].SetInt(trace_config.valid_level);
		}
		else
		{
			doc.AddMember("valid_level", trace_config.valid_level, allocator);
		}
		if (doc.HasMember("trace_file_size") && doc["trace_file_size"].IsInt())
		{
			doc["trace_file_size"].SetInt(trace_config.trace_file_size);
		}
		else
		{
			doc.AddMember("trace_file_size", trace_config.trace_file_size, allocator);
		}
		if (doc.HasMember("head_label_text") && doc["head_label_text"].IsString())
		{
			doc["head_label_text"].SetString(trace_config.head_label_text.c_str(), (rapidjson::SizeType)trace_config.head_label_text.size(), allocator);
		}
		else
		{
			doc.AddMember("head_label_text", rapidjson::StringRef(trace_config.head_label_text.c_str(), trace_config.head_label_text.size()), allocator);
		}
		if (doc.HasMember("trace_file_dir") && doc["trace_file_dir"].IsString())
		{
			doc["trace_file_dir"].SetString(trace_config.trace_file_dir.c_str(), (rapidjson::SizeType)trace_config.trace_file_dir.size(), allocator);
		}
		else
		{
			doc.AddMember("trace_file_dir", rapidjson::StringRef(trace_config.trace_file_dir.c_str(), trace_config.trace_file_dir.size()), allocator);
		}
		if (doc.HasMember("trace_com_name") && doc["trace_com_name"].IsString())
		{
			doc["trace_com_name"].SetString(trace_config.trace_com_name.c_str(), (rapidjson::SizeType)trace_config.trace_com_name.size(), allocator);
		}
		else
		{
			doc.AddMember("trace_com_name", rapidjson::StringRef(trace_config.trace_com_name.c_str(), trace_config.trace_com_name.size()), allocator);
		}

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