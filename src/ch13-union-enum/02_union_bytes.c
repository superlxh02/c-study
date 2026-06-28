/**
 * @file    02_union_bytes.c
 * @chapter 第十三章 - 共用体与枚举
 * @section 一.1.5 - 共用体常见用途：IntBytes 字节布局
 * @brief   演示利用共用体查看整数在内存中的字节排列（小端序/大端序）。
 *
 * 核心知识点：
 *   1. union 可以把同一块内存用不同的类型来解释
 *   2. bytes 的长度使用 sizeof(int)，不假定 int 必须是 4 字节
 *   3. 给 value 赋值后，通过 bytes 数组可以看到每个字节的值
 *   4. 可以借此判断当前系统是小端序 (little-endian) 还是大端序 (big-endian)
 *
 * 小端序 (x86/ARM 大多数情况)：低位字节在低地址
 *   例如 0x12345678 在内存中为：78 56 34 12
 * 大端序 (网络字节序)：高位字节在低地址
 *   例如 0x12345678 在内存中为：12 34 56 78
 */

#include <stdio.h>

/* 共用体 IntBytes：int 和等长的 unsigned char 数组共享空间
 * 这样就可以按字节查看整数的内存布局 */
union IntBytes
{
    int value;                  /* 整数值（通常 4 字节） */
    unsigned char bytes[sizeof(int)]; /* 覆盖 int 对象的全部字节 */
};

int main(void)
{
    union IntBytes ib;

    /* 将一个十六进制整数存入 value
     * 0x12345678 是一个 4 字节的数
     * 每个十六进制位代表 4 位二进制，两位十六进制 = 1 字节 */
    ib.value = 0x12345678;   /* 一个十六进制整数 */

    printf("===== IntBytes 字节布局演示 =====\n\n");

    /* 输出整数值 */
    printf("ib.value = 0x%X\n\n", ib.value);

    /* 按字节输出，观察当前实现中的实际排列顺序。 */
    printf("按字节查看内存布局：\n");
    for (size_t i = 0; i < sizeof ib.bytes; i++)
    {
        printf("  bytes[%zu] = 0x%02X%s\n", i, ib.bytes[i],
               i == 0 ? "  (最低地址)" : "");
    }

    /* 判断字节序 */
    printf("\n字节序判断：\n");
    if (ib.bytes[0] == 0x78)
    {
        printf("  当前系统为小端序 (Little-Endian)\n");
        printf("  低字节 0x78 存储在低地址 bytes[0]\n");
    }
    else if (ib.bytes[0] == 0x12)
    {
        printf("  当前系统为大端序 (Big-Endian)\n");
        printf("  高字节 0x12 存储在低地址 bytes[0]\n");
    }

    printf("\n说明：union 本身不记录当前存的是哪个成员，\n");
    printf("需要程序员自己记住或配合枚举使用（带标签的联合体）。\n");

    return 0;
}
