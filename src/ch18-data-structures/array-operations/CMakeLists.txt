# 本项目最低需要 CMake 3.16，以便稳定使用 C_STANDARD 等目标属性。
cmake_minimum_required(VERSION 3.16)
# 声明一个只使用 C 语言的独立示例项目。
project(ArrayOperationsDemo LANGUAGES C)

# 将演示入口与数组算法实现共同编译成可执行程序。
add_executable(array_operations src/main.c src/array_operations.c)
# 头文件目录只提供给当前目标，不向其他目标传播。
target_include_directories(array_operations PRIVATE include)
# 固定使用标准 C17，并关闭编译器私有扩展，保证示例可移植。
set_target_properties(array_operations PROPERTIES
    C_STANDARD 17 C_STANDARD_REQUIRED YES C_EXTENSIONS NO
)
# MSVC 需要显式启用 UTF-8，才能正确处理源码中的中文字符串。
if(MSVC)
    target_compile_options(array_operations PRIVATE /utf-8)
endif()
