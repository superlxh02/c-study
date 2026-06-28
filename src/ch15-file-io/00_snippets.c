/**
 * @file    00_snippets.c
 * @chapter 第十五章 - 文件IO
 * @section 一.3 ~ 三.3 - 文件操作片段集
 * @brief   演示：fopen/fclose 标准模式、fprintf 输出到 stderr、
 *          feof/ferror/clearerr 用法、fseek/rewind 基本用法。
 *
 * 本文件汇总了第十五章中分散在概念说明中的小代码片段。
 */

#include <stdio.h>

int main(void)
{
    /*====================================================================
     * 片段1：fopen / fclose 标准模式（第十五章 一.3.2）
     * 打开文件后必须检查返回值是否为 NULL；使用完后必须 fclose。
     * 这是文件操作的基本安全模板。
     *====================================================================*/
    printf("===== 片段1：fopen/fclose 标准模式 =====\n");
    {
        FILE *fp = fopen("data.txt", "r");
        if (fp == NULL)
        {
            printf("打开文件失败！(如果 data.txt 不存在则正常报错)\n");
            /* return 1; —— 实际出错时应退出 */
        }
        else
        {
            printf("文件打开成功！\n");
            /* ... 在这里进行读写操作 ... */
            fclose(fp);  /* 用完后必须关闭 */
            printf("文件已关闭。\n");
        }
    }
    printf("\n");

    /*====================================================================
     * 片段2：fprintf 输出到 stderr（第十五章 三.3）
     * stderr 是标准错误输出流，默认也输出到屏幕，
     * 但它独立于 stdout，不会被重定向影响（如 > file 只重定向 stdout）。
     * printf(...) 本质上就是 fprintf(stdout, ...)。
     *====================================================================*/
    printf("===== 片段2：fprintf(stderr, ...) =====\n");
    {
        fprintf(stderr, "[stderr] 这是一条错误信息 (通过 stderr 输出)\n");
        fprintf(stdout, "[stdout] 这是一条普通信息 (通过 stdout 输出)\n");
        printf("提示：printf(...) 等价于 fprintf(stdout, ...)\n");
    }
    printf("\n");

    /*====================================================================
     * 片段3：feof 的用法陷阱（第十五章 三.2.1）
     * feof() 只有在尝试读取失败后才返回真，不能用来提前判断。
     * 正确做法：用 while (fgets(...) != NULL)，而不是 while (!feof(fp))。
     *====================================================================*/
    printf("===== 片段3：正确的文件读取循环 =====\n");
    {
        FILE *fp = fopen("data.txt", "r");
        if (fp != NULL)
        {
            char line[256];
            /* 正确：用 fgets 的返回值判断 */
            int lineNum = 0;
            while (fgets(line, sizeof(line), fp) != NULL)
            {
                lineNum++;
            }
            printf("正确写法：while (fgets(...) != NULL) 读到 %d 行\n", lineNum);

            /* 错误写法示例（不要这样做）：
             * while (!feof(fp)) { fgets(...); ... }
             * 原因：feof 只在读取失败后才为真，会导致最后一行被处理两次
             */

            fclose(fp);
        }
        else
        {
            printf("data.txt 不存在，跳过此片段。\n");
        }
    }
    printf("\n");

    /*====================================================================
     * 片段4：fseek + ftell 组合（第十五章 三.1）
     * fseek 移动文件位置指示器，ftell 获取当前字节偏移。
     * rewind(fp) 等价于 fseek(fp, 0, SEEK_SET) —— 回到文件开头。
     *====================================================================*/
    printf("===== 片段4：fseek/ftell/rewind =====\n");
    {
        FILE *fp = fopen("data.txt", "rb");  /* 二进制模式更可靠 */
        if (fp != NULL)
        {
            /* 移动到文件末尾 */
            fseek(fp, 0, SEEK_END);
            long size = ftell(fp);  /* 获取当前偏移量 = 文件字节数 */
            printf("文件大小：%ld 字节\n", size);

            /* 回到文件开头 */
            rewind(fp);  /* 等价于 fseek(fp, 0, SEEK_SET) */

            fclose(fp);
        }
        else
        {
            printf("data.txt 不存在，跳过此片段。\n");
        }
    }

    return 0;
}
