/**
 * =====================================================
 * 文件名: 04_dynamic_struct.c
 * 所属章节: 第十章
 * 对应小节: 四-1.2 动态结构体
 * 演示内容: 用 malloc 动态分配结构体数组，运行时决定记录数量
 * =====================================================
 *
 * 场景：处理不确定数量的学生记录。
 * 如果用固定大小的数组 struct Student students[100]，可能浪费或不够。
 * 用 malloc 动态分配刚好够用的数量，灵活且节省内存。
 *
 * 编译：gcc -Wall -o 04_dynamic_struct 04_dynamic_struct.c
 * 运行：./04_dynamic_struct
 */

#include <stdio.h>
#include <stdint.h>  /* SIZE_MAX */
#include <stdlib.h>   /* malloc, free */

/* =================================================================
 * 定义 Student 结构体
 *   每个 Student 包含姓名、年龄、成绩三个字段
 * ================================================================= */
struct Student
{
    char name[20];
    int  age;
    float score;
};

int main(void)
{
    int n;

    /* 步骤1：运行时获取学生人数 */
    printf("请输入学生人数：");
    if (scanf("%d", &n) != 1 || n <= 0 ||
        (size_t)n > SIZE_MAX / sizeof(struct Student))
    {
        fprintf(stderr, "人数无效或所需空间过大\n");
        return 1;
    }

    /* 步骤2：在堆上动态分配 n 个 Student 结构体的空间
     *   n * sizeof(struct Student) 计算出需要的总字节数
     *   malloc 返回的指针赋给 struct Student * */
    struct Student *students = malloc((size_t)n * sizeof(struct Student));
    if (students == NULL)
    {
        printf("内存分配失败！\n");
        return 1;
    }

    /* 步骤3：通过结构体指针访问成员并输入数据
     *   students[i] 是 *(students + i) 的语法糖，得到第 i 个结构体
     *   用点运算符 . 访问成员：students[i].name 等
     */
    for (int i = 0; i < n; i++)
    {
        printf("请输入第 %d 个学生的姓名：", i + 1);
        if (scanf("%19s", students[i].name) != 1)
        {
            fprintf(stderr, "姓名输入失败\n");
            free(students);
            return 1;
        }
        printf("年龄：");
        if (scanf("%d", &students[i].age) != 1)
        {
            fprintf(stderr, "年龄输入失败\n");
            free(students);
            return 1;
        }
        printf("成绩：");
        if (scanf("%f", &students[i].score) != 1)
        {
            fprintf(stderr, "成绩输入失败\n");
            free(students);
            return 1;
        }
    }

    /* 步骤4：输出所有学生信息 */
    printf("\n===== 学生信息 =====\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s，年龄 %d，成绩 %.1f\n",
               students[i].name, students[i].age, students[i].score);
    }

    /* 步骤5：释放堆内存 */
    free(students);
    students = NULL;

    return 0;
}

/* ================================================================
 * 运行示例（用户输入用 ← 标记）：
 *
 *   请输入学生人数：2
 *   请输入第 1 个学生的姓名：ZhangSan
 *   年龄：20
 *   成绩：88.5
 *   请输入第 2 个学生的姓名：LiSi
 *   年龄：21
 *   成绩：92.0
 *
 *   ===== 学生信息 =====
 *   ZhangSan，年龄 20，成绩 88.5
 *   LiSi，年龄 21，成绩 92.0
 *
 * 要点总结：
 *   ① 学生人数 n 运行时决定 → 不浪费、不溢出。
 *   ② students[i].name 是点运算符访问，因为 students[i] 本身就是结构体。
 *   ③ 用完后 free(students) 释放整块内存。
 * ================================================================ */
