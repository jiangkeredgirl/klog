// kloglibtest.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include "kloglib.h"
#include "kspdlog.h"
#include "TraceTest1.h"
#include "TraceTest2.h"
#include <thread>
#include <iostream>

#define MYDEFINE_LEVEL 10

int trace_test1(const string& log_content);
int trace_test2(const string& log_content);

// test trace
int trace_test(const string& log_content)
{
	//setlocale(LC_ALL, "");
	// trace_test函数进入退出log
#if 1
	KlogTrack("333"); // 正确用法 注意要带参数("")，打印函数进入和退出的log
#else
	TrackCout << "333";
#endif
	KlogError("%s", log_content.c_str()); // error级别
	KlogWarn("%s", log_content.c_str()); // warning级别
	KlogOK("%s", log_content.c_str()); //c风格 ok级别
	KlogNotice("%s", log_content.c_str()); //c风格 notice级别
	KlogInfo("%s", log_content.c_str()); //c风格 info级别
	KlogDebug("%s", log_content.c_str()); //c风格 debug级别	
	KlogTemp("%s", log_content.c_str()); //c风格 temp级别
	Trace(TRACE_INFO, "%s", log_content.c_str());

	KlogOKCout << "\n\nc+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++trace\n\n";

	KlogErrorCout << log_content;//c++风格，编译器代码不能去掉
	KlogWarnCout << log_content;
	KlogOKCout << log_content; // tchar类型
	KlogNoticeCout << log_content;
	KlogInfoCout << log_content;
	KlogDebugCout << log_content;
	KlogTempCout << log_content;
	TraceCout(MYDEFINE_LEVEL) << log_content;

	printf("printf=================================\n");
	//cout << "cout==================================" << endl;
	//std::cout << "std::cout==================================" << endl;
	trace_test1("my log content 支持中文");
	return 0;
}

int trace_test1(const string& log_content)
{
	//TrackCout;
	//TraceErrorCout << log_content;//c++风格，编译器代码不能去掉
	//TraceWarningCout << log_content;
	//TraceOKCout << log_content; // tchar类型
	//TraceNoticeCout << log_content;
	//TraceInfoCout << log_content;
	//TraceDebugCout << log_content;
	//TraceTempCout << log_content;
	//TraceCout(MYDEFINE_LEVEL) << log_content;
	//trace_test2(u8"my log content 支持中文");
	return 0;
}

int trace_test2(const string& log_content)
{
	//TrackCout;
	//TraceErrorCout << log_content;//c++风格，编译器代码不能去掉
	//TraceWarningCout << log_content;
	//TraceOKCout << log_content; // tchar类型
	//TraceNoticeCout << log_content;
	//TraceInfoCout << log_content;
	//TraceDebugCout << log_content;
	//TraceTempCout << log_content;
	TraceCout(MYDEFINE_LEVEL) << log_content;
	return 0;
}

int trace_call_5(const string& log_content)
{
	KlogTrackCout;
	std::this_thread::sleep_for(std::chrono::seconds(5)); //睡眠1000毫秒
	return 0;
}
int trace_call_4(const string& log_content)
{
	KlogTrackCout;
	std::this_thread::sleep_for(std::chrono::seconds(5)); //睡眠1000毫秒
	trace_call_5(log_content);
	std::this_thread::sleep_for(std::chrono::seconds(5)); //睡眠1000毫秒
	return 0;
}
int trace_call_3(const string& log_content)
{
	KlogTrackCout;
	std::this_thread::sleep_for(std::chrono::seconds(5)); //睡眠1000毫秒
	trace_call_4(log_content);
	std::this_thread::sleep_for(std::chrono::seconds(5)); //睡眠1000毫秒
	return 0;
}
int trace_call_2(const string& log_content)
{
	KlogTrackCout;
	std::this_thread::sleep_for(std::chrono::seconds(5)); //睡眠1000毫秒
	trace_call_3(log_content);
	std::this_thread::sleep_for(std::chrono::seconds(5)); //睡眠1000毫秒
	return 0;
}
int trace_call_1(const string& log_content)
{
	KlogTrackCout;
	std::this_thread::sleep_for(std::chrono::seconds(5)); //睡眠1000毫秒
	trace_call_2(log_content);
	std::this_thread::sleep_for(std::chrono::seconds(5)); //睡眠1000毫秒
	trace_call_3(log_content);
	std::this_thread::sleep_for(std::chrono::seconds(5)); //睡眠1000毫秒
	return 0;
}
int trace_call_0(const string& log_content)
{
	KlogTrackCout;
	std::this_thread::sleep_for(std::chrono::seconds(5)); //睡眠1000毫秒
	trace_call_1(log_content);
	return 0;
}

int trace_thread(const string& log_content)
{
	KlogTrackCout;
	KlogOKCout << log_content; // tchar类型
	std::thread([log_content]()
		{
			KlogTrackCout;
			while (1)
			{
				KlogErrorCout << log_content;//c++风格，编译器代码不能去掉	
				std::this_thread::sleep_for(std::chrono::seconds(5)); //睡眠1000毫秒
			}
		}).detach();
	return 0;
}

void SetConsoleUtf8()
{
	SetConsoleTitle("klog输出");
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

void TestKlog()
{
	SetConsoleUtf8();
	KlogInfo("信息日志");
	KlogWarn("警告日志");
	KlogError("错误日志");
	//CreateConsole;
	//GenerateDump;
	//KlogCreateStdout;
	//KlogSetStdoutUTF8;
	KlogTrackCout;
	KlogOKCout << "\"支持双引号\"";
	int nvalue = 29;
	(KlogOKCout << "支持二进制数据:").write(reinterpret_cast<const char*>(&nvalue), sizeof(nvalue));
	//trace_test("my log content 支持中文");	
	trace_call_0("函数调用顺序测试");
	//trace_thread("线程1");
	//trace_thread("线程2");
	//trace_thread("线程3");
	//TraceTest1 test1;
	//TraceTest2 test2;
	//WaitTrace;
}

void TestSpdlog()
{
	KSpdlog::InitLog("./log", spdlog::level::level_enum::trace, false);
	LOG_INFO("信息日志");
	LOG_WARN("警告日志");
	LOG_ERROR("错误日志");
	LOG_INFO("错误	C7595	“std::basic_format_string<char,int>::basic_format_string”: 对即时函数的调用不是常量表达式");
	spdlog::info("spdlog测试对即时函数的调用不是常量表达式: 假设一个错误码:{}", 1);
	LOG_INFO("spdlog测试对即时函数的调用不是常量表达式: 假设一个错误码:{}", 1);
}


int _tmain()
{	
	// 设置控制台输出为 UTF-8
	SetConsoleOutputCP(CP_UTF8);
	// 可选：设置输入为 UTF-8
	SetConsoleCP(CP_UTF8);
	cout << "输出中文测试" << endl;


	TestSpdlog();
	TestKlog();


	std::cout << "按 Enter 键继续..." << std::endl;
	// 等待用户输入回车
	std::cin.get();
	std::cout << "程序继续..." << std::endl;
	return 0;
}

