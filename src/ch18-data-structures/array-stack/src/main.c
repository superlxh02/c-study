/* 引入顺序栈的类型和全部操作。 */
#include "array_stack.h"

#include <stdio.h> /* printf：输出栈操作结果。 */

/* 程序入口演示后进先出的访问顺序。 */
int main(void)
{
    Stack stack;          /* 栈对象本身位于当前函数的自动存储区。 */
    initStack(&stack);    /* 使用前必须把 top 初始化为 -1。 */

    /* 依次压入三个值；任何一次失败都立即返回错误状态。 */
    if (!push(&stack, 10)) return 1;
    if (!push(&stack, 20)) return 1;
    if (!push(&stack, 30)) return 1;

    int value = 0; /* 初始化接收变量，避免失败路径读取未定义值。 */
    /* peek 成功时，value 保存当前栈顶 30。 */
    if (peek(&stack, &value)) printf("栈顶：%d\n", value);

    /* 连续 pop 会按 30、20、10 的逆序取出。 */
    printf("出栈：");
    while (pop(&stack, &value)) printf("%d ", value);
    /* 空栈使 pop 返回 false，循环自然结束。 */
    printf("\n");
    /* 固定数组不需要手动释放内存。 */
    return 0;
}
