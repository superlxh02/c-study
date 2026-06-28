/**
 * @file    strtools.h
 * @chapter 第十七章 - C语言统一项目构建系统——CMake初识
 * @section 三、进阶与总结 → 3. 动手练习
 * @brief   字符串工具模块的头文件
 *
 * 声明 my_strlen() 函数，用于计算字符串的长度。
 * 使用 #pragma once 防止重复包含。
 */

#pragma once                    /* 编译指令：本文件在一个编译单元中只包含一次 */

/** 计算以 '\0' 结尾的字符串的长度（模仿标准库的 strlen） */
int my_strlen(const char *str);
