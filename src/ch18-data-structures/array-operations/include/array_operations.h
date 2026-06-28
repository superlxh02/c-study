/* 头文件保护宏避免同一声明被重复包含。 */
#ifndef C_STUDY_ARRAY_OPERATIONS_H
#define C_STUDY_ARRAY_OPERATIONS_H

#include <stdbool.h> /* bool：表示插入、删除是否成功。 */
#include <stddef.h>  /* size_t：表示容量、长度和下标。 */

/* 在无序数组中顺序查找；找到返回下标，失败返回 -1。 */
int linear_search(const int array[], size_t size, int target);
/* 在升序数组中二分查找；找到返回下标，失败返回 -1。 */
int binary_search(const int array[], size_t size, int target);
/* 在指定位置插入元素；函数会检查空指针、容量和下标。 */
bool array_insert(int array[], size_t capacity, size_t *size,
                  size_t index, int value);
/* 删除指定位置的元素，并通过 size 更新有效元素个数。 */
bool array_delete(int array[], size_t *size, size_t index);

/* 以下接口保留教程正文的命名，便于逐段对照。 */
/* 参数 size 必须非负，array 必须指向至少 size 个 int。 */
int linearSearch(int array[], int size, int target);
/* 参数约束同上，并且 array[0..size) 必须按升序排列。 */
int binarySearch(int array[], int size, int target);
/* 调用者必须保证 array 仍有空位，且 index 位于 [0, *size]。 */
void insertAt(int array[], int *size, int index, int value);
/* 调用者必须保证 index 位于 [0, *size)，且两个指针有效。 */
void deleteAt(int array[], int *size, int index);

#endif /* C_STUDY_ARRAY_OPERATIONS_H */
