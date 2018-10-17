echo copy to out bin package
echo f|xcopy /y  .\bin\klogserver*.exe                  .\OutKlogServerBin\
echo f|xcopy /y  .\bin\klogserver*.pdb                  .\OutKlogServerBin\
echo f|xcopy /y /s /i /f .\NetworkSDK\bin\*             .\OutKlogServerBin\
echo f|xcopy /y /s /i /f .\NetworkSDK\bin\*             .\bin\
