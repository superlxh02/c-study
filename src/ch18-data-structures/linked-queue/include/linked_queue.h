/* 头文件保护宏避免链式队列声明被重复展开。 */
#ifndef C_STUDY_LINKED_QUEUE_H
#define C_STUDY_LINKED_QUEUE_H

#include <stdbool.h> /* bool：操作结果和判空结果。 */
#include <stddef.h>  /* size_t：队列中的元素数量。 */

/* 每个队列节点保存一个整数以及后继节点地址。 */
typedef struct QueueNode
{
    int data;               /* 当前节点的数据。 */
    struct QueueNode *next; /* 下一个节点；队尾节点指向 NULL。 */
} QueueNode;

/* QNode 是教程正文中的节点类型名称。 */
typedef QueueNode QNode;

/* front 指向下一个出队节点，rear 指向当前队尾。 */
typedef struct
{
    QueueNode *front; /* 指向下一次出队的节点。 */
    QueueNode *rear;  /* 指向当前最后一个节点。 */
    size_t size;      /* 缓存元素数量，使查询长度保持 O(1)。 */
} LinkedQueue;

/* Queue 是正文使用的简短队列类型名称。 */
typedef LinkedQueue Queue;

/* 初始化空队列。 */
void queue_init(LinkedQueue *queue);
/* 判断队列是否为空；NULL 指针按空队列处理。 */
bool queue_is_empty(const LinkedQueue *queue);
/* 返回缓存的元素数量。 */
size_t queue_size(const LinkedQueue *queue);
/* 分配新节点并追加到队尾。 */
bool queue_enqueue(LinkedQueue *queue, int value);
/* 删除队首节点，并通过 out_value 返回其数据。 */
bool queue_dequeue(LinkedQueue *queue, int *out_value);
/* 查看队首数据但不删除节点。 */
bool queue_peek(const LinkedQueue *queue, int *out_value);
/* 释放全部节点并恢复空队列状态。 */
void queue_clear(LinkedQueue *queue);

/* 与教程正文一致的接口。enqueue 分配失败时打印错误并终止程序。 */
void initQueue(Queue *queue);
bool isQueueEmpty(Queue *queue);
void enqueue(Queue *queue, int value);
bool dequeue(Queue *queue, int *out_value);
void printQueue(Queue *queue);
void freeQueue(Queue *queue);

#endif /* C_STUDY_LINKED_QUEUE_H */
