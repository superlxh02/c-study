/**
 * @file    01_macro_safety.c
 * @chapter 第十四章 - 宏
 * @brief   展示带参数宏的括号规则，并用函数避免重复求值。
 *
 * 直接编译：clang 01_macro_safety.c -o macro_safety
 */
#include <stdio.h>

#define SQUARE(value) ((value) * (value))

static int square_int(int value)
{
    return value * value;
}

int main(void)
{
    int a = 1 + 2;
    printf("SQUARE(1 + 2) = %d\n", SQUARE(1 + 2));

    /* a++ 具有副作用，不能传给会重复使用参数的 SQUARE 宏。 */
    printf("square_int(a++) = %d\n", square_int(a++));
    printf("调用后 a = %d\n", a);
    return 0;
}
