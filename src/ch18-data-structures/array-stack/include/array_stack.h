/* 头文件保护宏防止重复定义 Stack 和相关函数。 */
#ifndef C_STUDY_ARRAY_STACK_H
#define C_STUDY_ARRAY_STACK_H

#include <stdbool.h> /* bool：操作成功、判空和判满结果。 */
#include <stddef.h>  /* size_t：栈内元素数量。 */

#define MAX_SIZE 100                    /* 正文使用的固定容量名称。 */
#define ARRAY_STACK_CAPACITY MAX_SIZE   /* 实现层使用的语义化别名。 */

/* 与正文一致：top 是栈顶下标，-1 表示空栈。 */
typedef struct
{
    int data[ARRAY_STACK_CAPACITY]; /* 连续存放栈中整数。 */
    int top;                        /* 当前栈顶下标，-1 表示空栈。 */
} Stack;

/* 实现层名称与正文的 Stack 表示同一类型。 */
typedef Stack ArrayStack;

/* 把栈初始化为空；stack 为 NULL 时不执行操作。 */
void stack_init(ArrayStack *stack);
/* NULL 指针按空栈处理，避免调用者误解引用。 */
bool stack_is_empty(const ArrayStack *stack);
/* 判断 top 是否已经到达数组最后一个有效下标。 */
bool stack_is_full(const ArrayStack *stack);
/* 返回当前元素个数；NULL 指针返回 0。 */
size_t stack_size(const ArrayStack *stack);
/* 未满时压入 value，成功返回 true。 */
bool stack_push(ArrayStack *stack, int value);
/* 非空且输出指针有效时弹出栈顶值。 */
bool stack_pop(ArrayStack *stack, int *out_value);
/* 读取但不移除栈顶值。 */
bool stack_peek(const ArrayStack *stack, int *out_value);

/* 第十九章正文使用的接口名称，内部复用上面的安全实现。 */
void initStack(Stack *stack);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
bool push(Stack *stack, int value);
bool pop(Stack *stack, int *out_value);
bool peek(Stack *stack, int *out_value);

#endif /* C_STUDY_ARRAY_STACK_H */
