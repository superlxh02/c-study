/**
 * @file    03_fprintf_fscanf.c
 * @chapter 第十五章 - 文件IO
 * @section 二.3.3 - 格式化读写：fprintf / fscanf 示例
 * @brief   演示用 fprintf 将结构体信息格式化写入文件，再用 fscanf 读回。
 *
 * 核心知识点：
 *   1. fprintf(FILE*, 格式串, ...) —— 用法同 printf，多了一个 FILE* 参数
 *   2. fscanf(FILE*, 格式串, ...) —— 用法同 scanf，多了一个 FILE* 参数
 *   3. fscanf 以空白字符（空格、换行、制表符）分隔数据
 *   4. 注意：fscanf 读字符串时，名字中不能有空格（否则会截断）
 *   5. 文件中内容是人类可读的文本
 */

#include <stdio.h>

/* 学生结构体 */
struct Student
{
    char name[20];   /* 姓名（不能包含空格，否则 fscanf 会截断） */
    int age;         /* 年龄 */
    float score;     /* 成绩 */
};

int main(void)
{
    /* 原始学生数据 */
    struct Student s1 = {"小明", 18, 92.5};

    printf("===== fprintf / fscanf 格式化读写 =====\n\n");
    printf("原始数据：%s %d %.1f\n\n", s1.name, s1.age, s1.score);

    /*====================================================================
     * 第一步：用 fprintf 将结构体信息格式化写入文本文件
     *
     * fprintf 和 printf 用法几乎一样：
     *   printf(格式, ...)       → 输出到屏幕 (stdout)
     *   fprintf(fp, 格式, ...)  → 输出到文件
     *
     * 以 "w" 模式打开：文件存在则清空，不存在则创建
     *====================================================================*/
    FILE *fp = fopen("student.txt", "w");
    if (fp == NULL)
    {
        printf("无法创建文件 student.txt\n");
        return 1;
    }

    /* 用空格分隔各字段，方便后续 fscanf 读取 */
    fprintf(fp, "%s %d %.1f\n", s1.name, s1.age, s1.score);
    fclose(fp);
    printf("已写入 student.txt\n");

    /*====================================================================
     * 第二步：用 fscanf 从文本文件中读回数据
     *
     * fscanf 和 scanf 用法几乎一样：
     *   scanf(格式, ...)        → 从键盘读取 (stdin)
     *   fscanf(fp, 格式, ...)   → 从文件读取
     *
     * 注意：s2.name 是数组名（即首地址），不需要 &；
     *       s2.age 和 s2.score 是普通变量，需要 & 取地址。
     *====================================================================*/
    fp = fopen("student.txt", "r");
    if (fp == NULL)
    {
        printf("无法打开 student.txt\n");
        return 1;
    }

    struct Student s2;  /* 用于存放读回的数据 */
    if (fscanf(fp, "%19s %d %f", s2.name, &s2.age, &s2.score) != 3)
    {
        fprintf(stderr, "学生数据格式错误\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    printf("从文件读回：%s %d %.1f\n", s2.name, s2.age, s2.score);

    printf("\n注意：fscanf 以空白字符分隔，名字中有空格会被截断。\n");
    printf("如果名字可能含空格，应该用 fgets + 手动解析。\n");

    return 0;
}
