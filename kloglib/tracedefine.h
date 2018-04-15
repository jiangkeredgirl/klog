#pragma once

// 是否生成trace 函数
#define  TRACE_OUT             1                     ///< 0 not output log, 1 output log
#define  TRACK_OUT             1                     ///< whether output trace of function called

// 是否使用glog
#define  USE_GLOG              0

// 是否使用线程输出trace
#define  TRACE_ASYNC           1                     ///< 0 not output log, 1 output log
#define  TRACE_SYNC_LOCK       1                     ///< 0 no use lock, 1 use lock when sync model

// 预定义8种trace等级，数字越大输出等级越低
#define  TRACE_TRACk           1                     ///< track out,0 not output
#define  TRACE_ERROR           2                     ///< error out,0 not output
#define  TRACE_WARNING         3                     ///< warning out,0 not output
#define  TRACE_OK              4                     ///< ok out,0 not output
#define  TRACE_NOTICE          5                     ///< notice out,0 not output
#define  TRACE_INFO            6                     ///< info out,0 not output
#define  TRACE_DEBUG           7                     ///< debug out,0 not output
#define  TRACE_TEMP            8                     ///< temporary out,0 not output
#define  TRACE_VALID_LEVEL     (TRACE_TEMP+10)      ///< 输出等级，1<= level && level <= TRACE_valid_level的trace全部输出

// 定义输出目标窗口，包括编译器输出窗口，控制台窗口，文件，tcp网络，com口，
#define  TRACE_TARGET_COMPILE      1                     ///< 0 not output to compile output,1 output to compile output
#define  TRACE_TARGET_CONSOLE      1                     ///< 0 not output to console,1 output to sonsole
#define  TRACE_TARGET_FILE         1                     ///< 0 not output to file, 1 output to file
#define  TRACE_TARGET_SOCKET       1                     ///< 0 not output to network, 1 output to network
#define  TRACE_TARGET_COM          1                     ///< 0 not output to com, 1 output to com

// 定义输出的log头，是否需要输出log头，以及log的哪些字段
#define  TRACE_HEAD                  1
#define  TRACE_HEAD_INDEX            1
#define  TRACE_HEAD_LEVEL            1
#define  TRACE_HEAD_LABEL            1
#define  TRACE_HEAD_THREAD_ID        1
#define  TRACE_HEAD_DATETIME         1
#define  TRACE_HEAD_RUNTIME          1
#define  TRACE_HEAD_FUNCTIONTIME     1
#define  TRACE_HEAD_PROCESS_NAME     1                     ///< display processname
#define  TRACE_HEAD_MODULE_NAME      1                     ///< display module namE
#define  TRACE_HEAD_FILE_NAME        1
#define  TRACE_HEAD_FUNCTION_NAME    1
#define  TRACE_HEAD_LINE             1
#define  TRACE_HEAD_ASYNC            1
#define  TRACE_HEAD_SYNC_LOCK        1
// log 标签
#define  TRACE_LABEL                ("kk")                ///< my output label

#define  TRACE_FILE_SIZE            (1000)
#define  TRACE_LIST_SIZE            10000
#define  ONE_TRACE_SIZE             1048576 // 一条trace预分配1M内存

