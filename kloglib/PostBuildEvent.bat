echo copy to out sdk package
echo f|xcopy /y  .\kloglib.h                          .\OutKlogSDK\include\
echo f|xcopy /y  .\klogcustomsetting.h                .\OutKlogSDK\include\
echo f|xcopy /y  .\tracemacr.h                        .\OutKlogSDK\include\
echo f|xcopy /y  .\traceprinter.h                     .\OutKlogSDK\include\
echo f|xcopy /y  .\traceloader.h                      .\OutKlogSDK\include\
echo f|xcopy /y  .\tracepackage.h                     .\OutKlogSDK\include\
echo f|xcopy /y  .\kspdlog.h                          .\OutKlogSDK\include\
echo f|xcopy /y  .\spdlogwrapper.h                    .\OutKlogSDK\include\
xcopy /y /e /i   .\fmt                                .\OutKlogSDK\include\fmt\
xcopy /y /e /i   .\spdlog                             .\OutKlogSDK\include\spdlog\
echo f|xcopy /y  .\config.h                           .\OutKlogSDK\sources\
echo f|xcopy /y  .\GenerateDumpInfo.h                 .\OutKlogSDK\sources\
echo f|xcopy /y  .\rapidjsonparser.h                  .\OutKlogSDK\sources\
echo f|xcopy /y  .\tracedefine.h                      .\OutKlogSDK\sources\
echo f|xcopy /y  .\traceloaderimpl.h                  .\OutKlogSDK\sources\
echo f|xcopy /y  .\traceprinterimpl.h                 .\OutKlogSDK\sources\
echo f|xcopy /y  .\TracePackageInl.h                  .\OutKlogSDK\sources\
echo f|xcopy /y  .\config.cpp                         .\OutKlogSDK\sources\
echo f|xcopy /y  .\GenerateDumpInfo.cpp               .\OutKlogSDK\sources\
echo f|xcopy /y  .\rapidjsonparser.cpp                .\OutKlogSDK\sources\
echo f|xcopy /y  .\traceloaderimpl.cpp                .\OutKlogSDK\sources\
echo f|xcopy /y  .\traceprinterimpl.cpp               .\OutKlogSDK\sources\
xcopy /y /e /i   ..\..\ktoolkit\kcommonhpp            .\OutKlogSDK\sources\kcommonhpp
xcopy /y /e /i   ..\..\thirdparty\rapidjson\include\rapidjson      .\OutKlogSDK\sources\rapidjson
echo f|xcopy /y  .\bin\kloglib*.lib                   .\OutKlogSDK\lib\
echo f|xcopy /y  .\bin\kloglib*.dll                   .\OutKlogSDK\bin\
echo f|xcopy /y  .\bin\kloglib*.pdb                   .\OutKlogSDK\bin\
echo f|xcopy /y  .\klog.config                        .\OutKlogSDK\bin\
echo f|xcopy /y /s /i /f .\KlogNetProtocolSDK\bin\*   .\OutKlogSDK\bin\
echo f|xcopy /y /s /i /f ..\..\ktoolkit\KNetworkSDK\bin\*          .\OutKlogSDK\bin\