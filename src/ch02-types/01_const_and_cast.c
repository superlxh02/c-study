/**
 * @file    01_const_and_cast.c
 * @chapter 第二章 - 关于类型和变量，我还想说这些
 * @brief   演示 const 对象和显式算术类型转换。
 *
 * 直接编译：clang 01_const_and_cast.c -o const_and_cast
 */
#include <stdio.h>

int main(void)
{
    const int hours_per_day = 24; /* const 对象应在声明时给出有意义的初值 */
    int total_minutes = hours_per_day * 60;

    int sum = 17;
    int count = 5;
    double average = (double)sum / count; /* 先转换一个操作数，避免整数除法 */

    printf("一天有 %d 分钟\n", total_minutes);
    printf("平均值：%.2f\n", average);
    return 0;
}
