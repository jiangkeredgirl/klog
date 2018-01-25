#include "config.h"
#include "kutility.h"
#include "rapidjsonparser.h"
#define CONFIG_FILE_NAME ("klog.config")

Config::Config()
{
}

Config &Config::instance()
{
    static Config _instance;
    return _instance;
}

int Config::GetTraceConfig(kk::TraceConfig& trace_config)
{
	int errorCode = 1;
	string path = CONFIG_FILE_NAME;
	string configContent;
	kk::Utility::ReadFile(path, configContent);
	if(!configContent.empty())
	{
		errorCode = CJsonParser::instance().GetTraceConfig(configContent, trace_config);
	}
	return errorCode;
}

int Config::SetTraceConfig(const kk::TraceConfig& trace_config)
{
	int errorCode = 1;
	string path = CONFIG_FILE_NAME;
	string configContent;	
	errorCode = CJsonParser::instance().SetTraceConfig(trace_config, configContent);
	kk::Utility::WriteFile(path, configContent);
	return errorCode;
}