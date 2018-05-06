@call "%VS141COMNTOOLS%VsDevCmd.bat"
cd /d %~dp0
MSBuild kloglibtest.vcxproj /t:rebuild /p:platform=x86 /p:configuration=debug   /p:PlatformToolset=v141
MSBuild kloglibtest.vcxproj /t:rebuild /p:platform=x86 /p:Configuration=release /p:PlatformToolset=v141
MSBuild kloglibtest.vcxproj /t:rebuild /p:platform=x64 /p:configuration=debug   /p:PlatformToolset=v141
MSBuild kloglibtest.vcxproj /t:rebuild /p:platform=x64 /p:Configuration=release /p:PlatformToolset=v141
pause