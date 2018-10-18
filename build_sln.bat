set build_tool_path=%~1
set sln_name=%2
set platform_version=%3
echo build_tool_path=%build_tool_path%, sln_name=%sln_name%, platform_version=%platform_version%
call "%build_tool_path%VsDevCmd.bat"
cd /d %~dp0
MSBuild %sln_name%.sln /t:rebuild /p:platform=x86 /p:configuration=debug   /p:PlatformToolset=v%platform_version%
MSBuild %sln_name%.sln /t:rebuild /p:platform=x86 /p:Configuration=release /p:PlatformToolset=v%platform_version%
MSBuild %sln_name%.sln /t:rebuild /p:platform=x64 /p:configuration=debug   /p:PlatformToolset=v%platform_version%
MSBuild %sln_name%.sln /t:rebuild /p:platform=x64 /p:Configuration=release /p:PlatformToolset=v%platform_version%
pause
