echo copy to out sdk package
set toolset=%1
echo f|xcopy /y  .\klognetprotocol.h                                                          .\OutKlogNetProtocolSDK\include\
echo f|xcopy /y  .\protocolserial.h                                                           .\OutKlogNetProtocolSDK\include\
echo f|xcopy /y  .\protocolserialpackage.h                                                    .\OutKlogNetProtocolSDK\include\
echo f|xcopy /y  .\bin\klognetprotocollib*.lib                                                .\OutKlogNetProtocolSDK\lib\
echo f|xcopy /y  .\bin\klognetprotocollib*.dll                                                .\OutKlogNetProtocolSDK\bin\
echo f|xcopy /y  .\bin\klognetprotocollib*.pdb                                                .\OutKlogNetProtocolSDK\bin\
echo f|xcopy /y  ..\..\thirdparty\boost\lib64-msvc-%toolset%\boost_serialization*.dll         .\OutKlogNetProtocolSDK\bin\