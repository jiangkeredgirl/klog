set project_name=klogclient
set platform_version=141
cd /d %~dp0
call build_project.bat "%VS141COMNTOOLS%",%project_name%,%platform_version%
pause