@call "%VS141COMNTOOLS%VsDevCmd.bat"
cd /d %~dp0
MSBuild kloglib.vcxproj /m /target:Rebuild /property:Platform=x86 /p:Configuration=Debug   /p:VisualStudioVersion=14.1
MSBuild kloglib.vcxproj /m /target:Rebuild /property:Platform=x86 /p:Configuration=Release /p:VisualStudioVersion=14.1
MSBuild kloglib.vcxproj /m /target:Rebuild /property:Platform=x64 /p:Configuration=Debug   /p:VisualStudioVersion=14.1
MSBuild kloglib.vcxproj /m /target:Rebuild /property:Platform=x64 /p:Configuration=Release /p:VisualStudioVersion=14.1
pause