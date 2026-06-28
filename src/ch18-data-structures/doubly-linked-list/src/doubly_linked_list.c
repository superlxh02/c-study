/**
 * @file    doubly_linked_list.c
 * @chapter 第十八章 - 数据存储结构
 * @brief   双向链表接口实现，重点维护 prev/next 的对称关系。
 */
#include "doubly_linked_list.h"

#include <stdio.h>  /* fprintf、printf：错误信息与遍历输出。 */
#include <stdlib.h> /* malloc、free、exit：节点生命周期管理。 */

/* 创建一个尚未连接前驱和后继的孤立节点。 */
static DListNode *dlist_create_node(int value)
{
    /* 按指针目标类型计算尺寸，避免重复书写结构体类型。 */
    DListNode *node = malloc(sizeof *node);
    /* 只有分配成功时才能初始化节点成员。 */
    if (node != NULL)
    {
        node->data = value; /* 保存节点数据。 */
        node->prev = NULL;  /* 尚未接入链表，所以没有前驱。 */
        node->next = NULL;  /* 尚未接入链表，所以没有后继。 */
    }
    /* 失败返回 NULL，由调用层决定恢复还是退出。 */
    return node;
}

/* 头插会改变调用者持有的 head，因此使用二级指针。 */
bool dlist_push_front(DListNode **head, int value)
{
    /* head 本身无效时无法更新链表入口。 */
    if (head == NULL) return false;
    /* 先分配节点；失败时原链表完全不变。 */
    DListNode *node = dlist_create_node(value);
    if (node == NULL) return false;

    node->next = *head; /* 新节点向后连接原头节点。 */
    if (*head != NULL) (*head)->prev = node; /* 原头向前连接新节点。 */
    *head = node; /* 更新调用者的链表入口。 */
    return true;  /* 双向链接维护完成。 */
}

/* 未维护尾指针的版本需要先遍历到链表末端。 */
bool dlist_push_back(DListNode **head, int value)
{
    /* 无可写 head 时不能插入。 */
    if (head == NULL) return false;
    /* 创建的新节点已经把 prev、next 初始化为 NULL。 */
    DListNode *node = dlist_create_node(value);
    if (node == NULL) return false;

    if (*head == NULL)
    {
        *head = node;
        return true;
    }

    DListNode *tail = *head; /* 从头节点开始寻找旧尾。 */
    while (tail->next != NULL) tail = tail->next; /* 沿 next 前进。 */
    tail->next = node; /* 旧尾的后继改为新节点。 */
    node->prev = tail; /* 双链表接边时，两个方向都必须更新。 */
    return true;       /* 头指针没有变化。 */
}

/* 删除第一个数据匹配的节点。 */
bool dlist_remove_first(DListNode **head, int value)
{
    /* 无头指针位置时没有可操作的链表。 */
    if (head == NULL) return false;

    DListNode *target = *head; /* 从头节点开始查找。 */
    /* 未命中时沿 next 移动，直至找到目标或到达末端。 */
    while (target != NULL && target->data != value) target = target->next;
    /* target 为 NULL 表示链表中不存在该值。 */
    if (target == NULL) return false;

    /* 非头节点由前驱直接绕过 target。 */
    if (target->prev != NULL) target->prev->next = target->next;
    else *head = target->next; /* 没有前驱，说明删除的是头节点。 */

    /* 非尾节点的后继也必须反向绕过 target。 */
    if (target->next != NULL) target->next->prev = target->prev;
    free(target); /* 两侧链接均修复后，才可释放目标节点。 */
    return true;  /* 第一个匹配节点删除成功。 */
}

/* 正向遍历只读取节点，不修改任何链接。 */
void dlist_print_forward(const DListNode *head)
{
    /* node 沿 next 从头走到尾。 */
    for (const DListNode *node = head; node != NULL; node = node->next)
        printf("%d <-> ", node->data);
    printf("NULL\n"); /* NULL 标识非循环链表的末端。 */
}

/* 反向遍历需要先找到尾节点，再沿 prev 返回。 */
void dlist_print_backward(const DListNode *head)
{
    /* 空链表没有尾节点，直接输出结束标志。 */
    if (head == NULL) { printf("NULL\n"); return; }

    const DListNode *tail = head; /* 从头开始定位尾节点。 */
    while (tail->next != NULL) tail = tail->next; /* 最终停在 next 为 NULL 处。 */
    /* 从尾到头沿 prev 逐个打印。 */
    for (const DListNode *node = tail; node != NULL; node = node->prev)
        printf("%d <-> ", node->data);
    printf("NULL\n"); /* 越过头节点后 prev 为 NULL。 */
}

/* 清理时只需沿 next 前进；prev 不参与节点回收。 */
void dlist_clear(DListNode **head)
{
    /* NULL 二级指针没有可修改的链表入口。 */
    if (head == NULL) return;
    /* 每轮删除当前头节点，直到链表为空。 */
    while (*head != NULL)
    {
        DListNode *next = (*head)->next; /* 释放前保存后继地址。 */
        free(*head);                     /* 当前节点不再访问。 */
        *head = next;                    /* 推进到下一节点。 */
    }
}

/* 正文版创建函数在内存不足时打印错误并终止演示程序。 */
DNode *createDNode(int data)
{
    DNode *node = dlist_create_node(data);
    if (node == NULL)
    {
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    return node; /* 返回已经完整初始化的非 NULL 节点。 */
}

/* 正文版头插返回新的头节点。 */
DNode *insertAtHead(DNode *head, int data)
{
    DNode *node = createDNode(data); /* 创建新节点。 */
    node->next = head;               /* 新节点后接原头。 */
    if (head != NULL) head->prev = node; /* 原头前接新节点。 */
    return node;                     /* 新节点成为新头。 */
}

/* 正文版尾插返回原头指针。 */
DNode *insertAtTail(DNode *head, int data)
{
    DNode *node = createDNode(data); /* 新节点的两个链接初始为 NULL。 */
    if (head == NULL) return node;   /* 空链表中新节点也是头节点。 */
    DNode *tail = head;              /* 从头寻找旧尾节点。 */
    while (tail->next != NULL) tail = tail->next; /* 顺着 next 前进。 */
    tail->next = node;               /* 建立正向链接。 */
    node->prev = tail;               /* 建立反向链接。 */
    return head;                     /* 原链表头保持不变。 */
}

/* 删除包装器返回可能改变的新头指针。 */
DNode *deleteNode(DNode *head, int data)
{
    DNode *target = head; /* 从头节点开始寻找第一个匹配值。 */
    while (target != NULL && target->data != data) target = target->next;
    if (target == NULL) return head; /* 未找到时链表保持不变。 */

    if (target == head)
    {
        head = target->next;              /* 先保存新的头节点。 */
        if (head != NULL) head->prev = NULL; /* 新头不再有前驱。 */
    }
    else
    {
        target->prev->next = target->next; /* 前驱跳过目标节点。 */
        if (target->next != NULL)
            target->next->prev = target->prev; /* 后继反向跳过目标。 */
    }

    free(target); /* 链接修复完成后再释放目标节点。 */
    return head;  /* 返回仍然有效、但可能已经改变的头指针。 */
}

void printForward(DNode *head)
{
    /* 复用实现层只读正向遍历。 */
    dlist_print_forward(head);
}

void printBackward(DNode *head)
{
    /* 复用实现层只读反向遍历。 */
    dlist_print_backward(head);
}

void freeDList(DNode *head)
{
    /* 局部 head 会被清零；调用者释放后还应自行把原指针置 NULL。 */
    dlist_clear(&head);
}
