/**
 * =====================================================
 * 文件名: 02_calloc_demo.c
 * 所属章节: 第十章
 * 对应小节: 二-3 calloc——申请并清零
 * 演示内容: 用 calloc 分配内存并自动初始化为 0
 * =====================================================
 *
 * calloc vs malloc：
 *   - calloc(num, size) — 申请 num 个元素，每个 size 字节，自动清零
 *   - malloc(total_bytes) — 申请 total_bytes 字节但不初始化，写入前不可读取
 *   - calloc 稍慢（因为要清零），如果马上覆盖写入，用 malloc 更高效
 *
 * 编译：gcc -Wall -o 02_calloc_demo 02_calloc_demo.c
 * 运行：./02_calloc_demo
 */

#include <stdio.h>
#include <stdlib.h>   /* calloc, free */

int main(void)
{
    int n = 5;

    /* calloc 申请并清零：
     *   参数1：元素个数 n
     *   参数2：每个元素的大小 sizeof(int)
     *   申请成功后，这块内存的所有字节都已经是 0
     */
    int *arr = calloc((size_t)n, sizeof(int));

    /* 必须检查返回值 */
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return 1;
    }

    /* 由于 calloc 自动清零，所有元素初始为 0
     * 不需要手动初始化，直接读取就是 0 */
    printf("calloc 分配后的数组：");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);   /* 全都输出 0 */
    }
    printf("\n");

    /* 对比 malloc：如果不调用 calloc 而用 malloc，
     * 则在写入前读取 arr[i] 会读取不确定值，可能产生未定义行为 */

    /* 释放内存 */
    free(arr);
    arr = NULL;        /* 良好习惯 */

    return 0;
}

/* ================================================================
 * 预期输出：
 *
 *   calloc 分配后的数组：0 0 0 0 0
 *
 * 总结：
 *   ｜         ｜ malloc                              ｜ calloc ｜
 *   ｜参数     ｜ 总字节数                            ｜ 元素个数 + 每个元素大小 ｜
 *   ｜初始化   ｜ 不初始化，写入前不可读取             ｜ 所有位清零 ｜
 *   ｜速度     ｜ 稍快                                ｜ 稍慢（因为要清零） ｜
 *   ｜适用场景 ｜ 马上会全部覆盖写入的数据              ｜ 需要干净初始状态的数据 ｜
 * ================================================================ */
