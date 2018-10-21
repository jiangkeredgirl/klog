#pragma once
#include "klognetprotocol.h"
#include "cstandard.h"

template<class T>
int GetMemoryDataFromSerial(const string& sdata, T& cdata)
{
	TraceBackDebugCout();
	TraceCout(TRACE_INFO) << "serialized text data:" << sdata;
	std::stringstream text_ss;
	text_ss << sdata;
	boost::archive::text_iarchive text_ia(text_ss);
	text_ia >> cdata;
	return 0;

}

template<class T>
int GetSerialFromMemoryData(const T& cdata, string& sdata)
{
	TraceBackDebugCout();
	std::stringstream text_ss;
	boost::archive::text_oarchive text_oa(text_ss);
	text_oa << cdata;
	sdata = text_ss.str();
	TraceCout(TRACE_INFO) << "serialized text size:" << sdata.size() << ", serialized text data:" << sdata;
	/// test 
	//T data_test;
	//GetMemoryDataFromSerial(sdata, data_test);
	return 0;
}

