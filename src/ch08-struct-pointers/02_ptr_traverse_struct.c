/**
 * @file    02_ptr_traverse_struct.c
 * @chapter 第八章 - 结构体指针
 * @section 一.3 - 结构体数组与指针的遍历
 * @brief   演示用指针遍历结构体数组：p 指向首元素，每次 p++ 自动跳过整个结构体。
 *
 * 核心知识点：
 *   1. 结构体数组名退化为指向首元素的指针
 *   2. p++ 使指针增加 sizeof(struct Student) 字节，自动指向下一个结构体
 *   3. p->成员 访问当前指向的结构体的成员
 */

#include <stdio.h>

/* 定义学生结构体 */
struct Student
{
    char name[20];   /* 姓名 */
    int age;         /* 年龄 */
    float score;     /* 成绩 */
};

int main(void)
{
    /* 创建结构体数组，包含 3 个学生的信息 */
    struct Student students[3] = {
        {"小明", 18, 92.5},
        {"小红", 19, 88.0},
        {"小刚", 18, 95.5}
    };

    printf("===== 指针遍历结构体数组 =====\n\n");

    /*--------------------------------------------------------------------
     * 用指针遍历结构体数组
     * students 是数组名，在此退化为指向 students[0] 的指针
     * 类型为 struct Student *
     *--------------------------------------------------------------------*/
    struct Student *p = students;  /* p 指向数组首元素 students[0] */

    for (int i = 0; i < 3; i++)
    {
        /* p->name 等价于 students[i].name */
        printf("学生%d：%s，年龄 %d，成绩 %.1f\n",
               i + 1, p->name, p->age, p->score);

        /* p++ 使指针增加 sizeof(struct Student) 字节
         * 自动跳到下一个结构体的起始地址 */
        p++;  /* 指针移到下一个结构体 */
    }

    printf("\n===== 对比：下标法遍历 =====\n\n");

    /* 同样的结果可以用下标法实现（不需要指针） */
    for (int i = 0; i < 3; i++)
    {
        printf("学生%d：%s，年龄 %d，成绩 %.1f\n",
               i + 1, students[i].name, students[i].age, students[i].score);
    }

    printf("\n两种写法输出完全相同，指针法在处理动态数组时更加灵活。\n");

    return 0;
}
