/**
 * =====================================================
 * 文件名: 18_square_function.c
 * 所属章节: 第一章 - C语言核心基础语法
 * 对应小节: 七、2. 为什么需要自定义函数
 * 演示内容: 自定义函数的定义和调用
 *           squarePlusFive 函数计算 "x的平方加5"
 *           展示了函数封装的三大好处：避免重复、代码清晰、易于修改
 * =====================================================
 */

#include <stdio.h>

/*
 * 自定义函数：squarePlusFive
 * 功能：计算 x 的平方加 5，即 f(x) = x^2 + 5
 *
 * 语法拆解：
 *   int              —— 返回值类型，说明函数返回一个整数
 *   squarePlusFive   —— 函数名，调用时使用
 *   (int x)          —— 参数列表，接收一个整数 x 作为输入
 *   { ... }          —— 函数体，包含要执行的代码
 *   return result;   —— 把计算结果返回给调用者
 */
int squarePlusFive(int x)
{
    int result = x * x + 5;     /* x * x 计算平方，+ 5 加上常数 */
    return result;              /* 将计算结果返回给调用者 */
}

int main(void)
{
    /* 调用 squarePlusFive 函数，传入实际参数（实参）
     * 函数调用语法：函数名(实参1, 实参2, ...)
     *
     * squarePlusFive(3)  —— 传入 3，计算 3*3+5 = 14
     * squarePlusFive(7)  —— 传入 7，计算 7*7+5 = 54
     * squarePlusFive(10) —— 传入10，计算10*10+5 = 105 */
    int result1 = squarePlusFive(3);   /* result1 = 14 */
    int result2 = squarePlusFive(7);   /* result2 = 54 */
    int result3 = squarePlusFive(10);  /* result3 = 105 */

    /* 输出每个计算结果 */
    printf("f(3) = %d\n", result1);
    printf("f(7) = %d\n", result2);
    printf("f(10) = %d\n", result3);

    return 0;
}

/* ============================================================
 * 编译: clang square_function.c -o square_function.exe
 * 运行: square_function.exe
 *
 * 预期输出:
 *   f(3) = 14
 *   f(7) = 54
 *   f(10) = 105
 *
 * 使用函数的好处：
 *   1. 避免重复代码 —— 同样的逻辑只需写一次，可以多次调用
 *   2. 代码更清晰 —— 把复杂问题拆分成小块的函数
 *   3. 易于修改 —— 只需要改函数内部，所有调用处都会生效
 *
 * 注意：函数定义写在 main 函数前面，这样 main 调用时
 *       编译器已经"认识"了这个函数。如果写在 main 后面，
 *       需要先做函数声明（见 20_forward_declaration.c）
 * ============================================================
 */
