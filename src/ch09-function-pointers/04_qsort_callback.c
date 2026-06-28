/**
 * =====================================================
 * 文件名: 04_qsort_callback.c
 * 所属章节: 第九章
 * 对应小节: 二-1.3 经典的回调应用——自定义排序
 * 演示内容: 使用标准库 qsort，通过函数指针传入自定义比较规则
 * =====================================================
 *
 * qsort 是 C 标准库的函数（声明在 <stdlib.h>）：
 *   void qsort(void *base,        // 数组首地址
 *              size_t nitems,     // 元素个数
 *              size_t size,       // 每个元素字节数
 *              int (*compar)(const void *, const void *));  // 比较函数
 *
 * qsort 不知道你要比较的是什么类型，也不知道比较规则。
 * 它每次需要比较两个元素时，就通过函数指针调用你提供的 compar。
 * 这正是"回调函数"的经典应用。
 *
 * 编译：gcc -Wall -o 04_qsort_callback 04_qsort_callback.c
 * 运行：./04_qsort_callback
 */

#include <stdio.h>
#include <stdlib.h>   /* qsort */

/* =================================================================
 * compareInt — 整数升序比较函数
 *
 * 参数是 const void *，因为 qsort 不知道元素具体类型，
 * 所以用 void * 通用指针。函数内部需要强制类型转换。
 *
 * 返回值约定（和 strcmp 一致）：
 *   a < b  → 返回负数 (如 -1)
 *   a == b → 返回 0
 *   a > b  → 返回正数 (如 1)
 * ================================================================= */
int compareInt(const void *a, const void *b)
{
    /* 转成指向只读 int 的指针再解引用，保留形参携带的 const 限定。 */
    int ia = *(const int *)a;
    int ib = *(const int *)b;

    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;

    /* 更简洁的写法（容易理解的版本参见上面）：
     *   return ia - ib;  // 升序，但注意整数溢出
     */
}

int main(void)
{
    int arr[] = {42, 7, 99, 3, 15};
    size_t size = sizeof arr / sizeof arr[0]; /* size_t 与 qsort 的参数类型一致 */

    /* 调用 qsort 排序：
     *   arr        — 数组（首元素地址）
     *   size       — 元素个数
     *   sizeof(int)— 每个元素占用的字节数
     *   compareInt — 比较函数的地址（即回调函数）
     */
    qsort(arr, size, sizeof(int), compareInt);

    /* 输出排序后的结果 */
    printf("排序后：");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

/* ================================================================
 * 预期输出：
 *
 *   排序后：3 7 15 42 99
 *
 * 回调模式分析：
 *   ① qsort 是库函数，它不知道排序的是 int 还是 float 还是结构体。
 *   ② 你通过 compareInt 告诉它"如何比较两个元素"。
 *   ③ qsort 在排序过程中，每需要比较时反调 compareInt。
 *   ④ 同样的机制可以用来排序任意类型：写不同的 compare 函数即可。
 *
 * 扩展练习建议：
 *   - 写 compareFloat 对 float 数组排序
 *   - 写 compareDesc 实现降序排列
 *   - 写 compareStudent 按成绩对结构体数组排序
 * ================================================================ */
