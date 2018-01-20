#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include <vector>
using namespace std;
#include "TracePrinter.h"

class Config
{
private:
    Config();
public:
    ~Config(){};
public:
    static Config& instance();

public:
	int GetTraceConfig(kk::TraceConfig& trace_config);
	int SetTraceConfig(const kk::TraceConfig& trace_config);
};

#endif // CONFIG_H
