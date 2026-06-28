/**
 * @file    01_storage_duration.c
 * @chapter 第十二章 - 生命周期
 * @brief   对比自动存储期对象与静态存储期对象。
 *
 * 直接编译：clang 01_storage_duration.c -o storage_duration
 */
#include <stdio.h>

static int next_call_number(void)
{
    /* count 具有静态存储期，但名字只在本函数的块作用域中可见。 */
    static int count = 0;
    count++;
    return count;
}

int main(void)
{
    /* local 具有自动存储期，每次进入此块都会创建一个新的对象。 */
    int local = 42;
    printf("局部对象：%d\n", local);
    printf("调用次数：%d\n", next_call_number());
    printf("调用次数：%d\n", next_call_number());
    return 0;
}
