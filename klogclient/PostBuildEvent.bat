echo copy bin file of sdk to bin
echo f|xcopy /y /s /i /f .\KlogSDK\bin\*      .\bin\
echo f|xcopy /y  .\bin\*.exe                  .\OutKlogClientBin\
echo f|xcopy /y  .\bin\*.pdb                  .\OutKlogClientBin\
echo f|xcopy /y  .\bin\*.dll                  .\OutKlogClientBin\
echo f|xcopy /y  .\bin\*.config               .\OutKlogClientBin\

set program_name=%1
echo program_name=%program_name%
cd /d %~dp0
call qtpacket.bat .\OutKlogClientBin\%program_name%
