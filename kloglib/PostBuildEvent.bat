echo copy to out sdk package
echo f|xcopy /y  .\kloglib.h                          .\OutKlogSDK\include\
echo f|xcopy /y  .\tracemacr.h                        .\OutKlogSDK\include\
echo f|xcopy /y  .\traceprinter.h                     .\OutKlogSDK\include\
echo f|xcopy /y  .\traceloader.h                      .\OutKlogSDK\include\
echo f|xcopy /y  .\bin\kloglib*.lib                   .\OutKlogSDK\lib\
echo f|xcopy /y  .\bin\kloglib*.dll                   .\OutKlogSDK\bin\
echo f|xcopy /y  .\bin\kloglib*.pdb                   .\OutKlogSDK\bin\