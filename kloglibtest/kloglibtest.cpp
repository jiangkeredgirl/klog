// kloglibtest.cpp : Defines the entry point for the console application.
//

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include "kloglib.h"
#include "TraceTest1.h"
#include "TraceTest2.h"

#define MYDEFINE_LEVEL 10

int trace_test1(const string& log_content);
int trace_test2(const string& log_content);

// test trace
int trace_test(const string& log_content)
{
	//setlocale(LC_ALL, "");
	// trace_test函数进入退出log
#if 1
	Track("333"); // 正确用法 注意要带参数("")，打印函数进入和退出的log
#else
	TrackCout << "333";
#endif
	TraceError("%s", log_content.c_str()); // error级别
	TraceWarning("%s", log_content.c_str()); // warning级别
	TraceOK("%s", log_content.c_str()); //c风格 ok级别
	TraceNotice("%s", log_content.c_str()); //c风格 notice级别
	TraceInfo("%s", log_content.c_str()); //c风格 info级别
	TraceDebug("%s", log_content.c_str()); //c风格 debug级别	
	TraceTemp("%s", log_content.c_str()); //c风格 temp级别
	Trace(TRACE_INFO, "%s", log_content.c_str());

	TraceOKCout << "\n\nc+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++trace\n\n";

	TraceErrorCout << log_content;//c++风格，编译器代码不能去掉
	TraceWarningCout << log_content;
	TraceOKCout << log_content; // tchar类型
	TraceNoticeCout << log_content;
	TraceInfoCout << log_content;
	TraceDebugCout << log_content;
	TraceTempCout << log_content;
	TraceCout(MYDEFINE_LEVEL) << log_content;

	printf("printf=================================\n");
	//cout << "cout==================================" << endl;
	//std::cout << "std::cout==================================" << endl;
	trace_test1(u8"my log content 支持中文");
	return 0;
}

int trace_test1(const string& log_content)
{
	TrackCout;
	TraceErrorCout << log_content;//c++风格，编译器代码不能去掉
	TraceWarningCout << log_content;
	TraceOKCout << log_content; // tchar类型
	TraceNoticeCout << log_content;
	TraceInfoCout << log_content;
	TraceDebugCout << log_content;
	TraceTempCout << log_content;
	TraceCout(MYDEFINE_LEVEL) << log_content;
	trace_test2(u8"my log content 支持中文");
	return 0;
}

int trace_test2(const string& log_content)
{
	TrackCout;
	TraceErrorCout << log_content;//c++风格，编译器代码不能去掉
	TraceWarningCout << log_content;
	TraceOKCout << log_content; // tchar类型
	TraceNoticeCout << log_content;
	TraceInfoCout << log_content;
	TraceDebugCout << log_content;
	TraceTempCout << log_content;
	TraceCout(MYDEFINE_LEVEL) << log_content;
	return 0;
}

void SetConsoleUTF8()
{
	SetConsoleTitle(L"klog输出");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	CONSOLE_FONT_INFOEX fontInfo;
	memset(&fontInfo, 0, sizeof(CONSOLE_FONT_INFOEX));
	fontInfo.cbSize = sizeof(fontInfo);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hConsole, false, &fontInfo);
	fontInfo.FontFamily = 54;
	fontInfo.dwFontSize.X = 8;
	fontInfo.dwFontSize.Y = 14;
	fontInfo.FontWeight = FW_NORMAL;
	wcscpy_s(fontInfo.FaceName, L"KaiTi");
	SetCurrentConsoleFontEx(hConsole, false, &fontInfo);
}

int _tmain()
{
	SetConsoleUTF8();
	TrackCout;
	trace_test(u8"my log content 支持中文");	
	//TraceTest1 test1;
	//TraceTest2 test2;
	WaitTrace;
	return 0;
}

