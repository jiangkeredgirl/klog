@call "%VS141COMNTOOLS%VsDevCmd.bat"
cd /d %~dp0
MSBuild klogserver.vcxproj /t:rebuild /p:platform=win32 /p:configuration=debug   /p:PlatformToolset=v141
MSBuild klogserver.vcxproj /t:rebuild /p:platform=win32 /p:Configuration=release /p:PlatformToolset=v141
MSBuild klogserver.vcxproj /t:rebuild /p:platform=x64   /p:configuration=debug   /p:PlatformToolset=v141
MSBuild klogserver.vcxproj /t:rebuild /p:platform=x64   /p:Configuration=release /p:PlatformToolset=v141
pause