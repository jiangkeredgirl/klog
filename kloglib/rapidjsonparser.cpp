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
		if (!doc.HasMember("trace_target_putty"))
		{
			break;
		}
		if (!doc["trace_target_putty"].IsBool())
		{
			break;
		}
		trace_config.trace_target_putty = doc["trace_target_putty"].GetBool();
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
		if (!doc.HasMember("trace_module"))
		{
			break;
		}
		if (!doc["trace_module"].IsBool())
		{
			break;
		}
		trace_config.trace_module = doc["trace_module"].GetBool();
		if (!doc.HasMember("trace_process"))
		{
			break;
		}
		if (!doc["trace_process"].IsBool())
		{
			break;
		}
		trace_config.trace_process = doc["trace_process"].GetBool();
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
		if (!doc.HasMember("trace_file_name"))
		{
			break;
		}
		if (!doc["trace_file_name"].IsString())
		{
			break;
		}
		trace_config.trace_file_name = doc["trace_file_name"].GetString();
		if (!doc.HasMember("valid_level"))
		{
			break;
		}
		if (!doc["valid_level"].IsInt())
		{
			break;
		}
		trace_config.valid_level = doc["valid_level"].GetInt();
		if (!doc.HasMember("TRACE_FILE_SIZE"))
		{
			break;
		}
		if (!doc["TARGET_FILE_size"].IsInt())
		{
			break;
		}
		trace_config.TARGET_FILE_size = doc["TARGET_FILE_size"].GetInt();

		if (!doc.HasMember("levels_info"))
		{
			break;
		}
		if (!doc["levels_info"].IsArray())
		{
			break;
		}
		for (rapidjson::SizeType i = 0; i < doc["levels_info"].Size(); ++i)
		{
			if (!doc["levels_info"][i].IsObject())
			{
				break;
			}
			pair<int/*level*/, kk::LevelInfo> levelinfo;
			if (!doc["levels_info"][i].HasMember("key"))
			{
				break;
			}
			if (!doc["levels_info"][i]["key"].IsInt())
			{
				break;
			}
			levelinfo.first = doc["levels_info"][i]["key"].GetInt();
			if (!doc["levels_info"][i].HasMember("value"))
			{
				break;
			}
			if (!doc["levels_info"][i]["value"].IsObject())
			{
				break;
			}		
			if (!doc["levels_info"][i]["value"].HasMember("is_out"))
			{
				break;
			}
			if (!doc["levels_info"][i]["value"]["is_out"].IsBool())
			{
				break;
			}
			levelinfo.second.is_out = doc["levels_info"][i]["value"]["is_out"].GetBool();
			if (!doc["levels_info"][i]["value"].HasMember("color"))
			{
				break;
			}
			if (!doc["levels_info"][i]["value"]["color"].IsInt())
			{
				break;
			}
			levelinfo.second.color = doc["levels_info"][i]["value"]["color"].GetInt();
			trace_config.levels_info.insert(levelinfo);
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