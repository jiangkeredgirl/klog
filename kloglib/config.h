#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include <vector>
using namespace std;

struct CameraAccount
{
	string oem;
	string account;
	string password;  
	CameraAccount()
    {
		oem = "";
		account = "";
		password = "";
    }
};

class Config
{
private:
    Config();
public:
    ~Config(){};
public:
    static Config& instance();

public:
	int GetCameraAccount(const string& dir, vector<CameraAccount>& accounts); 
	int GetHikIP(const string& dir, string& ip);
};

#endif // CONFIG_H
