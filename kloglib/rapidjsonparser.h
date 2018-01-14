#pragma once

#include <string>
#include "config.h"

using namespace std;


class CJsonParser
{
public:
	static CJsonParser& instance();	

public:
	int GetCameraAccount(const string& jsonContent, vector<CameraAccount>& accounts);
	int GetHikIP(const string& jsonContent, string& ip);

};

