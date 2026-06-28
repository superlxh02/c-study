/** 单链表演示入口：组合调用公共接口，不把实现细节塞进 main。 */
#include "singly_linked_list.h" /* Node 类型及链表操作接口。 */

#include <stdio.h> /* printf：输出每一步操作后的链表。 */

/* 程序入口按顺序演示尾插、头插、删除和释放。 */
int main(void)
{
    Node *head = NULL;                 /* NULL 表示初始链表为空。 */
    head = insertAtTail(head, 10);     /* 链表变为 10。 */
    head = insertAtTail(head, 20);     /* 链表变为 10 -> 20。 */
    head = insertAtTail(head, 30);     /* 链表变为 10 -> 20 -> 30。 */
    head = insertAtHead(head, 5);      /* 新头为 5。 */

    /* 输出 5 -> 10 -> 20 -> 30 -> NULL。 */
    printf("头插后：");
    printList(head);

    head = deleteNode(head, 20); /* 删除中间节点时 head 不变。 */
    printf("删除20：");
    printList(head);

    head = deleteNode(head, 5); /* 删除头节点时必须接收新 head。 */
    printf("删除5：");
    printList(head);

    freeList(head); /* 逐个归还剩余节点占用的堆内存。 */
    head = NULL;    /* 清除调用者一侧已经失效的旧地址。 */
    /* 所有动态内存均已释放。 */
    return 0;
}
