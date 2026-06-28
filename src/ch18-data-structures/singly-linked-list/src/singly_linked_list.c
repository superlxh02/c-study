/**
 * @file    singly_linked_list.c
 * @chapter 第十八章 - 数据存储结构
 * @brief   单链表接口的实现。
 */
#include "singly_linked_list.h"

#include <stdio.h>  /* fprintf、printf：错误信息和遍历输出。 */
#include <stdlib.h> /* malloc、free、exit：节点生命周期管理。 */

/* 创建一个尚未接入链表的新节点。 */
static SListNode *slist_create_node(int value)
{
    /* sizeof *node 自动跟随指针目标类型，避免类型修改后尺寸不同步。 */
    SListNode *node = malloc(sizeof *node);
    /* 只有分配成功才能写入新节点成员。 */
    if (node != NULL)
    {
        node->data = value; /* 保存调用者提供的数据。 */
        node->next = NULL;  /* 尚未接入链表，所以暂时没有后继。 */
    }
    /* 成功时返回新节点，失败时把 NULL 交给上层处理。 */
    return node;
}

/* 头插需要修改调用者的头指针，因此参数类型是二级指针。 */
bool slist_push_front(SListNode **head, int value)
{
    /* 没有可写的头指针位置时无法更新链表入口。 */
    if (head == NULL) return false;

    /* 先创建孤立节点，失败时原链表保持不变。 */
    SListNode *node = slist_create_node(value);
    if (node == NULL) return false;

    node->next = *head; /* 新节点先接住原头节点，避免丢失原链表。 */
    *head = node;       /* 再更新调用者持有的头指针。 */
    return true;        /* 两个指针更新完成，插入成功。 */
}

/* 尾插在不维护尾指针时需要从头遍历到最后一个节点。 */
bool slist_push_back(SListNode **head, int value)
{
    /* 二级指针本身必须有效。 */
    if (head == NULL) return false;

    /* 先分配节点，避免遍历后才发现内存不足。 */
    SListNode *node = slist_create_node(value);
    if (node == NULL) return false;

    if (*head == NULL)
    {
        *head = node; /* 空链表中，新节点同时是头节点和尾节点。 */
        return true;
    }

    SListNode *tail = *head; /* 行走指针从头节点出发。 */
    while (tail->next != NULL) tail = tail->next; /* 停在旧尾节点。 */
    tail->next = node; /* 旧尾节点接上新节点。 */
    return true;       /* 头指针没有改变。 */
}

/* 删除第一个值匹配的节点，而不是删除所有重复值。 */
bool slist_remove_first(SListNode **head, int value)
{
    /* 无头指针位置或空链表都没有节点可删。 */
    if (head == NULL || *head == NULL) return false;

    /* 头节点单独处理，因为删除后必须更新链表入口。 */
    if ((*head)->data == value)
    {
        SListNode *old_head = *head; /* 保存即将释放的旧头地址。 */
        *head = old_head->next;      /* 后继节点成为新头节点。 */
        free(old_head);              /* 链表已绕过旧头，现在可安全释放。 */
        return true;                 /* 删除完成。 */
    }

    /* previous 始终指向“候选目标”的前一个节点。 */
    SListNode *previous = *head;
    while (previous->next != NULL && previous->next->data != value)
    {
        previous = previous->next;
    }
    /* 到达尾部仍未命中，说明链表中不存在该值。 */
    if (previous->next == NULL) return false;

    SListNode *target = previous->next; /* 保存目标节点，供稍后释放。 */
    previous->next = target->next; /* 绕过目标节点后才能释放它。 */
    free(target);                   /* 目标已脱链，不再有有效访问。 */
    return true;                    /* 删除第一个匹配节点成功。 */
}

/* 只读遍历不会修改节点或链接。 */
void slist_print(const SListNode *head)
{
    /* node 每轮沿 next 前进一步，直到越过尾节点。 */
    for (const SListNode *node = head; node != NULL; node = node->next)
    {
        printf("%d -> ", node->data);
    }
    printf("NULL\n"); /* 用 NULL 明确展示非循环链表的末端。 */
}

/* clear 必须在释放每个节点前保存其后继地址。 */
void slist_clear(SListNode **head)
{
    /* NULL 二级指针没有可清理的链表入口。 */
    if (head == NULL) return;

    while (*head != NULL)
    {
        SListNode *next = (*head)->next; /* free 前先保存后继地址。 */
        free(*head); /* 释放当前头节点后不能再访问其成员。 */
        *head = next; /* 使用预先保存的地址推进到下一节点。 */
    }
}

/* 以下包装接口保留正文中的“返回新头指针”写法。 */
Node *createNode(int data)
{
    /* 正文版接口把分配失败视为无法恢复的演示程序错误。 */
    Node *node = slist_create_node(data);
    if (node == NULL)
    {
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    return node; /* 非 NULL 的完整初始化节点。 */
}

/* 正文版头插直接返回新的头节点。 */
Node *insertAtHead(Node *head, int data)
{
    Node *node = createNode(data); /* 分配并初始化新节点。 */
    node->next = head;             /* 接住原链表。 */
    return node;                   /* 调用者必须保存这个新头。 */
}

/* 正文版尾插返回未改变的头指针。 */
Node *insertAtTail(Node *head, int data)
{
    Node *node = createNode(data); /* 新节点的 next 已是 NULL。 */
    if (head == NULL) return node; /* 空链表中新节点就是头节点。 */
    Node *tail = head;             /* 从头开始寻找旧尾节点。 */
    while (tail->next != NULL) tail = tail->next; /* 顺着 next 前进。 */
    tail->next = node;             /* 将新节点追加到旧尾之后。 */
    return head;                   /* 非空链表的头节点没有变化。 */
}

/* 正文版删除通过局部 head 接收可能变化的新头。 */
Node *deleteNode(Node *head, int data)
{
    /* 是否找到不影响返回规则，因此显式忽略布尔结果。 */
    (void)slist_remove_first(&head, data);
    return head; /* 调用者用返回值更新自己的头指针。 */
}

void printList(Node *head)
{
    /* 复用 const 安全的实现层遍历函数。 */
    slist_print(head);
}

void freeList(Node *head)
{
    /* 传入局部副本的地址即可逐节点释放；调用者随后应自行置 NULL。 */
    slist_clear(&head);
}
