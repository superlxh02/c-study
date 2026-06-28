/**
 * =====================================================
 * 文件名: 00_snippets.c
 * 所属章节: 第十章
 * 对应小节: 三（内存泄漏与悬空指针）、二-2（free 后置 NULL）
 * 演示内容: 内存泄漏、悬空指针、free后置NULL安全习惯、realloc安全模式
 * =====================================================
 *
 * 警告：
 *   本文件中的危险代码已被注释保护，仅作概念演示。
 *   取消注释可能导致程序崩溃或不可预测的行为。
 *
 * 编译：gcc -Wall -o 00_snippets 00_snippets.c
 * 运行：./00_snippets
 */

#include <stdio.h>
#include <stdlib.h>

/* =================================================================
 * 【片段1】free 后立即置 NULL（对应 第十章 二-2.3）
 * 这是防御悬空指针的基本策略。
 * ================================================================= */
void demo_free_and_null(void)
{
    printf("====== 片段1：free 后立即置 NULL ======\n");

    int *scores = malloc(10 * sizeof(int));
    if (scores == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    /* 使用 scores ... */
    scores[0] = 42;
    printf("scores[0] = %d\n", scores[0]);

    /* 释放后立即置空 —— 良好习惯 */
    free(scores);
    scores = NULL;   /* 现在 scores 明确表示不指向任何有效内存 */

    printf("free 完成，scores 已置为 NULL。\n");
    printf("之后再访问 scores 就是安全的（因为可以为 NULL 检查）。\n");

    printf("\n");
}

/* =================================================================
 * 【片段2】内存泄漏示例（对应 第十章 三-1.1）
 * 申请了堆内存但忘记 free → 函数返回后这块内存永远无法被释放。
 *
 * !! 注意：以下代码仅为概念展示，leakExample 函数在此文件中
 *    不会被调用（被注释保护），因为它故意不释放内存。
 * ================================================================= */
void demo_memory_leak_concept(void)
{
    printf("====== 片段2：内存泄漏的概念 ======\n");

    printf("内存泄漏：你申请了堆内存，但用完后没有释放。\n\n");

    /*
     * 以下函数故意不释放内存——这就是内存泄漏的典型模式：
     *
     * void leakExample(void)
     * {
     *     int *p = malloc(100 * sizeof(int));
     *     // 忘记 free(p);  // 内存泄漏！函数返回后这块内存永远无法释放
     * }
     */

    printf("比喻：向仓库租了储物间，走的时候没办退租。\n");
    printf("仓库管理员以为你还要用，这间房就一直被你占着。\n");
    printf("久而久之，仓库里全是无人使用的\"幽灵房间\"。\n\n");

    printf("在程序里，内存泄漏会导致程序占用内存越来越多，\n");
    printf("最终可能耗尽系统内存。\n\n");

    printf("防御原则：每块 malloc/calloc 分配的内存，最终必须\n");
    printf("恰好调用一次 free。这句话要记住！\n");

    printf("\n");
}

/* =================================================================
 * 【片段3】悬空指针示例（对应 第十章 三-1.2）
 * free 后指针仍然存着原来的地址，但那块内存已经无效了。
 * 这时再通过指针访问 → 悬空指针 → 危险！
 *
 * !! 以下危险代码被注释，仅作概念说明。
 * ================================================================= */
void demo_dangling_pointer(void)
{
    printf("====== 片段3：悬空指针的概念 ======\n");

    printf("悬空指针：已经 free 了内存，但指针还存着旧地址。\n\n");

    /*
     * 危险代码示例（切勿运行）：
     *
     * int *p = malloc(sizeof(int));
     * *p = 42;
     * free(p);       // 房间已退租
     * *p = 100;      // 危险！悬空指针，操作已释放的内存！
     *
     * 程序可能崩溃，可能不崩溃但数据诡异，难以排查。
     */

    printf("比喻：已经把储物间退了，但通讯录上还写着旧门牌号。\n");
    printf("下次按那个门牌号去用房间，里面可能已经住了别人。\n\n");

    printf("防御策略：\n");
    printf("  ① free 后立即将指针置为 NULL：free(p); p = NULL;\n");
    printf("  ② 如果多个指针指向同一块内存，释放后要全部置 NULL\n");
    printf("     （这很难管理，所以设计时要避免多指针指向同一块堆内存）。\n");

    printf("\n");
}

/* =================================================================
 * 【片段4】realloc 安全模式（对应 第十章 二-4.3）
 * 绝对不能直接写 ptr = realloc(ptr, new_size);
 * 必须用临时指针接收返回值，确认成功后再赋值。
 * ================================================================= */
void demo_realloc_safe_pattern(void)
{
    printf("====== 片段4：realloc 安全模式 ======\n");

    /* 先分配 3 个 int */
    int *ptr = malloc(3 * sizeof(int));
    if (ptr == NULL) return;

    ptr[0] = 10; ptr[1] = 20; ptr[2] = 30;

    /* realloc 的安全模式：用临时指针接收返回值 */
    int *temp = realloc(ptr, 6 * sizeof(int));
    if (temp == NULL)
    {
        /* 扩展失败，但 ptr 仍然有效，可以继续用原数据或释放 */
        printf("realloc 扩展失败，但原数据仍保留在 ptr 中。\n");
        free(ptr);   /* 还是要释放原内存 */
        return;
    }
    /* 成功：用新指针更新 ptr */
    ptr = temp;
    ptr[3] = 40; ptr[4] = 50; ptr[5] = 60;

    printf("realloc 安全模式执行成功：\n");
    printf("  ptr 内容：%d %d %d %d %d %d\n",
           ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5]);

    free(ptr);
    ptr = NULL;

    printf("\n重要：绝对不要直接写 ptr = realloc(ptr, size);\n");
    printf("  因为如果 realloc 失败返回 NULL，ptr 的旧值就被覆盖了，\n");
    printf("  原内存再也无法释放 → 内存泄漏！\n");

    printf("\n");
}

/* =================================================================
 * main
 * ================================================================= */
int main(void)
{
    demo_free_and_null();
    demo_memory_leak_concept();
    demo_dangling_pointer();
    demo_realloc_safe_pattern();

    return 0;
}
