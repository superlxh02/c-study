/**
 * =====================================================
 * 文件名: 05_heap_practice.c
 * 所属章节: 第十章
 * 对应小节: 四-3 动手练习（堆内存综合练习）
 * 演示内容: 动态数组求和平均值 + 用 realloc 动态扩展数组
 * =====================================================
 *
 * 三个练习：
 *   练习1：动态数组 — 输入 n 个数字，计算总和与平均值
 *   练习2：原代码标注为"略"，此处保留注释
 *   练习3：realloc 动态扩展数组 — 从 3 个元素扩展到 6 个
 *
 * 编译：gcc -Wall -o 05_heap_practice 05_heap_practice.c
 * 运行：./05_heap_practice
 */

#include <stdio.h>
#include <stdint.h>  /* SIZE_MAX */
#include <stdlib.h>   /* malloc, realloc, free */

int main(void)
{
    /* ============================================================
     * 练习1：动态数组求和与平均值
     *   用 malloc 按需分配一个 double 数组，
     *   输入所有数值后计算总和与平均值。
     * ============================================================ */
    printf("===== 练习1：动态数组求和与平均值 =====\n");

    int n;
    printf("请输入数字个数：");
    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "请输入整数\n");
        return 1;
    }

    /* 输入验证 */
    if (n <= 0 || (size_t)n > SIZE_MAX / sizeof(double))
    {
        printf("数字个数无效或所需空间过大\n");
        return 1;
    }

    /* 在堆上申请 n 个 double 的空间 */
    double *arr = malloc((size_t)n * sizeof(double));
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return 1;
    }

    /* 输入数据并累加 */
    double sum = 0.0;
    printf("请输入 %d 个数字：\n", n);
    for (int i = 0; i < n; i++)
    {
        if (scanf("%lf", &arr[i]) != 1)
        {
            fprintf(stderr, "第 %d 个输入不是有效数字\n", i + 1);
            free(arr);
            return 1;
        }
        sum += arr[i];
    }

    /* 输出统计结果 */
    printf("总和 = %.2f\n", sum);
    printf("平均值 = %.2f\n", sum / n);

    /* 释放练习1的内存 */
    free(arr);
    arr = NULL;

    printf("\n");

    /* ============================================================
     * 练习2：用 calloc 创建计数器数组
     *   原文标注为"略"，此处仅说明意图。
     *   实际 calloc 用法请参见 02_calloc_demo.c。
     * ============================================================ */
    printf("===== 练习2：calloc 计数器数组 =====\n");
    printf("（原文标注为\"略\"，完整示例见 02_calloc_demo.c）\n\n");

    /* ============================================================
     * 练习3：用 realloc 动态扩展数组
     *   先分配 3 个 int，填入 1,2,3；
     *   然后用 realloc 扩展到 6 个 int，填入 4,5,6。
     *   验证原有数据被保留。
     * ============================================================ */
    printf("===== 练习3：动态扩展数组 =====\n");

    int cap = 3;
    int *nums = malloc((size_t)cap * sizeof(int));
    if (nums == NULL)
    {
        printf("malloc 失败！\n");
        return 1;
    }

    /* 初始 3 个元素 */
    nums[0] = 1;
    nums[1] = 2;
    nums[2] = 3;
    printf("当前数组大小 %d，内容：%d %d %d\n", cap, nums[0], nums[1], nums[2]);

    /* 扩展到 6 —— 使用 realloc 安全模式 */
    int new_cap = 6;
    int *temp = realloc(nums, (size_t)new_cap * sizeof(int));
    if (temp == NULL)
    {
        /* 扩展失败：nums 仍然有效，可以继续用或释放 */
        printf("扩展失败\n");
        free(nums);
        return 1;
    }
    nums = temp;          /* 用新指针更新 */
    cap = new_cap;        /* 更新容量变量 */

    /* 新扩展的 3 个位置填入数据 */
    nums[3] = 4;
    nums[4] = 5;
    nums[5] = 6;

    /* 输出扩展后的完整数组 */
    printf("扩展后大小 %d，内容：", cap);
    for (int i = 0; i < cap; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

    /* 释放 */
    free(nums);
    nums = NULL;

    return 0;
}

/* ================================================================
 * 运行示例（用户输入用 ← 标记）：
 *
 *   ===== 练习1：动态数组求和与平均值 =====
 *   请输入数字个数：4
 *   请输入 4 个数字：
 *   10.5
 *   20.5
 *   30.0
 *   40.0
 *   总和 = 101.00
 *   平均值 = 25.25
 *
 *   ===== 练习2：calloc 计数器数组 =====
 *   （原文标注为"略"，完整示例见 02_calloc_demo.c）
 *
 *   ===== 练习3：动态扩展数组 =====
 *   当前数组大小 3，内容：1 2 3
 *   扩展后大小 6，内容：1 2 3 4 5 6
 *
 * 总结：
 *   ① malloc 分配后必须检查 NULL。
 *   ② realloc 必须用临时指针接收返回值。
 *   ③ 每块动态内存最终必须 free 一次。
 *   ④ 堆内存的生命周期由程序员手动管理。
 * ================================================================ */
