# 指定本示例支持的最低 CMake 版本。
cmake_minimum_required(VERSION 3.16)
# 创建一个只启用 C 语言的独立项目。
project(SinglyLinkedListDemo LANGUAGES C)

# 一个数据结构对应一个可执行目标：main 演示接口，实现文件承载算法。
add_executable(singly_linked_list
    src/main.c
    src/singly_linked_list.c
)
# PRIVATE 表示 include 路径只服务于当前目标。
target_include_directories(singly_linked_list PRIVATE include)
# 明确使用标准 C17，并关闭编译器私有语法扩展。
set_target_properties(singly_linked_list PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO
)
# MSVC 默认不一定按 UTF-8 读取中文源码，因此显式指定编码。
if(MSVC)
    target_compile_options(singly_linked_list PRIVATE /utf-8)
endif()
