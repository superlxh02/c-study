/**
 * =====================================================
 * 文件名: 01_malloc_array.c
 * 所属章节: 第十章
 * 对应小节: 二-1 malloc——申请堆内存
 * 演示内容: 用 malloc 在堆上创建动态数组，运行时按需分配
 * =====================================================
 *
 * malloc 的核心要点：
 *   - malloc(n * sizeof(type)) — 申请 n 个 type 类型元素的空间
 *   - 返回 void*，在 C 中自动转换为目标指针类型
 *   - 必须检查返回值是否为 NULL（分配失败）
 *   - 用完后必须 free 释放
 *
 * 编译：gcc -Wall -o 01_malloc_array 01_malloc_array.c
 * 运行：./01_malloc_array
 */

#include <stdio.h>
#include <stdint.h>  /* SIZE_MAX */
#include <stdlib.h>   /* malloc, free */

int main(void)
{
    int n;

    /* 步骤1：运行时获取数组大小
     * 这个 n 的值在编译时完全未知——这正是动态数组存在的意义 */
    printf("请输入学生人数：");
    if (scanf("%d", &n) != 1 || n <= 0 || (size_t)n > SIZE_MAX / sizeof(int))
    {
        fprintf(stderr, "人数无效或所需空间过大\n");
        return 1;
    }

    /* 步骤2：在堆上申请存放 n 个 int 的空间
     *   n * sizeof(int)：计算出需要多少个字节
     *   例如 n=50, sizeof(int)=4 → 申请 200 字节
     *   malloc 返回堆上连续内存的起始地址 */
    int *scores = malloc((size_t)n * sizeof(int));

    /* 步骤3：必须检查是否申请成功
     *   如果系统内存不足，malloc 返回 NULL
     *   此时直接使用 scores 会导致程序崩溃 */
    if (scores == NULL)
    {
        printf("内存分配失败！\n");
        return 1;      /* 异常退出 */
    }

    /* 步骤4：把这块堆空间当作数组来使用
     *   scores[i] 的写法和普通数组完全一样！ */
    for (int i = 0; i < n; i++)
    {
        printf("请输入第 %d 个学生的成绩：", i + 1);
        if (scanf("%d", &scores[i]) != 1)
        {
            fprintf(stderr, "第 %d 个成绩不是有效整数\n", i + 1);
            free(scores); /* 异常返回前仍需释放已经分配的数组。 */
            return 1;
        }
    }

    /* 步骤5：输出验证 */
    printf("\n你输入的成绩：");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", scores[i]);
    }
    printf("\n");

    /* 步骤6：用完后必须释放
     *   堆内存不会在函数结束时自动回收，必须手动 free */
    free(scores);
    scores = NULL; /* 清除已失效地址，避免后续误用。 */

    return 0;
}

/* ================================================================
 * 运行示例（用户输入用 ← 标记）：
 *
 *   请输入学生人数：3
 *   请输入第 1 个学生的成绩：85
 *   请输入第 2 个学生的成绩：92
 *   请输入第 3 个学生的成绩：78
 *
 *   你输入的成绩：85 92 78
 *
 * 关键总结：
 *   ① 数组大小 n 在运行时由用户输入决定 — 这正是动态分配的威力。
 *   ② malloc(n * sizeof(int)) 返回 void*，自动转为 int*。
 *   ③ 必须检查 scores == NULL，NULL 解引用导致崩溃。
 *   ④ 必须 free(scores)，否则内存泄漏。
 * ================================================================ */
