echo copy bin file of sdk to bin
echo f|xcopy /y /s /i /f .\KlogSDK\bin\*      .\bin\
echo f|xcopy /y  .\bin\*.exe                  .\OutKloglibTestBin\
echo f|xcopy /y  .\bin\*.pdb                  .\OutKloglibTestBin\
echo f|xcopy /y  .\bin\*.dll                  .\OutKloglibTestBin\

