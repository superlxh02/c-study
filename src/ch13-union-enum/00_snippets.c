/**
 * @file    00_snippets.c
 * @chapter 第十三章 - 共用体与枚举
 * @section 二.1.5~1.6 - 枚举与 switch 配合 / 手动指定枚举值 / sizeof union
 * @brief   演示：枚举与 switch 经典配合、手动指定枚举值、共用体内存大小。
 *
 * 本文件汇总了第十三章中分散在各小节的小代码片段。
 */

#include <stdio.h>

/* 定义星期枚举 */
enum Weekday
{
    MONDAY,     /* 0 */
    TUESDAY,    /* 1 */
    WEDNESDAY,  /* 2 */
    THURSDAY,   /* 3 */
    FRIDAY,     /* 4 */
    SATURDAY,   /* 5 */
    SUNDAY      /* 6 */
};

/* 共用体：所有成员共享同一块内存 */
union Data
{
    int i;      /* 4 字节 */
    float f;    /* 4 字节 */
    char c;     /* 1 字节 */
};

int main(void)
{
    /*====================================================================
     * 片段1：枚举与 switch 经典配合（第十三章 二.1.5）
     * 用 switch 对枚举值做分支判断，可读性远好于裸数字。
     * 多个 case 可以合并（如工作日 / 周末分组）。
     *====================================================================*/
    printf("===== 片段1：枚举与 switch 配合 =====\n");
    {
        enum Weekday today = SATURDAY;

        switch (today)
        {
            case MONDAY:
            case TUESDAY:
            case WEDNESDAY:
            case THURSDAY:
            case FRIDAY:
                printf("工作日\n");
                break;
            case SATURDAY:
            case SUNDAY:
                printf("周末\n");
                break;
            default:
                break;
        }
    }
    printf("\n");

    /*====================================================================
     * 片段2：手动指定枚举值（第十三章 二.1.4）
     * 可以手动指定某个标识符的值，后续标识符在此基础上 +1。
     *====================================================================*/
    printf("===== 片段2：手动指定枚举值 =====\n");
    {
        /* 方式1：完全手动指定 */
        enum Color
        {
            RED = 1,
            GREEN = 5,
            BLUE = 10
        };
        printf("Color: RED=%d, GREEN=%d, BLUE=%d\n", RED, GREEN, BLUE);

        /* 方式2：部分手动指定，其余自动递增 */
        enum ErrorCode
        {
            OK = 0,
            FILE_NOT_FOUND,      /* 1 —— 自动在前一个基础上 +1 */
            PERMISSION_DENIED,   /* 2 */
            UNKNOWN = 99         /* 手动指定跳转 */
        };
        printf("ErrorCode: OK=%d, FILE_NOT_FOUND=%d, PERMISSION_DENIED=%d, UNKNOWN=%d\n",
               OK, FILE_NOT_FOUND, PERMISSION_DENIED, UNKNOWN);
    }
    printf("\n");

    /*====================================================================
     * 片段3：sizeof(union) —— 共用体内存大小（第十三章 一.1.4）
     * 共用体的大小至少能容纳最大的成员，同时要满足内存对齐要求。
     * 本示例中 int=4, float=4, char=1，所以 sizeof 通常为 4。
     *====================================================================*/
    printf("===== 片段3：sizeof(union) =====\n");
    {
        printf("sizeof(union Data) = %d\n", (int)sizeof(union Data));
        printf("  (成员：int=4, float=4, char=1，取最大者并满足对齐 => 通常为4)\n");
        printf("  所有成员从同一地址开始，空间只要装得下最大的那个就行。\n");
    }

    return 0;
}
