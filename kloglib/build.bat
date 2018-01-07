cd /d %~dp0
@call "%VS141COMNTOOLS%VsDevCmd.bat"
MSBuild kloglib.vcxproj /m /target:Rebuild /p:Configuration=Debug /property:Platform=Win32
MSBuild kloglib.vcxproj /m /target:Rebuild /p:Configuration=Release /property:Platform=Win32
MSBuild kloglib.vcxproj /m /target:Rebuild /p:Configuration=Debug /property:Platform=x64
MSBuild kloglib.vcxproj /m /target:Rebuild /p:Configuration=Release /property:Platform=x64