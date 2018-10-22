echo copy bin file of sdk to bin
echo f|xcopy /y /s /i /f .\KlogNetProtocolSDK\bin\*      .\bin\
echo f|xcopy /y /s /i /f ..\NetworkSDK\bin\*             .\bin\
echo f|xcopy /y  .\bin\*.exe                             .\OutKlogServerBin\
echo f|xcopy /y  .\bin\*.pdb                             .\OutKlogServerBin\
echo f|xcopy /y  .\bin\*.dll                             .\OutKlogServerBin\
