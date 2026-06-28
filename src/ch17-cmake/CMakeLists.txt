# ============================================================================
# @file     CMakeLists.txt
# @chapter  第十七章 - C语言统一项目构建系统——CMake初识
# @section  三、进阶与总结 → 3. 动手练习
# @brief    CMake 构建配置文件
#
# CMake 是构建系统生成器，它不直接编译代码，而是根据本文件生成
# 给底层构建工具（如 Ninja）使用的构建指令文件（build.ninja）。
#
# 构建流程：
#   1. cmake -S . -B build -G Ninja     ← 配置并生成 build.ninja
#   2. cmake --build build              ← 调用 Ninja 执行编译
#   3. build\strtools_demo.exe          ← 运行生成的可执行文件
# ============================================================================

# 指定 CMake 最低版本要求
cmake_minimum_required(VERSION 3.16)

# 定义项目名称和使用的编程语言
# LANGUAGES C 明确告诉 CMake 本项目只使用 C 语言
project(StrToolsDemo LANGUAGES C)

# 用指定的源文件生成可执行文件
# 目标名: strtools_demo
# 源文件: src/main.c 和 src/strtools.c
add_executable(strtools_demo
    src/main.c
    src/strtools.c
)

# 给 strtools_demo 这个目标添加头文件搜索路径
# PRIVATE 表示这个路径仅对 strtools_demo 可见
# 等价于手写命令中的：clang ... -Iinclude
target_include_directories(strtools_demo PRIVATE include)

# 明确要求标准 C17，并关闭各编译器自己的非标准语法扩展。
set_target_properties(strtools_demo PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO
)

# MSVC 默认按当前 Windows 代码页读取源码；本教程源码统一保存为 UTF-8。
if(MSVC)
    target_compile_options(strtools_demo PRIVATE /utf-8)
endif()
