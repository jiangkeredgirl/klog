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

int ProtocolSerial::Serial(const string& serial, NetEvent& object)
{
	return GetObjectFromSerial(serial, object);
}

int ProtocolSerial::Serial(const NetEvent& object, string& serial)
{
	return GetSerialFromObject(object, serial);
}

int ProtocolSerial::Serial(const string& serial, GetKlogServerPortEvent& object)
{
	return GetObjectFromSerial(serial, object);
}

int ProtocolSerial::Serial(const GetKlogServerPortEvent& object, string& serial)
{
	return GetSerialFromObject(object, serial);
}

int ProtocolSerial::Serial(const string& serial, SendKlogServerPortEvent& object)
{
	return GetObjectFromSerial(serial, object);
}

int ProtocolSerial::Serial(const SendKlogServerPortEvent& object, string& serial)
{
	return GetSerialFromObject(object, serial);
}

int ProtocolSerial::Serial(const string& serial, SendKlogConfigEvent& object)
{
	return GetObjectFromSerial(serial, object);
}

int ProtocolSerial::Serial(const SendKlogConfigEvent& object, string& serial)
{
	return GetSerialFromObject(object, serial);
}

int ProtocolSerial::Serial(const string& serial, GetKlogConfigEvent& object)
{
	return GetObjectFromSerial(serial, object);
}

int ProtocolSerial::Serial(const GetKlogConfigEvent& object, string& serial)
{
	return GetSerialFromObject(object, serial);
}

int ProtocolSerial::Serial(const string& serial, SendKlogMessageEvent& object)
{
	return GetObjectFromSerial(serial, object);
}

int ProtocolSerial::Serial(const SendKlogMessageEvent& object, string& serial)
{
	return GetSerialFromObject(object, serial);
}

int ProtocolSerial::Serial(const string& serial, GetKlogMessageEvent& object)
{
	return GetObjectFromSerial(serial, object);
}

int ProtocolSerial::Serial(const GetKlogMessageEvent& object, string& serial)
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