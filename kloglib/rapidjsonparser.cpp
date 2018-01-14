#include "rapidjsonparser.h"
#include "kutility.h"
#include "rapidjson/document.h"  
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"


CJsonParser& CJsonParser::instance()
{
	static CJsonParser _instance;
	return _instance;
}


int CJsonParser::GetCameraAccount(const string& jsonContent, vector<CameraAccount>& accounts)
{
	int errorCode = 1;
	rapidjson::Document doc;
	doc.Parse(jsonContent.c_str());
	do
	{
		if (!doc.IsObject())
		{
			break;
		}
		if (!doc.HasMember("LoginAcount"))
		{
			break;
		}
		if (!doc["LoginAcount"].IsArray())
		{
			break;
		}
		for (rapidjson::SizeType i = 0; i < doc["LoginAcount"].Size(); ++i)
		{
			if (!doc["LoginAcount"][i].IsObject())
			{
				break;
			}
			CameraAccount account;
			if (!doc["LoginAcount"][i].HasMember("oem"))
			{
				break;
			}
			if (!doc["LoginAcount"][i]["oem"].IsString())
			{
				break;
			}
			account.oem = doc["LoginAcount"][i]["oem"].GetString();
			if (!doc["LoginAcount"][i].HasMember("account"))
			{
				break;
			}
			if (!doc["LoginAcount"][i]["account"].IsString())
			{
				break;
			}
			account.account = doc["LoginAcount"][i]["account"].GetString();
			if (!doc["LoginAcount"][i].HasMember("password"))
			{
				break;
			}
			if (!doc["LoginAcount"][i]["password"].IsString())
			{
				break;
			}
			account.password = doc["LoginAcount"][i]["password"].GetString();
			accounts.push_back(account);

		}
		errorCode = 0;
	} while (0);
	return errorCode;
}

int CJsonParser::GetHikIP(const string& jsonContent, string& ip)
{
	int errorCode = 1;
	rapidjson::Document doc;
	doc.Parse(jsonContent.c_str());
	do
	{
		if (!doc.IsObject())
		{
			break;
		}
		if (!doc.HasMember("HikIP"))
		{
			break;
		}
		if (!doc["HikIP"].IsString())
		{
			break;
		}
		ip = doc["HikIP"].GetString();
		errorCode = 0;
	} while (0);
	return errorCode;
}