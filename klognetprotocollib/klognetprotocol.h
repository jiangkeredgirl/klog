#pragma once

#include <string>
using namespace std;

enum NetEventType
{
	UNKNOWN = 0,
	SEND_KLOG_CONFIG,
	GET_KLOG_CONFIG,
	SEND_KLOG_MESSAGE,
	GET_KLOG_MESSAGE
};

struct NetEvent
{
	NetEventType event_type;
};

struct KlogSourceInfo
{
	string sourece_ip;
	int    source_port = 0;
	string source_program_name;
};

struct SendKlogConfig : public NetEvent
{
	KlogSourceInfo source_info;
	string         klog_config; // 配置文件
	SendKlogConfig()
	{
		event_type = NetEventType::SEND_KLOG_CONFIG;
	}
};

struct GetKlogConfig : public NetEvent
{
	GetKlogConfig()
	{
		event_type = NetEventType::GET_KLOG_CONFIG;
	}
};

struct SendKlogMessage : public NetEvent
{
	KlogSourceInfo source_info;
	string         klog_message; // klog 日志
	SendKlogMessage()
	{
		event_type = NetEventType::SEND_KLOG_MESSAGE;
	}
};

struct GetKlogMessage : public NetEvent
{
	KlogSourceInfo source_info;
	GetKlogMessage()
	{
		event_type = NetEventType::GET_KLOG_MESSAGE;
	}
};
