#include "GenerateDumpInfo.h"
#include <Windows.h>
#include <DbgHelp.h>

GenerateDumpInfo::GenerateDumpInfo()
{
}


GenerateDumpInfo::~GenerateDumpInfo()
{
}


GenerateDumpInfo& GenerateDumpInfo::instance()
{
	static GenerateDumpInfo _instance;
	return _instance;
}

//生产DUMP文件
int GenerateMiniDump(HANDLE hFile, PEXCEPTION_POINTERS pExceptionPointers, PWCHAR pwAppName)
{
	BOOL bOwnDumpFile = FALSE;
	HANDLE hDumpFile = hFile;
	MINIDUMP_EXCEPTION_INFORMATION ExpParam;

	typedef BOOL(WINAPI * MiniDumpWriteDumpT)(
		HANDLE,
		DWORD,
		HANDLE,
		MINIDUMP_TYPE,
		PMINIDUMP_EXCEPTION_INFORMATION,
		PMINIDUMP_USER_STREAM_INFORMATION,
		PMINIDUMP_CALLBACK_INFORMATION
		);

	MiniDumpWriteDumpT pfnMiniDumpWriteDump = NULL;
	HMODULE hDbgHelp = LoadLibrary(L"DbgHelp.dll");
	if (hDbgHelp)
		pfnMiniDumpWriteDump = (MiniDumpWriteDumpT)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");

	if (pfnMiniDumpWriteDump)
	{
		if (hDumpFile == NULL || hDumpFile == INVALID_HANDLE_VALUE)
		{
			//TCHAR szPath[MAX_PATH] = { 0 };
			TCHAR szFileName[MAX_PATH] = { 0 };
			//TCHAR* szAppName = pwAppName;
			TCHAR* szVersion = L"v1.0";
			TCHAR dwBufferSize = MAX_PATH;
			SYSTEMTIME stLocalTime;

			GetLocalTime(&stLocalTime);
			//GetTempPath(dwBufferSize, szPath);

			//wsprintf(szFileName, L"%s%s", szPath, szAppName);
			CreateDirectory(szFileName, NULL);

			wsprintf(szFileName, L"%s-%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp",
				//szPath, szAppName, szVersion,
				szVersion,
				stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
				stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond,
				GetCurrentProcessId(), GetCurrentThreadId());
			hDumpFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);

			bOwnDumpFile = TRUE;
			OutputDebugString(szFileName);
		}

		if (hDumpFile != INVALID_HANDLE_VALUE)
		{
			ExpParam.ThreadId = GetCurrentThreadId();
			ExpParam.ExceptionPointers = pExceptionPointers;
			ExpParam.ClientPointers = FALSE;

			pfnMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
				hDumpFile, MiniDumpWithDataSegs, (pExceptionPointers ? &ExpParam : NULL), NULL, NULL);

			if (bOwnDumpFile)
				CloseHandle(hDumpFile);
		}
	}

	if (hDbgHelp != NULL)
		FreeLibrary(hDbgHelp);

	return EXCEPTION_EXECUTE_HANDLER;
}


LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
{
	if (IsDebuggerPresent())
	{
		return EXCEPTION_CONTINUE_SEARCH;
	}

	return GenerateMiniDump(NULL, lpExceptionInfo, L"test");
}

//#ifndef _M_IX86
//#error "The following code only works for x86!"
//#endif

// 此函数一旦成功调用，之后对 SetUnhandledExceptionFilter 的调用将无效
//void DisableSetUnhandledExceptionFilter()
//{
//	void* addr = (void*)GetProcAddress(LoadLibraryA("kernel32.dll"),
//		"SetUnhandledExceptionFilter");
//
//	if (addr)
//	{
//		unsigned char code[16];
//		int size = 0;
//
//		code[size++] = 0x33;
//		code[size++] = 0xC0;
//		code[size++] = 0xC2;
//		code[size++] = 0x04;
//		code[size++] = 0x00;
//
//		DWORD dwOldFlag, dwTempFlag;
//		VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
//		WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
//		VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);
//	}
//}

int GenerateDumpInfo::Generate(const std::string dumpFileName)
{
	//加入崩溃dump文件功能 
	SetUnhandledExceptionFilter(ExceptionFilter);
	//DisableSetUnhandledExceptionFilter();
	return 0;
}