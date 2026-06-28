/* 引入数组查找、插入和删除接口。 */
#include "array_operations.h"

#include <stdio.h> /* printf：输出演示结果。 */

/* 只读打印数组当前的有效区间。 */
static void print_array(const int array[], size_t size)
{
    /* 每轮按下标输出一个有效元素。 */
    for (size_t i = 0; i < size; i++) printf("%d ", array[i]);
    /* 一组数组内容输出完毕后换行。 */
    printf("\n");
}

/* 程序入口依次演示插入、线性查找、删除和二分查找。 */
int main(void)
{
    /* 物理容量为 100，目前只有前 5 个位置存放有效数据。 */
    int array[100] = {10, 20, 30, 40, 50};
    size_t size = 5; /* size 只记录有效元素数量，不等同于物理容量。 */

    /* 先打印插入前的初始数组。 */
    printf("插入前：");
    print_array(array, size);
    /* 在下标 2 插入 99，并检查操作是否成功。 */
    if (!array_insert(array, 100, &size, 2, 99)) return 1;
    /* 打印插入后的有效区间。 */
    printf("插入后：");
    print_array(array, size);

    /* 插入后数组不再有序，所以先用线性查找定位 40。 */
    printf("线性查找 40：下标 %d\n", linear_search(array, size, 40));
    /* 删除刚插入的 99，使数组重新恢复升序。 */
    if (!array_delete(array, &size, 2)) return 1;
    /* 打印删除后的数组内容。 */
    printf("删除 99 后：");
    print_array(array, size);
    /* 恢复升序后，二分查找可以正确定位 40。 */
    printf("二分查找 40：下标 %d\n", binary_search(array, size, 40));
    /* 所有演示均成功完成，以 0 表示正常退出。 */
    return 0;
}
