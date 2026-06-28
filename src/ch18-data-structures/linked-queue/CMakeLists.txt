# 指定本示例支持的最低 CMake 版本。
cmake_minimum_required(VERSION 3.16)
# 创建一个只启用 C 语言的独立项目。
project(LinkedQueueDemo LANGUAGES C)

# 公共声明放在 include，队列实现与 main 分别编译。
add_executable(linked_queue src/main.c src/linked_queue.c)
# 把公共头文件目录加入当前目标的搜索路径。
target_include_directories(linked_queue PRIVATE include)
# 统一使用标准 C17，并禁止依赖编译器私有扩展。
set_target_properties(linked_queue PROPERTIES
    C_STANDARD 17 C_STANDARD_REQUIRED YES C_EXTENSIONS NO
)
# MSVC 默认不一定按 UTF-8 读取中文源码，因此显式指定编码。
if(MSVC)
    target_compile_options(linked_queue PRIVATE /utf-8)
endif()
