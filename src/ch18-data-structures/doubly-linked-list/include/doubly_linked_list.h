/* 头文件保护宏避免节点类型和接口重复声明。 */
#ifndef C_STUDY_DOUBLY_LINKED_LIST_H
#define C_STUDY_DOUBLY_LINKED_LIST_H

#include <stdbool.h> /* bool：报告插入、删除操作是否成功。 */

/* 双链表节点同时记录前驱和后继，因此可以双向遍历。 */
typedef struct DListNode
{
    int data;                  /* 当前节点保存的整数。 */
    struct DListNode *prev;    /* 前驱节点；头节点的 prev 为 NULL。 */
    struct DListNode *next;    /* 后继节点；尾节点的 next 为 NULL。 */
} DListNode;

/* DNode 是教程正文使用的简短类型名称。 */
typedef DListNode DNode;

/* 在头部插入节点，并通过二级指针更新调用者的 head。 */
bool dlist_push_front(DListNode **head, int value);
/* 在尾部插入节点；当前实现需要先遍历到尾部。 */
bool dlist_push_back(DListNode **head, int value);
/* 删除第一个等于 value 的节点。 */
bool dlist_remove_first(DListNode **head, int value);
/* 沿 next 指针从头到尾打印。 */
void dlist_print_forward(const DListNode *head);
/* 先定位尾节点，再沿 prev 指针反向打印。 */
void dlist_print_backward(const DListNode *head);
/* 释放所有节点，并把调用者的 head 重置为 NULL。 */
void dlist_clear(DListNode **head);

/* 与教程正文一致的接口名称。 */
DNode *createDNode(int data);
DNode *insertAtHead(DNode *head, int data);
DNode *insertAtTail(DNode *head, int data);
DNode *deleteNode(DNode *head, int data);
void printForward(DNode *head);
void printBackward(DNode *head);
void freeDList(DNode *head);

#endif /* C_STUDY_DOUBLY_LINKED_LIST_H */
