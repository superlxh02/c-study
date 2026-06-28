/**
 * 第十八章“数组的增删改查”配套实现。
 * 安全接口使用 size_t 表示容量，并在修改数组前验证全部参数。
 */
#include "array_operations.h"

#include <limits.h> /* INT_MAX：保证 size_t 下标能安全转换为 int。 */

/* 线性查找从第一个元素开始逐个比较。 */
int linear_search(const int array[], size_t size, int target)
{
    /* 返回类型是 int，因此过大的下标无法表示；空数组地址也不可访问。 */
    if (array == NULL || size > (size_t)INT_MAX) return -1;

    /* i 每轮前进一步，最坏情况下需要检查全部 size 个元素。 */
    for (size_t i = 0; i < size; i++)
    {
        /* 第一次匹配时立即返回，因而重复值会返回最靠前的下标。 */
        if (array[i] == target) return (int)i;
    }
    /* 循环结束仍未命中，用 -1 表示“未找到”。 */
    return -1;
}

/* 二分查找使用左闭右开区间 [left, right)。 */
int binary_search(const int array[], size_t size, int target)
{
    /* 与线性查找保持一致：拒绝空指针和 int 无法表示的下标。 */
    if (array == NULL || size > (size_t)INT_MAX) return -1;

    /* left 指向候选区间首元素，初始为数组开头。 */
    size_t left = 0;
    /* right 指向候选区间后一位置，初始为 size。 */
    size_t right = size;
    /* 区间非空时继续折半。 */
    while (left < right)
    {
        /* 这种写法避免直接计算 left + right 可能产生的溢出。 */
        size_t middle = left + (right - left) / 2;
        /* 命中后把已验证范围内的下标转换成 int 返回。 */
        if (array[middle] == target) return (int)middle;
        /* 中间值较小时，目标只可能位于右半区。 */
        if (array[middle] < target) left = middle + 1;
        /* 中间值较大时，保留 middle 左侧的半区。 */
        else right = middle;
    }
    /* 候选区间缩为空，说明数组中没有目标值。 */
    return -1;
}

/* 安全插入接口同时接收物理容量和有效长度。 */
bool array_insert(int array[], size_t capacity, size_t *size,
                  size_t index, int value)
{
    /* 任一指针无效、数组已满或插入位置越界时都拒绝修改。 */
    if (array == NULL || size == NULL || *size >= capacity || index > *size)
        return false;

    /* 从后向前搬移，避免尚未复制的旧元素被提前覆盖。 */
    for (size_t i = *size; i > index; i--) array[i] = array[i - 1];
    /* 搬移完成后，index 位置已经空出，可以写入新值。 */
    array[index] = value;
    /* 有效元素数量随插入成功增加一。 */
    (*size)++;
    /* 返回 true 告诉调用者本次修改已经完成。 */
    return true;
}

/* 删除操作通过向前搬移后续元素来填补空位。 */
bool array_delete(int array[], size_t *size, size_t index)
{
    /* 空指针或 index 不在有效范围内时，数组保持不变。 */
    if (array == NULL || size == NULL || index >= *size) return false;

    /* 将 index 后面的元素依次向前移动一格。 */
    for (size_t i = index; i + 1 < *size; i++) array[i] = array[i + 1];
    /* 最后一个旧值无需清零；缩短有效长度即可视为已删除。 */
    (*size)--;
    /* 返回 true 表示删除成功。 */
    return true;
}

/* 教程命名包装器把非负 int 长度转换为安全接口使用的 size_t。 */
int linearSearch(int array[], int size, int target)
{
    /* 负长度没有意义，直接按未找到处理。 */
    if (size < 0) return -1;
    /* 实际查找逻辑复用经过参数检查的线性查找函数。 */
    return linear_search(array, (size_t)size, target);
}

/* 教程命名的二分查找包装器。 */
int binarySearch(int array[], int size, int target)
{
    /* 先排除无法转换成 size_t 的负长度。 */
    if (size < 0) return -1;
    /* 调用者仍需保证输入数组已经按升序排列。 */
    return binary_search(array, (size_t)size, target);
}

/* 该函数逐字对应正文基础版本，容量与下标前置条件由调用者保证。 */
void insertAt(int array[], int *size, int index, int value)
{
    /* 从当前尾部开始后移，为 index 位置腾出空间。 */
    for (int i = *size; i > index; i--) array[i] = array[i - 1];
    /* 把新元素写入空出的位置。 */
    array[index] = value;
    /* 同步更新调用者持有的有效长度。 */
    (*size)++;
}

/* 该函数逐字对应正文基础删除版本。 */
void deleteAt(int array[], int *size, int index)
{
    /* 从 index 开始，用后一个元素覆盖前一个元素。 */
    for (int i = index; i < *size - 1; i++) array[i] = array[i + 1];
    /* 缩短有效长度；数组末尾残留值不再属于有效数据。 */
    (*size)--;
}
