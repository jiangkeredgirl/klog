#include "protocolserialimpl.h"
#include "klognetprotocolarchive.h"

template<class T>
int GetObjectFromSerial(const string& serial, T& object)
{
	std::stringstream text_ss;
	text_ss << serial;
	boost::archive::text_iarchive text_ia(text_ss);
	text_ia >> object;
	return 0;

}

template<class T>
int GetSerialFromObject(const T& object, string& serial)
{
	std::stringstream text_ss;
	boost::archive::text_oarchive text_oa(text_ss);
	text_oa << object;
	serial = text_ss.str();
	return 0;
}

  
ProtocolSerial::ProtocolSerial(void)
{

}
ProtocolSerial::~ProtocolSerial(void)
{

}

int ProtocolSerial::Serial(const string& serial, SendKlogConfig& object)
{
	return GetObjectFromSerial(serial, object);
}

int ProtocolSerial::Serial(const SendKlogConfig& object, string& serial)
{
	return GetSerialFromObject(object, serial);
}

int ProtocolSerial::Serial(const string& serial, GetKlogConfig& object)
{
	return GetObjectFromSerial(serial, object);
}

int ProtocolSerial::Serial(const GetKlogConfig& object, string& serial)
{
	return GetSerialFromObject(object, serial);
}

int ProtocolSerial::Serial(const string& serial, SendKlogMessage& object)
{
	return GetObjectFromSerial(serial, object);
}

int ProtocolSerial::Serial(const SendKlogMessage& object, string& serial)
{
	return GetSerialFromObject(object, serial);
}

int ProtocolSerial::Serial(const string& serial, GetKlogMessage& object)
{
	return GetObjectFromSerial(serial, object);
}

int ProtocolSerial::Serial(const GetKlogMessage& object, string& serial)
{
	return GetSerialFromObject(object, serial);
}


KLOGNETPROTOCOLLIB_API IProtocolSerial* NewSerial()
{
	return new ProtocolSerial();
}

KLOGNETPROTOCOLLIB_API void DeleteSerial(IProtocolSerial* serial)
{
	if (serial)
	{
		delete dynamic_cast<ProtocolSerial*>(serial);
		serial = nullptr;
	}
}