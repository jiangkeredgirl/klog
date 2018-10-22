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
	virtual int Serial(const string& serial, SendKlogConfig& object) = 0;
	virtual int Serial(const SendKlogConfig& object, string& serial) = 0;
	virtual int Serial(const string& serial, GetKlogConfig& object) = 0;
	virtual int Serial(const GetKlogConfig& object, string& serial) = 0;
	virtual int Serial(const string& serial, SendKlogMessage& object) = 0;
	virtual int Serial(const SendKlogMessage& object, string& serial) = 0;
	virtual int Serial(const string& serial, GetKlogMessage& object) = 0;
	virtual int Serial(const GetKlogMessage& object, string& serial) = 0;
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