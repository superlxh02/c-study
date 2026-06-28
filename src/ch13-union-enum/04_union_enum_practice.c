/**
 * @file    04_union_enum_practice.c
 * @chapter 第十三章 - 共用体与枚举
 * @section 三.2 - 动手练习（共用体与枚举综合）
 * @brief   综合练习：共用体与枚举配合（带标签的联合体）、枚举月份天数、sizeof union。
 *
 * 练习内容：
 *   练习1 - 共用体与枚举配合：使用 Shape 共用体和 ShapeType 枚举
 *           根据类型标签选择正确的成员来读取
 *   练习2 - 枚举表示月份，用 switch 输出各月天数
 *   练习3 - 验证 sizeof(union Shape)
 *
 * 附加挑战（在注释中给出了实现提示）：
 *   挑战1 - 定义 union Number { int; float; double; }，观察覆盖效果
 *   挑战2 - 用枚举表示交通灯 (RED, YELLOW, GREEN)，switch 输出动作
 *   挑战3 - 将 Student 结构体与年级枚举结合
 */

#include <stdio.h>

/* 定义表示图形的共用体
 * 圆只需要半径，矩形需要宽和高
 * 它们不会同时使用，所以用共用体节省内存 */
union Shape
{
    double radius;               /* 圆：半径 */
    struct { double w, h; } rect; /* 矩形：宽和高（匿名内嵌结构体） */
};

/* 定义图形类型枚举——作为"标签"告诉程序员当前 union 中存的是什么 */
enum ShapeType { CIRCLE, RECTANGLE };

int main(void)
{
    /*====================================================================
     * 练习1：共用体与枚举配合（带标签的联合体）
     * 用 ShapeType 枚举标记当前 Shape 共用体中存放的是圆还是矩形
     *====================================================================*/
    printf("===== 练习1：共用体与枚举配合 =====\n\n");

    enum ShapeType type = CIRCLE;  /* 当前图形类型标签 */
    union Shape s;                 /* 图形数据 */

    if (type == CIRCLE)
    {
        /* 圆形：使用 radius 成员 */
        s.radius = 5.0;
        printf("圆形，半径 = %.2f\n", s.radius);
        printf("面积 = π × r² = %.2f\n", 3.14 * s.radius * s.radius);
    }
    else if (type == RECTANGLE)
    {
        /* 矩形：使用 rect 成员 */
        s.rect.w = 3.0;
        s.rect.h = 4.0;
        printf("矩形，宽 = %.2f, 高 = %.2f\n", s.rect.w, s.rect.h);
        printf("面积 = w × h = %.2f\n", s.rect.w * s.rect.h);
    }

    /*====================================================================
     * 练习2：用枚举表示月份，输出各月天数
     * 通过 switch 语句将月份映射到对应的天数
     *====================================================================*/
    printf("\n===== 练习2：枚举表示月份 =====\n\n");

    /* 定义月份枚举：JAN=1，后面的自动递增（FEB=2, MAR=3...） */
    enum Month { JAN=1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
    enum Month m = MAR;  /* 三月 */

    printf("%d 月有 ", m);
    switch (m)
    {
        /* 31 天的月份 */
        case JAN: case MAR: case MAY: case JUL: case AUG: case OCT: case DEC:
            printf("31 天\n");
            break;
        /* 30 天的月份 */
        case APR: case JUN: case SEP: case NOV:
            printf("30 天\n");
            break;
        /* 二月：平年28天，闰年29天 */
        case FEB:
            printf("28 或 29 天\n");
            break;
        default:
            printf("无效月份\n");
    }

    /*====================================================================
     * 练习3：共用体内存大小
     * sizeof(union Shape) 至少能容纳最大的成员
     * 最大成员是 struct { double w, h; } 即 2 个 double = 16 字节
     *====================================================================*/
    printf("\n===== 练习3：sizeof(union) =====\n\n");

    printf("sizeof(union Shape) = %d\n", (int)sizeof(union Shape));
    printf("  (最大成员：struct { double w, h; }，2×8=16 字节)\n");
    printf("  所有成员共享同一块内存，大小取最大者并满足对齐。\n");

    printf("\n========================================\n");
    printf("挑战题提示（请自行实现）：\n");
    printf("  1. union Number { int i; float f; double d; };\n");
    printf("     依次赋值观察各成员被覆盖后的值\n");
    printf("  2. enum TrafficLight { RED, YELLOW, GREEN };\n");
    printf("     switch(light) { case RED: printf(\"停\\n\"); break; ... }\n");
    printf("  3. struct Student { ...; enum Grade grade; };\n");
    printf("     其中 enum Grade { FRESHMAN, SOPHOMORE, JUNIOR, SENIOR };\n");
    printf("     printf 时根据 grade 输出对应的中文年级名\n");

    return 0;
}
