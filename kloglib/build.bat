set project_name=kloglib
set platform_version=141
cd /d %~dp0
call build_project.bat "%VS141COMNTOOLS%",%project_name%,%platform_version%
pause