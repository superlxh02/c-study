/**
 * @file    04_fwrite_fread.c
 * @chapter 第十五章 - 文件IO
 * @section 二.4.3 - 二进制读写：fwrite / fread 示例
 * @brief   演示用 fwrite 将结构体数组按二进制写入文件，再用 fread 读回。
 *
 * 核心知识点：
 *   1. fwrite(ptr, size, count, stream) —— 将内存数据按块写入文件
 *      ptr: 数据地址，size: 每块字节数，count: 块数
 *      返回实际写入的完整块数
 *   2. fread(ptr, size, count, stream) —— 从文件按块读取数据到内存
 *      参数同 fwrite，返回实际读到的完整块数
 *   3. 二进制模式：fopen 时加 "b"（如 "wb", "rb"）
 *      - 在 Linux/macOS 上 "b" 无实际影响
 *      - 在 Windows 上可防止换行符转换
 *   4. 优点：速度快、文件紧凑；缺点：人不可读、跨平台兼容性差
 */

#include <stdio.h>

/* 学生结构体 */
struct Student
{
    char name[20];   /* 姓名 */
    int age;         /* 年龄 */
    float score;     /* 成绩 */
};

int main(void)
{
    /* 准备结构体数组数据 */
    struct Student list[2] = {
        {"小明", 18, 92.5},
        {"小红", 19, 88.0}
    };

    printf("===== fwrite / fread 二进制读写 =====\n\n");

    /*====================================================================
     * 第一步：二进制写入
     *
     * "wb" = write + binary（二进制只写模式）
     * fwrite 参数说明：
     *   list                     —— 要写入的数据地址
     *   sizeof(struct Student)   —— 每个数据块的大小（一个结构体）
     *   2                        —— 数据块个数
     *   fp                       —— 目标文件指针
     *
     * fwrite 把 list 中的 2 个 struct Student 的原始内存字节直接写入文件，
     * 不经过任何格式转换。生成的文件人看不懂，但写入和读取非常快。
     *====================================================================*/
    printf("原始数据：\n");
    for (int i = 0; i < 2; i++)
    {
        printf("  %s %d %.1f\n", list[i].name, list[i].age, list[i].score);
    }

    FILE *fp = fopen("students.dat", "wb");  /* "b" 表示二进制模式 */
    if (fp == NULL)
    {
        printf("无法创建文件 students.dat\n");
        return 1;
    }
    if (fwrite(list, sizeof(struct Student), 2, fp) != 2)
    {
        fprintf(stderr, "写入 students.dat 失败\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);
    printf("\n已用二进制格式写入 students.dat\n");

    /*====================================================================
     * 第二步：二进制读取
     *
     * "rb" = read + binary（二进制只读模式）
     * fread 参数说明：
     *   readList                 —— 存放读取数据的内存地址
     *   sizeof(struct Student)   —— 每个数据块的大小
     *   2                        —— 要读取的数据块个数
     *   fp                       —— 源文件指针
     *
     * fread 把文件中的原始字节直接恢复到 struct Student 的内存布局中。
     *====================================================================*/
    struct Student readList[2];  /* 用于存放读回的数据 */
    fp = fopen("students.dat", "rb");
    if (fp == NULL)
    {
        printf("无法打开 students.dat\n");
        return 1;
    }
    if (fread(readList, sizeof(struct Student), 2, fp) != 2)
    {
        fprintf(stderr, "students.dat 数据不完整或读取失败\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    printf("从文件读回：\n");
    for (int i = 0; i < 2; i++)
    {
        printf("  %s %d %.1f\n", readList[i].name, readList[i].age, readList[i].score);
    }

    printf("\n注意：二进制文件跨平台性较差（字节序、对齐可能不同）。\n");
    printf("但对于本地程序来说非常方便。\n");

    return 0;
}
