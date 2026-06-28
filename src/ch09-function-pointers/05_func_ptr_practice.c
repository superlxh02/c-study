/**
 * =====================================================
 * 文件名: 05_func_ptr_practice.c
 * 所属章节: 第九章
 * 对应小节: 三-3 动手练习（compute 函数）
 * 演示内容: 用 typedef 定义函数指针类型，通过 compute 函数灵活调度运算
 * =====================================================
 *
 * 设计思路：
 *   ① typedef 定义 Operation 函数指针类型（接收两个 int，返回 int）
 *   ② 编写多个具体运算函数（add / multiply / max / subtract）
 *   ③ compute 函数接收两个数与一个 Operation，返回运算结果
 *   ④ main 通过传入不同的 Operation，用同一行 compute 调用实现不同运算
 *
 * 编译：gcc -Wall -o 05_func_ptr_practice 05_func_ptr_practice.c
 * 运行：./05_func_ptr_practice
 */

#include <stdio.h>

/* =================================================================
 * 定义函数指针类型别名 Operation
 *   Operation 是"指向 返回int、接收两个int 的函数"的类型
 *   此后声明函数指针变量时可以写 Operation op; 更简洁
 * ================================================================= */
typedef int (*Operation)(int, int);

/* =================================================================
 * 运算函数集合（签名均为 int (int, int)，匹配 Operation）
 * ================================================================= */

/* 加法 */
int add(int a, int b)
{
    return a + b;
}

/* 乘法 */
int multiply(int a, int b)
{
    return a * b;
}

/* 取最大值 */
int max(int a, int b)
{
    return a > b ? a : b;
}

/* 减法（练习扩展：原题未给出，这里自行添加） */
int subtract(int a, int b)
{
    return a - b;
}

/* =================================================================
 * compute — 通用计算函数
 *   接收两个操作数 x, y 和一个操作函数指针 op，
 *   返回 op(x, y) 的结果。
 *
 * compute 本身完全不知道具体是什么运算，
 * 运算逻辑由调用者通过 op 参数注入。
 * ================================================================= */
int compute(int x, int y, Operation op)
{
    return op(x, y);    /* 回调：调用传入的运算函数 */
}

int main(void)
{
    int a = 12, b = 6;

    printf("计算 a = %d, b = %d\n\n", a, b);

    /* 传入不同的回调函数（Operation），得到不同的计算结果 */

    /* 加法：compute 内部调用 add(12, 6) */
    printf("加法结果：%d\n", compute(a, b, add));

    /* 乘法：compute 内部调用 multiply(12, 6) */
    printf("乘法结果：%d\n", compute(a, b, multiply));

    /* 最大值：compute 内部调用 max(12, 6) */
    printf("最大值结果：%d\n", compute(a, b, max));

    /* 减法：compute 内部调用 subtract(12, 6) */
    printf("减法结果：%d\n", compute(a, b, subtract));

    return 0;
}

/* ================================================================
 * 预期输出：
 *
 *   计算 a = 12, b = 6
 *
 *   加法结果：18
 *   乘法结果：72
 *   最大值结果：12
 *   减法结果：6
 *
 * 设计总结：
 *   ① typedef int (*Operation)(int, int); 将复杂的函数指针语法简化。
 *   ② compute 函数 = 框架 / 调度器，不关心具体操作。
 *   ③ add / multiply / max / subtract = 策略，可任意替换和扩展。
 *   ④ 这是"策略模式"在 C 语言中的朴素实现。
 * ================================================================ */
