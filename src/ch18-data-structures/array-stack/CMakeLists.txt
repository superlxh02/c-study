# 指定本示例支持的最低 CMake 版本。
cmake_minimum_required(VERSION 3.16)
# 创建一个只启用 C 语言的独立项目。
project(ArrayStackDemo LANGUAGES C)

# 将演示入口和栈实现共同编译成一个可执行程序。
add_executable(array_stack src/main.c src/array_stack.c)
# 把公共头文件目录加入当前目标的搜索路径。
target_include_directories(array_stack PRIVATE include)
# 统一所有平台上的 C 语言标准要求。
set_target_properties(array_stack PROPERTIES
    C_STANDARD 17 C_STANDARD_REQUIRED YES C_EXTENSIONS NO
)
# MSVC 默认不一定按 UTF-8 读取中文源码，因此显式指定编码。
if(MSVC)
    target_compile_options(array_stack PRIVATE /utf-8)
endif()
