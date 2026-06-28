/**
 * =====================================================
 * 文件名: 03_realloc_demo.c
 * 所属章节: 第十章
 * 对应小节: 二-4 realloc——调整已分配内存的大小
 * 演示内容: 用 realloc 扩展动态数组容量，同时保留原有数据
 * =====================================================
 *
 * realloc 的行为：
 *   - 如果当前块后面有足够空间 → 原地扩展，返回原指针
 *   - 如果后面空间不够 → 分配新块，拷贝旧数据，释放旧块，返回新指针
 *   - 如果完全失败 → 返回 NULL，旧块仍然有效
 *
 * 安全模式（必须遵守）：
 *   int *temp = realloc(ptr, new_size);
 *   if (temp == NULL) { 处理失败并保留原指针 }
 *   else ptr = temp;
 *   绝对不要：ptr = realloc(ptr, new_size);  ← 失败时旧地址丢失！
 *
 * 编译：gcc -Wall -o 03_realloc_demo 03_realloc_demo.c
 * 运行：./03_realloc_demo
 */

#include <stdio.h>
#include <stdlib.h>   /* malloc, realloc, free */

int main(void)
{
    int n = 3;

    /* 步骤1：先申请 3 个 int 的空间 */
    int *arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) return 1;

    /* 填入初始数据 */
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    printf("原始数组（容量 %d）：%d %d %d\n", n, arr[0], arr[1], arr[2]);

    /* 步骤2：扩展到 5 个 int
     * 使用安全模式：用临时指针 temp 接收 realloc 返回值 */
    n = 5;
    int *temp = realloc(arr, (size_t)n * sizeof(int));
    if (temp == NULL)
    {
        /* realloc 失败，arr 仍然指向旧块，数据完好 */
        printf("内存扩展失败，原数据仍保留在 arr 中\n");
        free(arr);    /* 还是要释放旧块 */
        return 1;
    }
    arr = temp;        /* 成功：用新指针更新 arr */

    /* 步骤3：新增的两个元素手动赋值
     *   前 3 个元素的值（10, 20, 30）被 realloc 自动保留了 */
    arr[3] = 40;
    arr[4] = 50;

    /* 步骤4：输出扩展后的完整数组 */
    printf("扩展后数组（容量 %d）：", n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    /* 步骤5：释放 */
    free(arr);
    arr = NULL;

    return 0;
}

/* ================================================================
 * 预期输出：
 *
 *   原始数组（容量 3）：10 20 30
 *   扩展后数组（容量 5）：10 20 30 40 50
 *
 * 要点回顾：
 *   ① realloc 会自动保留旧数据（10, 20, 30 还在）。
 *   ② 必须用临时指针接收返回值，成功后再赋值给原指针。
 *   ③ realloc 返回的指针可能与原指针相同也可能不同（看内存布局）。
 *   ④ 如果 realloc 失败返回 NULL，原内存块依旧有效，仍需 free。
 * ================================================================ */
