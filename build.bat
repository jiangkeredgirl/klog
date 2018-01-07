cd /d %~dp0
@call "%VS141COMNTOOLS%VsDevCmd.bat"
MSBuild klog.sln /m /target:Rebuild /p:Configuration=Debug /property:Platform=Win32
MSBuild klog.sln /m /target:Rebuild /p:Configuration=Release /property:Platform=Win32
MSBuild klog.sln /m /target:Rebuild /p:Configuration=Debug /property:Platform=x64 
MSBuild klog.sln /m /target:Rebuild /p:Configuration=Release /property:Platform=x64
