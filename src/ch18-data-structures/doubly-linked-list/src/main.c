/* 引入双链表节点类型及操作函数。 */
#include "doubly_linked_list.h"

#include <stdio.h> /* printf：输出正向和反向遍历结果。 */

/* 程序入口演示双向链接的建立、遍历、删除与释放。 */
int main(void)
{
    DNode *head = NULL;              /* NULL 表示初始链表为空。 */
    head = insertAtTail(head, 10);   /* 链表变为 10。 */
    head = insertAtTail(head, 20);   /* 链表变为 10 <-> 20。 */
    head = insertAtHead(head, 5);    /* 新头为 5。 */

    printf("正向：");     /* 沿 next 输出 5、10、20。 */
    printForward(head);
    printf("反向：");     /* 先找尾节点，再沿 prev 输出 20、10、5。 */
    printBackward(head);
    head = deleteNode(head, 10); /* 同时修复 5 与 20 之间的双向链接。 */
    printf("删除 10 后：");
    printForward(head);

    freeDList(head); /* 逐个释放剩余节点。 */
    head = NULL;     /* 清除调用者一侧的悬空地址。 */
    /* 所有堆内存均已归还。 */
    return 0;
}
