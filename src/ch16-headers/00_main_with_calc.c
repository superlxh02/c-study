/**
 * @file    00_main_with_calc.c
 * @chapter 第十六章 - C语言头文件与代码文件组织
 * @section 二、多文件项目组织 → 2. 动手练习
 * @brief   使用 calc 模块的主程序
 *
 * 演示多文件项目中的 main(void) 函数如何引用 calc 模块。
 * 本文件需要和 src/calc.c 一起编译。
 *
 * 编译命令（在 ch16-headers/ 目录下执行）：
 *   clang 00_main_with_calc.c src/calc.c -Iinclude -o calc_demo.exe
 *
 * 注意：本文件放在 ch16-headers/ 根目录（模拟 practice/ 目录结构），
 * 而模块文件在 src/ 和 include/ 子目录中。
 */

#include <stdio.h>         /* 系统头文件：printf */
#include "calc.h"          /* 自定义模块头文件：square、cube */

int main(void)
{
    int n = 5;

    /* 调用 calc 模块的 square() 函数 */
    printf("%d 的平方 = %d\n", n, square(n));

    /* 调用 calc 模块的 cube() 函数 */
    printf("%d 的立方 = %d\n", n, cube(n));

    return 0;
}
