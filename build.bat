set sln_name=klog
set platform_version=141
cd /d %~dp0
call build_sln.bat "%VS141COMNTOOLS%",%sln_name%,%platform_version%
rem pause 影响每天的自动编译