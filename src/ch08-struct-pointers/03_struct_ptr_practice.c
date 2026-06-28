/**
 * @file    03_struct_ptr_practice.c
 * @chapter 第八章 - 结构体指针
 * @section 二.2 - 动手练习（结构体指针综合）
 * @brief   综合练习：通过指针访问结构体、修改成员、遍历结构体数组。
 *
 * 练习内容：
 *   练习1 - 通过结构体指针访问并输出 Book 信息
 *   练习2 - 通过指针修改结构体成员
 *   练习3 - 用指针遍历结构体数组
 *
 * 附加挑战（在注释中给出了实现提示）：
 *   挑战1 - 写 printStudent 函数，参数为结构体指针，用 -> 输出
 *   挑战2 - malloc 动态分配结构体，指针赋值，最后 free
 *   挑战3 - 改用下标法完成同样遍历，比较两种写法
 */

#include <stdio.h>

/* 定义图书结构体 */
struct Book
{
    char title[50];   /* 书名 */
    int pages;        /* 页数 */
    float price;      /* 价格 */
};

int main(void)
{
    /*====================================================================
     * 练习1：通过指针访问结构体
     * 创建 Book 变量和指向它的指针，用 -> 输出所有成员。
     *====================================================================*/
    printf("===== 练习1：通过指针访问结构体 =====\n\n");

    struct Book book1 = {"C语言教程", 320, 45.5f};
    struct Book *p = &book1;            /* p 指向 book1 */

    printf("通过 p-> 访问 Book 信息：\n");
    printf("  书名：%s\n", p->title);    /* 等价于 (*p).title */
    printf("  页数：%d\n", p->pages);
    printf("  价格：%.1f 元\n", p->price);

    /*====================================================================
     * 练习2：通过指针修改成员
     * 使用 -> 直接修改结构体成员的值。
     *====================================================================*/
    printf("\n===== 练习2：通过指针修改成员 =====\n\n");

    p->price = 39.9f;  /* f 后缀表示 float 常量，避免从 double 收窄 */
    printf("优惠后价格：%.1f 元\n", p->price);
    printf("(book1.price 也变为 %.1f 元，因为修改的就是原变量)\n\n", book1.price);

    /*====================================================================
     * 练习3：用指针遍历结构体数组
     * 声明 Book 数组，用指针 ptr 从头遍历到尾。
     * ptr++ 自动跳过整个 struct Book。
     *====================================================================*/
    printf("===== 练习3：指针遍历结构体数组 =====\n\n");

    struct Book books[3] = {
        {"C语言入门", 280, 35.0f},
        {"数据结构", 450, 59.0f},
        {"算法导论", 600, 79.5f}
    };

    struct Book *ptr = books;  /* ptr 指向 books[0] */
    for (int i = 0; i < 3; i++)
    {
        printf("《%s》 %d页  %.1f元\n", ptr->title, ptr->pages, ptr->price);
        ptr++;  /* ptr 移到下一个 struct Book，自动跳过整个结构体 */
    }

    printf("\n========================================\n");
    printf("挑战题提示（请自行实现）：\n");
    printf("  1. 写 printStudent 函数：\n");
    printf("     void printStudent(struct Student *s) {\n");
    printf("         printf(\"%%s %%d %%.1f\\n\", s->name, s->age, s->score);\n");
    printf("     }\n");
    printf("  2. 动态分配结构体：\n");
    printf("     struct Student *p = malloc(sizeof(struct Student));\n");
    printf("     p->age = 20; ... free(p);\n");
    printf("  3. 下标法遍历：\n");
    printf("     for(i=0;i<3;i++) printf(\"%%s\\n\", books[i].title);\n");

    return 0;
}
