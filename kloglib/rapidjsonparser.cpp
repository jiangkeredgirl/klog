#include "rapidjsonparser.h"
#include "kutility.h"
#include "rapidjson/document.h"  
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

namespace kk
{

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
			DecodeValue(doc, "output_compile", trace_config.output_compile);
			DecodeValue(doc, "output_console", trace_config.output_console);
			DecodeValue(doc, "output_com", trace_config.output_com);
			DecodeValue(doc, "output_file", trace_config.output_file);
			DecodeValue(doc, "output_socket", trace_config.output_socket);
			DecodeValue(doc, "file_level", trace_config.file_level);
			DecodeValue(doc, "file_module", trace_config.file_module);
			DecodeValue(doc, "file_date", trace_config.file_date);
			DecodeValue(doc, "async", trace_config.async);
			DecodeValue(doc, "head", trace_config.head);
			DecodeValue(doc, "head_index", trace_config.head_index);
			DecodeValue(doc, "head_functrack", trace_config.head_functrack);
			DecodeValue(doc, "head_functime", trace_config.head_functime);
			DecodeValue(doc, "head_level", trace_config.head_level);
			DecodeValue(doc, "head_label", trace_config.head_label);
			DecodeValue(doc, "head_threadid", trace_config.head_threadid);
			DecodeValue(doc, "head_processname", trace_config.head_processname);
			DecodeValue(doc, "head_modulename", trace_config.head_modulename);
			DecodeValue(doc, "head_filename", trace_config.head_filename);
			DecodeValue(doc, "head_funcname", trace_config.head_funcname);
			DecodeValue(doc, "head_line", trace_config.head_line);
			DecodeValue(doc, "head_datetime", trace_config.head_datetime);
			DecodeValue(doc, "head_runtime", trace_config.head_runtime);
			DecodeValue(doc, "head_async", trace_config.head_async);
			DecodeValue(doc, "valid_level", trace_config.valid_level);
			DecodeValue(doc, "valid_console_level", trace_config.valid_console_level);
			DecodeValue(doc, "console_format", trace_config.console_format);
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
			EncodeValue(doc, allocator, "output_compile", trace_config.output_compile);
			EncodeValue(doc, allocator, "output_console", trace_config.output_console);
			EncodeValue(doc, allocator, "output_com", trace_config.output_com);
			EncodeValue(doc, allocator, "output_file", trace_config.output_file);
			EncodeValue(doc, allocator, "output_socket", trace_config.output_socket);
			EncodeValue(doc, allocator, "file_level", trace_config.file_level);
			EncodeValue(doc, allocator, "file_module", trace_config.file_module);
			EncodeValue(doc, allocator, "file_date", trace_config.file_date);
			EncodeValue(doc, allocator, "async", trace_config.async);
			EncodeValue(doc, allocator, "head", trace_config.head);
			EncodeValue(doc, allocator, "head_index", trace_config.head_index);
			EncodeValue(doc, allocator, "head_functrack", trace_config.head_functrack);
			EncodeValue(doc, allocator, "head_functime", trace_config.head_functime);
			EncodeValue(doc, allocator, "head_level", trace_config.head_level);
			EncodeValue(doc, allocator, "head_label", trace_config.head_label);
			EncodeValue(doc, allocator, "head_threadid", trace_config.head_threadid);
			EncodeValue(doc, allocator, "head_processname", trace_config.head_processname);
			EncodeValue(doc, allocator, "head_modulename", trace_config.head_modulename);
			EncodeValue(doc, allocator, "head_filename", trace_config.head_filename);
			EncodeValue(doc, allocator, "head_funcname", trace_config.head_funcname);
			EncodeValue(doc, allocator, "head_line", trace_config.head_line);
			EncodeValue(doc, allocator, "head_datetime", trace_config.head_datetime);
			EncodeValue(doc, allocator, "head_runtime", trace_config.head_runtime);
			EncodeValue(doc, allocator, "head_async", trace_config.head_async);
			EncodeValue(doc, allocator, "valid_level", trace_config.valid_level);
			EncodeValue(doc, allocator, "valid_console_level", trace_config.valid_console_level);
			EncodeValue(doc, allocator, "console_format", trace_config.console_format);
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
			if (!trace_entry.functrack.empty())
			{
				trace_entry.is_track = true;
			}
			DecodeValue(doc, "functime", functime);
			if (functime.size() > 2)
			{
				functime.erase(functime.end() - 2, functime.end());
				trace_entry.functime = stoi(functime);
			}
			DecodeValue(doc, "level", strlevel);
			trace_entry.level = kk::TracePrinterImpl::instance().StrToLevel(strlevel);
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
		rapidjson::Document doc;
		rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
		doc.Parse(jsonContent.c_str());
		if (!doc.IsObject())
		{
			doc.SetObject();
		}
		do
		{
			if (trace_entry.is_track && !TracePrinterImpl::instance().trace_config().track_out)
			{
				break;
			}
			if (trace_entry.is_track || TracePrinterImpl::instance().trace_config().head)
			{
				if (TracePrinterImpl::instance().trace_config().head_index)
				{
					EncodeValue(doc, allocator, "index", trace_entry.index);
				}
				if (!trace_entry.functrack.empty() && TracePrinterImpl::instance().trace_config().head_functrack)
				{
					EncodeValue(doc, allocator, "functrack", trace_entry.functrack);
				}
				if (trace_entry.is_track && TracePrinterImpl::instance().trace_config().head_functime)
				{
					EncodeValue(doc, allocator, "functime", to_string(trace_entry.functime) + "ms");
				}
				if (TracePrinterImpl::instance().trace_config().head_level)
				{
					EncodeValue(doc, allocator, "level", TracePrinterImpl::instance().LevelToStr(trace_entry.level));
				}
				if (TracePrinterImpl::instance().trace_config().head_label)
				{
					EncodeValue(doc, allocator, "label", trace_entry.label);
				}
				if (TracePrinterImpl::instance().trace_config().head_threadid)
				{
					EncodeValue(doc, allocator, "threadid", trace_entry.threadid);
				}
				if (TracePrinterImpl::instance().trace_config().head_processname)
				{
					EncodeValue(doc, allocator, "processname", trace_entry.processname);
				}
				if (TracePrinterImpl::instance().trace_config().head_modulename)
				{
					EncodeValue(doc, allocator, "modulename", trace_entry.modulename);
				}
				if (TracePrinterImpl::instance().trace_config().head_filename)
				{
					EncodeValue(doc, allocator, "filename", trace_entry.filename);
				}
				if (TracePrinterImpl::instance().trace_config().head_funcname)
				{
					EncodeValue(doc, allocator, "funcname", trace_entry.funcname);
				}
				if (TracePrinterImpl::instance().trace_config().head_line)
				{
					EncodeValue(doc, allocator, "line", trace_entry.line);
				}
				if (TracePrinterImpl::instance().trace_config().head_datetime)
				{
					EncodeValue(doc, allocator, "datetime", kk::Utility::GetDateTimeStr(trace_entry.datetime));
				}
				if (TracePrinterImpl::instance().trace_config().head_runtime)
				{
					EncodeValue(doc, allocator, "runtime", kk::Utility::GetRunTimeStr(trace_entry.runtime));
				}
				if (TracePrinterImpl::instance().trace_config().head_async)
				{
					EncodeValue(doc, allocator, "async", trace_entry.async);
				}
			}
			if (!trace_entry.content.empty())
			{
				EncodeValue(doc, allocator, "content", trace_entry.content);
			}
			rapidjson::StringBuffer buffer;
			rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer); //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json
			doc.Accept(writer);
			jsonContent = buffer.GetString();
			jsonContent += "\n\n";
			errorCode = 0;
		} while (0);
		return errorCode;
	}

	int CJsonParser::EncodeTraceContent(const string& trace_content, string& jsonContent)
	{
		int errorCode = 1;
		rapidjson::Document doc;
		rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
		doc.Parse(jsonContent.c_str());
		if (!doc.IsObject())
		{
			doc.SetObject();
		}
		if (!trace_content.empty())
		{

			EncodeValue(doc, allocator, "content", trace_content);
			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer); //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json
			doc.Accept(writer);
			jsonContent = buffer.GetString();
			jsonContent.erase(0, 1);
			jsonContent.erase(jsonContent.size() - 1, 1);
			errorCode = 0;
		}
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

}