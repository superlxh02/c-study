# 指定本示例支持的最低 CMake 版本。
cmake_minimum_required(VERSION 3.16)
# 创建一个只启用 C 语言的独立项目。
project(DoublyLinkedListDemo LANGUAGES C)

# main.c 只演示调用；双链表算法位于独立实现文件中。
add_executable(doubly_linked_list src/main.c src/doubly_linked_list.c)
# 把公共头文件目录加入当前目标的搜索路径。
target_include_directories(doubly_linked_list PRIVATE include)
# 要求标准 C17，避免示例无意依赖编译器扩展。
set_target_properties(doubly_linked_list PROPERTIES
    C_STANDARD 17 C_STANDARD_REQUIRED YES C_EXTENSIONS NO
)
# MSVC 默认不一定按 UTF-8 读取中文源码，因此显式指定编码。
if(MSVC)
    target_compile_options(doubly_linked_list PRIVATE /utf-8)
endif()
