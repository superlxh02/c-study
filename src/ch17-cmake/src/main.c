/**
 * @file    main.c
 * @chapter 第十七章 - C语言统一项目构建系统——CMake初识
 * @section 三、进阶与总结 → 3. 动手练习
 * @brief   使用 strtools 模块的主程序
 *
 * 通过 CMake 构建系统来编译这个多文件项目。
 * 不使用手写的 clang 命令，而是用 CMakeLists.txt 描述项目结构。
 *
 * 构建步骤（在 ch17-cmake/ 目录下执行）：
 *   1. 配置与生成： cmake -S . -B build -G Ninja
 *   2. 编译：       cmake --build build
 *   3. 运行：       build\strtools_demo.exe
 */

#include <stdio.h>             /* 系统头文件：printf */
#include "strtools.h"          /* 自定义模块：my_strlen */

int main(void)
{
    char *msg = "Hello, CMake!";

    /* 调用 my_strlen() 计算字符串长度 */
    printf("字符串 \"%s\" 的长度是 %d\n", msg, my_strlen(msg));

    return 0;
}
