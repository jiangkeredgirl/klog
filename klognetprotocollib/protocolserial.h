#pragma once
#ifdef KLOGNETPROTOCOLLIB_EXPORTS
#define KLOGNETPROTOCOLLIB_API __declspec(dllexport)
#else
#define KLOGNETPROTOCOLLIB_API __declspec(dllimport)
#endif

#include "klognetprotocol.h"

class IProtocolSerial
{
public:
	virtual int Serial(const string& serial, NetEvent& object) = 0;
	virtual int Serial(const NetEvent& object, string& serial) = 0;
	virtual int Serial(const string& serial, SendKlogClientTypeEvent& object) = 0;
	virtual int Serial(const SendKlogClientTypeEvent& object, string& serial) = 0;
	virtual int Serial(const string& serial, GetKlogServerPortEvent& object) = 0;
	virtual int Serial(const GetKlogServerPortEvent& object, string& serial) = 0;
	virtual int Serial(const string& serial, SendKlogServerPortEvent& object) = 0;
	virtual int Serial(const SendKlogServerPortEvent& object, string& serial) = 0;
	virtual int Serial(const string& serial, SendKlogConfigEvent& object) = 0;
	virtual int Serial(const SendKlogConfigEvent& object, string& serial) = 0;
	virtual int Serial(const string& serial, GetKlogConfigEvent& object) = 0;
	virtual int Serial(const GetKlogConfigEvent& object, string& serial) = 0;
	virtual int Serial(const string& serial, SendKlogMessageEvent& object) = 0;
	virtual int Serial(const SendKlogMessageEvent& object, string& serial) = 0;
	virtual int Serial(const string& serial, GetKlogMessageEvent& object) = 0;
	virtual int Serial(const GetKlogMessageEvent& object, string& serial) = 0;
};

#ifdef __cplusplus
extern "C" {
#endif

	KLOGNETPROTOCOLLIB_API IProtocolSerial* NewSerial();
	typedef IProtocolSerial* (*NewSerialFun)();
	KLOGNETPROTOCOLLIB_API void DeleteSerial(IProtocolSerial* serial);
	typedef void(*DeleteSerialFun)(IProtocolSerial* serial);

#ifdef __cplusplus
}
#endif