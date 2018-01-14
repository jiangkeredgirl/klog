#include "config.h"
#include "kutility.h"
#include "rapidjsonparser.h"

Config::Config()
{
}

Config &Config::instance()
{
    static Config _instance;
    return _instance;
}

int Config::GetCameraAccount(const string& dir, vector<CameraAccount>& accounts)
{
	int errorCode = 1;
	string path = dir + "topcameratest.config";
	string configContent;
	kk::Utility::ReadFile(path, configContent);
	if(!configContent.empty())
	{
		errorCode = CJsonParser::instance().GetCameraAccount(configContent, accounts);
	}
	return errorCode;
}

int Config::GetHikIP(const string& dir, string& ip)
{
	int errorCode = 1;
	string path = dir + "topcameratest.config";
	string configContent;
	kk::Utility::ReadFile(path, configContent);
	if (!configContent.empty())
	{
		errorCode = CJsonParser::instance().GetHikIP(configContent, ip);
	}
	return errorCode;
}