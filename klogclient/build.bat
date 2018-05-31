@call "%VS141COMNTOOLS%VsDevCmd.bat"
cd /d %~dp0
MSBuild klogclient.vcxproj /t:rebuild /p:platform=x64 /p:configuration=debug   /p:PlatformToolset=v141
MSBuild klogclient.vcxproj /t:rebuild /p:platform=x64 /p:Configuration=release /p:PlatformToolset=v141
MSBuild klogclient.vcxproj /t:rebuild /p:platform=x64 /p:configuration=debug   /p:PlatformToolset=v141
MSBuild klogclient.vcxproj /t:rebuild /p:platform=x64 /p:Configuration=release /p:PlatformToolset=v141
pause