/* 引入链式队列类型和操作接口。 */
#include "linked_queue.h"

#include <stdio.h> /* printf：输出入队和出队结果。 */

/* 程序入口演示链式队列的先进先出顺序。 */
int main(void)
{
    Queue queue;       /* 队列控制对象保存首尾指针和长度。 */
    initQueue(&queue); /* 使用前将其初始化为空队列。 */

    enqueue(&queue, 10); /* 第一个节点同时成为队首和队尾。 */
    enqueue(&queue, 20); /* 20 追加到当前队尾之后。 */
    enqueue(&queue, 30); /* 30 成为新的队尾。 */

    /* 从 front 沿 next 展示当前队列。 */
    printf("入队后：");
    printQueue(&queue);

    int value = 0; /* 接收每次出队的数据。 */
    /* dequeue 依次返回 10、20、30，空队列时返回 false。 */
    while (dequeue(&queue, &value)) printf("出队：%d\n", value);
    freeQueue(&queue); /* 即使队列已经为空，重复清理仍然安全。 */
    /* 所有动态节点均已释放。 */
    return 0;
}
