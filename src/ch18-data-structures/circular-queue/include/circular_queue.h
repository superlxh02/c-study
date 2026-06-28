/* 头文件保护宏防止结构体与函数声明被重复包含。 */
#ifndef C_STUDY_CIRCULAR_QUEUE_H
#define C_STUDY_CIRCULAR_QUEUE_H

#include <stdbool.h> /* bool：判空、判满及操作结果。 */
#include <stddef.h>  /* size_t：安全表示数组下标和队列长度。 */

/* 为区分“空”和“满”，本实现保留一个空槽，实际容量为 5。 */
#define CIRCULAR_QUEUE_STORAGE 6 /* 底层数组实际拥有的槽位数。 */
#define CIRCULAR_QUEUE_CAPACITY (CIRCULAR_QUEUE_STORAGE - 1) /* 可存元素数。 */
#define MAX_SIZE CIRCULAR_QUEUE_STORAGE /* 与正文中的宏名称保持一致。 */

typedef struct
{
    int data[CIRCULAR_QUEUE_STORAGE]; /* 固定容量的底层循环缓冲区。 */
    size_t front; /* 指向下一个出队元素。 */
    size_t rear;  /* 指向下一个入队空槽。 */
} CircularQueue;

/* 初始化 front 和 rear，使队列进入空状态。 */
void circular_queue_init(CircularQueue *queue);
/* front 与 rear 相等时队列为空。 */
bool circular_queue_is_empty(const CircularQueue *queue);
/* rear 的下一槽等于 front 时队列已满。 */
bool circular_queue_is_full(const CircularQueue *queue);
/* 使用模运算计算当前有效元素个数。 */
size_t circular_queue_size(const CircularQueue *queue);
/* 在 rear 指向的空槽写入数据并循环后移。 */
bool circular_queue_enqueue(CircularQueue *queue, int value);
/* 从 front 取出数据并循环后移。 */
bool circular_queue_dequeue(CircularQueue *queue, int *out_value);
/* 查看队首但不改变 front。 */
bool circular_queue_peek(const CircularQueue *queue, int *out_value);

/* 与教程正文一致的接口名称。 */
void initQueue(CircularQueue *queue);
bool isEmpty(CircularQueue *queue);
bool isFull(CircularQueue *queue);
int getSize(CircularQueue *queue);
bool enqueue(CircularQueue *queue, int value);
bool dequeue(CircularQueue *queue, int *out_value);

#endif /* C_STUDY_CIRCULAR_QUEUE_H */
