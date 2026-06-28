/**
 * @file    linked_queue.c
 * @chapter 第十九章 - 通用抽象数据结构
 * @brief   使用单链节点实现先进先出的队列。
 */
#include "linked_queue.h"

#include <stdio.h>  /* fprintf、printf：错误与队列内容输出。 */
#include <stdlib.h> /* malloc、free、exit：节点内存管理。 */

/* 初始化必须同时设置 front、rear 和缓存长度。 */
void queue_init(LinkedQueue *queue)
{
    /* NULL 指针没有可初始化的队列对象。 */
    if (queue == NULL) return;
    queue->front = NULL; /* 空队列没有队首。 */
    queue->rear = NULL;  /* 空队列也没有队尾。 */
    queue->size = 0;     /* 有效节点数从零开始。 */
}

/* front 是否为空足以判断链式队列是否为空。 */
bool queue_is_empty(const LinkedQueue *queue)
{
    /* 无有效对象时也按空队列处理。 */
    return queue == NULL || queue->front == NULL;
}

/* 直接返回缓存长度，不需要遍历链表。 */
size_t queue_size(const LinkedQueue *queue)
{
    /* NULL 队列指针对应长度零。 */
    return queue == NULL ? 0 : queue->size;
}

/* 入队需要创建一个新的尾节点。 */
bool queue_enqueue(LinkedQueue *queue, int value)
{
    /* 调用者必须提供有效的队列对象。 */
    if (queue == NULL) return false;

    /* 为一个节点申请恰好所需的堆内存。 */
    QueueNode *node = malloc(sizeof *node);
    /* 分配失败时原队列保持不变。 */
    if (node == NULL) return false;
    node->data = value; /* 保存入队数据。 */
    node->next = NULL; /* 新节点将成为队尾，所以没有后继。 */

    if (queue->rear == NULL)
    {
        queue->front = node; /* 空队列的首个节点同时也是队首。 */
    }
    else
    {
        queue->rear->next = node; /* 旧队尾接上新节点。 */
    }
    queue->rear = node; /* 无论之前是否为空，新节点都是新队尾。 */
    queue->size++;      /* 缓存长度与实际节点数同步增加。 */
    return true;        /* 入队完成。 */
}

/* 出队删除并释放当前 front 节点。 */
bool queue_dequeue(LinkedQueue *queue, int *out_value)
{
    /* 空队列无值可取，NULL 输出地址也不能写入。 */
    if (queue_is_empty(queue) || out_value == NULL) return false;

    QueueNode *old_front = queue->front; /* 保存即将释放的队首。 */
    *out_value = old_front->data;        /* 先把数据交给调用者。 */
    queue->front = old_front->next;      /* 队首移动到后继节点。 */
    free(old_front);                     /* 旧队首已脱链，可以释放。 */
    queue->size--;                       /* 缓存长度同步减少。 */

    /* 删除最后一个节点后，rear 也必须恢复为空。 */
    if (queue->front == NULL) queue->rear = NULL;
    return true; /* 数据取出、节点释放和状态更新均已完成。 */
}

/* peek 只读取队首，不删除节点。 */
bool queue_peek(const LinkedQueue *queue, int *out_value)
{
    /* 与 dequeue 使用相同的判空和输出指针检查。 */
    if (queue_is_empty(queue) || out_value == NULL) return false;
    *out_value = queue->front->data; /* front 始终指向下一出队节点。 */
    return true;                     /* 队列链接和长度均未改变。 */
}

/* clear 反复复用 dequeue，确保每个节点恰好释放一次。 */
void queue_clear(LinkedQueue *queue)
{
    /* NULL 对象没有可释放内容。 */
    if (queue == NULL) return;
    int ignored = 0; /* dequeue 必须有有效输出地址，值本身无需使用。 */
    while (queue_dequeue(queue, &ignored)) { }
}

void initQueue(Queue *queue)
{
    queue_init(queue);
}

bool isQueueEmpty(Queue *queue)
{
    return queue_is_empty(queue);
}

void enqueue(Queue *queue, int value)
{
    /* 正文接口把分配失败视为演示程序无法恢复的错误。 */
    if (!queue_enqueue(queue, value))
    {
        fprintf(stderr, "内存分配失败\n");
        queue_clear(queue);
        exit(EXIT_FAILURE);
    }
}

bool dequeue(Queue *queue, int *out_value)
{
    return queue_dequeue(queue, out_value);
}

void printQueue(Queue *queue)
{
    /* 先输出逻辑队首标记。 */
    printf("队首 -> ");
    /* queue 有效时沿 next 打印全部节点。 */
    if (queue != NULL)
    {
        for (QueueNode *node = queue->front; node != NULL; node = node->next)
            printf("%d -> ", node->data);
    }
    printf("NULL (队尾)\n"); /* NULL 表示链式队列末端。 */
}

void freeQueue(Queue *queue)
{
    /* 清空后 front、rear 为 NULL，size 为 0。 */
    queue_clear(queue);
}
