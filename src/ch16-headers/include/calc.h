/**
 * @file    calc.h
 * @chapter 第十六章 - C语言头文件与代码文件组织
 * @section 二、多文件项目组织 → 2. 动手练习
 * @brief   计算工具模块的头文件（使用 #pragma once）
 *
 * 演示头文件保护的另一种写法：#pragma once。
 * 这种方式比 #ifndef 更简洁，大多数现代编译器都支持。
 */

#pragma once                    /* 告诉编译器：本文件在整个编译单元中只包含一次 */

/* ===== 函数声明 ===== */

/** 计算整数 x 的平方 */
int square(int x);

/** 计算整数 x 的立方 */
int cube(int x);
