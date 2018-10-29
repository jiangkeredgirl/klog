#pragma once

#include <string>
using namespace std;

enum class NetEventType
{
	UNKNOWN = 0,
	GET_KLOG_SERVER_PORT,
	SEND_KLOG_SERVER_PORT,
	SEND_KLOG_CONFIG,
	GET_KLOG_CONFIG,
	SEND_KLOG_MESSAGE,
	GET_KLOG_MESSAGE
};

enum class KlogClientType
{
	UNKNOWN = 0,
	SOURCE_ENDPOINT,
	SINK_ENDPOINT
};

class NetEvent
{
public:
	virtual ~NetEvent() {};
	NetEventType event_type;
};

class GetKlogServerPortEvent : public NetEvent
{
public:
	virtual ~GetKlogServerPortEvent() {};
	KlogClientType client_type;
};

class SendKlogServerPortEvent : public NetEvent
{
public:
	virtual ~SendKlogServerPortEvent() {};
	int sync_message_port;
	int async_message_port;
};

class KlogSourceInfo
{
public:
	virtual ~KlogSourceInfo() {};
	string sourece_ip;
	int    source_port = 0;
	string source_program_name;
};

class SendKlogConfigEvent : public NetEvent
{
public:
	SendKlogConfigEvent()
	{
		event_type = NetEventType::SEND_KLOG_CONFIG;
	}
	virtual ~SendKlogConfigEvent() {};
	KlogSourceInfo source_info;
	string         klog_config; // 配置文件

};

class GetKlogConfigEvent : public NetEvent
{
public:
	GetKlogConfigEvent()
	{
		event_type = NetEventType::GET_KLOG_CONFIG;
	}
	virtual ~GetKlogConfigEvent() {};
};

class SendKlogMessageEvent : public NetEvent
{
public:
	SendKlogMessageEvent()
	{
		event_type = NetEventType::SEND_KLOG_MESSAGE;
	}
	virtual ~SendKlogMessageEvent() {};
	KlogSourceInfo source_info;
	string         klog_message; // klog 日志	
};

class GetKlogMessageEvent : public NetEvent
{
public:
	GetKlogMessageEvent()
	{
		event_type = NetEventType::GET_KLOG_MESSAGE;
	}
	virtual ~GetKlogMessageEvent() {};
	KlogSourceInfo source_info;
};
