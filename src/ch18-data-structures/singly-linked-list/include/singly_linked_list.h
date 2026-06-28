/* 头文件保护宏避免节点定义和接口重复出现。 */
#ifndef C_STUDY_SINGLY_LINKED_LIST_H
#define C_STUDY_SINGLY_LINKED_LIST_H

#include <stdbool.h> /* bool：报告插入和删除是否成功。 */

/*
 * 单链表节点：data 保存数据，next 指向下一个节点。
 * 头指针为 NULL 表示空链表，尾节点的 next 为 NULL。
 */
typedef struct SListNode
{
    int data;                  /* 当前节点保存的整数。 */
    struct SListNode *next;    /* 后继节点地址。 */
} SListNode;

/* 教程正文使用更短的 Node 名称；二者是同一个类型。 */
typedef SListNode Node;

/* 插入成功返回 true；内存分配失败返回 false，原链表保持不变。 */
bool slist_push_front(SListNode **head, int value);
bool slist_push_back(SListNode **head, int value);

/* 删除第一个等于 value 的节点；没有找到时返回 false。 */
bool slist_remove_first(SListNode **head, int value);

/* 只读遍历不会修改节点，因此参数使用 const。 */
void slist_print(const SListNode *head);

/* 释放所有节点，并把调用者持有的头指针重置为 NULL。 */
void slist_clear(SListNode **head);

/* 与第十八章正文逐段示例一致的接口。 */
Node *createNode(int data);
Node *insertAtHead(Node *head, int data);
Node *insertAtTail(Node *head, int data);
Node *deleteNode(Node *head, int data);
void printList(Node *head);
void freeList(Node *head);

#endif /* C_STUDY_SINGLY_LINKED_LIST_H */
