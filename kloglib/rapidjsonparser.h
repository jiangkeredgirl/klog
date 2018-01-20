#pragma once

#include <string>
#include "config.h"
using namespace std;

class CJsonParser
{
public:
	static CJsonParser& instance();
public:
	int GetTraceConfig(const string& jsonContent, kk::TraceConfig& trace_config);
	int SetTraceConfig(const kk::TraceConfig& trace_config, string& jsonContent);
};

