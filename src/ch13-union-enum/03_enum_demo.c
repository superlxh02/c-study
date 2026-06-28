/**
 * @file    03_enum_demo.c
 * @chapter 第十三章 - 共用体与枚举
 * @section 二.1.3 - 枚举语法示例
 * @brief   演示枚举（enum）的核心用法：用有意义的标识符代替"魔法数字"。
 *
 * 核心知识点：
 *   1. enum 给一组相关整型常量起有意义的名字
 *   2. 默认第一个标识符值为 0，后面依次 +1
 *   3. 可以手动指定值，未指定的在前一个基础上 +1
 *   4. 枚举是与某种整数类型兼容的独立类型，可提高代码可读性
 */

#include <stdio.h>

/* 定义星期枚举
 * 默认从 0 开始：MONDAY=0, TUESDAY=1, ..., SUNDAY=6 */
enum Weekday
{
    MONDAY,     /* 0 —— 星期一 */
    TUESDAY,    /* 1 —— 星期二 */
    WEDNESDAY,  /* 2 —— 星期三 */
    THURSDAY,   /* 3 —— 星期四 */
    FRIDAY,     /* 4 —— 星期五 */
    SATURDAY,   /* 5 —— 星期六 */
    SUNDAY      /* 6 —— 星期日 */
};

int main(void)
{
    /*--------------------------------------------------------------------
     * 声明枚举变量并赋值
     * today 的值是 WEDNESDAY，即整数 2
     *--------------------------------------------------------------------*/
    enum Weekday today = WEDNESDAY;

    printf("===== 枚举 enum 演示 =====\n\n");

    /* 这些枚举值都能表示为 int，经整数提升后可用 %d 输出。 */
    printf("today = %d\n", today);  /* 输出 2 */

    /* 用有意义的标识符做判断，可读性远好于 if (today == 2) */
    if (today == WEDNESDAY)
    {
        printf("今天是星期三\n");
    }

    /* 遍历所有星期 */
    printf("\n所有星期枚举值：\n");
    printf("  MONDAY    = %d\n", MONDAY);
    printf("  TUESDAY   = %d\n", TUESDAY);
    printf("  WEDNESDAY = %d\n", WEDNESDAY);
    printf("  THURSDAY  = %d\n", THURSDAY);
    printf("  FRIDAY    = %d\n", FRIDAY);
    printf("  SATURDAY  = %d\n", SATURDAY);
    printf("  SUNDAY    = %d\n", SUNDAY);

    printf("\n枚举的优点：\n");
    printf("  - 可读性：if (today == FRIDAY) 远比 if (today == 4) 清晰\n");
    printf("  - 组织性：相关常量归为一组，便于管理\n");
    printf("  - 类型提示：枚举类型能帮助编译器发现部分可疑用法\n");

    return 0;
}
