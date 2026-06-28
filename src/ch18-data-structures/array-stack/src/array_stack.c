/**
 * @file    array_stack.c
 * @chapter 第十九章 - 通用抽象数据结构
 * @brief   固定容量顺序栈实现。
 */
#include "array_stack.h"

/* 初始化只需要把栈顶下标恢复到空栈哨兵值 -1。 */
void stack_init(ArrayStack *stack)
{
    /* 先检查指针，避免调用者误传 NULL 时发生解引用。 */
    if (stack != NULL) stack->top = -1;
}

/* 空指针无法表示可用栈，因此本实现也把它视为空。 */
bool stack_is_empty(const ArrayStack *stack)
{
    /* 短路求值保证 stack 为 NULL 时不会访问 stack->top。 */
    return stack == NULL || stack->top == -1;
}

/* top 到达最后一个下标时，固定数组已经没有空槽。 */
bool stack_is_full(const ArrayStack *stack)
{
    /* NULL 不是“已满的有效栈”，因此返回 false。 */
    return stack != NULL && stack->top == ARRAY_STACK_CAPACITY - 1;
}

/* 元素个数总是比栈顶下标大一。 */
size_t stack_size(const ArrayStack *stack)
{
    /* 空指针返回 0；有效栈把 top + 1 转换为无符号长度。 */
    return stack == NULL ? 0 : (size_t)(stack->top + 1);
}

/* push 只修改 top 和新栈顶对应的数组槽。 */
bool stack_push(ArrayStack *stack, int value)
{
    /* 空指针或满栈都无法继续写入。 */
    if (stack == NULL || stack_is_full(stack)) return false;
    stack->top++;                     /* 先移动到下一个空位。 */
    stack->data[stack->top] = value;  /* 再写入新栈顶元素。 */
    return true;                       /* 两步完成后报告成功。 */
}

/* pop 先读取当前栈顶，再把 top 下移。 */
bool stack_pop(ArrayStack *stack, int *out_value)
{
    /* 空栈没有值可取，NULL 输出指针也不能被写入。 */
    if (stack_is_empty(stack) || out_value == NULL) return false;
    *out_value = stack->data[stack->top]; /* 把旧栈顶值交给调用者。 */
    stack->top--;                     /* 取值后再下移栈顶。 */
    return true;                      /* 原数组槽无需清零，后续 push 会覆盖。 */
}

/* peek 与 pop 的区别是不会改变 top。 */
bool stack_peek(const ArrayStack *stack, int *out_value)
{
    /* 与 pop 使用同样的边界和指针检查。 */
    if (stack_is_empty(stack) || out_value == NULL) return false;
    *out_value = stack->data[stack->top]; /* 只复制值，不移除元素。 */
    return true;                          /* 读取成功。 */
}

/* 下列短包装器保留教程中的驼峰命名，不复制算法逻辑。 */
void initStack(Stack *stack) { stack_init(stack); }
bool isEmpty(Stack *stack) { return stack_is_empty(stack); }
bool isFull(Stack *stack) { return stack_is_full(stack); }
bool push(Stack *stack, int value) { return stack_push(stack, value); }
bool pop(Stack *stack, int *out_value) { return stack_pop(stack, out_value); }
bool peek(Stack *stack, int *out_value) { return stack_peek(stack, out_value); }
