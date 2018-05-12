﻿// kloglibtest.cpp : Defines the entry point for the console application.
//

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#include "kloglib.h"

#define MYDEFINE_LEVEL 10

// test trace
int trace_test(const string& log_content)
{
	//setlocale(LC_ALL, "");
	// trace_test函数进入退出log
#if 1
	Track(""); // 正确用法 注意要带参数("")，打印函数进入和退出的log
#else
	TrackCout();
#endif
	TraceError("%s", log_content.c_str()); // error级别
	TraceWarning("%s", log_content.c_str()); // warning级别
	TraceOK("%s", log_content.c_str()); //c风格 ok级别
	TraceNotice("%s", log_content.c_str()); //c风格 notice级别
	TraceInfo("%s", log_content.c_str()); //c风格 info级别
	TraceDebug("%s", log_content.c_str()); //c风格 debug级别	
	TraceTemp("%s", log_content.c_str()); //c风格 temp级别
	Trace(TRACE_INFO, "%s", log_content.c_str());

	TraceOKCout() << "\n\nc+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++trace\n\n";

	TraceErrorCout() << log_content;//c++风格，编译器代码不能去掉
	TraceWarningCout() << log_content;
	TraceOKCout() << log_content; // tchar类型
	TraceNoticeCout() << log_content;
	TraceInfoCout() << log_content;
	TraceDebugCout() << log_content;
	TraceTempCout() << log_content;
	TraceCout(MYDEFINE_LEVEL) << log_content;
	return 0;
}


int main()
{
	//SetConsoleTitle(L"My Console Window - 你好");
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//char* a = setlocale(LC_ALL, "chinese");
	//SetConsoleOutputCP(CP_UTF8);
	//SetConsoleCP(CP_UTF8);

	//CONSOLE_FONT_INFOEX fontInfo;
	//fontInfo.cbSize = sizeof(fontInfo);
	//fontInfo.FontFamily = 54;
	//fontInfo.FontWeight = 400;
	//fontInfo.nFont = 0;
	//const wchar_t myFont[] = L"KaiTi";
	//fontInfo.dwFontSize = { 18, 41 };
	//std::copy(myFont, myFont + (sizeof(myFont) / sizeof(wchar_t)), fontInfo.FaceName);
	//SetCurrentConsoleFontEx(hConsole, false, &fontInfo);


	trace_test("my log content");
	WaitTrace();
	return 0;
}

