//#define KLOG_HEADER_ONLY
#if 0
#ifdef KLOG_HEADER_ONLY
#include <filesystem>
namespace fs = std::filesystem;
inline static int temp_init_path = []()->int {
	// 设置当前工作目录
	fs::current_path("./KlogSDK/include");
	fs::current_path("./KlogSDK/sources");
	fs::current_path("./KlogSDK/sources/kcommonhpp");
	fs::current_path("../KlogSDK/sources/kcommonhpp");
	return 0;
	}();
#endif // KLOG_HEADER_ONLY
#endif
#include "tracemacr.h"