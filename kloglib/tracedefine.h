#pragma once

// 是否生成trace 函数
#define  TRACE_OUT             1                     ///< 0 not output log, 1 output log
#define  TRACK_OUT             1                     ///< whether output trace of function called
// 是否使用glog
#define  USE_GLOG              1

// 是否使用线程输出trace
#define  TRACE_ASYNC           1                     ///< 0 not output log, 1 output log

// 预定义6种trace等级，数字越大输出等级越低
#define  TRACE_ERROR           1                     ///< error out,0 not output
#define  TRACE_WARNING         2                     ///< warning out,0 not output
#define  TRACE_OK              3                     ///< ok out,0 not output
#define  TRACE_NOTICE          4                     ///< notice out,0 not output
#define  TRACE_INFO            5                     ///< info out,0 not output
#define  TRACE_DEBUG           6                     ///< debug out,0 not output
#define  TRACE_TEMP            7                     ///< temporary out,0 not output
#define  TRACE_OUT_LEVEL       (TRACE_TEMP+10)      ///< 输出等级，1<= level && level <= TRACE_OUT_LEVEL的trace全部输出

// 定义输出目标窗口，包括编译器输出窗口，控制台窗口，文件，tcp网络，com口，
#define  TRACE_COMPILE         1                     ///< 0 not output to compile output,1 output to compile output
#define  TRACE_CONSOLE         1                     ///< 0 not output to console,1 output to sonsole
#define  TRACE_FILE            1                     ///< 0 not output to file, 1 output to file
#define  TRACE_SOCKET          1                     ///< 0 not output to network, 1 output to network
#define  TRACE_PUTTY           1                     ///< 0 not output to com, 1 output to com
// 定义3种输出范围，模块内输出(log内存在模块之间独立)，进程内输出(log在模块之间按先后顺序输出，进程共享一个log内存），进程间输出（进程间共享一个log内存)
#define  TRACE_MODULE          1                     ///< log out scope in the module
#define  TRACE_PROCESS         0                     ///< log out scope in the process
#define  TRACE_PROCESS_ALL     0                     ///< log out scope in all process
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

#define  TRACE_FILE_SIZE            (1024 * 1024 * 100)
#define  TRACE_LIST_SIZE            10000

