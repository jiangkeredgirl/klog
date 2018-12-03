set sln_name=klog
set platform_version=141
cd /d %~dp0
call build_sln.bat "%VS141COMNTOOLS%",%sln_name%,%platform_version%

echo f|xcopy /y /s /i /f .\kloglib\OutKlogSDK\*                          .\OutBinOfSln\OutKlogSDK
echo f|xcopy /y /s /i /f .\kloglibtest\OutKloglibTestBin\*               .\OutBinOfSln\OutKloglibTestBin
echo f|xcopy /y /s /i /f .\klognetprotocollib\OutKlogNetProtocolSDK\*    .\OutBinOfSln\OutKlogNetProtocolSDK
echo f|xcopy /y /s /i /f .\klogserver\OutKlogServerBin\*                 .\OutBinOfSln\OutKlogServerBin
echo f|xcopy /y /s /i /f .\klogclient\OutKlogClientBin\*                 .\OutBinOfSln\OutKlogClientBin

set out_path=%1
if "%out_path%"=="" ( echo out_path is null) else (
echo out_path is "%out_path%
echo f|xcopy /e /y  .\OutBinOfSln\*  %out_path%
)

rem pause effect daily build
rem pause 