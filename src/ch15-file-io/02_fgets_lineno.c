/**
 * @file    02_fgets_lineno.c
 * @chapter 第十五章 - 文件IO
 * @section 二.2.3 - 行读写：fgets / fputs 示例
 * @brief   演示用 fgets 逐行读取文件，并显示行号。
 *
 * 核心知识点：
 *   1. fgets(str, n, stream) —— 最多读 n-1 个字符，遇到 '\n' 或 EOF 停止
 *   2. fgets 会保留读到的换行符 '\n'（如果读到了），并在末尾自动加 '\0'
 *   3. fgets 返回 NULL 表示读到文件尾或出错
 *   4. fputs(str, stream) —— 写入字符串，不自动加换行符
 *   5. sizeof(line) 获取缓冲区大小，比硬编码数字更安全
 */

#include <stdio.h>

int main(void)
{
    /* 以只读模式打开文件 */
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("无法打开文件 data.txt\n");
        printf("请先创建 data.txt 文件再运行本程序。\n");
        return 1;
    }

    /* 缓冲区：用于存放每一行的内容
     * 大小 256 表示每行最多读 255 个字符（留 1 字节给 '\0'） */
    char line[256];
    int num = 1;  /* 行号计数器 */

    /*--------------------------------------------------------------------
     * 逐行读取并输出
     *
     * fgets(line, sizeof(line), fp)：
     *   - 从 fp 最多读 sizeof(line)-1 个字符到 line
     *   - 遇到 '\n' 会停止并保留 '\n' 在 line 中
     *   - 自动在末尾添加 '\0'
     *   - 返回 NULL 表示读到文件尾（或出错）
     *
     * printf 中的 %s 直接输出 line，因为 line 本身可能已包含换行符，
     * 所以 printf 不用额外加 \n
     *--------------------------------------------------------------------*/
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%d: %s", num, line);  /* line 本身已包含换行符 */
        num++;
    }

    fclose(fp);
    printf("\n共 %d 行\n", num - 1);

    return 0;
}
