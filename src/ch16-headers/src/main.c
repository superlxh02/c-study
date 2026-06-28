/**
 * @file    main.c
 * @chapter 第十六章 - C语言头文件与代码文件组织
 * @section 一、头文件基础 → 3. 头文件里放什么
 * @brief   使用 mathutils 模块的主程序
 *
 * 演示如何通过 #include "mathutils.h" 来使用另一个模块的函数。
 * main.c 只需要知道函数声明，不需要知道函数的具体实现。
 * 编译时需要同时编译 main.c 和 mathutils.c，链接器会把它们合在一起。
 *
 * 编译命令（在项目根目录执行）：
 *   clang src/main.c src/mathutils.c -Iinclude -o ch16_mathutils.exe
 *
 *   -Iinclude  让编译器去 include/ 目录找 mathutils.h
 *   src/main.c src/mathutils.c  把所有源文件一起编译
 */

#include <stdio.h>            /* 系统头文件用尖括号 <> */
#include "mathutils.h"        /* 自己的头文件用双引号 "" */

int main(void)
{
    int x = 10, y = 5;

    /* 调用 add() —— 函数声明来自 mathutils.h，定义在 mathutils.c */
    printf("%d + %d = %d\n", x, y, add(x, y));

    /* 调用 subtract() —— 同样来自 mathutils 模块 */
    printf("%d - %d = %d\n", x, y, subtract(x, y));

    return 0;
}
