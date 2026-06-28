/* 引入环形队列类型和操作函数。 */
#include "circular_queue.h"

#include <stdio.h> /* printf：输出队列状态和数据。 */

/* 程序入口演示队尾下标绕回数组开头的过程。 */
int main(void)
{
    CircularQueue queue; /* 固定数组直接包含在队列对象中。 */
    initQueue(&queue);   /* 使用前把 front、rear 都置为 0。 */

    /* 实际容量为 5，依次入队 10、20、30、40、50。 */
    for (int value = 10; value <= 50; value += 10)
    {
        /* 容量和循环次数匹配；若实现异常失败则立即退出。 */
        if (!enqueue(&queue, value)) return 1;
    }

    /* 五个有效槽已全部使用，此处应输出“是”。 */
    printf("已满？%s\n", isFull(&queue) ? "是" : "否");

    int value = 0; /* 接收每次出队的整数。 */
    /* 先取出 10，为后续绕回腾出第一个槽。 */
    if (!dequeue(&queue, &value)) return 1;
    printf("出队：%d\n", value);
    /* 再取出 20，为下标 1 腾出空间。 */
    if (!dequeue(&queue, &value)) return 1;
    printf("出队：%d\n", value);
    /* 60 写入下标 5 后 rear 绕回 0，70 随后写入下标 0。 */
    if (!enqueue(&queue, 60)) return 1;
    if (!enqueue(&queue, 70)) return 1;

    /* 按 FIFO 顺序输出剩余的 30、40、50、60、70。 */
    printf("当前队列：");
    while (dequeue(&queue, &value)) printf("%d ", value);
    /* 队列为空后 dequeue 返回 false，循环结束。 */
    printf("\n");
    /* 队列不使用堆内存，因此无需 free。 */
    return 0;
}
