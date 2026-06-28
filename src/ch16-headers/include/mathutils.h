/**
 * @file    mathutils.h
 * @chapter 第十六章 - C语言头文件与代码文件组织
 * @section 一、头文件基础 → 3. 头文件里放什么
 * @brief   数学工具模块的头文件（说明书）
 *
 * 演示头文件的经典写法：使用 #ifndef / #define / #endif 包含保护，
 * 声明模块对外提供的函数接口。
 */

#ifndef MATHUTILS_H       /* 如果没有定义 MATHUTILS_H 这个宏，就执行下面内容 */
#define MATHUTILS_H       /* 定义 MATHUTILS_H 宏，防止下次再被包含 */

/* ===== 函数声明（只有函数头，没有函数体）===== */

/** 计算两个整数的和 */
int add(int a, int b);

/** 计算两个整数的差（a - b） */
int subtract(int a, int b);

#endif                     /* 包含保护结束标记 */
