/**
 * @file    circular_queue.c
 * @chapter 第十九章 - 通用抽象数据结构
 * @brief   用取模运算复用数组前端空间的环形队列。
 */
#include "circular_queue.h"

/* 空环形队列用 front == rear 表示。 */
void circular_queue_init(CircularQueue *queue)
{
    /* NULL 指针没有可初始化的对象。 */
    if (queue == NULL) return;
    queue->front = 0; /* 下一个出队位置从数组开头开始。 */
    queue->rear = 0;  /* 下一个入队位置也从数组开头开始。 */
}

/* 判空只需比较两个循环下标。 */
bool circular_queue_is_empty(const CircularQueue *queue)
{
    /* 短路求值避免 queue 为 NULL 时解引用。 */
    return queue == NULL || queue->front == queue->rear;
}

/* 本实现保留一个空槽，以区分“空”和“满”。 */
bool circular_queue_is_full(const CircularQueue *queue)
{
    /* NULL 不是一个已满的有效队列。 */
    if (queue == NULL) return false;
    /* rear 的下一位置追上 front 时，说明可用容量已经耗尽。 */
    return (queue->rear + 1) % CIRCULAR_QUEUE_STORAGE == queue->front;
}

/* 模运算同时处理 rear 位于 front 前方和绕回后的两种情况。 */
size_t circular_queue_size(const CircularQueue *queue)
{
    /* 无有效队列对象时没有元素。 */
    if (queue == NULL) return 0;
    /* 先加存储槽数避免无符号减法下溢，再对槽数取模。 */
    return (queue->rear + CIRCULAR_QUEUE_STORAGE - queue->front)
           % CIRCULAR_QUEUE_STORAGE;
}

/* 入队在 rear 指向的空槽写值，然后移动 rear。 */
bool circular_queue_enqueue(CircularQueue *queue, int value)
{
    /* 无队列对象或队列已满时不能写入。 */
    if (queue == NULL || circular_queue_is_full(queue)) return false;
    queue->data[queue->rear] = value; /* 当前 rear 保证指向可写空槽。 */
    queue->rear = (queue->rear + 1) % CIRCULAR_QUEUE_STORAGE; /* 循环后移。 */
    return true; /* 写入和下标更新均已完成。 */
}

/* 出队读取 front 指向的值，然后移动 front。 */
bool circular_queue_dequeue(CircularQueue *queue, int *out_value)
{
    /* 空队列无值可取，NULL 输出指针也不能写入。 */
    if (circular_queue_is_empty(queue) || out_value == NULL) return false;
    *out_value = queue->data[queue->front]; /* 先保存队首数据。 */
    queue->front = (queue->front + 1) % CIRCULAR_QUEUE_STORAGE; /* 再后移。 */
    return true; /* 原槽无需清零，后续入队会覆盖。 */
}

/* peek 只复制队首值，不改变任何下标。 */
bool circular_queue_peek(const CircularQueue *queue, int *out_value)
{
    /* 复用判空逻辑，并检查调用者提供的输出地址。 */
    if (circular_queue_is_empty(queue) || out_value == NULL) return false;
    *out_value = queue->data[queue->front]; /* front 始终指向当前队首。 */
    return true; /* 队列状态保持不变。 */
}

/* 以下包装器保持教程正文中的函数名称。 */
void initQueue(CircularQueue *queue) { circular_queue_init(queue); }
bool isEmpty(CircularQueue *queue) { return circular_queue_is_empty(queue); }
bool isFull(CircularQueue *queue) { return circular_queue_is_full(queue); }
int getSize(CircularQueue *queue) { return (int)circular_queue_size(queue); }
bool enqueue(CircularQueue *queue, int value)
{
    return circular_queue_enqueue(queue, value);
}
bool dequeue(CircularQueue *queue, int *out_value)
{
    return circular_queue_dequeue(queue, out_value);
}
