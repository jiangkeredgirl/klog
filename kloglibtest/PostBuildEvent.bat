echo copy bin file of sdk to bin
echo f|xcopy /y /s /i /f .\KlogSDK\bin\*      .\bin\
echo f|xcopy /y  .\bin\*.exe                  .\OutKlogLibTestBin\
echo f|xcopy /y  .\bin\*.pdb                  .\OutKlogLibTestBin\
echo f|xcopy /y  .\bin\*.dll                  .\OutKlogLibTestBin\
echo f|xcopy /y  .\bin\*.config               .\OutKlogLibTestBin\

