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
			trace_config.level_on_off.insert(on_off);
		}	
		errorCode = 0;
	} while (0);
	return errorCode;
}

int CJsonParser::SetTraceConfig(const kk::TraceConfig& trace_config, string& jsonContent)
{
	int errorCode = 1;
	rapidjson::Document doc;
	doc.Parse(jsonContent.c_str());
	do
	{
		errorCode = 0;
	} while (0);
	return errorCode;
}